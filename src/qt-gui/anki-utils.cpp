#include <qjson/parser.h>
#include <QDebug>

#include "main.h"
#include "anki-utils.hpp"
#include "exceptions.hpp"


namespace anki_lite
{

QVariantMap parse_json(const QString &json_text)
{
    QJson::Parser parser;
    QByteArray json;
    json.append(Q_STR(json_text));
    bool ok;
    QVariantMap result = parser.parse (json, &ok).toMap();
    if (!ok) {
        QString err = "An error occurred during parsing, text=" + json_text;
        qFatal("%s", Q_STR(err));
        throw DbJsonExcp();
    }
    return result;
}

#if 0
// :fixme: - not used
QString remove_quotes(const QString &str)
{
    qDebug() << __FUNCTION__ << "str=" << str;
    int len = str.length();
    if (len >= 2 && str[0] == '"' && str[len -1] == '"') {
        return str.right(len - 1).left(len -2);
    } else {
        return str;
    }
}
#endif

} // namespace anki_lite
