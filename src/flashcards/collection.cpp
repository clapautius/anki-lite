#include <stdexcept>
#include <map>
#include <QDebug>

#include "collection.hpp"
#include "anki-utils.hpp"

using std::map;
using std::string;

namespace anki_lite
{

/**
 * Build a collection, add Deck objects but without cards.
 *
 * @param[in] conf : json text from database containing configuration data.
 * @param[in] decks : json text from database containing decks data.
 **/
Collection::Collection(const QString &conf, const QString &decks)
  : m_valid(false), m_conf_json(conf), m_decks_json(decks)
{
    // decode decks
    try {
        QVariantMap decks_map = parse_json(m_decks_json);
        for(QVariantMap::const_iterator iter = decks_map.begin(); iter != decks_map.end();
            ++iter) {
            qDebug() << iter.key() << iter.value();

            QVariantMap deck_map = iter.value().toMap();
            map<string, string> deck_stl_map;
            if (deck_map.empty()) {
                qDebug() << "No details for deck with id " << iter.key() << "(empty map)";
            } else {
                deck_stl_map["name"] = Q_STR(deck_map["name"].toString());
            }

            Deck deck(Q_STR(iter.key()), deck_stl_map);
            qDebug() << "New deck object: " << deck.toString().c_str();
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


const Deck& Collection::get_deck(unsigned index) const
{
    if (index >= m_decks.size()) {
        throw std::runtime_error("Index out of bounds for m_decks");
    }
    return m_decks[index];
}


Deck& Collection::get_deck(unsigned index)
{
    if (index >= m_decks.size()) {
        throw std::runtime_error("Index out of bounds for m_decks");
    }
    return m_decks[index];
}

unsigned Collection::get_no_of_decks() const
{
    return m_decks.size();
}

};
