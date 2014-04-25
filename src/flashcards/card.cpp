#include "card.hpp"

namespace anki_lite
{

Card::Card(DbId id, const QString &front_text, const QString &back_text)
  : m_id(id), m_front_text(front_text), m_back_text(back_text)
{
}

} // namespace anki_lite
