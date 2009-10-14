// Implementation of wlineeditinputhandler

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

#include <qcheckbox.h>

#include "wcheckboxeditinputhandler.h"

wCheckBoxEditInputHandler::wCheckBoxEditInputHandler(QWidget *w,bool df) : wInputHandler(w)
{
   setWidget(w);
   defaultVal=df;
}

//
// Set current widget pointer -- make sure it is a QLineEdit,connect
// textChanged to this() so we can get input.
//
void wCheckBoxEditInputHandler::setWidget(QWidget *w)
{
   wInputHandler::setWidget(w);
   if(w) {
      realP=dynamic_cast<QCheckBox *>(inputWidget);
      Q_ASSERT(realP > 0);
      connect(realP,SIGNAL(toggled(bool)),this,SLOT(toggled(bool)));
   }

   //Q_ASSERT(if(w) realP && w);
   
}

void wCheckBoxEditInputHandler::toggled(bool st)
{
   if(st)
      currentText="1";
   else
      currentText="0";
   Dirty=TRUE;
}
//
// Clear field.
//
void wCheckBoxEditInputHandler::clear()
{
   realP->setChecked(defaultVal);
   Dirty=FALSE;
}

void wCheckBoxEditInputHandler::setWidgetData(const QString &input)
{
   Q_ASSERT(realP != 0);
   bool trueFalse=FALSE;

   if("1" == input)
      trueFalse=TRUE;
   realP->setChecked(trueFalse);

   Dirty=FALSE;
}

//
// What has been entered?
//
QString wCheckBoxEditInputHandler::getWidgetData()
{
   Q_ASSERT(realP != 0);

   return(currentText);
}
