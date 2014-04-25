#include <QDebug>

#include <iostream> // :tmp:

#include "deck.hpp"
#include "anki-utils.hpp"

namespace anki_lite
{

Deck::Deck(const QString &id, const QVariant &details)
  : m_id(-1)
{
    qDebug() << __FUNCTION__ << "(id=" << id <<")";
    bool ok = false;
    m_id = id.toLongLong(&ok);
    if (!ok) {
        qDebug() << "Invalid id in deck: id str = " << id.toLong();
        m_id = -1;
    } else {
        QVariantMap deck_map = details.toMap();
        if (deck_map.empty()) {
            qDebug() << "No details for deck with id " << m_id << "(empty map)";
            m_id = -1;
        } else {
            m_name = deck_map["name"].toString();
        }
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


QString Deck::toString() const
{
    QString ret = QString("Deck: id=%1, name=%2").arg(m_id).arg(m_name);
    return ret;
}

} // namespace anki_lite
