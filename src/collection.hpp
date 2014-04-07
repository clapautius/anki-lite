#ifndef ANKI_LITE_COLLECTION_HPP_
#define ANKI_LITE_COLLECTION_HPP_

#include <string>
#include "anki-db.hpp"

namespace anki_lite
{

class Collection
{
public:

    void read_from_db(const AnkiDb &database);

private:


};

} // namespace anki_lite
