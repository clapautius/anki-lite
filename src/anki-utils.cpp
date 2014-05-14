#include "anki-utils.hpp"

#include "exceptions.hpp"

namespace anki_lite
{

Id string_to_id(const std::string &id_str)
{
    Id id;
    char *ptr = NULL;
    id = strtoll(id_str.c_str(), &ptr, 10);
    if (id == 0 && ptr == id_str.c_str()) {
        throw InvalidData("Error converting string to Id");
    }
    return id;
}

} // namespace anki_lite
