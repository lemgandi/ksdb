/*
 * This is the object which contains information about each field in the 
 * database.
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
#ifndef DATAFIELD_H
#define DATAFIELD_H

#include <qmap.h>
#include <qpoint.h>
#include <qsize.h>
#include <qpair.h>

typedef QPair<QPoint,QSize> fieldLoc;

class dataField
{
 public:
   dataField();
   dataField(const QString &,const fieldLoc &);
   dataField(const dataField &);
   dataField & operator=(const dataField &);
   bool operator==(const dataField &);
   ~dataField();
   const QString & getName() const;
   const QString & setName(const QString &);
   const fieldLoc & getLoc() const;
   const fieldLoc & setLoc(const fieldLoc &);
   
 private:
   QString name;
   fieldLoc location;
   const dataField & operator+(const dataField &);
};

typedef QMap<int,dataField> dataFieldMap;

#endif
