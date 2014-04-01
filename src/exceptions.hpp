#ifndef ANKI_LITE_EXCEPTIONS_HPP_
#define ANKI_LITE_EXCEPTIONS_HPP_

#include <stdexcept>
#include <string>

namespace anki_lite
{

   class DbExcp : public std::runtime_error
   {
      DbExcp(const std::string &text)
      : std::runtime_error(text)
      {
      }

   };

}; // namespace anki_lite

#endif
