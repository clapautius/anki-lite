#include "collection.hpp"

namespace anki_lite
{

Collection::Collection(const QString &conf, const QString &decks)
  : m_conf_json(conf), m_decks_json(decks)
{
}

};
