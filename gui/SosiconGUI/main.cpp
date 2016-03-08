#include "dlgmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DlgMain w;
    w.show();

    return a.exec();
}
