#include <qapplication.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qlabel.h>
#include <qtextedit.h>
#include <qlineedit.h>
#include <qfiledialog.h>
#include <iostream>
#include <qpopupmenu.h>
using std::cout;
using std::endl;

#include "screenmaker.h"
#include "testwidget.h"
#include "mockeditfield.h"


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
testWidget::testWidget(QWidget *parent, const char *name) : 
   QWidget(parent,name)
{
   QPushButton *quitButton = new QPushButton("&Quit",this,"quit");
   QPushButton *clearButton = new QPushButton("&Clear",this,"Clear");
   QPushButton *editButton = new QPushButton("&Edit",this,"Edit");
   QPushButton *makeButton = new QPushButton("&Make",this,"Make");
   QPushButton *themeButton = new QPushButton("&Theme",this,"Theme");
   QPushButton *dumpButton = new QPushButton("&Dump",this,"Dump");

   connect(quitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
   scrMakerWidget = new screenMaker(this,"screenmaker");
   connect(scrMakerWidget,SIGNAL(regionSelected(QWidget *)),this,SLOT(regionDefined(QWidget *)));
   connect(clearButton,SIGNAL(clicked()),scrMakerWidget,SLOT(clearDrawingField()));
   connect(themeButton,SIGNAL(clicked()),this,SLOT(newBg()));
   connect(makeButton,SIGNAL(clicked()),this,SLOT(toDrawMode()));
   connect(dumpButton,SIGNAL(clicked()),this,SLOT(dumpWidgets()));

   connect(this,SIGNAL(drawMode()),scrMakerWidget,SLOT(drawMode()));
   connect(editButton,SIGNAL(clicked()),scrMakerWidget,SLOT(selectMode()));
   connect(scrMakerWidget,SIGNAL(widgetSelected(QWidget *)),this,SLOT(selectWidget(QWidget *)));
   connect(scrMakerWidget,SIGNAL(widgetResized(QWidget *)),this,SLOT(deSelectWidget(QWidget *)));
   connect(scrMakerWidget,SIGNAL(widgetMoved(QWidget *)),this,SLOT(deSelectWidget(QWidget *)));


   QVBoxLayout *buttonBox=new QVBoxLayout;
   buttonBox->addWidget(quitButton);
   buttonBox->addWidget(editButton);
   buttonBox->addWidget(makeButton);
   buttonBox->addWidget(clearButton);
   buttonBox->addWidget(themeButton);
   buttonBox->addWidget(dumpButton);

   QHBoxLayout *screenBox = new QHBoxLayout;
   screenBox->addWidget(scrMakerWidget);

   QGridLayout *theGrid = new QGridLayout(this,2,2,10,0,"theGrid");
   theGrid->addLayout(buttonBox,0,0);
   theGrid->addLayout(screenBox,0,1);
   currentWidget=0;
   cutMenu=new QPopupMenu(this,"cutMenu");
   cutMenu->insertItem("&Move",this,SLOT(moveItem()));
   cutMenu->insertItem("&Resize",this,SLOT(resizeItem()));
   cutMenu->insertItem("&Properties",this,SLOT(itemProperties()));
}

//
// Move selected item around in the screenmaker.
//
void testWidget::moveItem()
{
   scrMakerWidget->moveWidget(currentWidget);
}

//
//Resize selected item in the screenmaker
//
void testWidget::resizeItem()
{
   cout << "resizeItem()" << endl;
   scrMakerWidget->resizeWidget(currentWidget);
}

//
//Edit item properties on selected widget in screenmaker.
//
void testWidget::itemProperties()
{
   QMessageBox::information(this,"Message","This is where an item properties menu would go",QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
}
//
// Show an object as selected.
//
void testWidget::selectWidget(QWidget *selected)
{
   oldColor =  selected->paletteBackgroundColor();
   selected->setPaletteBackgroundColor(red);
   currentWidget=selected;
   cutMenu->exec();
}

void testWidget::toDrawMode()
{
   unselectWidget();
   emit(drawMode());
}

void testWidget::unselectWidget()
{

   if(currentWidget)
      currentWidget->setPaletteBackgroundColor(oldColor);

   currentWidget=0;

}
//
// Turn given widget color back to oldcolor.
//
void testWidget::deSelectWidget(QWidget *w)
{
   w->setPaletteBackgroundColor(oldColor);
}
//
//Find a theme file, make it the new background of the screenwidget.
void testWidget::newBg()
{
   QPixmap bgmap;
   QString fn=QFileDialog::getOpenFileName(
     ".",
     "Images (*.png *.xpm *.jpg)",
     this,
     "open file dialog",
     "Choose a file to open" );
   if(fn)
   {
      bgmap.load(fn);
      scrMakerWidget->setBackground(bgmap);
   }

}

void testWidget::makeLabel()
{
   QWidget *thelabel = new QLabel("A Label",0);
   thelabel->resize(currentWidget->size());
   scrMakerWidget->replaceWidget(currentWidget,(QWidget *)thelabel);
}

void testWidget::makeField()
{
   QWidget *theField;

   if (currentWidget->height() > scrMakerWidget->cellHeight())
      theField = new mockTextEditField("Text Entry Field","",0,0);
   else 
      theField=new mockLineEditField("Line Entry Field",0,0);

   connect(theField,SIGNAL(mousePressed(QMouseEvent *)),scrMakerWidget,SLOT(mousePressed(QMouseEvent *)));

   theField->resize(currentWidget->size());

   scrMakerWidget->replaceWidget(currentWidget,theField);
}

void testWidget::removeCurrentWidget()
{
   scrMakerWidget->removeWidget(currentWidget);
}

void testWidget::displayMsg(const char *msg)
{
   int action = QMessageBox::information(this,"Message",msg,"&Quit","&Label","&Field",0,2);
   switch(action) 
   {
      case 0:
	 removeCurrentWidget();
         break;
      case 1:
	 makeLabel();
	 break;
      case 2:
	 makeField();
   }
}

void testWidget::regionDefined(QWidget *selectedAreaWidget)
{
   currentWidget=selectedAreaWidget;
   QString mymsg = QString("A menu to define the object at %1 %2.")
     .arg(selectedAreaWidget->x())
      .arg(selectedAreaWidget->y());
   
   displayMsg(mymsg);
}

void testWidget::dumpWidgets()
{
   WPList myList=scrMakerWidget->getFieldList();

   QWidget *currentWidget=myList.first();
   QPoint trueLoc;
   while(currentWidget)
   {
      qDebug("Widget: %p",currentWidget);
      qDebug("\tLocation: %d %d",currentWidget->x(),currentWidget->y());
      trueLoc=scrMakerWidget->viewportToContents(currentWidget->pos());
      qDebug("\tTrue Location: %d %d",trueLoc.x(),trueLoc.y());
      qDebug("\tName: %s",(const char *)currentWidget->name());      
      currentWidget=myList.next();
   }

}
