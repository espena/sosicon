#include "mainfrm.h"
#include "ui_mainfrm.h"

#include "worker.h"
#include "MainFrm.h"
#include "ui_MainFrm.h"
#include <QIcon>
#include <QColor>
#include <QThread>
#include <QTextCodec>
#include <QFileDialog>
#include <QFontMetrics>
#include <QStandardPaths>

MainFrm::MainFrm( QWidget *parent ) :
    QMainWindow( parent ),
    mUi( new Ui::MainFrm )
{
    mUi->setupUi(this);
    setWindowIcon( windowIcon() );
    mUi->setupUi( this );
    mUi->txtFileTitle->setValidator( new QRegExpValidator( QRegExp( "^[A-Za-z0-9_\\-]+$" ), this ) );
    setStyleSheet( "QListView { background-color: #fff } QListView { color: #000; } QListView::item:selected { background-color: #ff0; color: #000 }" );
    updateAll();
}

MainFrm::~MainFrm()
{
    delete mUi;
}

void MainFrm::
dragEnterEvent( QDragEnterEvent *event )
{
    if ( event->mimeData()->hasFormat( "text/uri-list" ) ) {
        event->acceptProposedAction();
    }
}

void MainFrm::
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

void MainFrm::
dragLeaveEvent( QDragLeaveEvent* event )
{
   event->accept();
}

void MainFrm::
dragMoveEvent( QDragMoveEvent *event )
{
    event->acceptProposedAction();
}


void MainFrm::
onCancelSosicon()
{
    mCancel = true;
    mUi->lstConsoleOutput->addItem( "Aborting operation" );
    int i = mUi->lstConsoleOutput->count() - 1;
    mUi->lstConsoleOutput->item( i )->setTextColor( QColor( 255, 0, 0 ) );
    mUi->lstConsoleOutput->setCurrentRow( i );
}

void MainFrm::
onRunSosicon()
{
    updateAll();
    if( !mCancel ) {
        mUi->btnCancel->setEnabled( true );
        mUi->btnRunSosicon->setEnabled( false );
        mRunFlag = true;
        QThread *thread = new QThread();
        Worker *worker = new Worker();
        connect( this, SIGNAL( startConversion( QString, QMutex*, bool* ) ), worker, SLOT( startConversion( QString, QMutex*, bool* ) ) );
        connect( worker, SIGNAL( logMessage( QString, bool ) ), this, SLOT( onLogMessage( QString, bool ) ) );
        connect( worker, SIGNAL( finished() ), this, SLOT( onQuitSosicon() ) );
        connect( worker, SIGNAL( finished() ), thread, SLOT( quit() ) );
        connect( worker, SIGNAL( finished() ), worker, SLOT( deleteLater() ) );
        connect( thread, SIGNAL( finished() ), thread, SLOT( deleteLater() ) );
        worker->moveToThread( thread );
        thread->start();
        emit startConversion( mUi->txtCommandLine->toPlainText(), &mMutex, &mCancel );
    }
}

void MainFrm::
onShapefileBrowse()
{
    QString dir = QFileDialog::getExistingDirectory( this, "Select destination directory", mShapeFilePath );
    if( !dir.isEmpty() ) {
        mShapeFilePath = dir;
        updateAll();
    }
}

void MainFrm::
onQuitSosicon()
{
    mUi->lstConsoleOutput->clearSelection();
    mUi->lstSosiFiles->clearSelection();
    mUi->btnCancel->setEnabled( false );
    mUi->btnRunSosicon->setEnabled( mUi->lstSosiFiles->count() > 0 );
    mCancel = false;
    mRunFlag = false;
}

void MainFrm::
onConversionChanged( int tabIndex )
{
    updateAll();
}

void MainFrm::
onCreateSubdirChanged()
{
    updateAll();
}

void MainFrm::
onAddSosiFile()
{
    QStringList files =
            QFileDialog::getOpenFileNames(
                this,
                tr( "Select SOSI files" ),
                tr( "" ),
                tr( "SOSI files (*.sos)" ) );
    mUi->lstSosiFiles->addItems( files );
    updateAll();
}

void MainFrm::
onFileSelect()
{
    updateAll();
}

void MainFrm::
onFileRemove()
{
    qDeleteAll( mUi->lstSosiFiles->selectedItems() );
    updateAll();
}

void MainFrm::
onFileClear()
{
    mUi->lstSosiFiles->clear();
    updateAll();
}

void MainFrm::
onLogMessage( QString msg, bool update )
{
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

void MainFrm::
onUseFileTitleChanged()
{
    updateAll();
}

void MainFrm::
onFileTitleChanged()
{
    updateCommandLine();
}

void MainFrm::
updateAll()
{
    updateUi();
    updateCommandLine();
}

void MainFrm::
updateUi()
{
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
    mUi->btnRunSosicon->setEnabled( !mRunFlag && mUi->lstSosiFiles->count() > 0 );
}

void MainFrm::
updateCommandLine()
{
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
