#include <string.h>
#include <iostream>
#include "collection.hpp"
#include "simple-db.hpp"

using namespace anki_lite;
using namespace std;

void simple_db_automatic_tests()
{
    // hton64 & ntoh64
    uint64_t uint;
    uint = SimpleDb::hton64(5);
    if (uint != 0x500000000000000) {
        cout << "SimpleDb::hton64() error" << endl;
    }

    // SimpleDb::prepare_record
    char buffer[SimpleDb::m_record_size] = { 0 };
    char buffer_ok[SimpleDb::m_record_size] = {
        0,
        0, 0, 0, 0, 0, 0, 0, 5,
        'f', 'r', 'o', 'n', 't', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0,
        0, 0, 0, 0, 0, 0, 0, 10 };
    SimpleDb::prepare_record(SimpleDb::k_cards_table, 5, "front",
                             SimpleDb::k_field_int, 10, buffer);
    if (memcmp(buffer, buffer_ok, SimpleDb::m_record_size) != 0) {
        cout << "SimpleDb::prepare_record error" << endl;
        for (unsigned int i = 0; i < SimpleDb::m_record_size; i++) {
            cout<<hex<<(unsigned)buffer[i]<<" ";
        }
        cout << dec << endl;
    }
}


void simple_db_write_and_read()
{
    anki_lite::Collection col;
    TextMapT deck_details;
    deck_details["name"] = "deck1";
    Deck deck(1, deck_details);
    boost::shared_ptr<ICard> card(new Card(1, "front1", "back1"));
    card->set_deck_id(1);
    deck.add_card(card);
    card.reset(new Card(2, "front2", "back2"));
    card->set_deck_id(1);
    deck.add_card(card);
    col.add_deck(deck);
    cout << col.to_string() << endl;

    SimpleDb db("test-db.bin");
    db.open_storage();
    db.write_collection(col);
    db.close_storage();

    anki_lite::Collection col2;
    db.open_storage();
    db.get_collection(col2);
    db.close_storage();
    cout <<  col.to_string() <<endl;
}


int main(int, char**)
{
    simple_db_automatic_tests();
    simple_db_write_and_read();

    Card card(5, "front", "back");
    SimpleDb db("simple-db.bin");
    db.open_storage();
    db.write_card(card);
    db.close_storage();
}
