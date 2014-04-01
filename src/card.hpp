#ifndef ANKI_LITE_CARD_HPP_
#define ANKI_LITE_CARD_HPP_

#include <string>

namespace anki_lite
{
   class ICard
   {
     public:

      virtual std::string get_front_text() const = 0;

      virtual std::string get_back_text() const = 0;
   };

   class Card: public ICard
   {
     public:

      Card(const std::string &front_text, const std::string &back_text);

      virtual std::string get_front_text() const
      {
         return m_front_text;
      }

      virtual std::string get_back_text() const
      {
         return m_back_text;
      }

     private:

      unsigned long int m_id;

      std::string m_front_text;

      std::string m_back_text;
   };

} // namespace anki_lite

#endif
