// Implementation of base widgethandler -- 
// make a widget if we do not know what it is.

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


#include <qwidget.h>
#include <qframe.h>

#include "widgethandler.h"
#include "typedefs.h"


widgetHandler::widgetHandler() : QObject()
{
   return;
}

void widgetHandler::setWidgetSizeShape(QWidget *wp,QSize wSize,QPoint wLoc)
{
   wp->resize(wSize);
   wp->move(wLoc);
}

//
// Make a widget.
//
QWidget * widgetHandler::makeWidget(const QString &wTypeName,QSize wSize,QPoint wLoc, const fieldVals &)
{
   QWidget * retVal=new QFrame(0,wTypeName,0);
   setWidgetSizeShape(retVal,wSize,wLoc);
   return retVal;
}
