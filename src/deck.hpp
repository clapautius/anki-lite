#ifndef ANKI_LITE_DECK_HPP_
#define ANKI_LITE_DECK_HPP_

#include <vector>
#include <boost/shared_ptr.hpp>
#include <QVariant>
#include "main.h"
#include "card.hpp"

namespace anki_lite
{

class Deck
{
public:

    Deck(const QString &id, const QVariant &details);

    bool add_card(const boost::shared_ptr<ICard> &card);

    bool is_valid() const;

    QString toString() const;

    DbId id() const
    {
        return m_id;
    }

private:

    long long int m_id;

    QString m_name;

    std::vector<boost::shared_ptr<ICard> > m_cards;
};

} // namespace anki_lite

#endif
