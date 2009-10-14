#ifndef WLINEEDITINPUTHANDLER_H
#define WLINEEDITINPUTHANDLER_H

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

#include "winputhandler.h"

class QLineEdit;

class wLineEditInputHandler : public wInputHandler
{
   Q_OBJECT
   public:
      wLineEditInputHandler(QWidget *w=0);
   public slots:
      QString getWidgetData();
      void setWidgetData(const QString &);
      void clear();
      void textChanged(const QString &);
      void setWidget(QWidget *);

   protected:
      QLineEdit *realP; 
      QString currentText;
};

#endif // WLINEEDITINPUTHANDLER_H
