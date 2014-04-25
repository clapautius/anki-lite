#ifndef ANKI_LITE_CARD_HPP_
#define ANKI_LITE_CARD_HPP_

#include <QString>
#include "main.h"

namespace anki_lite
{
class ICard
{
public:

    virtual QString front_text() const = 0;

    virtual QString back_text() const = 0;

    virtual DbId id() const = 0;
};

class Card: public ICard
{
public:

    Card(DbId id, const QString &front_text, const QString &back_text);

    virtual QString front_text() const
    {
        return m_front_text;
    }

    virtual QString back_text() const
    {
        return m_back_text;
    }

    virtual DbId id() const
    {
        return m_id;
    }

private:

    DbId m_id;

    QString m_front_text;

    QString m_back_text;
};

} // namespace anki_lite

#endif
