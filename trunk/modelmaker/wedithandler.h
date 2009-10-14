#ifndef WEDITWHANDLER_H
#define WEDITWHANDLER_H

/*
* Copyright Charles Shapiro Sep 2009
*
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
//
// This is the ancestor class for objects which create widgets in the 
// modelmaker. It includes methods for handling and connecting to the 
// screenmaker so that we can select those objects for editing or moving.
//

#include <qapplication.h>

#include "typedefs.h"
#include "widgethandler.h"

class QWidget;
class screenMaker;


class wEditHandler : public widgetHandler
{
   Q_OBJECT
 public:
   wEditHandler(const screenMaker *s=0);
   void setScreenMaker(const screenMaker *);
   void connectWidget(QWidget *);

 protected:
   const screenMaker *theScreenMaker;
};
#endif // WEDITWHANDLER_H
