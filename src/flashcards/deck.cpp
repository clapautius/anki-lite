#include <sstream>
#include <iostream> // :fixme:

#include "deck.hpp"
//#include "anki-utils.hpp"

using std::string;
using std::map;
using std::ostringstream;
using std::endl;

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

Deck::Deck(Id id, std::map<std::string, std::string> &details)
  : m_id(id)
{
#ifdef ANKI_DEBUG
    std::cout << __FUNCTION__ << ": New deck (id=" << id << ")" << endl;
#endif
    m_name = details["name"];
}


Deck::Deck(const string &id, map<string, string> &details)
     : m_id(-1)
{
    // :fixme:
    //qDebug() << __FUNCTION__ << "(id=" << id <<")";
#ifdef ANKI_DEBUG
    std::cout << __FUNCTION__ << ": New deck (id=" << id <<")" << endl;
#endif
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


string Deck::to_string() const
{
    ostringstream ret;
    ret << "Deck: id=" << m_id << ", name=" << m_name << endl;
    for (unsigned i = 0; i < get_no_of_cards(); i++) {
        boost::shared_ptr<const ICard> card = get_card(i);
        ret << card->to_string() <<endl;
    }
    return ret.str();
}


unsigned int Deck::get_no_of_cards() const
{
    return m_cards.size();
}


boost::shared_ptr<ICard> Deck::get_card(unsigned index)
{
    // :fixme: check boundaries
    return m_cards[index];
}


boost::shared_ptr<const ICard> Deck::get_card(unsigned index) const
{
    // :fixme: check boundaries
    return m_cards[index];
}

} // namespace anki_lite
