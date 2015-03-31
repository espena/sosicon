#include "dlgmain.h"
#include "shapefile_options_page.h"
#include "utils.h"
#include <QtWidgets>

DlgMain::DlgMain(QWidget *parent)
    : QDialog( parent )
{

    mMainLayout = new QHBoxLayout;

    mSourceFileLayout = new QVBoxLayout;
    mSourceFileGroup = new QGroupBox( tr( "SOSI source files" ) );
    mSourceFileList = new QListWidget;
    mSourceFileAddBtn = new QPushButton( tr( "Add" ), this );
    mSourceFileRemBtn = new QPushButton( tr( "Remove" ), this );

    mConversionGroup = new QGroupBox( tr( "Conversion" ) );
    mConversionLayout = new QHBoxLayout;
    mConversionList = new QListWidget;
    mConversionPages = new QStackedWidget;

    mShapefileOptionsPage = new ShapefileOptionsPage( this );

    mOutputGroup = new QGroupBox( tr( "Output" ) );
    mOutputLayout = new QVBoxLayout;
    mOutputStartBtn = new QPushButton( tr( "Start" ), this );

    mSourceFileList->setSelectionMode( QAbstractItemView::ExtendedSelection );
    mSourceFileRemBtn->setEnabled( false );
    mSourceFileLayout->addWidget( mSourceFileList );
    mSourceFileLayout->addWidget( mSourceFileAddBtn );
    mSourceFileLayout->addWidget( mSourceFileRemBtn );
    mSourceFileGroup->setMaximumWidth( 300 );
    mSourceFileGroup->setLayout( mSourceFileLayout );
    mMainLayout->addWidget( mSourceFileGroup );

    mConversionList->setViewMode( QListView::IconMode );
    mConversionList->setIconSize( QSize(50, 50 ) );
    mConversionList->setMovement( QListView::Static );
    mConversionList->setSpacing( 12 );
    mConversionList->setMaximumWidth( 100 );
    mConversionPages->addWidget( mShapefileOptionsPage );
    mConversionLayout->addWidget( mConversionList );
    mConversionLayout->addWidget( mConversionPages );
    mConversionGroup->setLayout( mConversionLayout );
    mMainLayout->addWidget( mConversionGroup );

    mMainLayout->addWidget( mOutputGroup );
    mOutputLayout->addWidget( mOutputStartBtn );
    mOutputGroup->setLayout( mOutputLayout );

    setWindowTitle( tr( "Sosicon conversion tool" ) );
    setLayout( mMainLayout );

    connect( mSourceFileAddBtn,
             SIGNAL( clicked() ),
             this, SLOT( addInputFiles() ) );

    connect( mSourceFileRemBtn,
             SIGNAL( clicked() ),
             this, SLOT( remInputFiles() ) );

    connect( mSourceFileList,
             SIGNAL( itemClicked( QListWidgetItem* ) ),
             this, SLOT( sourceFileSelectionChanged() ) );
}

DlgMain::~DlgMain()
{

}

void DlgMain::addInputFiles() {
    QStringList inputFiles = QFileDialog::getOpenFileNames(
                this,
                tr( "Select SOSI source files" ),
                0,
                tr("SOSI (*.sos);; All files (*.*)" ) );
    for( int i = 0; i < inputFiles.length(); i++ ) {
        QListWidgetItem *item = new QListWidgetItem;
        item->setData( Qt::UserRole, inputFiles[ i ] );
        item->setText( utils::pathAbbr( inputFiles[ i ], 35 ) );
        mSourceFileList->addItem( item );
    }
}

void DlgMain::remInputFiles() {
    qDeleteAll( mSourceFileList->selectedItems() );
    updateGUI();
}

void DlgMain::sourceFileSelectionChanged() {
    updateGUI();
}

void DlgMain::updateGUI() {
    mSourceFileRemBtn->setEnabled( mSourceFileList->selectedItems().length() > 0 );
}
