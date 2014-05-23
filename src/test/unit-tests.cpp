#include <iostream>
#include <string.h>

#include "cli-utils.hpp"
#include "simple-db.hpp"
#include "collection.hpp"
#include "memo-alg-sm2.hpp"

using namespace std;
using namespace anki_lite;

bool g_tst_all_tests_ok = true;

#define TST_CHECK_EQUAL(X, Y) { if (X == Y) ; \
        else { cout << "Test failed: " << X << " == " << Y << " (line " \
                    << __LINE__ << ")" << endl << endl; g_tst_all_tests_ok = false; } }

#define TST_CHECK(X) { if (X) ; \
        else { cout << "Test failed: " << #X << " (line " \
                    << __LINE__ << ")" << endl << endl; g_tst_all_tests_ok = false; } }

void cli_tests()
{
    // CLI unit tests
    vector<string> tokens;
    tokenize_cmd(" \t\tana are  mere \t. ", tokens);
    TST_CHECK_EQUAL(tokens.size(), 4);
    TST_CHECK_EQUAL(tokens[0], "ana");
    TST_CHECK_EQUAL(tokens[1], "are");
    TST_CHECK_EQUAL(tokens[2], "mere");
    TST_CHECK_EQUAL(tokens[3], ".");
}


void simple_db_automatic_tests()
{
    // hton64 & ntoh64
    uint64_t uint;
    uint = SimpleDb::hton64(5);
    TST_CHECK_EQUAL(uint, 0x500000000000000);

    // SimpleDb::prepare_record
    char buffer[SimpleDb::m_record_size] = { 0 };
    char buffer_ok[SimpleDb::m_record_size] = {
        0, 0,
        'f', 'r', 'o', 'n', 't', 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 5,
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


void collection_automatic_tests()
{
    Collection col;
    Id id = col.get_free_id();
    TST_CHECK_EQUAL(id, 1);

    // add a new deck with the previous id
    TextMapT deck_details;
    deck_details["name"] = "default";
    Deck deck(id, deck_details);
    col.add_deck(deck);

    // we should get the next id
    id = col.get_free_id();
    TST_CHECK_EQUAL(id, 2);

    // try to get a card from an empty collection
    boost::shared_ptr<ICard> card = col.get_next_card();
    TST_CHECK_EQUAL(card.get(), 0);
}


void alg_sm2_automatic_tests()
{
    MemoAlgSm2 alg;
    Interval intv;
    int e_factor;

    // test interval calculation
    intv = alg.compute_new_interval(0, 1, 250);
    TST_CHECK_EQUAL(intv, 1);
    intv = alg.compute_new_interval(1, 2, 250);
    TST_CHECK_EQUAL(intv, 6);
    intv = alg.compute_new_interval(6, 3, 300);
    TST_CHECK_EQUAL(intv, 18);

    // test e-factor calculation
    e_factor = alg.compute_new_e_factor(250, 5);
    TST_CHECK_EQUAL(e_factor, 260);
    e_factor = alg.compute_new_e_factor(250, 0);
    TST_CHECK((abs(e_factor - 170) < 3));
}


int main()
{
    cli_tests();
    simple_db_automatic_tests();
    collection_automatic_tests();
    alg_sm2_automatic_tests();

    if (g_tst_all_tests_ok) {
        cout << "All tests passed." << endl;
        return 0;
    } else {
        return 1;
    }
}
