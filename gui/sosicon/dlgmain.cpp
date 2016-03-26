#include "worker.h"
#include "DlgMain.h"
#include "ui_DlgMain.h"
#include <QIcon>
#include <QThread>
#include <QTextCodec>
#include <QFileDialog>
#include <QFontMetrics>
#include <QStandardPaths>

DlgMain::
DlgMain( QWidget *parent ) :
    QDialog( parent ),
    mUi( new Ui::DlgMain ) {
    setWindowIcon( windowIcon() );
    mUi->setupUi( this );
    mUi->txtFileTitle->setValidator( new QRegExpValidator( QRegExp( "^[A-Za-z0-9_\\-]+$" ), this ) );
    setStyleSheet( "QListView { background-color: #fff } QListView { color: #000; } QListView::item:selected { background-color: #ff0; color: #000 }" );
    updateAll();
}

DlgMain::~DlgMain() {
    delete mUi;
}

void DlgMain::
dragEnterEvent( QDragEnterEvent *event ) {
    if ( event->mimeData()->hasFormat( "text/uri-list" ) ) {
        event->acceptProposedAction();
    }
}

void DlgMain::
dropEvent( QDropEvent *event )
{
    bool accepted;
    QList<QUrl> urls = event->mimeData()->urls();
    for( QList<QUrl>::iterator i = urls.begin(); i != urls.end(); i++ ) {
        QString fileName = ( *i ).toLocalFile();
        if ( fileName.endsWith( ".sos", Qt::CaseInsensitive ) ) {
            mUi->lstSosiFiles->addItem( fileName );
            accepted = true;
        }
    }
    if( accepted ) {
        event->acceptProposedAction();
        updateAll();
    }
}

void DlgMain::
dragLeaveEvent( QDragLeaveEvent* event )
{
   event->accept();
}

void DlgMain::
dragMoveEvent( QDragMoveEvent *event )
{
    event->acceptProposedAction();
}

void DlgMain::
onRunSosicon() {
    updateAll();
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
        updateAll();
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
    updateAll();
}

void DlgMain::
onCreateSubdirChanged() {
    updateAll();
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
    updateAll();
}

void DlgMain::
onFileSelect() {
    updateAll();
}

void DlgMain::
onFileRemove() {
    qDeleteAll( mUi->lstSosiFiles->selectedItems() );
    updateAll();
}

void DlgMain::
onFileClear() {
    mUi->lstSosiFiles->clear();
    updateAll();
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
onUseFileTitleChanged() {
    updateAll();
}

void DlgMain::
onFileTitleChanged() {
    updateCommandLine();
}

void DlgMain::
updateAll() {
    updateUi();
    updateCommandLine();
}

void DlgMain::
updateUi() {
    QFontMetrics fm( mUi->lblShapefilePath->font() );
    mShapeFileTitle = mUi->txtFileTitle->text().trimmed();
    if( mShapeFileTitle.isEmpty() ) {
        mShapeFileTitle = "sosi_export";
    }
    mUi->txtFileTitle->setEnabled( mUi->chkFileTitle->checkState() == Qt::Checked );
    if( mShapeFilePath.isEmpty() ) {
        mShapeFilePath = QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation );
    }
    mUi->lblShapefilePath->setText( fm.elidedText( mShapeFilePath, Qt::TextElideMode::ElideMiddle, mUi->lblShapefilePath->width() ) );
    mUi->btnRemove->setEnabled( mUi->lstSosiFiles->selectedItems().count() > 0 );
    mUi->btnClear->setEnabled( mUi->lstSosiFiles->count() > 0 );
    mUi->btnRunSosicon->setEnabled( mUi->lstSosiFiles->count() > 0 );
}

void DlgMain::
updateCommandLine() {
    QString action, options, fileNames;
    QString conversion = mUi->tabConversion->tabBar()->tabText( mUi->tabConversion->currentIndex() );

    mShapeFileTitle = mUi->txtFileTitle->text().trimmed();
    if( mShapeFileTitle.isEmpty() ) {
        mShapeFileTitle = "sosi_export";
    }

    if( conversion == "PostGIS" ) {
        action = "-2psql ";
    }
    else if( conversion == "Shapefile" ) {
        action = "-2shp ";
        if( mUi->chkFileTitle->checkState() == Qt::Checked ) {
            options = "-o \"" + mShapeFilePath + "/" + mShapeFileTitle  + ".shp\" ";
        }
        else {
            options = "-d \"" + mShapeFilePath + "\" ";
        }
        if( mUi->chkCreateSubdir->checkState() == Qt::Checked ) {
            options += "-s ";
        }
    }
    for( int i = 0; i < mUi->lstSosiFiles->count(); i++ ) {
        fileNames += mUi->lstSosiFiles->item( i )->text() + " ";
    }
    mUi->txtCommandLine->setText( "sosicon " + action + options + fileNames.trimmed() );
}
