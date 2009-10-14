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
#include <cstring>
#include <qlineedit.h>

#include "wlineeditinputhandler.h"

wLineEditInputHandler::wLineEditInputHandler(QWidget *w) : wInputHandler(w)
{
   setWidget(w);
}

//
// Set current widget pointer -- make sure it is a QLineEdit,connect
// textChanged to this() so we can get input.
//
void wLineEditInputHandler::setWidget(QWidget *w)
{
   wInputHandler::setWidget(w);
   if(w) {
      realP=dynamic_cast<QLineEdit *>(inputWidget);
      Q_ASSERT(realP > 0);
      connect(realP,SIGNAL(textChanged(const QString &)),this,SLOT(textChanged(const QString &)));
   }

   //Q_ASSERT(if(w) realP && w);
   
}

void wLineEditInputHandler::textChanged(const QString &newText)
{
   currentText=newText;
   Dirty=TRUE;
}
//
// Clear field.
//
void wLineEditInputHandler::clear()
{
   realP->setText("");
   Dirty=FALSE;
}

void wLineEditInputHandler::setWidgetData(const QString &input)
{
   Q_ASSERT(realP != 0);
   realP->setText(input);
   Dirty=FALSE;
}

//
// What has been entered?
//
QString wLineEditInputHandler::getWidgetData()
{
   Q_ASSERT(realP != 0);
   return(currentText);
}
