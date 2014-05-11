add_executable (anki-lite-cli
  anki-lite-cli.cpp)

target_link_libraries (anki-lite-cli anki-lite)

include_directories (.. ../base ../flashcards)
