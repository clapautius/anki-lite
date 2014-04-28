######################################################################
# Automatically generated by qmake (2.01a) Vi apr. 25 12:08:21 2014
######################################################################

TEMPLATE = app
TARGET =
DEPENDPATH += . src src/base src/flashcards
INCLUDEPATH += . src src/base src/flashcards
QT += sql
LIBS += -lqjson

# Input
HEADERS += src/anki-db.hpp \
           src/anki-lite-main-wnd.h \
           src/anki-utils.hpp \
           src/main.h \
           src/base/exceptions.hpp \
           src/flashcards/card.hpp \
           src/flashcards/collection.hpp \
           src/flashcards/collection-builder.hpp \
           src/flashcards/deck.hpp
FORMS += src/anki-lite-main-wnd.ui
SOURCES += src/anki-db.cpp \
           src/anki-lite-main-wnd.cpp \
           src/anki-utils.cpp \
           src/main.cpp \
           src/flashcards/card.cpp \
           src/flashcards/collection.cpp \
           src/flashcards/collection-builder.cpp \
           src/flashcards/deck.cpp
