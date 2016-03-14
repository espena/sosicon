#include "DlgMain.h"
#include "ui_DlgMain.h"
#include "../../src/command_line.h"
#include "../../src/factory.h"
#include "../../src/interface/i_converter.h"
#include <QFileDialog>
#include <exception>
#include <ios>
#include <iostream>
#include <locale>

DlgMain::
DlgMain( QWidget *parent ) :
    QDialog( parent ),
    mUi( new Ui::DlgMain )
{
    mUi->setupUi( this );
    updateUi();
}

DlgMain::~DlgMain()
{
    delete mUi;
}

void DlgMain::
onRunSosicon() {
    sosicon::CommandLine cmd;
    cmd.parse( mUi->txtCommandLine->toPlainText().toStdString() );
    try {
        sosicon::IConverter* converter = 0;
        sosicon::Factory::get( converter, &cmd );
        if( converter ) {
            converter->run();
            sosicon::Factory::release( converter );
        }
    }
    catch( std::exception ex ) {
        sosicon::cout << ex.what() << "\n";
    }
}

void DlgMain::
onConversionChanged( int tabIndex ) {
    updateUi();
}

void DlgMain::
onAddSosiFile() {
    QStringList files =
            QFileDialog::getOpenFileNames(
                this,
                tr( "Select SOSI files" ),
                tr( "" ),
                tr( "SOSI files (*.sos)" ) );
    mUi->lstSosiFiles->addItems( files );
    updateUi();
}

void DlgMain::
updateUi() {
    QTabWidget *tab = mUi->tabConversion;
    QString action = " ";
    QString conversion = tab->tabBar()->tabText( tab->currentIndex() );
    if( conversion == "PostGIS" ) {
        action = "-2psql ";
    }
    else if( conversion == "Shapefile" ) {
        action = "-2shp ";
    }
    QString fileNames = tr( "" );
    for( int i = 0; i < mUi->lstSosiFiles->count(); i++ ) {
        fileNames += mUi->lstSosiFiles->item( i )->text() + " ";
    }
    mUi->txtCommandLine->setText( tr( "sosicon " ) + action + fileNames.trimmed() );
}
