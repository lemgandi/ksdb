/*
 * Implementation of datafield -- each field in the screen.
 */
/*
* This file is part of ksdb
*
*    ksdb is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    ksdb is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with ksdb.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "datafield.h"

// The null constructor
dataField::dataField()
{
   dataField("",fieldLoc(QPoint(),QSize()));
}

// The copy constructor
dataField::dataField(const dataField & other)
{
   name=other.getName();
   location=other.getLoc();
}
// Destructor
dataField::~dataField()
{
}

// Assignment from another.
dataField & dataField::operator=(const dataField &lhs)
{
   name=lhs.getName();
   location=lhs.getLoc();
   return *this;
}

// Is this equal to another?
bool dataField::operator==(const dataField &lhs)
{
   fieldLoc lhsloc=lhs.getLoc();
   QString lhsname=lhs.getName();
   bool retVal=false;
   if (lhsname == name)
   {
      if ((lhsloc.first == location.first) && (lhsloc.second == location.second))
	 retVal=true;
   }
   return retVal;
}


// Construct a dataField with values
dataField::dataField(const QString & myName,const fieldLoc & myLoc) : name(myName),location(myLoc)
{
   name=myName;
   location=myLoc;
}

// Get my name
const QString & dataField::getName() const
{
   return name;
}

//Set my name
const QString & dataField::setName(const QString &newName)
{
   name=newName;
   return name;
}

const fieldLoc & dataField::getLoc() const
{
   return location;
}

const fieldLoc & dataField::setLoc(const fieldLoc &newLoc)
{
   location=newLoc;
   return location;
}
