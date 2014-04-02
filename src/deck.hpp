#ifndef ANKI_LITE_DECK_HPP_
#define ANKI_LITE_DECK_HPP_

#include <vector>
#include <boost/shared_ptr.hpp>
#include "card.hpp"

namespace anki_lite
{

class Deck
{
public:

    bool add_card(const boost::shared_ptr<ICard> &card);

private:

    std::vector<boost::shared_ptr<ICard> > m_cards;
};

} // namespace anki_lite

#endif
