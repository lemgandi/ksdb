//
// Implementation file for widgetButtonHandler -- make label widgets from
// file data.
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
// #import <qpushbutton.h>

#import "mockeditfield.h"
#import "screenmaker.h"

#import "weditbuttonhandler.h"

wEditButtonHandler::wEditButtonHandler(const screenMaker *s) : wEditHandler(s)
{
   return;
}

//
// Make a label widget and return it.
//
QWidget *wEditButtonHandler::makeWidget(const QString &,QSize wSize,QPoint wLoc,const fieldVals &vals)
{
   QWidget *retVal = new mockPushButtonField(vals["buttonLegend"],0,vals["buttonType"]);
   setWidgetSizeShape(retVal,wSize,wLoc);
   connectWidget(retVal);

   return retVal;
}

