#include <stdexcept>
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>

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

    // connect list
    connect(listWidget, SIGNAL(activated (const QModelIndex&)),
            this, SLOT(on_deck_selected(const QModelIndex&)));
}


void AnkiLiteMainWnd::show_decks(const anki_lite::Collection &collection)
{
    listWidget->clear();
    for (unsigned i = 0; i < collection.get_no_of_decks(); ++i) {
        listWidget->addItem(collection.get_deck(i).name());
    }
}


void AnkiLiteMainWnd::on_deck_selected(const QModelIndex & index)
{
    QString deck_name = index.data().toString();
    if (deck_name.isEmpty()) {
        QMessageBox::warning(NULL, "Error", tr("Invalid deck selected"));
    } else {
        qDebug() << "Deck activated: " << deck_name;
    }
}
