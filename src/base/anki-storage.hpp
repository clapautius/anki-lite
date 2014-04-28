#ifndef ANKI_LITE_ANKI_STORAGE_HPP_
#define ANKI_LITE_ANKI_STORAGE_HPP_

#include <stdint.h>


namespace anki_lite
{

class Collection;
class Deck;

class AnkiStorage
{
public:

    virtual ~AnkiStorage() {};

    /**
     * @throw DbExcp in case of error.
     */
    virtual void open_storage() = 0;

    /**
     * @throw DbExcp in case of error.
     */
    virtual void close_storage() = 0;

    virtual void get_collection(Collection&) const = 0;

    /**
     * Read deck data and creates the Deck objects. The decks will have all the config
     * params but no cards in them. Use get_cards_for_deck to add cards.
     *
     * @throw DbExcp in case of error.
     */
    virtual void get_decks(std::vector<Deck> &decks) const = 0;

    /**
     * @throw DbExcp in case of error.
     */
    virtual void get_cards_for_deck(Deck&) const = 0;

};

} // namespace anki_lite

#endif
