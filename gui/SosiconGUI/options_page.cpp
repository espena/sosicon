#include "options_page.h"
#include "utils.h"
#include <QtWidgets>

OptionsPage::OptionsPage( QWidget *parent )
    : QWidget( parent ), mParent( parent )
{
    mMainLayout = new QVBoxLayout;
    mHeader = new QLabel;

    mFilenameGroup = new QGroupBox;
    mFilenameLayout = new QHBoxLayout;
    mFilenameBrowseBtn = new QPushButton( "..." );
    mFilenameLabel = new QLabel;

    mMainLayout->addWidget( mHeader );

    mFilenameBrowseBtn->setFixedSize( 24, 24 );
    mFilenameLabel->setFixedSize( 300, 25 );
    mFilenameLabel->setFrameStyle( QFrame::Panel | QFrame::Sunken );
    mFilenameLabel->setAlignment( Qt::AlignTop );
    mFilenameLayout->addWidget( mFilenameLabel );
    mFilenameLayout->addWidget( mFilenameBrowseBtn );
    mFilenameGroup->setMaximumHeight( 80 );
    mFilenameGroup->setLayout( mFilenameLayout );
    mMainLayout->addWidget( mFilenameGroup );

    setLayout( mMainLayout );

    connect( mFilenameBrowseBtn,
             SIGNAL( clicked() ),
             this, SLOT( setOutputFilename() ) );
}

void OptionsPage::setOutputFilename()
{
    mOutputFilename = QFileDialog::getSaveFileName( mParent, tr( "Output file name" ) );
    mFilenameLabel->setText( utils::pathAbbr( mOutputFilename, 50 ) );
}
