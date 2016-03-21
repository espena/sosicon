#include "worker.h"

void::Worker::
startConversion( QString cmdStr, QMutex *mutex ) {
    mutex->lock();
    sosicon::CommandLine cmd;
    cmd.parse( cmdStr.toStdString() );
    sosicon::logstream.addEventListener( this );
    try {
        sosicon::IConverter* converter = 0;
        sosicon::Factory::get( converter, &cmd );
        if( converter ) {
            converter->run();
            sosicon::Factory::release( converter );
        }
        sosicon::logstream << "*** Conversion completed! ***\n";
    }
    catch( std::exception ex ) {
        sosicon::logstream << ex.what() << "\n";
    }
    sosicon::logstream.removeEventListener( this );
    emit finished();
    mutex->unlock();
}

void Worker::
onEvent( sosicon::LogEvent& e, sosicon::EventDispatcher<sosicon::LogEvent>& d ) {
    emit logMessage( QString::fromLatin1( e.mMessage.c_str() ), e.mUpdate );
}
