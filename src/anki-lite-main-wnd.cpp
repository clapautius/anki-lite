#include <stdexcept>
#include <QMessageBox>
#include <QPushButton>

#include "anki-lite-main-wnd.h"
#include "main.h"

using anki_lite::Collection;

AnkiLiteMainWnd::AnkiLiteMainWnd( QWidget *, char *)
{
    setupUi(this);

    // connect close button
    const QPushButton *p_close_button = mp_button_box->button(QDialogButtonBox::Close);
    if (p_close_button == NULL) {
        QMessageBox::critical(NULL, "Error", tr("No close button present. BUG"));
        throw std::runtime_error("No close button present. BUG");
    }
    connect(p_close_button, SIGNAL(clicked(bool)), this, SLOT(close()));
}


void AnkiLiteMainWnd::show_decks(const anki_lite::Collection &collection)
{
    listWidget->clear();
    for (unsigned i = 0; i < collection.get_no_of_decks(); ++i) {
        listWidget->addItem(collection.get_deck(i).name());
    }
}
