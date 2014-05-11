#ifndef ANKI_LITE_COLLECTION_HPP_
#define ANKI_LITE_COLLECTION_HPP_

#include <vector>
//#include <QString>
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

    unsigned get_no_of_decks() const;

    std::string to_string() const;

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
