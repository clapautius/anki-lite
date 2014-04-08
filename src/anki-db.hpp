#ifndef ANKI_LITE_DB_HPP_
#define ANKI_LITE_DB_HPP_

#include <QString>
#include <QtSql/QtSql>
#include "exceptions.hpp"
#include "collection.hpp"
#include "deck.hpp"
#include "card.hpp"


namespace anki_lite
{

class AnkiDb
{
public:

    /**
     * @throw DbExcp in case of error.
     */
    void open_db(const QString &filename = "");

    /**
     * @throw DbExcp in case of error.
     */
    void close_db();

    Collection get_collection() const;

    Deck get_deck_by_id(long int id) const;

private:

    QSqlDatabase m_db;
};

} // namespace anki_lite

#endif
