#ifndef ANKI_LITE_COLLECTION_HPP_
#define ANKI_LITE_COLLECTION_HPP_

#include <QString>

namespace anki_lite
{

class Collection
{
public:

    Collection(const QString &conf, const QString &decks);

private:

    QString m_conf_json;

    QString m_decks_json;
};

} // namespace anki_lite

#endif
