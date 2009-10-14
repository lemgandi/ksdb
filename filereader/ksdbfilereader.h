/*
 * Read a file into modelmaker. Parse xml, create wData list.
 */
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
#ifndef FILEREADER_H
#define FILEREADER_H

#include <qapplication.h>
#include <qwidget.h>
#include <qstring.h>

#include "typedefs.h"
#include "ksdbxmlparser.h"

#include "widgethandler.h" //  for widgetHandlerDictionary definition

class QSize;
class QPixmap;


class ksdbFileReader : public QXmlDefaultHandler
{
   //   Q_OBJECT

public:
   ksdbFileReader(const QString & fileName ="",const widgetHandlerDictionary &wh=widgetHandlerDictionary() );
   ~ksdbFileReader();
   void setFileName(const QString &);
   const QString & getFileName();
   bool readFile();
   QPixmap getBGPixMap();
   const widgetData & getData();
   QSize getStartScreenSize();
   void setHandlerDictionary(const widgetHandlerDictionary &);
   const widgetHandlerDictionary &getHandlerDictionary();
   QString errorString();
   QString getVersion();
   void setVersion(QString theVersion);

 protected:

   QString readFN;
   QString currentError;
   widgetData myData;
   QSize screenSize;
   KsdbXmlParser *myParser;
   QXmlSimpleReader theReader;
};

#endif //FILEREADER_H
