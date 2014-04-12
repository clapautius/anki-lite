#ifndef ANKI_LITE_MAIN_WND_H_
#define ANKI_LITE_MAIN_WND_H_

#include <QDialog>

#include "ui_anki-lite-main-wnd.h"
#include "collection.hpp"

class AnkiLiteMainWnd : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:

    AnkiLiteMainWnd( QWidget *parent = 0, char *name = 0 );

    void show_decks(const anki_lite::Collection &collection);

    protected slots:

private:

};

#endif
