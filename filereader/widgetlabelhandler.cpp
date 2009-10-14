//
// Implementation file for widgetlabelHandler -- make label widgets from
// file data.
//

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

#import <qlabel.h>

#import "widgetlabelhandler.h"

widgetLabelHandler::widgetLabelHandler() : widgetHandler()
{
   return;
}

widgetLabelHandler::~widgetLabelHandler()
{
   return;
}

//
// Make a label widget and return it.
//
QWidget *widgetLabelHandler::makeWidget(const QString &,QSize wSize,QPoint wLoc,const fieldVals &values)
{
   QWidget *retVal = new QLabel(values["labelText"],0);
   setWidgetSizeShape(retVal,wSize,wLoc);
   return retVal;
}
