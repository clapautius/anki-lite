#include "anki-lite-main-wnd.h"
#include "main.h"

using anki_lite::Collection;

AnkiLiteMainWnd::AnkiLiteMainWnd( QWidget *, char *)
{
    setupUi(this);
}


void AnkiLiteMainWnd::show_decks(const anki_lite::Collection &collection)
{
    // :fixme: clear list first
    for (unsigned i = 0; i < collection.get_no_of_decks(); ++i) {
        listWidget->addItem(collection.get_deck(i).name());
    }
}
