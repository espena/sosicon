#ifndef DLGMAIN_H
#define DLGMAIN_H

#include <QDialog>

class ShapefileOptionsPage;

QT_BEGIN_NAMESPACE
class QGroupBox;
class QHBoxLayout;
class QVBoxLayout;
class QListWidget;
class QPushButton;
class QStackedWidget;
QT_END_NAMESPACE

class DlgMain : public QDialog
{
    Q_OBJECT

    QHBoxLayout             *mMainLayout;

    QPushButton             *mSourceFileAddBtn;
    QGroupBox               *mSourceFileGroup;
    QVBoxLayout             *mSourceFileLayout;
    QListWidget             *mSourceFileList;
    QPushButton             *mSourceFileRemBtn;

    QGroupBox               *mConversionGroup;
    QHBoxLayout             *mConversionLayout;
    QListWidget             *mConversionList;
    QStackedWidget          *mConversionPages;

    ShapefileOptionsPage    *mShapefileOptionsPage;

    QVBoxLayout             *mOutputLayout;
    QGroupBox               *mOutputGroup;
    QPushButton             *mOutputStartBtn;

    QString pathAbbr( QString path, int maxlen );
    void updateGUI();

public:
    DlgMain(QWidget *parent = 0);
    ~DlgMain();

public slots:
    void addInputFiles();
    void remInputFiles();
    void sourceFileSelectionChanged();
};

#endif // DLGMAIN_H
