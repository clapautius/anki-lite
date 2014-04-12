#ifndef ANKI_LITE_MAIN_H
#define ANKI_LITE_MAIN_H

#include <QApplication>
#include <QString>

#define ANKI_LITE_VER "0.1" // :release:

#define Q_STR(x) (x).toUtf8().constData()

extern QApplication *gp_app;

typedef qlonglong DbId;

#endif
