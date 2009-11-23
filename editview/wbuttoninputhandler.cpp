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

#include <qpushbutton.h>

#include "wbuttoninputhandler.h"

//
// Create.
//
wButtonInputHandler::wButtonInputHandler(QWidget *w,QWidget *r,const fieldVals & md) : wInputHandler(w)
{

   receiver=r;
   metaData=md;

   // Order is important here. The other fields must be set up before the
   // call to setWidget.

   setWidget(w);
}

//
// Dump metadata to debug.
//
void wButtonInputHandler::dumpMData()
{
   qDebug("Dumping data for %p containing %d items",&metaData,metaData.count());
   fieldVals::ConstIterator iter;
   for(iter=metaData.constBegin(); iter != metaData.constEnd();++iter)   
      qDebug("K=%s  V=%s",(const char *)iter.key(),(const char *)iter.data());
}

//
// Set up my connections to mainwindow. Which connection I set up depends on
// my buttonType.
//
void wButtonInputHandler::setupConnections()
{
   qDebug("setupConnections");
   QString buttonType=metaData["buttonType"];

   if ("Prev" == buttonType) 
      connect(realP,SIGNAL(clicked()),receiver,SLOT(Prev()));   
   else if ("Next" == buttonType)
      connect(realP,SIGNAL(clicked()),receiver,SLOT(Next()));
   else if ("Search" == buttonType)
      connect(realP,SIGNAL(clicked()),receiver,SLOT(Search()));
   else if ("First" == buttonType)
      connect(realP,SIGNAL(clicked()),receiver,SLOT(First()));
   else if ("Last" == buttonType)
      connect(realP,SIGNAL(clicked()),receiver,SLOT(Last()));
   else if ("Clear" == buttonType)
      connect(realP,SIGNAL(clicked()),receiver,SLOT(clearScreen()));
   else if ("Write" == buttonType)
      connect(realP,SIGNAL(clicked()),receiver,SLOT(writeRecord()));
   else if ("Delete" == buttonType)
      connect(realP,SIGNAL(clicked()),receiver,SLOT(delRecord()));
   else if ("Unorder" == buttonType)
      connect(realP,SIGNAL(clicked()),receiver,SLOT(unOrderDB()));
   else // Quit == buttonType or defailt
      connect(realP,SIGNAL(clicked()),receiver,SLOT(Quit()));

   return;
}

//
// Set current widget pointer -- make sure it is a QPushButton,connect
// pushed to various signals it so we can control screens.
//
void wButtonInputHandler::setWidget(QWidget *w)
{
   wInputHandler::setWidget(w);
   if(w) 
   {
      realP=dynamic_cast<QPushButton *>(inputWidget);   
      Q_ASSERT(realP > 0);
   }
   setupConnections();
}


//
// Clear field.
//
void wButtonInputHandler::clear()
{
   Dirty=FALSE;
}

void wButtonInputHandler::setWidgetData(const QString &)
{
   Q_ASSERT(realP != 0);
}

//
// What has been entered?
//
QString wButtonInputHandler::getWidgetData()
{
   Q_ASSERT(realP != 0);
   return(QString(""));
}
