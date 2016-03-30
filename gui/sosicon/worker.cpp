#include "worker.h"
#include <iostream>
#include <sstream>

void::Worker::
startConversion( QString cmdStr, QMutex *mutex, bool *cancel ) {
    mutex->lock();
    std::stringstream ssIn, ssOut;
    std::streambuf* realCin = std::cin.rdbuf( ssIn.rdbuf() );
    std::streambuf* realCout = std::cout.rdbuf( ssOut.rdbuf() );
    sosicon::CommandLine cmd;
    cmd.parse( cmdStr.toStdString() );
    sosicon::logstream.addEventListener( this );
    try {
        sosicon::IConverter* converter = 0;
        sosicon::Factory::get( converter, &cmd );
        if( converter ) {
            converter->run( cancel );
            sosicon::Factory::release( converter );
        }
        if( *cancel ) {
            sosicon::logstream << "\r*** Conversion aborted by the user! ***\n";
        }
        else {
            sosicon::logstream << "*** Conversion completed! ***\n";
        }
    }
    catch( std::exception ex ) {
        sosicon::logstream << ex.what() << "\n";
    }
    sosicon::logstream.removeEventListener( this );
    emit finished();
    std::cout.rdbuf( realCout );
    std::cin.rdbuf( realCin );
    mutex->unlock();
}

void Worker::
onEvent( sosicon::LogEvent& e, sosicon::EventDispatcher<sosicon::LogEvent>& d ) {
    emit logMessage( QString::fromLatin1( e.mMessage.c_str() ), e.mUpdate );
}
