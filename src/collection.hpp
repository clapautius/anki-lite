#ifndef ANKI_LITE_COLLECTION_HPP_
#define ANKI_LITE_COLLECTION_HPP_

#include <vector>
#include <QString>
#include "deck.hpp"

namespace anki_lite
{

/**
 * Keeps data about a collection (configuration, decks).
 */
class Collection
{
public:

    Collection(const QString &conf, const QString &decks);

    bool is_valid() const;

    Deck& get_deck(unsigned index);

    int get_no_of_decks() const;

private:

    bool m_valid;

    QString m_conf_json;

    QString m_decks_json;

    std::vector<Deck> m_decks;
};

} // namespace anki_lite

#endif
