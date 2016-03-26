#include "mainfrm.h"
#include <QApplication>
#include <memory>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );
    MainFrm mainFrm;
    mainFrm.show();
    int res = app.exec();
    return res;
}
