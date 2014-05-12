add_executable (anki-lite-cli
  anki-lite-cli.cpp
  cli-utils.cpp)

target_link_libraries (anki-lite-cli anki-lite)

include_directories (.. ../base ../flashcards)
