#include "anki-db.hpp"
#include "anki-utils.hpp"

using std::string;
using boost::shared_ptr;

namespace anki_lite
{

void AnkiDb::open_db(const QString &filename)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(Q_STR(filename));
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

    // get 'decks' field
    result = query.value(10);
    if (!result.isValid()) {
        throw DbExcp("Error getting 'decks' field from 'col' table");
    }
    QString decks_json = result.toString();
    qDebug()<<":debug: decks(json): "<<decks_json;

    Collection col(conf_json, decks_json);

    // read cards for every deck
    for (unsigned i = 0; i < col.get_no_of_decks(); ++i) {
        Deck &deck = col.get_deck(i);
        get_deck_data_from_db(deck);
    }

    return col;
}


void AnkiDb::get_deck_data_from_db(Deck &deck) const
{
    qDebug()<<"loading deck with id "<<deck.id();
    QSqlQuery query;
    query.prepare("select c.id, n.sfld, n.flds "
                  "from cards c, notes n "
                  "where c.nid = n.id and c.did = ?");
    query.addBindValue(deck.id());
    query.exec();
    while (query.next()) {
        DbId card_id = query.value(0).toLongLong();
        QString front_text = query.value(1).toString();
        QString back_text = query.value(2).toString();
        boost::shared_ptr<ICard> card(new Card(card_id,
                                               Q_STR(front_text), Q_STR(back_text)));
        if (deck.add_card(card)) {
            qDebug()<<"New card in deck "<<deck.name().c_str()
                    <<": back_text="<<card->back_text_cstr();
        } else {
            qWarning()<<"Error adding card in deck "<<deck.name().c_str();
        }
    }
}


}
