#include "deck.hpp"

namespace anki_lite
{

Deck::Deck(const QString &id, const QVariant &details)
{

}


bool Deck::add_card(const boost::shared_ptr<ICard> &card)
{
    bool rc = true;
    m_cards.push_back(card);
    return rc;
}

} // namespace anki_lite
