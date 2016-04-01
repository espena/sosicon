#include "mainfrm.h"
#include "ui_mainfrm.h"

#include "worker.h"
#include "MainFrm.h"
#include "ui_MainFrm.h"
#include <QSettings>
#include <QIcon>
#include <QColor>
#include <QFileInfo>
#include <QThread>
#include <QShowEvent>
#include <QTextCodec>
#include <QFileDialog>
#include <QFontMetrics>
#include <QStandardPaths>
#include <QAbstractItemModel>

MainFrm::MainFrm( QWidget *parent ) :
    QMainWindow( parent ),
    mCancel( false ),
    mRunFlag( false ),
    mUi( new Ui::MainFrm )
{
    mUi->setupUi(this);
    setWindowIcon( windowIcon() );
    mUi->setupUi( this );
    mUi->txtFileTitle->setValidator( new QRegExpValidator( QRegExp( "^[A-Za-z0-9_\\-]+$" ), this ) );
    setStyleSheet( "QListView { background-color: #fff } QListView { color: #000; } QListView::item:selected { background-color: #ff0; color: #000 }" );
    connect( mUi->lstSosiFiles->model(), SIGNAL( rowsInserted( const QModelIndex &, int, int ) ), this, SLOT( onSosiFileListChanged() ) );
    connect( mUi->lstSosiFiles->model(), SIGNAL( rowsRemoved( const QModelIndex &, int, int ) ), this, SLOT( onSosiFileListChanged() ) );
    QSettings settings( "sosicon.espenandersen.no", "Sosicon" );
    QString docPath = QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation );
    mShapeDirPath = settings.value( "mru_path_shapefile", docPath ).toString();
    mPostGisFilePath = settings.value( "mru_path_postgis", docPath + "/postgis_dump.sql" ).toString();
}

MainFrm::~MainFrm()
{
    QSettings settings( "sosicon.espenandersen.no", "Sosicon" );
    settings.setValue( "mru_path_shapefile", mUi->lblShapefilePath->text() );
    settings.setValue( "mru_path_postgis", mUi->lblPostGisPath->text() );
    delete mUi;
}

void MainFrm::
addSosiFiles( QStringList filenames ) {
    for( QStringList::iterator i = filenames.begin(); i != filenames.end(); i++ ) {
        addSosiFile( *i );
    }
}

void MainFrm::
addSosiFile( QString filename )
{
    if( mUi->lstSosiFiles->findItems( filename, Qt::MatchFixedString ).count() == 0 ) {
        mUi->lstSosiFiles->addItem( filename );
    }
}

void MainFrm::
onSosiFileListChanged()
{
    updateAll();
}

void MainFrm::
dragEnterEvent( QDragEnterEvent *event )
{
    if ( event->mimeData()->hasFormat( "text/uri-list" ) ) {
        event->acceptProposedAction();
    }
}

void MainFrm::
showEvent( QShowEvent* )
{
    updateAll();
}

void MainFrm::
dropEvent( QDropEvent *event )
{
    bool accepted;
    QList<QUrl> urls = event->mimeData()->urls();
    for( QList<QUrl>::iterator i = urls.begin(); i != urls.end(); i++ ) {
        QString filename = ( *i ).toLocalFile();
        if ( filename.endsWith( ".sos", Qt::CaseInsensitive ) ) {
            addSosiFile( filename );
            accepted = true;
        }
    }
    if( accepted ) {
        event->acceptProposedAction();
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
    QString dir = QFileDialog::getExistingDirectory( this, "Select destination directory", mShapeDirPath );
    if( !dir.isEmpty() ) {
        mShapeDirPath = dir;
        updateAll();
    }
}

void MainFrm::
onPostGisBrowse()
{
    QFileDialog dlg( this );
    dlg.setDefaultSuffix( "sql" );
    QString file = dlg.getSaveFileName( this, "Select output file", QFileInfo( mPostGisFilePath ).path(), "PostgreSQL files (*.sql *.dump)" );
    if( !file.isEmpty() ) {
        mPostGisFilePath = file;
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
onConversionChanged( int )
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
    addSosiFiles( files );
}

void MainFrm::
onFileSelect()
{
    updateUi();
}

void MainFrm::
onFileRemove()
{
    qDeleteAll( mUi->lstSosiFiles->selectedItems() );
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
    if( mShapeDirPath.isEmpty() ) {
        mShapeDirPath = QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation );
    }
    mUi->lblShapefilePath->setText( fm.elidedText( mShapeDirPath, Qt::TextElideMode::ElideMiddle, mUi->lblShapefilePath->width() ) );
    if( mPostGisFilePath.isEmpty() ) {
        mPostGisFilePath = QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation ) + "/postgis_dump.sql";
    }
    mUi->lblPostGisPath->setText( fm.elidedText( mPostGisFilePath, Qt::TextElideMode::ElideMiddle, mUi->lblPostGisPath->width() ) );
    mUi->btnRemove->setEnabled( mUi->lstSosiFiles->selectedItems().count() > 0 );
    mUi->btnClear->setEnabled( mUi->lstSosiFiles->count() > 0 );
    mUi->btnRunSosicon->setEnabled( ( mRunFlag == false ) && ( mUi->lstSosiFiles->count() > 0 ) );
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
        action = "-2psql -o " + mPostGisFilePath + " ";
    }
    else if( conversion == "Shapefile" ) {
        action = "-2shp ";
        if( mUi->chkFileTitle->checkState() == Qt::Checked ) {
            options = "-o \"" + mShapeDirPath + "/" + mShapeFileTitle  + ".shp\" ";
        }
        else {
            options = "-d \"" + mShapeDirPath + "\" ";
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
