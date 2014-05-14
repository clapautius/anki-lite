#ifndef ANKI_LITE_SIMPLE_DB_HPP_
#define ANKI_LITE_SIMPLE_DB_HPP_
/**
 * Simple Db
 * ---------
 * There are two files, one containing fixed-size records and another one containing
 * variable data (strings).
 *
 * Ints are stored in network byte order.
 */

#include <stdint.h>
#include <string>
#include <fstream>
#include "anki-storage.hpp"
#include "anki-types.hpp"
#include "card.hpp"
#include "deck.hpp"


void simple_db_automatic_tests(); // :tmp:

namespace anki_lite
{

class SimpleDb : public AnkiStorage
{
public:

    SimpleDb(const std::string &filename);

    virtual ~SimpleDb() {};

    /**
     * @throw DbExcp in case of error.
     */
    virtual void open_storage();

    /**
     * @throw DbExcp in case of error.
     */
    virtual void close_storage();

    virtual void get_collection(Collection&);

    virtual void write_collection(const Collection &collection);

protected:

    /**
     * Read deck data and creates the Deck objects. The decks will have all the config
     * params but no cards in them. Use get_cards_for_deck to add cards.
     *
     * @throw DbExcp in case of error.
     */
    virtual void get_decks(std::vector<Deck> &decks);

    /**
     * @throw DbExcp in case of error.
     */
    virtual void get_cards_for_deck(Deck&);

    /**
     * @throw DbExcp in case of error.
     */
    virtual void write_deck(const Deck &decks);

    /**
     * @throw DbExcp in case of error.
     */
    virtual void write_cards_for_deck(const Deck &deck);

private:

    enum FieldType
    {
        k_field_int,
        k_field_string
    };

    enum Table
    {
        k_cards_table,
        k_decks_table,
        k_collection_table,
        k_max_table
    };

    struct Record
    {
        Table table;
        uint64_t id;
        std::string field;
        FieldType field_type;
        uint64_t value;
        std::string str_value;
    };

    static const unsigned int m_field_size = 14;

    // table id + id + field name + field type + field value
    static const unsigned int m_record_size = 1 + 8 + m_field_size + 1 + 8;

    /**
     * Network to host for 64 bits values.
     */
    static uint64_t ntoh64(uint64_t input);

    /**
     * Host to network for 64 bits values.
     */
    static uint64_t hton64(uint64_t input);

    /**
     * Helper function that fills the buffer with record data.
     */
    static char* prepare_record(Table table, Id id, const std::string &field,
                                FieldType field_type, int64_t value,
                                char buffer[m_record_size]);

    /**
     * Write to db file a fixed width record.
     */
    void write_record(Table table, Id id, const std::string &field, int64_t value,
                      FieldType field_type = k_field_int);

    /**
     * Write the record and the string to the records and strings files.
     */
    void write_record(Table table, Id id, const std::string &field,
                      const std::string &str);

    void read_all_records();

    uint64_t record_get_int_value(Table table, Id id, const std::string &field);

    std::string record_get_str_value(Table table, Id id, const std::string &field);

public: // :tmp:
    void write_card(const ICard &card);

    boost::shared_ptr<ICard> read_card(Id card_id);

private:
    bool m_init;

    std::string m_filename;

    std::fstream m_records_stream;

    std::fstream m_strings_stream;

    typedef std::map<uint64_t, std::map<std::string, Record> > TableMap;

    std::vector<TableMap> m_records;

    bool m_records_loaded;

    friend void ::simple_db_automatic_tests(); // :tmp:
};

} // namespace anki_lite

#endif
