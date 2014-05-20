#include <stdexcept>
#include <map>
#include <sstream>
//#include <QDebug>

#include "collection.hpp"
//#include "anki-utils.hpp"

using std::map;
using std::string;
using std::ostringstream;
using std::endl;

namespace anki_lite
{


Collection::Collection()
  : m_valid(false)
{
}


bool Collection::set_conf(const TextMapT &conf)
{
    bool rc = true;
    m_conf = conf;
    // :fixme: check various mandatory values in conf
    m_valid = true;
    return rc;
}


bool Collection::set_decks(std::vector<TextMapT> &decks)
{
    bool rc = true;
    if (m_valid) {
        for (unsigned i = 0; i < decks.size(); i++) {
            TextMapT::iterator it = decks[i].find("id");
            if (it != decks[i].end()) {
                // extrart id from map and then erase it
                string id = it->second;
                decks[i].erase(it);
                Deck deck(id, decks[i]);
                m_decks.push_back(deck);
            } else {
                rc = false;
                break;
            }
        }
    } else {
        rc = false;
    }
    return rc;
}

#if 0

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

#endif

bool Collection::is_valid() const
{
    return m_valid;
}


bool Collection::add_deck(const Deck &deck)
{
    // :fixme: add extra checks (check duplicate ids, etc.)
    m_decks.push_back(deck);
    return true;
}


const Deck& Collection::get_deck_by_idx(unsigned index) const
{
    if (index >= m_decks.size()) {
        throw std::runtime_error("Index out of bounds for m_decks");
    }
    return m_decks[index];
}


Deck& Collection::get_deck_by_idx(unsigned index)
{
    if (index >= m_decks.size()) {
        throw std::runtime_error("Index out of bounds for m_decks");
    }
    return m_decks[index];
}


Deck& Collection::get_deck_by_id(Id id)
{
    for (unsigned i = 0; i < m_decks.size(); i++) {
        if (m_decks[i].id() == id) {
            return m_decks[i];
        }
    }
    throw std::runtime_error("Cannot find deck by id");
}


unsigned Collection::get_no_of_decks() const
{
    return m_decks.size();
}


std::string Collection::to_string() const
{
    ostringstream ostr;
    ostr << "Collection:" << endl;
    for (unsigned i = 0; i < get_no_of_decks(); i++) {
        const Deck &deck = get_deck_by_idx(i);
        ostr << deck.to_string() << endl;
    }
    return ostr.str();
}


Id Collection::get_free_id() const
{
    Id max_id = 0;
    for (unsigned i = 0; i < get_no_of_decks(); i++) {
        const Deck &deck = get_deck_by_idx(i);
        if (deck.id() > max_id) {
            max_id = deck.id();
        }
        for (unsigned j = 0; j < deck.get_no_of_cards(); j++) {
            boost::shared_ptr<const ICard> card = deck.get_card(j);
            if (card->id() > max_id) {
                max_id = card->id();
            }
        }
    }
    return max_id + 1;
}


boost::shared_ptr<ICard> Collection::get_next_card(Id deck_id)
{
    int min_due = -1;
    boost::shared_ptr<ICard> min_due_card;
    for (unsigned i = (deck_id == -1 ? 0 : deck_id);
         i < (deck_id == -1 ? get_no_of_decks() : deck_id + 1); i++) {
        Deck &deck = get_deck_by_idx(i);
        for (unsigned j = 0; j < deck.get_no_of_cards(); j++) {
            boost::shared_ptr<ICard> card = deck.get_card(j);
            if (card->due() < min_due || min_due == -1) {
                min_due = card->due();
                min_due_card = card;
            }
        }
    }
    return min_due_card;
}


};
