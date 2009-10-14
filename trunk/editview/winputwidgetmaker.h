#ifndef  WINPUTWIDGETMAKER_H
#define WINPUTWIDGETMAKER_H

//
// Ancestor class for reading widget out of a file and assigning a
// winputhandler to it.
//

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
#import <qmainwindow.h>


#import "widgethandler.h"
#import "winputhandler.h"

class wInputWidgetMaker : public widgetHandler
{
 Q_OBJECT
 public:
   wInputWidgetMaker(QWidget *, inputHandlerList *);
 // Implemented in my descendents, but I just take the one in widgetHandler.
 // virtual QWidget *makeWidget(const QString &,QSize,QPoint,const fieldVals &)

 protected:
   QWidget *parentScreen;
   inputHandlerList *outInputHandlers;
};
#endif  // WINPUTWIDGETMAKER_H

