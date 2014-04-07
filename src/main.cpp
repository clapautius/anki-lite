#include <QSettings>
#include <QMessageBox>

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
    try {
        gp_app=new QApplication( argc, argv );
        gp_main_wnd = new AnkiLiteMainWnd();
        gp_main_wnd->show();

        // load database data
        anki_lite::AnkiDb db;
        db.open_db(".../Anki/User 1/collection.anki2"); // :todo:
        anki_lite::Collection collection = db.get_collection();

        gp_app->exec();
    }
    catch (std::exception &e) {
        QMessageBox::critical(NULL, "Error", QString("Got exception: ") + e.what());
        return 1;
    }
    return 0;
}
