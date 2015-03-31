#include "utils.h"
#include <QtWidgets>

QString utils::pathAbbr( QString path, int maxlen ) {
    if( path.length() > maxlen ) {
        QStringList pathParts = path.split( QRegExp( "[\\/\\\\]" ) );
        const int n = pathParts.length();
        QString tail, head = pathParts[ n - 1 ];
        for( int i = 0; i < n; i++ ) {
            if( tail.length() + pathParts[ i ].length() + head.length() < maxlen - 5 ) {
                tail += ( i == 0 ? "" : "/" ) + pathParts[ i ];
            }
            else {
                path = tail + "/../" + head;
                break;
            }
        }
    }
    return path;
}


