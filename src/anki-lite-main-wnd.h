#ifndef ANKI_LITE_MAIN_WND_H
#define ANKI_LITE_MAIN_WND_H

#include <QDialog>

#include "ui_anki-lite-main-wnd.h"

class AnkiLiteMainWnd : public QMainWindow, public Ui::MainWindow
{
  Q_OBJECT

public:

  AnkiLiteMainWnd( QWidget *parent = 0, char *name = 0 );

protected slots:

private:

};

#endif
