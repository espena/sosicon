#ifndef SHAPEFILE_OPTIONS_PAGE_H
#define SHAPEFILE_OPTIONS_PAGE_H

#include <QWidget>
#include "options_page.h"

QT_BEGIN_NAMESPACE
class QListWidget;
QT_END_NAMESPACE

class ShapefileOptionsPage : public OptionsPage
{
    Q_OBJECT

    QGroupBox   *mGeometrySelectGroup;
    QVBoxLayout *mGeometrySelectLayout;
    QListWidget *mGeometrySelectList;

    void addGeometrySelection( QString displayName, QString sosiName );

public:
    ShapefileOptionsPage( QWidget *parent = 0 );
    virtual ~ShapefileOptionsPage() { }
};

#endif // SHAPEFILE_OPTIONS_PAGE_H
