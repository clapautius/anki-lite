#include <qjson/parser.h>

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

} // namespace anki_lite
