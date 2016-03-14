#ifndef DLGMAIN_H
#define DLGMAIN_H

#include <QDialog>

namespace Ui {
    class DlgMain;
}

class DlgMain : public QDialog
{
    Q_OBJECT

public:
    explicit DlgMain( QWidget *parent = 0 );
    ~DlgMain();

private slots:
    void onRunSosicon();
    void onAddSosiFile();
    void onConversionChanged( int tabIndex );

private:
    void updateUi();
    Ui::DlgMain *mUi;
};

#endif // DLGMAIN_H
