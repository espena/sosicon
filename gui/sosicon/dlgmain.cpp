#include "worker.h"
#include "DlgMain.h"
#include "ui_DlgMain.h"
#include <QThread>
#include <QTextCodec>
#include <QFileDialog>
#include <QFontMetrics>
#include <QStandardPaths>

DlgMain::
DlgMain( QWidget *parent ) :
    QDialog( parent ),
    mUi( new Ui::DlgMain )
{
    mUi->setupUi( this );
    setStyleSheet( "QListView { background-color: #fff } QListView { color: #000; } QListView::item:selected { background-color: #ff0; color: #000 }" );
    updateUi();
}

DlgMain::~DlgMain()
{
    delete mUi;
}

void DlgMain::
onRunSosicon() {
    QThread *thread = new QThread();
    Worker *worker = new Worker();
    connect( this, SIGNAL( startConversion( QString, QMutex* ) ), worker, SLOT( startConversion( QString, QMutex* ) ) );
    connect( worker, SIGNAL( logMessage( QString, bool ) ), this, SLOT( onLogMessage( QString, bool ) ) );
    connect( worker, SIGNAL( finished() ), this, SLOT( onQuitSosicon() ) );
    connect( worker, SIGNAL( finished() ), thread, SLOT( quit() ) );
    connect( worker, SIGNAL( finished() ), worker, SLOT( deleteLater() ) );
    connect( thread, SIGNAL( finished() ), thread, SLOT( deleteLater() ) );
    worker->moveToThread( thread );
    thread->start();
    emit startConversion( mUi->txtCommandLine->toPlainText(), &mMutex );
    this->setEnabled( false );
}

void DlgMain::
onShapefileBrowse() {
    QString dir = QFileDialog::getExistingDirectory( this, "Select destination directory", mShapeFilePath );
    if( !dir.isEmpty() ) {
        mShapeFilePath = dir;
        updateUi();
    }
}

void DlgMain::
onQuitSosicon() {
    mUi->lstConsoleOutput->clearSelection();
    mUi->lstSosiFiles->clearSelection();
    this->setEnabled( true );
}

void DlgMain::
onConversionChanged( int tabIndex ) {
    updateUi();
}

void DlgMain::
onCreateSubdirChanged() {
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
onFileSelect() {
    updateUi();
}

void DlgMain::
onFileRemove() {
    qDeleteAll( mUi->lstSosiFiles->selectedItems() );
    updateUi();
}

void DlgMain::
onFileClear() {
    mUi->lstSosiFiles->clear();
    updateUi();
}

void DlgMain::
onLogMessage( QString msg, bool update ) {
    QListWidget *lst = mUi->lstConsoleOutput;
    int n = lst->count();
    if( update && n > 0 ) {
        lst->item( n - 1 )->setText( msg );
    }
    else {
        lst->addItem( msg );
        n++;
    }
    lst->setCurrentRow( n - 1 );
    if( msg.startsWith( "Reading " ) ) {
        mUi->lstSosiFiles->clearSelection();
        QRegExp r( "^Reading (.*)$" );
        if( r.indexIn( msg ) != -1 ) {
            QList<QListWidgetItem *> items = mUi->lstSosiFiles->findItems( r.cap( 1 ), Qt::MatchExactly );
            if( items.count() > 0 ) {
                items.at( 0 )->setSelected( true );
            }
        }
    }
}

void DlgMain::
updateUi() {
    QTabWidget *tab = mUi->tabConversion;
    QFontMetrics fm( mUi->lblShapefilePath->font() );
    QString action, options, fileNames;
    QString conversion = tab->tabBar()->tabText( tab->currentIndex() );
    if( mShapeFilePath.isEmpty() ) {
        mShapeFilePath = QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation );
    }
    mUi->lblShapefilePath->setText( fm.elidedText( mShapeFilePath, Qt::TextElideMode::ElideMiddle, mUi->lblShapefilePath->width() ) );
    mUi->btnRemove->setEnabled( mUi->lstSosiFiles->selectedItems().count() > 0 );
    mUi->btnClear->setEnabled( mUi->lstSosiFiles->count() > 0 );
    mUi->btnRunSosicon->setEnabled( mUi->lstSosiFiles->count() > 0 );
    if( conversion == "PostGIS" ) {
        action = "-2psql ";
    }
    else if( conversion == "Shapefile" ) {
        action = "-2shp ";
        options = "-d \"" + mShapeFilePath + "\" ";
        if( mUi->chkCreateSubdir->checkState() == Qt::Checked ) {
            options += "-s ";
        }
    }
    for( int i = 0; i < mUi->lstSosiFiles->count(); i++ ) {
        fileNames += mUi->lstSosiFiles->item( i )->text() + " ";
    }
    mUi->txtCommandLine->setText( "sosicon " + action + options + fileNames.trimmed() );
}
