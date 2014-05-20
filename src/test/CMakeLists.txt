add_executable (anki-lite-unit-tests
  unit-tests.cpp
  ../cli/cli-utils.cpp
  ../simple-db.cpp
  ../flashcards/collection.cpp
  ../flashcards/deck.cpp
  ../flashcards/card.cpp)

include_directories (.. ../cli ../flashcards ../base)
