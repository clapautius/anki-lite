#ifndef ANKI_LITE_COLLECTION_HPP_
#define ANKI_LITE_COLLECTION_HPP_

#include <vector>
#include "anki-types.hpp"
#include "deck.hpp"

namespace anki_lite
{

/**
 * Keeps data about a collection (configuration, decks).
 */
class Collection
{
public:

    Collection();

    bool set_conf(const TextMapT &conf);

    bool add_deck(const Deck &deck);

    // :fixme: to be removed
    /**
     * @param[in] decks : they will be modified.
     */
    bool set_decks(std::vector<TextMapT> &decks);

    /*
    Collection(const QString &conf, const QString &decks);
    */

    bool is_valid() const;

    const Deck& get_deck_by_idx(unsigned index) const;

    Deck& get_deck_by_idx(unsigned index);

    /**
     * Return the deck having the id 'id'.
     *
     * @throw std::runtime_error() if no such deck exists.
     */
    Deck& get_deck_by_id(Id id);

    unsigned get_no_of_decks() const;

    std::string to_string() const;

    /**
     * Return an id for a deck or a card that is not used.
     *
     * @todo Make separate functions for deck ids and card ids. :fixme:
     */
    Id get_free_id() const;

private:

    bool m_valid;

    TextMapT m_conf;

    /*
    QString m_conf_json;

    QString m_decks_json;
    */

    std::vector<Deck> m_decks;
};

} // namespace anki_lite

#endif
