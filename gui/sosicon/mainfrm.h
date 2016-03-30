#ifndef MAINFRM_H
#define MAINFRM_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QList>
#include <QUrl>
#include <QMimeData>
#include <QMutex>
#include <memory>
#include "../../src/log_event.h"

namespace Ui {
    class MainFrm;
}

class MainFrm : public QMainWindow
{
    Q_OBJECT

    QMutex mMutex;
    QString mShapeFileTitle;
    QString mShapeFilePath;

    bool mCancel;
    bool mRunFlag;

public:
    explicit MainFrm(QWidget *parent = 0);
    ~MainFrm();

private slots:
    void onSosiFileListChanged();
    void onRunSosicon();
    void onCancelSosicon();
    void onQuitSosicon();
    void onAddSosiFile();
    void onConversionChanged( int tabIndex );
    void onFileSelect();
    void onFileRemove();
    void onFileClear();
    void onLogMessage( QString msg, bool update );
    void onShapefileBrowse();
    void onCreateSubdirChanged();
    void onUseFileTitleChanged();
    void onFileTitleChanged();

private:
    void updateUi();
    void updateCommandLine();
    void updateAll();
    Ui::MainFrm *mUi;

    virtual void showEvent( QShowEvent *event );
    virtual void dragEnterEvent( QDragEnterEvent *event );
    virtual void dropEvent( QDropEvent *event );
    virtual void dragLeaveEvent( QDragLeaveEvent *event );
    virtual void dragMoveEvent( QDragMoveEvent *event );

signals:
    void startConversion( QString cmdStr, QMutex *mutex, bool* cancel );
};

#endif // MAINFRM_H
