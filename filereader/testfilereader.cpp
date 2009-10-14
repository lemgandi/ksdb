//
// Test file reader
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

#include <iostream>

#include <qapplication.h>
// #include <qgridview.h>
#include <qmainwindow.h>
#include <qsize.h>
#include <qwidget.h>
#include <qpixmap.h>


#include "wtextedithandler.h"
#include "wlineedithandler.h"
#include "wlabelhandler.h"
#include "wcheckboxhandler.h"
#include "wbuttonhandler.h"

using std::cerr;
using std::cout;
using std::endl;

#include "typedefs.h"

#include "ksdbfilereader.h"
#include "version.h"

// 
// Test widget to display fields on screen.
//
class testWidget : public QMainWindow
{
public:
   testWidget(QSize,widgetData,QPixmap,QWidget *parent=0,const char *name=0);
protected:
   //   void paintCell(QPainter *,int,int);
};

//
// Make test widget
//
testWidget::testWidget(QSize theSize,widgetData theData,QPixmap bgmap,
   QWidget *parent,const char *name) : QMainWindow(parent,name,WType_TopLevel)
{
   this->resize(theSize);

   widgetData::iterator iter;
   for(iter=theData.begin(); iter != theData.end(); ++iter)
   {
      QWidget *wP=iter.key();
      cout << "Adding Child " <<  wP << " at X: " << wP->x() 
	   << " Y: " << wP->y() << endl;
      // addChild(wP,wP->x(),wP->y());
      wP->reparent(this,0,wP->pos(),TRUE);
   }
   if(! bgmap.isNull())
   {
      cout << "Setting background to serial: " 
	   << bgmap.serialNumber() << endl;
      this->setPaletteBackgroundPixmap(bgmap);
   }

}


//
// Required for QGridView; do nothing for now.
//
// void testWidget::paintCell(QPainter *,int,int)
// {
//   return;
// }

//
// Dump current widget values.
//
void dumpCurrentWidgetValues(const widgetData & wData)
{
   cout << "dumpCurrentWidgetValues()" << endl;
    widgetData::ConstIterator iter;
    cout << "dumpCurrentWidget number of widgets: " << wData.size() << endl;
    for(iter=wData.constBegin();iter != wData.constEnd();++iter)
    {
	QWidget *wPtr=iter.key();
	cout << "Widget Pointer: " << wPtr << endl;
	if (wPtr) 	
	   cout << "Widget at " << iter.key()->x() << " " << iter.key()->y() << ":" << endl;
	fieldVals vals=iter.data();
	fieldVals::ConstIterator jIter;
	for (jIter=vals.constBegin();jIter!= vals.constEnd();++jIter)
	   cout << "\t" << (const char *)jIter.key() << " : " 
		<< (const char *)jIter.data() << endl;
    }
	cout <<  "Dump current widget values: finish" << endl;
}

//
// Main Line
//
int main(int argc, char **argv)
{
   QApplication a(argc,argv);
   widgetHandlerDictionary wHandlers;


   wHandlers.insert("defailt",new widgetHandler());
   wHandlers.insert("QLabel", new wLabelHandler());
   wHandlers.insert("QLineEdit", new wLineEditHandler());
   wHandlers.insert("QTextEdit", new wTextEditHandler());
   wHandlers.insert("QCheckBox",new wCheckboxHandler());
   wHandlers.insert("QPushButton",new wButtonHandler());
   wHandlers.setAutoDelete(TRUE);

   if(2 == a.argc())
   {
      ksdbFileReader myFReader(a.argv()[1],wHandlers);
      myFReader.setVersion(QString(VERSION));

      if (myFReader.readFile())
      {
	 QSize mySize(myFReader.getStartScreenSize());
	 cout << "Screen Size: W " << mySize.width() << " H " 
	      << mySize.height() << endl;
	 widgetData myData=myFReader.getData();
	 dumpCurrentWidgetValues(myData);
	 QPixmap bgMap(myFReader.getBGPixMap());
	 if(! bgMap.isNull())
	 {
	    cout << "BG pix map serial: " << bgMap.serialNumber() << endl;
	 }
	 testWidget w(mySize,myData,bgMap,0,"Testwidget");
	 a.setMainWidget(&w);
	 w.show();
	 return a.exec();
      }
      else
	 cout << "Error: " << (const char *)myFReader.errorString() << endl;
   }
   else
   {
      cout << "Usage: %s " << argv[0] << "<infile>" << endl;
      cout << "infile must exist of course." << endl;
      return 1;
   }
			
}
