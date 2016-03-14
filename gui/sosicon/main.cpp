#include "dlgmain.h"
#include <QApplication>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );
    DlgMain dlg;
    dlg.show();
    int res = app.exec();
    return res;
}
