#include "shape_header.h"

sosicon::shape::ShapeHeader::
ShapeHeader() {
    mFileCode.i   = 9994;
    mFileLength.i = 0;
    mVersion.i    = 1000;
    mShapeType.t  = geom::none;
}

sosicon::shape::geom::ShapeType sosicon::shape::ShapeHeader::
shapeTypeFromSosiType( sosi::ElementType sosiType ) {

    geom::ShapeType t;

    switch( sosiType ) {

        case sosi::sosi_element_flate:
            t = geom::polygon;
            break;

        case sosi::sosi_element_punkt:
            t = geom::point;
            break;

        default:
            t = geom::none;
            break;
    }

    return t;
}

void sosicon::shape::ShapeHeader::
writeBinary( std::ostream &os ) {
    char header[ 100 ] = { 0x00 };
    byteOrder::toBigEndian    ( mFileCode.b,          header,      4 );
    byteOrder::toBigEndian    ( mFileLength.b,        header + 24, 4 );
    byteOrder::toLittleEndian ( mVersion.b,           header + 28, 4 );
    byteOrder::toLittleEndian ( mShapeType.b,         header + 32, 4 );
    byteOrder::toLittleEndian ( mBoundingBox.mXmin.b, header + 36, 8 );
    byteOrder::toLittleEndian ( mBoundingBox.mYmin.b, header + 44, 8 );
    byteOrder::toLittleEndian ( mBoundingBox.mXmax.b, header + 52, 8 );
    byteOrder::toLittleEndian ( mBoundingBox.mYmax.b, header + 60, 8 );
    byteOrder::toLittleEndian ( mBoundingBox.mZmin.b, header + 68, 8 );
    byteOrder::toLittleEndian ( mBoundingBox.mZmax.b, header + 76, 8 );
    byteOrder::toLittleEndian ( mBoundingBox.mMmin.b, header + 84, 8 );
    byteOrder::toLittleEndian ( mBoundingBox.mMmax.b, header + 92, 8 );
    os.write( header, sizeof( header ) );
}