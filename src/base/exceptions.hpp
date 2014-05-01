#ifndef ANKI_LITE_EXCEPTIONS_HPP_
#define ANKI_LITE_EXCEPTIONS_HPP_

#include <stdexcept>
#include <string>

namespace anki_lite
{

class IoExcp : public std::runtime_error
{
public:
    IoExcp(const std::string &text = "IO error")
      : std::runtime_error(text)
    {
    }
};


/**
 * Unknown internal error (probably a bug).
 */
class InternalError : public std::logic_error
{
public:
    InternalError(const std::string &text = "Internal error")
      : std::logic_error(text)
    {
    }
};


class DbExcp : public std::runtime_error
{
public:

    DbExcp(const std::string &text = "Anki internal database error")
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
