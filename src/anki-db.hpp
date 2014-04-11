#ifndef ANKI_LITE_DB_HPP_
#define ANKI_LITE_DB_HPP_

#include <QString>
#include <QtSql/QtSql>
#include <stdint.h>

#include "exceptions.hpp"
#include "main.h"
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

    void get_deck_data_from_db(Deck&) const;

private:

    QSqlDatabase m_db;
};

} // namespace anki_lite

#endif
