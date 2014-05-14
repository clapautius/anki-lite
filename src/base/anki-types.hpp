#ifndef ANKI_LITE_ANKI_TYPES_HPP
#define ANKI_LITE_ANKI_TYPES_HPP

#include <stdint.h>
#include <time.h>
#include <map>
#include <string>

#define ANKI_DEBUG

namespace anki_lite
{

typedef int64_t Id;

typedef std::map<std::string, std::string> TextMapT;

typedef time_t Interval;

}

#endif
