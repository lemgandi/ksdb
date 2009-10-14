// Implementation of ksdbxmlparser -- read ksdb xml files.
//
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

#include <qsize.h>
#include <qpoint.h>
#include <qframe.h>

#include "ksdbxmlparser.h"


//
// Create myself with pointer to output data.
//
KsdbXmlParser::KsdbXmlParser(widgetData *odp,QSize *osp)
{
   theDatap=odp;
   screenSizep=osp;
   stateString="";
   parseError="oops";
   clearWFields();
}

void KsdbXmlParser::setVersion(QString newVer)
{
   correctVersion=newVer;
}

QString KsdbXmlParser::getVersion()
{
   return correctVersion;
}

//
// Put handlers into parser.
void KsdbXmlParser::setWHandlers(const widgetHandlerDictionary &newW)
{
   wHandlers=newW;
}
//
// Get handlers out of parser.
//
const widgetHandlerDictionary & KsdbXmlParser::getWHandlers()
{
   return wHandlers;
}
//
// Destroy myself.
//
KsdbXmlParser::~KsdbXmlParser()
{
   return;
}

// 
// Start parsing document
//
bool KsdbXmlParser::startDocument()
{
   return TRUE;
}

// 
// Hit start of an element.
//
bool KsdbXmlParser::startElement(const QString &,const QString &localName,const QString &,const QXmlAttributes & atts)
{
   bool retVal=TRUE;
   //   qDebug("startElement localName: [%s]\n",(const char *)localName);
   // if(atts.count())
   //   qDebug("\tAtts:");
   //   for(int ii=0;ii<atts.count();++ii)
   // {
   //   qDebug("%s=%s\n",(const char *)atts.qName(ii),(const char *)atts.value(ii));
   // }
   QString localNstr = QString(" %1").arg(localName);
   stateString.append(localNstr);
   if(" ksdb widget mdata val" == stateString)
   {
      wVals[atts.value("K")]=atts.value("V");
   }
   if(" ksdb" == stateString)
   {
      if (! correctVersion.isNull())
      {
	 qDebug("Find Correct version");
	 int ival=atts.index("version");
	 if(-1 != ival)
	 {
	    QString fv=atts.value(ival);
	    qDebug("Version: %s",(const char *)fv);
	    if(fv != correctVersion)
	    {
	       parseError=QString(
               "This file is for version %1. I am version %2")
	       .arg(fv).arg(correctVersion);
	       retVal=FALSE;
	    }
	 }
	 else 
	 {
	    parseError=QString(
            "This file has no version information. I am version %1")
            .arg(correctVersion);
	    retVal=FALSE;
	 }
      }

   }

   return retVal;
}

//
// Hit end of an element
//
bool KsdbXmlParser::endElement(const QString &,const QString &localN,const QString &)
{
   bool retVal=TRUE;
   // qDebug("endElement localName: [%s]\n",(const char *)localN);
   int newLen=stateString.length() - (localN.length()+1);
   stateString.truncate(newLen);
   qDebug("endElement: localN=%s",(const char *)localN);
   if("widget" == localN)
   {
      setupWidget();
      clearWFields();
   }

   return retVal;
}

//
//Hit some characters.
//
bool KsdbXmlParser::characters(const QString &characters)
{
   //   qDebug("characters stateString=%s characters=%s\n",
   //  (const char *)stateString,(const char *)characters);

   bool retVal=TRUE;

   if (" ksdb screen size height" == stateString)   
      screenSizep->setHeight(characters.toInt());
   else if (" ksdb screen size width" == stateString)   
      screenSizep->setWidth(characters.toInt());   
   else if (" ksdb screen backgroundfn" == stateString)
      bgFN=characters;
   else if (" ksdb widget size height" == stateString)
      wSize.setHeight(characters.toInt());
   else if (" ksdb widget size width" == stateString)
      wSize.setWidth(characters.toInt());
   else if (" ksdb widget location x" == stateString)
      wLoc.setX(characters.toInt());
   else if (" ksdb widget location y" == stateString)
      wLoc.setY(characters.toInt());
   else if (" ksdb widget qtwidgetname" == stateString)
      widgetName=characters;
   else
   {
      parseError=QString("Invalid or garbled tags: %1").arg(stateString);
      qDebug("parseError: %s\n",(const char *)parseError);
      retVal=FALSE;
   }
   return retVal;
}

//
// Return latest error.
QString KsdbXmlParser::errorString()
{
   return parseError;
}

bool KsdbXmlParser::endDocument()
{
   // Make sure output is ok here.
   return TRUE;
}

//
// Set up widget in theDatap (output widget data).
// This is where widget setup objects will get called.
//
bool KsdbXmlParser::setupWidget()
{   
   bool retVal=TRUE;
   widgetHandler *wmaker=wHandlers.find(widgetName);
   if(! wmaker)
      wmaker = wHandlers["defailt"];
   
   currentWidget = wmaker->makeWidget(widgetName,wSize,wLoc,wVals);
   qDebug("currentWidget: %p",currentWidget);
   theDatap->insert(currentWidget,wVals);
   return retVal;
}


//
// Clear local widget data in preparation for next widget.
//
bool KsdbXmlParser::clearWFields()
{
   bool retVal=TRUE;

   wVals.clear();
   widgetName="";
   currentWidget=0;
   // I would clear wSize and wLoc here, but that does not appear to be 
   // necessary.
   return retVal;
}

//
// What is in the widget list now?
//
void KsdbXmlParser::dumpCurrentFieldVals()
{
    qDebug("dumpCurrentFieldVals()");
    fieldVals::ConstIterator vIter;
    qDebug("dumpCurrentFieldVals number of vals: %u",wVals.size());
    for(vIter=wVals.constBegin();vIter != wVals.constEnd();++vIter)
       qDebug("\t%s : %s",(const char *)vIter.key(),(const char *)vIter.data());

    qDebug("Dump current widget values: finish");
}

QString KsdbXmlParser::getBGFN()
{
   return bgFN;
}
