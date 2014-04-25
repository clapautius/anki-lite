#ifndef ANKI_LITE_CARD_HPP_
#define ANKI_LITE_CARD_HPP_

#include <string>
#include "anki-types.h"

namespace anki_lite
{

class ICard
{
public:

    virtual std::string front_text() const = 0;

    virtual std::string back_text() const = 0;

    // :fixme: should be removed - atm needed for qDebug
    virtual const char* front_text_cstr() const = 0;

    // :fixme: should be removed - atm needed for qDebug
    virtual const char* back_text_cstr() const = 0;

    virtual Id id() const = 0;
};

class Card: public ICard
{
public:

    Card(Id id, const std::string &front_text, const std::string &back_text);

    virtual std::string front_text() const
    {
        return m_front_text;
    }

    virtual std::string back_text() const
    {
        return m_back_text;
    }

    virtual const char* front_text_cstr() const
    {
        return m_front_text.c_str();
    }

    virtual const char* back_text_cstr() const
    {
        return m_back_text.c_str();
    }

    virtual Id id() const
    {
        return m_id;
    }

private:

    Id m_id;

    std::string m_front_text;

    std::string m_back_text;
};

} // namespace anki_lite

#endif
