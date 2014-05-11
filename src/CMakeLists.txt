add_subdirectory (cli)

add_library (anki-lite
  simple-db.cpp
  flashcards/card.cpp
  flashcards/collection.cpp
  flashcards/collection-builder.cpp
  flashcards/deck.cpp
  flashcards/memo-alg-sm2.cpp)

include_directories (. flashcards base)
