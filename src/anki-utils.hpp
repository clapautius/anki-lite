#ifndef ANKI_LITE_ANKI_UTILS_HPP_
#define ANKI_LITE_ANKI_UTILS_HPP_

#include <QVariantMap>

namespace anki_lite
{

/**
 * @throw DbJsonExcp on failure.
 */
QVariantMap parse_json(const QString &json_text);


} // namespace anki_lite

#endif
