#include <QDebug>

#include "collection.hpp"
#include "anki-utils.hpp"

namespace anki_lite
{

Collection::Collection(const QString &conf, const QString &decks)
  : m_valid(false), m_conf_json(conf), m_decks_json(decks)
{
    // decode decks
    try {
        QVariantMap decks_map = parse_json(m_decks_json);
        for(QVariantMap::const_iterator iter = decks_map.begin(); iter != decks_map.end();
            ++iter) {
            qDebug() << iter.key() << iter.value();
            Deck deck(iter.key(), iter.value());
            m_decks.push_back(deck);
        }
    }
    catch (...) {
        qDebug() << "Error parsing decks json";
        return;
    }
    m_valid = true;
}


bool Collection::is_valid() const
{
    return m_valid;
}

};
