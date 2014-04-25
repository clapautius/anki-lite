#include "card.hpp"

using std::string;

namespace anki_lite
{

Card::Card(Id id, const string &front_text, const string &back_text)
  : m_id(id), m_front_text(front_text), m_back_text(back_text)
{
}

} // namespace anki_lite
