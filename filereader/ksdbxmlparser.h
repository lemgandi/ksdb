#ifndef KSDBXMLPARSER_H
#define KSDBXMLPARSER_H

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
#include <qxml.h>
#include <qstring.h>
#include <qsize.h>
#include "widgethandler.h"
#include "typedefs.h"

class QString;
class QSize;
class QPoint;

class KsdbXmlParser : public QXmlDefaultHandler
{

 public:
   KsdbXmlParser(widgetData *outData,QSize *scrSize);
   ~KsdbXmlParser();
   bool startDocument();
   bool startElement( const QString &,const QString &,const QString & ,
		      const QXmlAttributes &);
   bool endElement( const QString &,const QString &,const QString &);
   bool characters( const QString &);
   bool endDocument();
   QString errorString();
   QString getBGFN();
   void setWHandlers(const widgetHandlerDictionary &);
   const widgetHandlerDictionary & getWHandlers();
   void setVersion(QString newVer);
   QString getVersion();

 protected:
   QString correctVersion;
   bool setupWidget();
   bool clearWFields();
   void dumpCurrentFieldVals();
   QSize *screenSizep;
   QWidget *currentWidget;
   QString bgFN;
   QSize wSize;
   QPoint wLoc;
   fieldVals wVals;
   widgetData *theDatap;
   QString widgetName;
   QString parseError;
   // stateString is a stack which contains the current started tags. I pop
   // from the stack when the tag ends. It should of course be empty at the
   // end of parsing.
   QString stateString;
   widgetHandlerDictionary wHandlers;
};


#endif //KSDBXMLPARSER_H
