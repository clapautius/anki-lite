TEMPLATE = app
TARGET =
DEPENDPATH += . .. ../base ../flashcards
INCLUDEPATH += . .. ../base ../flashcards
QMAKE_CXXFLAGS += -Wall -g3 -O0 -std=c++11

# Input
HEADERS += ../simple-db.hpp \
           ../base/anki-storage.hpp \
           ../base/anki-types.hpp \
           ../base/exceptions.hpp \
           ../flashcards/card.hpp \
           ../flashcards/collection-builder.hpp \
           ../flashcards/collection.hpp \
           ../flashcards/deck.hpp

SOURCES += ../simple-db.cpp \
           ../flashcards/card.cpp \
           ../flashcards/collection-builder.cpp \
           ../flashcards/collection.cpp \
           ../flashcards/deck.cpp

SOURCES += anki-lite-cli.cpp
