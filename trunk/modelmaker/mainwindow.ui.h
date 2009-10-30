/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

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
//
// Initialize myself.
//
void mainWindow::init()
{
    
    currentWidget=0;
    Dirty=FALSE;
    fieldEditorScreen = new fieldEditor(this,"fieldEditor");
    fieldEditorScreen->move(100,100);
    connect(fieldEditorScreen,
	    SIGNAL(collectedValues(const fieldVals &,QWidget *)),
	    this,SLOT(editorValues(const fieldVals &,QWidget *)));

    connect(this,
	    SIGNAL(pushReplaceWidget(const QWidget *,const screenMaker *)),
	    fieldEditorScreen,
	    SLOT(setReplaceWidget(const QWidget *,const screenMaker *)));
    connect(this,SIGNAL(editWidgetData(const fieldVals &)),
	    fieldEditorScreen,SIGNAL(setEditData(const fieldVals &)));
    connect(this,SIGNAL(widgetSizeChanged(QWidget *,fieldVals *)),
	    fieldEditorScreen,
	    SIGNAL(widgetSizeChanged(QWidget *,fieldVals *)));
    
    selectMenu=new QPopupMenu(this,"selectMenu");
    selectMenu->insertItem("re&Size",this,SLOT(resizeWidget()));
    selectMenu->insertItem("&Move",this,SLOT(moveWidget()));
    selectMenu->insertItem("&Delete",this,SLOT(menuDeleteWidget()));
    selectMenu->insertItem("&Edit",this,SLOT(editWidget()));
    selectMenu->insertSeparator();
    selectMenu->insertItem("&Reselect",this,SLOT(selectAnotherWidget()));
    selectMenu->insertItem("&Quit",this,SLOT(quitSelect()));   
}

// Exit; dump contents of data list to stdout as needed.
//
void mainWindow::destroy()
{
    qDebug("mainWindow::destroy()");
    // fileExit(); Hmm. This doesn t work right.
    dumpCurrentWidgetValues();
}
//
// Clear screenmaker and start anew.
//
void mainWindow::fileNew()
{
   bool success=TRUE;
   if(Dirty)
   {
      int resp=QMessageBox::question(this,"Clear Screen","You have unsaed data. Sure you wish to clear the screen and start a new file?",QMessageBox::Cancel,QMessageBox::Ok,QMessageBox::NoButton);
      switch(resp) 
      {
      case 1:
	 success=TRUE;
	 break;
      default:
	 success=FALSE;
	 break;
      }
   }
   if(TRUE == success)
   {
      screenMaker3->clearDrawingField();
      fileSaveName.truncate(0);
   }
}


void mainWindow::fileOpen()
{
   QString fn=QFileDialog::getOpenFileName(".","*.ksdb *.xml;;*.*",
	   this,"Open File","Choose file to edit");
   qDebug("Open File: %s",(const char *)fn);
   if(! fn.isNull()) {
      screenMaker3->clearDrawingField();
      widgetHandlerDictionary wHandlers;
      wHandlers.insert("defailt",new widgetHandler());
      wHandlers.insert("QLabel", new wLabelHandler());
      wHandlers.insert("QLineEdit", new wEditLineEditHandler(screenMaker3));
      wHandlers.insert("QTextEdit", new wEditTextEditHandler(screenMaker3));
      wHandlers.insert("QCheckBox",new wEditCheckboxHandler(screenMaker3));
      wHandlers.insert("QPushButton",new wEditButtonHandler(screenMaker3));
      wHandlers.setAutoDelete(TRUE);
      ksdbFileReader theReader(fn,wHandlers);
      if(theReader.readFile())
      {
	 fileSaveName=fn;
         QPixmap myPmap=theReader.getBGPixMap();
	 if (! myPmap.isNull())
	 {
	    screenMaker3->setBackground(myPmap);
	 }
	 QSize startSize=theReader.getStartScreenSize();
	 QSize sizeDiff=size()-screenMaker3->size();
	 screenMaker3->resize(startSize);
	 resize(startSize+sizeDiff);
	 wData=theReader.getData();
	 dumpCurrentWidgetValues();
	 WPList wptrs;
	 widgetData::Iterator iter;
	 for(iter = wData.begin();iter != wData.end(); ++iter)
	    wptrs.append(iter.key());
	 screenMaker3->setFieldList(wptrs);
      }     
      else 
      {
	  QMessageBox::critical(this,"Bad File",
          QString("File %1 is not valid.\nError: %2")
	  .arg(fn).arg(theReader.errorString()));	 
      }
      wHandlers.clear();  // This is supposed to delete all my new()s above
   }
}

//
// Prepare to draw widgets in screenMaker3. Unselect any currently 
// selecte widget.
//
void mainWindow::gotoDrawMode()
{
    qDebug("gotoDrawMode: currentWidget=%p",currentWidget);
    deSelectWidget();
    screenMaker3->drawMode();
}

// 
// Prepare to select widgets in screenMaker 3. Unselect any currently
// selected widget.
//
void mainWindow::gotoSelectMode()
{
     qDebug("gotoSelectMode: currentWidget=%p",currentWidget);
     deSelectWidget();         
    screenMaker3->selectMode();
}
//
// Save file to disk
//
void mainWindow::fileSave()
{
    qDebug("Save File");
    if (fileSaveName.isNull())
	getSaveFileName();
    if (! fileSaveName.isNull()) 
    {
       qDebug("screenMaker3 bg: %p",screenMaker3->paletteBackgroundPixmap());
       qDebug("fileSaveName: %s",(const char *)fileSaveName);
       qDebug("screenMaker3: %p",screenMaker3);
       fileSaver mySaver(screenMaker3,wData,fileSaveName,VERSION);
       qDebug("saveBG");
       mySaver.saveBG(QString(fileSaveName+".png"));
       qDebug("saveFile");
       mySaver.saveFile();
       Dirty=FALSE;
    }
}


void mainWindow::fileSaveAs()
{
    qDebug("File Save As");
    getSaveFileName();
    fileSave();
}


void mainWindow::filePrint()
{

}

//
// Good Bye.  Ask to save file if necessary.
//
void mainWindow::fileExit()
{
   qDebug("fileExit");
   if(Dirty)
   {
       int action=QMessageBox::question(this,
	"Exit","You have unsaved changes here.",
	"Continue Editing","Save and Exit","Quit (lose changes)");
       switch(action) 
       {
       case 1:
	  fileSave(); // No break here to drop through to exit.
       case 2:
	   QApplication::exit(0);
	   break;
       default: // case 0 and safest assumption.
	   return;
       }
   }  
   else
      QApplication::exit(0);
}

void mainWindow::helpIndex()
{

}


void mainWindow::helpContents()
{

}


void mainWindow::helpAbout()
{
   QMessageBox::about(this,"About modelmaker",
   QString("Modelmaker Version %1\n").arg(VERSION)+
   QString("Copyright(c) Charles Shapiro Sep 2009\n")+
   QString("With gracious assistance from Michael Hirsch\n")+
   QString("This progam is released under GNU General Public License version 3\n"));
}

//
// User has drawn a region on the screen; display context menu
// to gather information about the region, then change it to 
// an appropriate widget (e.g. label or text field).
void mainWindow::regionDefined( QWidget * w)
{
   currentWidget=w;
   qDebug("Region Defined widget=%p",w);   
   if (checkWidgetCollision(w))   
      screenMaker3->removeWidget(w);   
   else
   {
       emit pushReplaceWidget(w,screenMaker3);
       makeNewWidget(w);   
   }
}

void mainWindow::moveItem()
{

}


void mainWindow::resizeItem()
{

}


void mainWindow::itemProperties()
{

}

//
// Put new image into background.
//
void mainWindow::newBackground()
{
    qDebug("New background");

   QPixmap newbg;
   QString fn=QFileDialog::getOpenFileName(
     ".",
     "Images (*.png *.xpm *.jpg)",
     this,
     "New Background File",
     "Choose a new background pixmap" );

   if(fn)
   {
      newbg.load(fn);
      emit newBackground(newbg);
      Dirty=TRUE;
   }
 
}

//
// Unselect currently selected widget.
//
void mainWindow::deSelectWidget()
{
   if (currentWidget)
    {
       currentWidget->setPaletteBackgroundColor(oldColor);
       currentWidget=0;
    }
}

//
// Make a new widget (e.g. label, input field) from 
// a selected region in the screenmaker. Pop up a context dialog
// to let user choose type and properties. Signals between the dialog and 
// (mainWindow *)this are what control putting the widget into 
// screenMaker3
void mainWindow::makeNewWidget( QWidget *w)
{
     Q_ASSERT(w != 0);     
     fieldEditorScreen->exec();
}

//
// Set a widget to show as selected.
//
void mainWindow::setWidgetSelected(QWidget *w)
{
   qDebug("setWidgetSelected w=%p",w);
   Q_ASSERT(w != 0);
   oldColor=w->paletteBackgroundColor();
   w->setPaletteBackgroundColor(red);
}

//
// Respond to widgetSelected signal from screenMaker3
//
void mainWindow::widgetSelected(QWidget * w)
{
   qDebug("widgetSelected: Widget at %d %d selected",w->x(),w->y());
   fieldVals fv=wData[w];
   setWidgetSelected(w);
   currentWidget=w;
   fieldValues=wData[w];
   //   qDebug("Widget Name: %s",fv["name"].latin1());
   showMenu();
}

// 
// Respond to screenMaker3 widgetResized signal;
// this will have to change widget type from
// QTextEdit to QLineEdit and back on input widgets some day.
// For now just redisplay the select menu.
//
void mainWindow::widgetResized(QWidget *theW)
{

   qDebug("mainwindow:widgetResized theW->x=%d theW->y=%d",
	  theW->x(),theW->y());
   QWidget *oldWidgetPtr=currentWidget;
 
   emit editWidgetData(wData[currentWidget]);
   emit pushReplaceWidget(currentWidget,screenMaker3);

   emit widgetSizeChanged(theW,&wData[currentWidget]);
   wData.remove(oldWidgetPtr);
   deSelectWidget();
   
   Dirty=TRUE;
   //   showMenu();
}
// 
// Respond to screenMaker3 widgetMoved signal;
// redisplay select menu.
//
void mainWindow::widgetMoved(QWidget *)
{
   deSelectWidget();
   Dirty=TRUE;
   //   showMenu();
}
//
// Show the selected popup menu
//
void mainWindow::showMenu()
{    
   qDebug("Showmenu");
   if(! selectMenu->isVisible())
      while (-1 == selectMenu->exec(this->mapToGlobal(QPoint(0,0)))){}
}
//
// Slot to receive results of field editor screen(s).
//
void mainWindow::editorValues( const fieldVals & newVals,QWidget *newWidget )
{
   qDebug("editorValues newWidget=%p",newWidget);
   qDebug("screenMaker3 state: %d",screenMaker3->currentState());
   fieldValues=newVals;
   if(newWidget) 
   {
       wData[newWidget]=newVals;     
       Dirty=TRUE;
   }
   setupNewWidget(newWidget);   
}

//
// What is in the widget list now?
//
void mainWindow::dumpCurrentWidgetValues()
{
    qDebug("dumpCurrentWidgetValues()");
    widgetData::ConstIterator iter;
    qDebug("dumpCurrentWidget number of widgets: %u",wData.size());
    for(iter=wData.constBegin();iter != wData.constEnd();++iter)
    {
	const QWidget *wPtr=iter.key();
	qDebug("Widget Pointer: %p",wPtr);
	if (wPtr)
	   qDebug("Widget at %d %d:",iter.key()->x(),iter.key()->y());
	fieldVals vals=iter.data();
	fieldVals::ConstIterator jIter;
	for (jIter=vals.constBegin();jIter!= vals.constEnd();++jIter)
	    qDebug("\t%s : %s",(const char *)jIter.key(),(const char *)jIter.data());
	
    }
    qDebug("Dump current widget values: finish");
}

// 
// Remove the current widget if e.g. we started to create it but decided not
// to complete the process.
//
void mainWindow::removeCurrentWidget()
{
    screenMaker3->removeWidget(currentWidget);
    wData.remove(currentWidget);
    currentWidget=0;
}

//
// Slot to replace current widget with widget made by widget editor.
//
void mainWindow::setupNewWidget( QWidget *wp )
{
  qDebug("setupNewWidget currentWidget:%p newWidget: %p",currentWidget,wp);
  qDebug("screenMaker3->curentState=%d",screenMaker3->currentState());
  if (wp)       
  {
        screenMaker3->replaceWidget(currentWidget,wp);
        currentWidget=wp;
        oldColor=wp->paletteBackgroundColor();
    }
  else if (screenMaker::DRAGGING == screenMaker3->currentState())
  {
     removeCurrentWidget();
  }
}

//
// Resize the selected widget.
//
void mainWindow::resizeWidget()
{
    Q_ASSERT(currentWidget != 0);
    qDebug("resizeWidget: currentWidget=%p",currentWidget);
    screenMaker3->setFocus();
    emit( resizeWidget(currentWidget));    
}
// 
// Move the selected widget.
//
void mainWindow::moveWidget()
{
    Q_ASSERT(currentWidget != 0);
    qDebug("moveWidget");
    emit(moveWidget(currentWidget));
}
//
// Select another widget
//
void mainWindow::selectAnotherWidget()
{
    qDebug("selectAnotherWidget");
    deSelectWidget();
    gotoSelectMode();
}
//
// Delete the current widget
//
void mainWindow::deleteWidget()
{
   qDebug("deleteWidget");
   emit( destroyWidget(currentWidget));
   wData.remove(currentWidget);
   Dirty=TRUE;
   currentWidget=0;
}

// 
// Quit edit menu.
//
void mainWindow::quitSelect()
{
    deSelectWidget();
    gotoDrawMode();
}

//
// Edit widget type and metadata
//
void mainWindow::editWidget()
{
    qDebug("EditWidget:");
    Q_ASSERT(currentWidget != 0);
    QWidget * oldWidgetPtr=currentWidget;

    qDebug("editWidget current=%p",currentWidget);

    emit editWidgetData(wData[currentWidget]);
    emit pushReplaceWidget(currentWidget,screenMaker3);
    if(currentWidget)
    {
	wData.remove(oldWidgetPtr);
	makeNewWidget(currentWidget);
    }
    // showMenu();
}

//
// Delete widget from edit menu. Handle current state.
//
void mainWindow::menuDeleteWidget()
{
    deleteWidget();
    gotoSelectMode();
}

//
// Get the name of the file to save.
//
void mainWindow::getSaveFileName()
{
    fileSaveName=QFileDialog::getSaveFileName(".","*.ksdb *.xml;;*.*",this,"Save file as","Choose a file to hold this model");
}

//
// Are two widgets overlapping?
//
bool mainWindow::checkWidgetCollision( const QWidget *testWidget)
{
  bool retVal=FALSE;
  QRect checkRect=testWidget->geometry();
  QRect testRect;
  widgetData::ConstIterator iter;  
  for(iter=wData.constBegin(); iter != wData.constEnd(); ++iter)
  {
     testRect=iter.key()->geometry();     
     if (checkRect.intersects(testRect))
     {
	retVal=TRUE;
	break;
     }
  }
  return retVal;
}

void mainWindow::closeEvent(QCloseEvent *)
{
    qDebug("Closevent");    
    fileExit();
}

