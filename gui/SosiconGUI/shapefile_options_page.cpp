#include "shapefile_options_page.h"
#include <QtWidgets>

ShapefileOptionsPage::ShapefileOptionsPage( QWidget *parent )
    : OptionsPage( parent )
{
    mGeometrySelectList = new QListWidget;
    mGeometrySelectGroup = new QGroupBox( tr( "Geometry types to export" ) );
    mGeometrySelectLayout = new QVBoxLayout;

    mFilenameGroup->setTitle( tr( "Output file" ) );
    mGeometrySelectList->setMaximumHeight( 80 );
    mGeometrySelectList->setStyleSheet(" QListWidget { padding-top: 5px;}");
    mGeometrySelectGroup->setMaximumHeight( 120 );
    mGeometrySelectLayout->addWidget( mGeometrySelectList );
    mGeometrySelectGroup->setLayout( mGeometrySelectLayout );
    mMainLayout->addWidget( mGeometrySelectGroup );

    addGeometrySelection( tr( "Point" ), "PUNKT" );
    addGeometrySelection( tr( "Curves" ), "KURVE" );
    addGeometrySelection( tr( "Polygons" ), "FLATE" );
}

void ShapefileOptionsPage::addGeometrySelection( QString displayName, QString sosiName )
{
    QListWidgetItem *item = new QListWidgetItem( displayName, mGeometrySelectList );
    item->setData( Qt::UserRole, sosiName );
    item->setFlags( item->flags() | Qt::ItemIsUserCheckable );
    item->setCheckState( Qt::Unchecked );
}
