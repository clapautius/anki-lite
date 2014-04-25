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

    /**
     * @param[in] id : deck id, as string
     * @param[in] details : deck details, json
     */
    Deck(const std::string &id, const std::string &details);

    bool add_card(const boost::shared_ptr<ICard> &card);

    bool is_valid() const;

    std::string toString() const;

    Id id() const
    {
        return m_id;
    }

    std::string name() const
    {
        return m_name;
    }

private:

    Id m_id;

    std::string m_name;

    std::vector<boost::shared_ptr<ICard> > m_cards;
};

} // namespace anki_lite

#endif
