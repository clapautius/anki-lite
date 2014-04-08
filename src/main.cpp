#include <QSettings>
#include <QMessageBox>
#include <QDir>

#include "main.h"
#include "anki-lite-main-wnd.h"
#include "anki-db.hpp"
#include "exceptions.hpp"

using namespace Ui;
using std::vector;

QApplication *gp_app = NULL;
QSettings g_settings("clapautius", "anki-lite");
AnkiLiteMainWnd *gp_main_wnd = NULL;


int main( int argc, char **argv )
{
    int rc = 0;
    try {
        gp_app=new QApplication( argc, argv );
        gp_main_wnd = new AnkiLiteMainWnd();
        gp_main_wnd->show();

        // load database data
        anki_lite::AnkiDb db;
        // :fixme: - read from prefs.db first
        db.open_db(QDir::homePath()+"/Anki/User 1/collection.anki2");
        anki_lite::Collection collection = db.get_collection();

        gp_app->exec();
    }
    catch (std::exception &e) {
        QMessageBox::critical(NULL, "Error", QString("Got exception: ") + e.what());
        rc = 1;
    }
    catch (...) {
        QMessageBox::critical(NULL, "Error", "Got an unknown exception. Aborting!");
        rc = 1;
    }
    delete gp_main_wnd;
    delete gp_app;
    return rc;
}
