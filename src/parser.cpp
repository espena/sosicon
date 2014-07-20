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
#include "parser.h"

sosicon::Parser::
Parser() {
    mPendingElementLevel = 0;
    mElementStack.push_back( new sosi::SosiElement( "ROOT", "", "", 0, 0, mElementIndex ) );
}

sosicon::Parser::
~Parser() {
    mElementStack.front()->deleteChildren();
    delete mElementStack.front();
}

void sosicon::Parser::
digestPendingElement() {
    ISosiElement* previousElement = mElementStack.back();
    int previousLevel = previousElement->getLevel();
    if( mPendingElementLevel > 0 ) {

        while( mElementStack.back()->getLevel() >= mPendingElementLevel ) {
            mElementStack.pop_back();
        }

        previousElement = mElementStack.back();

        mElementStack.push_back(
            new sosi::SosiElement(
                sosicon::stringUtils::trim( mPendingElementName ),
                sosicon::stringUtils::trim( mPendingElementSerial ),
                sosicon::stringUtils::trim( mPendingElementAttributes ),
                mPendingElementLevel,
                mElementStack.front(),
                mElementIndex ) );

        previousElement->addChild( mElementStack.back() );
    }
    mPendingElementName.clear();
    mPendingElementSerial.clear();
    mPendingElementAttributes.clear();
    mPendingElementLevel = 0;
}

void sosicon::Parser::
dump() {
    mElementStack.front()->dump();
}

sosicon::ISosiElement* sosicon::Parser::
getRootElement() {
    return mElementStack.front();
}