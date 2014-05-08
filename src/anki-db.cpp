#include "anki-db.hpp"
#include "anki-utils.hpp"

using std::string;
using std::map;
using boost::shared_ptr;

namespace anki_lite
{

AnkiSqliteDb::AnkiSqliteDb(const QString &filename)
  : m_db_filename(filename)
{
}


void AnkiSqliteDb::open_storage()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(Q_STR(m_db_filename));
    if (!m_db.open()) {
        throw DbExcp(Q_STR(m_db.lastError().text()));
    }
};


void AnkiSqliteDb::close_storage()
{
    m_db.close();
}


void AnkiSqliteDb::get_collection(Collection &collection)
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
    TextMapT conf_map = convert_json_conf_to_map(conf_json);
    collection.set_conf(conf_map);

    std::vector<Deck> decks;
    get_decks(decks);

    for (unsigned i = 0; i < decks.size(); i++) {
        collection.add_deck(decks[i]);
    }

    // read cards for every deck
    for (unsigned i = 0; i < collection.get_no_of_decks(); ++i) {
        Deck &deck = collection.get_deck_by_idx(i);
        get_cards_for_deck(deck);
    }
}


void AnkiSqliteDb::get_decks(std::vector<Deck> &decks)
{
    QSqlQuery query = m_db.exec("select decks "
                                "from col");
    if (m_db.lastError().type() != QSqlError::NoError) {
        throw DbExcp(Q_STR(m_db.lastError().text()));
    };
    query.next();
    QVariant result;

    // get 'decks' field
    result = query.value(0);
    if (!result.isValid()) {
        throw DbExcp("Error getting 'decks' field from 'col' table");
    }
    QString decks_json = result.toString();
    qDebug()<<":debug: decks(json): "<<decks_json;

    // decode decks
    QVariantMap decks_map = parse_json(decks_json);
    for(QVariantMap::const_iterator iter = decks_map.begin(); iter != decks_map.end();
        ++iter) {
        qDebug() << iter.key() << iter.value();

        QVariantMap deck_map = iter.value().toMap();
        map<string, string> deck_stl_map;
        if (deck_map.empty()) {
            qDebug() << "No details for deck with id " << iter.key() << "(empty map)";
        } else {
            deck_stl_map["name"] = Q_STR(deck_map["name"].toString());
        }

        Deck deck(Q_STR(iter.key()), deck_stl_map);
        qDebug() << "New deck object: " << deck.to_string().c_str();
        decks.push_back(deck);
    }
}


void AnkiSqliteDb::get_cards_for_deck(Deck &deck)
{
    qDebug()<<"loading deck with id "<<deck.id();
    QSqlQuery query;
    query.prepare("select c.id, n.sfld, n.flds "
                  "from cards c, notes n "
                  "where c.nid = n.id and c.did = ?");
    query.addBindValue((qulonglong)deck.id());
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


TextMapT AnkiSqliteDb::convert_json_conf_to_map(const QString &)
{
    TextMapT conf;
    // :todo:
    return conf;
}


}
