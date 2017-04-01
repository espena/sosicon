#include "mainfrm.h"
#include <QApplication>
#include <QResource>
#include <QFont>
#include <QFontDatabase>
#include <memory>

int main( int argc, char *argv[] )
{
    QApplication::setAttribute( Qt::AA_EnableHighDpiScaling );
    QApplication app( argc, argv );
    QResource::registerResource( "sosicon.rcc" );
    QString fontPath = ":/fonts/DejaVuSansCondensed.ttf";
    int fontId = QFontDatabase::addApplicationFont( fontPath );
    if( fontId != -1 )
    {
        QFont font( "DejaVuSansCondensed" );
        app.setFont( font );
    }
    app.addLibraryPath( "INSTALL/extdll" );
    MainFrm mainFrm;
    mainFrm.show();
    int res = app.exec();
    return res;
}
