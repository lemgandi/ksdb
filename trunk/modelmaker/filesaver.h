/*
 * Save a file from the modelmaker. Make a string with our xml inside it, then
 * write the string to the named file.
 *
 */

/*
* This file is part of ksdb
* Copyright (c) Charles Shapiro Sep 2009
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

#ifndef FILESAVER_H
#define FILESAVER_H

#include <qapplication.h>
#include <qwidget.h>
#include <qstring.h>

#include "typedefs.h"
#include "screenmaker.h"

class fileSaver : public QObject
{

Q_OBJECT

public:
   fileSaver(const screenMaker *,const widgetData &,
	     const QString & fileName="",const QString &version="");
   ~fileSaver();
   const QString & getVersion();
   void setVersion(const QString &);
   const QString & getFileName();
   void setFileName(const QString &);
   const char *getSaveString();
   bool saveBG(const QString &saveFN);
   bool saveFile();
   void serialize();

protected:
   QString fileName;
   QString fileVersion;
   QString bgFileName;
   QString saveString;
   widgetData saveData;
   const screenMaker *currentScreen;
   void putSaveStartData();
   void putWidgetData(const QWidget *,const fieldVals &);
   void putSaveEndData();
};


#endif // FILESAVER_H
