#ifndef PAGES
#define PAGES

#include <QWidget>
QT_BEGIN_NAMESPACE
class QGroupBox;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
QT_END_NAMESPACE

class OptionsPage : public QWidget
{
    Q_OBJECT

    QString          mOutputFilename;

protected:

    QWidget         *mParent;

    QVBoxLayout     *mMainLayout;

    QLabel          *mHeader;

    QGroupBox       *mFilenameGroup;
    QHBoxLayout     *mFilenameLayout;
    QLabel          *mFilenameLabel;
    QPushButton     *mFilenameBrowseBtn;

public:
    OptionsPage( QWidget *parent = 0 );

public slots:
    void setOutputFilename();

};

#endif // PAGES

