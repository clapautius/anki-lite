#include <sstream>
#include <iostream> // :fixme:

#include "deck.hpp"
#include "anki-utils.hpp"

using std::string;
using std::map;

namespace anki_lite
{

#if 0
Deck::Deck(const string &id, const string &details)
  : m_id(-1)
{
    // :fixme:
    //qDebug() << __FUNCTION__ << "(id=" << id <<")";
    std::cout << __FUNCTION__ << "(id=" << id <<")";
    char *ptr = NULL;
    m_id = strtoll(id.c_str(), &ptr, 10);
    if (m_id == 0 && ptr == id.c_str()) {
        // :fixme:
        //qDebug() << "Invalid id in deck: id str = " << id.toLong();
        std::cout << "Invalid id in deck: id str = " << id.c_str();
        m_id = -1;
    } else {
        QVariantMap deck_map = details.toMap();
        if (deck_map.empty()) {
            // :fixme:
            //qDebug() << "No details for deck with id " << m_id << "(empty map)";
            std::cout << "No details for deck with id " << m_id << "(empty map)";
            m_id = -1;
        } else {
            m_name = deck_map["name"].toString();
        }
    }
}

#endif

Deck::Deck(const string &id, map<string, string> &details)
     : m_id(-1)
{
    // :fixme:
    //qDebug() << __FUNCTION__ << "(id=" << id <<")";
    std::cout << __FUNCTION__ << "(id=" << id <<")";
    char *ptr = NULL;
    m_id = strtoll(id.c_str(), &ptr, 10);
    if (m_id == 0 && ptr == id.c_str()) {
        // :fixme:
        //qDebug() << "Invalid id in deck: id str = " << id.toLong();
        std::cout << "Invalid id in deck: id str = " << id.c_str();
        m_id = -1;
    } else {
         m_name = details["name"];
    }
}


bool Deck::add_card(const boost::shared_ptr<ICard> &card)
{
    bool rc = true;
    m_cards.push_back(card);
    return rc;
}


bool Deck::is_valid() const
{
    return m_id >= 0;
}


string Deck::toString() const
{
    std::ostringstream ret;
    ret<<"Deck: id="<<m_id<<", name="<<m_name;
    return ret.str();
}

} // namespace anki_lite
