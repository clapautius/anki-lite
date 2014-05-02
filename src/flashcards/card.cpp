#include <sstream>
#include "card.hpp"

using std::string;
using std::ostringstream;
using std::endl;

namespace anki_lite
{

Card::Card(Id id, const string &front_text, const string &back_text)
  : m_id(id), m_deck_id(0), m_front_text(front_text), m_back_text(back_text)
{
}


string Card::to_string() const
{
    ostringstream ostr;
    ostr << "Card (id" << id() << ")" << endl;
    ostr << "  deck id: " << deck_id() <<endl;
    ostr << "  front text: " << front_text() << endl;
    ostr << "  back text: " << back_text() << endl;
    return ostr.str();
}

} // namespace anki_lite
