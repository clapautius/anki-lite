#ifndef ANKI_LITE_DB_HPP_
#define ANKI_LITE_DB_HPP_

#include <QString>
#include <QtSql/QtSql>
#include <stdint.h>

#include "exceptions.hpp"
#include "main.h"
#include "anki-storage.hpp"
#include "collection.hpp"
#include "deck.hpp"
#include "card.hpp"


namespace anki_lite
{

class AnkiSqliteDb : public AnkiStorage
{
public:

    AnkiSqliteDb(const QString &db_name = "");

    virtual ~AnkiSqliteDb() {};

    /**
     * @throw DbExcp in case of error.
     */
    virtual void open_storage();

    /**
     * @throw DbExcp in case of error.
     */
    virtual void close_storage();

    virtual void get_collection(Collection &collection) const;

    /**
     * Read deck data and creates the Deck objects. The decks will have all the config
     * params but no cards in them. Use get_cards_for_deck to add cards.
     *
     * @throw DbExcp in case of error.
     */
    virtual void get_decks(std::vector<Deck> &decks) const;

    /**
     * @throw DbExcp in case of error.
     */
    virtual void get_cards_for_deck(Deck&) const;

protected:

    static TextMapT convert_json_conf_to_map(const QString &json_conf);

    QString m_db_filename;

    QSqlDatabase m_db;
};

} // namespace anki_lite

#endif
