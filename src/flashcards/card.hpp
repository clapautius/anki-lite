#ifndef ANKI_LITE_CARD_HPP_
#define ANKI_LITE_CARD_HPP_

#include <string>
#include "anki-types.hpp"

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

    virtual void set_deck_id(Id) = 0;

    virtual Id deck_id() const = 0;

    virtual std::string to_string() const = 0;

    virtual int e_factor() const = 0;

    virtual void set_e_factor(int e_factor) = 0;

    virtual Interval last_view() const = 0;

    virtual void set_last_view_now() = 0;

    virtual void set_last_view(Interval) = 0;

    virtual void set_interval(Interval intv) = 0;

    virtual Interval due() const = 0;

    virtual int repetition() const = 0;

    virtual void inc_repetition() = 0;

    virtual void reset_repetition(int new_value = 0) = 0;

    virtual Interval interval() const = 0;
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

    virtual void set_deck_id(Id deck_id)
    {
        m_deck_id = deck_id;
    }

    virtual Id deck_id() const
    {
        return m_deck_id;
    }

    virtual std::string to_string() const;

    virtual int e_factor() const
    {
        return m_e_factor;
    }

    virtual void set_e_factor(int e_factor)
    {
        m_e_factor = e_factor;
    }

    virtual Interval last_view() const
    {
        return m_last_view;
    }

    virtual void set_last_view_now()
    {
        m_last_view = time(NULL);
    }

    virtual void set_last_view(Interval i)
    {
        m_last_view = i;
    }

    virtual Interval interval() const
    {
        return m_interval;
    }

    virtual void set_interval(Interval intv)
    {
        m_interval = intv;
    }

    Interval due() const
    {
        return m_last_view + m_interval * (24 * 60 * 60);
    }

    virtual int repetition() const
    {
        return m_repetition;
    }

    virtual void inc_repetition()
    {
        ++m_repetition;
    }

    virtual void reset_repetition(int new_value = 0)
    {
        m_repetition = new_value;
    }

private:

    Id m_id;

    Id m_deck_id;

    std::string m_front_text;

    std::string m_back_text;

    int m_e_factor;

    Interval m_last_view;

    Interval m_interval;

    int m_repetition;
};

} // namespace anki_lite

#endif
