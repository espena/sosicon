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

    QListWidget *mGeometrySelectList;

public:
    ShapefileOptionsPage( QWidget *parent = 0 );
};

#endif // SHAPEFILE_OPTIONS_PAGE_H

