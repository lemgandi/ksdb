// Implementation of fileReader -- read a ksdb file back into the modelmaker
// or elsewhere.

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

#include <qapplication.h>
#include <qxml.h>
#include <qwindowdefs.h>
#include <qpixmap.h>
#include <qfile.h>


#include "ksdbfilereader.h"
#include "ksdbxmlparser.h"
#include "widgethandler.h" 

//
// Instantiation. Filename may be null.
//
ksdbFileReader::ksdbFileReader(const QString & fn,const widgetHandlerDictionary & wdh)
{
   readFN=fn;
   myParser= new KsdbXmlParser(&myData,&screenSize);
   setHandlerDictionary(wdh);
   theReader.setFeature(
   "http://trolltech.com/xml/features/report-whitespace-only-CharData",FALSE);
   theReader.setContentHandler(myParser);
}

QString ksdbFileReader::getVersion()
{
   return myParser->getVersion();
}

void ksdbFileReader::setVersion(QString theVersion)
{
   myParser->setVersion(theVersion);
}

//
// Return current error.
//
QString ksdbFileReader::errorString()
{
   return myParser->errorString();
}

//
// Set widget handlers as necessary.
// 
void ksdbFileReader::setHandlerDictionary(const widgetHandlerDictionary &wd)
{
   myParser->setWHandlers(wd);
}
const widgetHandlerDictionary & ksdbFileReader::getHandlerDictionary()
{
   return myParser->getWHandlers();
}
//
// Might need later?
//
ksdbFileReader::~ksdbFileReader()
{
   delete myParser;
}

void ksdbFileReader::setFileName(const QString &fn)
{
   readFN=fn;
}

const QString & ksdbFileReader::getFileName()
{
   return readFN;
}

//
// Read xml data from filename
bool ksdbFileReader::readFile()
{
   bool retVal=TRUE;

   if(readFN.isNull())
      retVal=FALSE;

   if( (retVal) && (! QFile::exists(readFN)) )
   {
      currentError= "No File " + readFN;
      retVal=FALSE;
   }

   if(retVal)
   {
      qDebug("Reading File %s",(const char *)readFN);
      QFile inXmlFile(readFN);
      QXmlInputSource src(&inXmlFile);
      retVal=theReader.parse(src);      
      if(! retVal)
	 currentError=myParser->errorString();
   }
   return retVal;
}

const widgetData & ksdbFileReader::getData()
{
   return myData;
}

QSize ksdbFileReader::getStartScreenSize()
{
   return screenSize;
}

QPixmap ksdbFileReader::getBGPixMap()
{
   qDebug("getBGPixMap()");
   QPixmap retVal;

   QString backgroundFN=myParser->getBGFN();

   qDebug("getBGPixMap(): backgroundFN=%s",(const char *)backgroundFN);

   if (! backgroundFN.isNull())
   {
      if (QFile::exists(backgroundFN))
	 retVal.load(backgroundFN);
   }
   return retVal;
}
