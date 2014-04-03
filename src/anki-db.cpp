#include "anki-db.hpp"
#include "main.h"

using std::string;

namespace anki_lite
{

void AnkiDb::open_db(const std::string &filename)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(filename.c_str());
    if (!m_db.open()) {
        throw DbExcp(Q_STR(m_db.lastError().text()));
    }
};

}
