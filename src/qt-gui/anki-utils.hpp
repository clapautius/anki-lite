#ifndef ANKI_LITE_ANKI_UTILS_HPP_
#define ANKI_LITE_ANKI_UTILS_HPP_

#include <QVariantMap>

#define Q_STR(x) (x).toUtf8().constData()

namespace anki_lite
{

/**
 * @throw DbJsonExcp on failure.
 */
QVariantMap parse_json(const QString &json_text);

//QString remove_quotes(const QString &str); // :fixme: not used

} // namespace anki_lite

#endif
