#ifndef WINPUTHANDLER_H
#define WINPUTHANDLER_H

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

// Widget input handler ancestor class. These classes receive signals from
// input fields (e.g. checkboxes, text edit fields) and hold the information 
// entered. You need one object for each widget on a page.

#include <qptrlist.h>

#include <qobject.h>

class QWidget;

class wInputHandler : public QObject
{
   Q_OBJECT
   public:
      wInputHandler(QWidget *w=0);

   public slots:
      bool hasData();
      virtual void setWidget(QWidget *);
      QWidget *getWidget();
      virtual QString getWidgetData()=0;
      virtual void setWidgetData(const QString &)=0;
      virtual void clear()=0;

 protected:
      QWidget *inputWidget;
      bool Dirty;
};

typedef QPtrList<wInputHandler> inputHandlerList;
typedef QPtrListIterator<wInputHandler> inputHandlerIterator;

#endif //WINPUTHANDLER_H
