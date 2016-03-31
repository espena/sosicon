#include "mainfrm.h"
#include <QApplication>
#include <memory>

#pragma warning ( disable: 4996 )
#pragma warning ( disable: 4244 )
#pragma warning ( disable: 4189 )
#pragma warning ( disable: 4 )

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );
    app.addLibraryPath( "INSTALL/extdll" );
    MainFrm mainFrm;
    mainFrm.show();
    int res = app.exec();
    return res;
}
