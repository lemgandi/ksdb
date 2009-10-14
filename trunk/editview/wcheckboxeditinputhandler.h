#ifndef WCHECKBOXINPUTHANDLER_H
#define WCHECKBOXINPUTHANDLER_H

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

class QCheckBox;

class wCheckBoxEditInputHandler : public wInputHandler
{
   Q_OBJECT
   public:
      wCheckBoxEditInputHandler(QWidget *w=0,bool defaultState=FALSE);
   public slots:
      QString getWidgetData();
      void setWidgetData(const QString &);
      void clear();
      void toggled(bool);
      void setWidget(QWidget *);

   protected:
      QCheckBox *realP; 
      QString currentText;
      bool defaultVal;
};

#endif // WCHECKBOXINPUTHANDLER_H
