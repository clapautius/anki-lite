#include <QSettings>

#include "main.h"
#include "anki-lite-main-wnd.h"

using namespace Ui;
using std::vector;

QApplication *gp_app = NULL;
QSettings g_settings("clapautius", "anki-lite");
AnkiLiteMainWnd *gp_main_wnd = NULL;


int main( int argc, char **argv )
{
    gp_app=new QApplication( argc, argv );
    gp_main_wnd = new AnkiLiteMainWnd();
    gp_main_wnd->show();
    gp_app->exec();
    return 0;
}
