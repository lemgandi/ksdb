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

#import <qcheckbox.h>

#import "wcheckboxhandler.h"


//
// Make a label widget and return it.
//
QWidget *wCheckboxHandler::makeWidget(const QString &,QSize wSize,QPoint wLoc,const fieldVals &values)
{
   bool checked=FALSE;
   QWidget *retVal;

   if("TRUE" == values["initialValue"])
      checked=TRUE;

   QCheckBox *myBox = new QCheckBox(values["legend"],0,values["fieldName"]);
   myBox->setChecked(checked);

   retVal=myBox;
   setWidgetSizeShape(retVal,wSize,wLoc);
   return retVal;
}
