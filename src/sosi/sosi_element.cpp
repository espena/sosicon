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
#include "sosi_element.h"

//std::vector<std::string> sosicon::sosi::SosiElement::mReferences;

sosicon::sosi::SosiElement::
SosiElement() { }

sosicon::sosi::SosiElement::
~SosiElement() { }

void sosicon::sosi::SosiElement::
set( const std::string& key, const std::string& val ) {
  mData[ key ] = val;
}

void sosicon::sosi::SosiElement::
append( const std::string& key, char val ) {

  if( key == "ref" ) {
    if( ':' == val ) {
      if( mReferences.size() > 0 ) {
        std::cout << "References for ID " << mData[ "id" ] << "\n";
        std::cout << mReferences.back();
        std::cout << "\n\n";
      }
      mReferences.push_back( "" );
    }
    else if( ' ' != val ) {
      mReferences.back() += val;
    }
  }
  else {
    mData[ key ] += val;
  }
}

std::string sosicon::sosi::SosiElement::
getData( const char* key ) {
    return mData.find( key ) != mData.end() ? mData[ key ] : "";
}

std::vector<std::string>& sosicon::sosi::SosiElement::
getFields() {
  mFields.clear();
  for( std::map<std::string, std::string>::iterator i = mData.begin(); i != mData.end(); i++ ) {
    mFields.push_back( i->first );
  }
  return mFields;
}

std::string sosicon::sosi::SosiElement::
getType() {
  return "SOSI ELEMENT";
}
