#ifndef ANKI_LITE_EXCEPTIONS_HPP_
#define ANKI_LITE_EXCEPTIONS_HPP_

#include <stdexcept>
#include <string>

namespace anki_lite
{

class DbExcp : public std::runtime_error
{
public:

    DbExcp(const std::string &text = "Database error")
      : std::runtime_error(text)
    {
    }

};


class DbJsonExcp : public DbExcp
{
public:

    DbJsonExcp(const std::string &text = "Invalid JSON in DB")
      : DbExcp(text)
    {
    }

};

}; // namespace anki_lite

#endif
