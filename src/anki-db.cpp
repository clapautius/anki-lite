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


Collection AnkiDb::get_collection() const
{
    QSqlQuery query = m_db.exec("select id, crt, mod, scm, ver, dty, usn, ls, conf, "
                                "models, decks, dconf, tags "
                                "from col");
    if (m_db.lastError().type() != QSqlError::NoError) {
        throw DbExcp(Q_STR(m_db.lastError().text()));
    };
    query.next();
    QVariant result;
    // get 'conf' field
    result = query.value(8);
    if (!result.isValid()) {
        throw DbExcp("Error getting 'conf' field from 'col' table");
    }
    QString conf_json = result.toString();
    qDebug()<<":debug: conf(json): "<<conf_json;

    Collection col(conf_json, "");
    return col;
}

}
