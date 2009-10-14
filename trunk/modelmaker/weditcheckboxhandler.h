#ifndef WEDITCHECKBOXHANDLER_H
#define WEDITCHECKBOXHANDLER_H
// Create a label widget from widget data (e.g. read from disk)

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
#include "typedefs.h"
#include "wedithandler.h"

class QWidget;
class screenMaker;

class wEditCheckboxHandler : public wEditHandler
{
 Q_OBJECT
 public:
   wEditCheckboxHandler(const screenMaker *s=0);
   QWidget *makeWidget(const QString &,QSize,QPoint,const fieldVals &);
};


#endif // WEDITCHECKBOXHANDLER_H

