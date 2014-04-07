#ifndef ANKI_LITE_DB_HPP_
#define ANKI_LITE_DB_HPP_

#include <string>
#include <QtSql/QtSql>
#include "exceptions.hpp"
#include "collection.hpp"

namespace anki_lite
{

class AnkiDb
{
public:

    /**
     * @throw DbExcp in case of error.
     */
    void open_db(const std::string &filename = "");

    /**
     * @throw DbExcp in case of error.
     */
    void close_db();

    Collection get_collection() const;

private:

    QSqlDatabase m_db;
};

} // namespace anki_lite

#endif
