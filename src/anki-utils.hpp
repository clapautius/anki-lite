#ifndef ANKI_LITE_ANKI_UTILS_HPP_
#define ANKI_LITE_ANKI_UTILS_HPP_

#include "anki-types.hpp"

namespace anki_lite
{

/**
 * @throw InvalidData on failure.
 */
Id string_to_id(const std::string &s);

} // namespace anki_lite

#endif
