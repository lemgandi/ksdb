//
// Implementation for filesaver -- save a modelmaker file to disk.
//

/*
* Copyright (c) Charles Shapiro Sep 2009    
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




#include "filesaver.h"
#include "screenmaker.h"

#include <qpixmap.h>
#include <qfile.h>
#include <qtextstream.h>
// 
// Create a filesaver. Must pass a pointer to screenmaker. I get 
// the screen size and shape from this.
//
fileSaver::fileSaver(const screenMaker *cm,const widgetData &sd,const QString & fn,const QString &Version)
{
   qDebug("screenMaker: %p widgetData %p fn %s",cm,&sd,(const char *)fn);
   fileName=fn;
   currentScreen=cm;
   saveData=sd;
   setVersion(Version);
}

const QString & fileSaver::getVersion()
{
   return fileVersion;
}

void fileSaver::setVersion(const QString &newver)
{
   fileVersion=newver;
}
//
// Destroy myself.
//
fileSaver::~fileSaver()
{
}
//
// What filename am I currently saving to?
//
const QString & fileSaver::getFileName()
{
   return fileName;
}

//
// Set save file name.
//
void fileSaver::setFileName(const QString &fn)
{
   fileName=fn;
}

//
// Save serialized string to a file.
//
bool fileSaver::saveFile()
{
   bool retVal=TRUE;

   qDebug("fileSaver::saveFile");

   if( fileName.isNull() ) 
      retVal=FALSE;

   if(TRUE == retVal)
   {
      qDebug("fileSaver::saveFile(): fileName=%s",(const char *)fileName);
      if (saveString.isNull())
	 serialize();
      QFile outfile(fileName);
      if (outfile.open(IO_WriteOnly)) {
	 QTextStream ostrea(&outfile);
	 ostrea << saveString;
	 qDebug("Save string to file %s",fileName.latin1());
      }
      else
	 retVal = FALSE;
      outfile.close();      
   }
   return retVal;
}

//
// Get metadata for a specific widget in the screenmaker.
//
void fileSaver::serialize()
{
   putSaveStartData();
   widgetData::ConstIterator iter;   
   for(iter=saveData.constBegin();iter != saveData.constEnd(); ++iter)
   {
      const QWidget *wptr=iter.key();
      fieldVals vals=iter.data();
      putWidgetData(wptr,vals);
   }
   putSaveEndData();
}

// 
// Save screenmaker background to a file.
//
bool fileSaver::saveBG(const QString &saveFN)
{
   bool retVal=TRUE;

   const QPixmap *screenBG = currentScreen->paletteBackgroundPixmap();

   if(screenBG)
   {
      qDebug("Saving screenBG");
      retVal=screenBG->save(saveFN,"PNG");
      if(retVal)
	 bgFileName=saveFN;
   }
   return retVal;
}

//
// Start save string.
//
void fileSaver::putSaveStartData()
{
   QWidget *myViewPort=currentScreen->viewport();
   int screenH=myViewPort->height();
   int screenW=myViewPort->width();
   QString wStr=QString("<size><height>%1</height><width>%2</width></size>")
      .arg(screenH)
      .arg(screenW);
   if (! bgFileName.isNull())
   {
      QString fStr=QString("<backgroundfn>%1</backgroundfn>").arg(bgFileName);
      wStr.append(fStr);
   }

   saveString = "<!DOCTYPE KSDB>";
   if( ! fileVersion.isNull())
      saveString += QString("<ksdb version=\"%1\">").arg(fileVersion);
   else
      saveString += QString("<ksdb>");
   qDebug("saveString: %s",(const char *)saveString);

   saveString += "<screen>";
   saveString += wStr;
   saveString += "</screen>";
}

// 
// Save widget state.
//
void fileSaver::putWidgetData(const QWidget *w,const fieldVals &mdata)
{
   saveString.append("<widget>");
   QString nameStr = QString("<qtwidgetname>%1</qtwidgetname>").arg(mdata["widgetname"]);
   saveString.append(nameStr);
   QString sizeStr = QString("<size><height>%1</height><width>%2</width></size>")
      .arg(w->height()).arg(w->width());
   saveString.append(sizeStr);
   QString locStr = QString("<location><x>%1</x><y>%2</y></location>")
      .arg(w->x()).arg(w->y());
   saveString.append(locStr);
   saveString.append("<mdata>");
   fieldVals::ConstIterator iter;
   QString appstr;
   for( iter=mdata.constBegin();iter != mdata.constEnd(); ++iter )
   {
      QString k=iter.key();
      QString d=iter.data();
      appstr=QString("<val K=\"%1\" V=\"%2\" />").arg(k).arg(d);
      saveString.append(appstr);
   }
   saveString.append("</mdata>");
   saveString.append("</widget>");
}

//
// Put end marker.
//
void fileSaver::putSaveEndData()
{
   saveString.append("</ksdb>");
}
