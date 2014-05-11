#include <string.h>
#include <stdint.h>
#include "collection.hpp"
#include "simple-db.hpp"
#include "exceptions.hpp"

#include <iostream> // :debug:

using namespace std;
using boost::shared_ptr;

namespace anki_lite {

SimpleDb::SimpleDb(const string &filename)
  : m_init(false), m_filename(filename), m_records_loaded(false)
{
    for (int i = 0; i < k_max_table; i++) {
        map<uint64_t, map<string, Record> > empty_records_map;
        m_records.push_back(empty_records_map);
    }
}


void SimpleDb::open_storage()
{
    m_records_stream.open(m_filename.c_str(),
                          fstream::in | fstream::out | fstream::binary | fstream::app);
    if (!m_records_stream) {
        throw IoExcp(string("Cannot open file " + m_filename));
    }
    m_strings_stream.open((m_filename + ".str").c_str(),
                          fstream::in | fstream::out | fstream::binary | fstream::app);
    if (!m_strings_stream) {
        throw IoExcp(string("Cannot open file " + m_filename));
    }
    m_init = true;
}


void SimpleDb::close_storage()
{
    if (m_init) {
        m_strings_stream.close();
        m_records_stream.close();
        m_init = false;
    }
}


void SimpleDb::get_collection(Collection &collection)
{
    // :todo - read config

    // get decks
    vector<Deck> decks;
    get_decks(decks);
    for (unsigned i = 0; i < decks.size(); i++) {
        collection.add_deck(decks[i]);
    }
}


void SimpleDb::get_decks(vector<Deck> &decks)
{
    TableMap::iterator it;
    TableMap &decks_table = m_records[k_decks_table];
    for (it = decks_table.begin(); it != decks_table.end(); ++it) {
        uint64_t deck_id = it->first;
        if (!(it->second)["name"].str_value.empty()) {
            map<string, string> deck_details;
            deck_details["name"] = (it->second)["name"].str_value;
            Deck deck(deck_id, deck_details);
            get_cards_for_deck(deck);
            decks.push_back(deck);
        }
    }
}


void SimpleDb::get_cards_for_deck(Deck &deck)
{
    TableMap::iterator it;
    TableMap &cards_table = m_records[k_cards_table];
    for (it = cards_table.begin(); it != cards_table.end(); ++it) {
        uint64_t card_id = it->first;
        Id deck_id = cards_table[card_id]["deck_id"].value;
        if (deck.id() == deck_id) {
            string front_text = cards_table[card_id]["front_text"].str_value;
            string back_text = cards_table[card_id]["back_text"].str_value;
            boost::shared_ptr<ICard> card(new Card(card_id, front_text, back_text));
            card->set_deck_id(deck_id);
            deck.add_card(card);
        }
    }
}


boost::shared_ptr<ICard> SimpleDb::read_card(Id card_id)
{
    Id deck_id = record_get_int_value(k_cards_table, card_id, "deck_id");
    string front_text = record_get_str_value(k_cards_table, card_id, "front_text");
    string back_text = record_get_str_value(k_cards_table, card_id, "back_text");
    boost::shared_ptr<ICard> card(new Card(card_id, front_text, back_text));
    card->set_deck_id(deck_id);
    return card;
}


char* SimpleDb::prepare_record(
  Table table, Id id, const string &field, FieldType field_type,
  int64_t field_value, char buffer[m_record_size])
{
    char *pos = buffer;
    if (field.size() + 1 > m_field_size) {
        throw InternalError("Field name too big");
    }
    *pos++ = table;
    uint64_t value = hton64((uint64_t)id);
    *(uint64_t*)pos = value;
    pos += sizeof(value);
    ::memcpy(pos, field.c_str(), field.size() + 1);
    pos += m_field_size;
    *pos++ = field_type;
    value = hton64((uint64_t)field_type);
    *(uint64_t*)pos = field_type;
    value = hton64((uint64_t)field_value);
    *(uint64_t*)pos = value;
    return buffer;
}


void SimpleDb::write_record(Table table, Id id, const string &field, int64_t field_value)
{
    char buffer[m_record_size] = { 0 };
    prepare_record(table, id, field, k_field_int, field_value, buffer);
    m_records_stream.seekp(0, ios_base::end);
    m_records_stream.write(buffer, sizeof (buffer));
    if (!m_records_stream.good()) {
        throw IoExcp("Error writing to records file");
    }
}


void SimpleDb::write_record(Table table, Id id, const string &field, const string &str)
{
    // first write string to string stream
    m_strings_stream.seekp(0, ios_base::end);
    int64_t cur_offset = m_strings_stream.tellp();
    //cout<<"offset: "<<cur_offset<<endl; // :debug:
    m_strings_stream.write(str.c_str(), str.size() + 1);
    if (!m_strings_stream.good()) {
        throw IoExcp("Error writing to strings file");
    }
    write_record(table, id, field, cur_offset);
}


uint64_t SimpleDb::ntoh64(uint64_t input)
{
    uint64_t rval;
    uint8_t *data = (uint8_t *)&rval;

    data[0] = input >> 56;
    data[1] = input >> 48;
    data[2] = input >> 40;
    data[3] = input >> 32;
    data[4] = input >> 24;
    data[5] = input >> 16;
    data[6] = input >> 8;
    data[7] = input >> 0;

    return rval;
}


uint64_t SimpleDb::hton64(uint64_t input)
{
    return (ntoh64(input));
}


void SimpleDb::write_collection(const Collection &collection)
{
    // :todo: - write conf

    // write decks
    for (unsigned i = 0; i < collection.get_no_of_decks(); i++) {
        write_deck(collection.get_deck_by_idx(i));
    }
}


void SimpleDb::write_deck(const Deck &deck)
{
    write_record(k_decks_table, deck.id(), "name", deck.name());
}


void SimpleDb::write_cards_for_deck(const Deck &deck)
{
    unsigned cards = deck.get_no_of_cards();
    for (unsigned i = 0; i < cards; i++) {
        write_card(*deck.get_card(i));
    }
}


void SimpleDb::write_card(const ICard &card)
{
    write_record(k_cards_table, card.id(), "deck_id", card.deck_id());
    write_record(k_cards_table, card.id(), "front_text", card.front_text());
    write_record(k_cards_table, card.id(), "back_text", card.back_text());
}


void SimpleDb::read_all_records()
{
    Record record;
    char buffer[m_record_size];
    char *ptr = buffer;
    char str_buffer[128];
    m_records_stream.seekg(0);
    while (m_records_stream.good()) {
        m_records_stream.read(buffer, m_record_size);
        if (!m_records_stream.good()) {
            break;
        }
        record.table = static_cast<Table>(*ptr++);
        record.id = ntoh64(*(uint64_t*)ptr);
        ptr += sizeof (uint64_t);
        record.field = ptr;
        ptr += m_field_size;
        record.field_type = static_cast<FieldType>(*ptr++);
        record.value = ntoh64(*(uint64_t*)ptr);
        if (record.field_type == k_field_string) {
            m_strings_stream.seekg(record.value);
            m_strings_stream.getline(str_buffer, sizeof(str_buffer), 0);
            if (!m_strings_stream.good()) {
                throw IoExcp("Error reading from strings file");
            }
            record.str_value = str_buffer;
        }
        m_records[record.table][record.id][record.field] = record;
    }
    if (m_records_stream.eof()) {
        if (m_records_stream.gcount() != 0) {
            throw IoExcp("Incomplete record in db file");
        }
    } else {
        throw IoExcp("Error reading from db file");
    }
    m_records_loaded = true;
}


uint64_t SimpleDb::record_get_int_value(Table table, Id id, const std::string &field)
{
    if (m_records[table].count(id) == 1) {
        if (m_records[table][id].count(field) == 1) {
            if (m_records[table][id][field].field_type == k_field_int) {
                return m_records[table][id][field].value;
            }
        }
    }
    throw DbExcp("Needed value not found in DB");
}


std::string SimpleDb::record_get_str_value(Table table, Id id, const std::string &field)
{
    if (m_records[table].count(id) == 1) {
        if (m_records[table][id].count(field) == 1) {
            if (m_records[table][id][field].field_type == k_field_string) {
                return m_records[table][id][field].str_value;
            }
        }
    }
    throw DbExcp("Needed value not found in DB");
}

} // namespace anki_lite
