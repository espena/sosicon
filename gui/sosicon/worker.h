#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QMutex>
#include <exception>
#include "../../src/command_line.h"
#include "../../src/factory.h"
#include "../../src/logger.h"
#include "../../src/log_event.h"
#include "../../src/interface/i_converter.h"
#include <ios>
#include <iostream>
#include <locale>

class Worker :
        public QObject,
        public sosicon::LogEventDispatcher::Listener {

    Q_OBJECT

    QString mCmdStr;

public:
    virtual void onEvent( sosicon::LogEvent& e, sosicon::EventDispatcher<sosicon::LogEvent>& d );

public slots:
    void startConversion( QString cmdStr, QMutex *mutex, bool *cancel );

signals:
    void logMessage( QString msg, bool update );
    void finished();
};

#endif // WORKER_H
