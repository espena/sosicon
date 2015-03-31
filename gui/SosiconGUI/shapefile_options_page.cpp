#include "shapefile_options_page.h"
#include <QtWidgets>

ShapefileOptionsPage::ShapefileOptionsPage( QWidget *parent )
    : OptionsPage( parent )
{
    mFilenameGroup->setTitle( tr( "Output file" ) );
    mGeometrySelectList = new QListWidget;
    mMainLayout->addWidget( mGeometrySelectList );
}
