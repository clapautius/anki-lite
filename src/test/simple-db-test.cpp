#include <string.h>
#include <iostream>
#include "collection.hpp"
#include "simple-db.hpp"

using namespace anki_lite;
using namespace std;

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
    simple_db_write_and_read();

    Card card(5, "front", "back");
    SimpleDb db("simple-db.bin");
    db.open_storage();
    db.write_card(card);
    db.close_storage();
}
