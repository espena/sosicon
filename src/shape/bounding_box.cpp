/*
 *  This file is part of the command-line tool sosicon.
 *  Copyright (C) 2012  Espen Andersen
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "bounding_box.h"

sosicon::shape::BoundingBox::
BoundingBox() {
    mXmin.d = std::numeric_limits<double>::max();
    mXmax.d = std::numeric_limits<double>::min();
    mYmin.d = std::numeric_limits<double>::max();
    mYmax.d = std::numeric_limits<double>::min();
}

void sosicon::shape::BoundingBox::
merge( IRectangle& rect ) {
    mXmin.d = std::min( rect.left(), mXmin.d );
    mXmax.d = std::max( rect.right(), mXmax.d );
    mYmin.d = std::min( rect.top(), mYmin.d );
    mYmax.d = std::max( rect.bottom(), mYmax.d );
}