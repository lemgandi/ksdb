/*
 * Implementation of the gizmo which makes a screen.
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
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qframe.h>
#include <qptrvector.h>
#include <qsize.h>
#include <qpixmap.h>
#include <qsizegrip.h>

#include "screenmaker.h"

//
// Create a screenmaker widget.
//
screenMaker::screenMaker( QWidget *parent, const char *name)
   : QGridView( parent, name,WStaticContents )
{
   QDesktopWidget *dt=QApplication::desktop();
   int hpixels=dt->height();
   int wpixels=dt->width();
   int cellwidth=fontMetrics().width("m");
   int cellheight=fontMetrics().height()+5;

   minimumSize.setWidth(dt->width() /4);
   minimumSize.setHeight(dt->height() / 4);

   resizeContents(wpixels,hpixels);
   setNumCols(wpixels / cellwidth);
   setNumRows(hpixels / cellheight);
   setCellHeight(cellheight);
   setCellWidth(cellwidth);

   selectedRegion=0;
   // Set to draw widgets at first.
   drawMode();   
   setResizePolicy(QScrollView::Manual);
   //   QSizeGrip *mycornerwidget = new QSizeGrip(this);
   // setCornerWidget(mycornerwidget);
   qDebug("Create screenmaker with %d cells",numCols() * numRows());
   allowOverlap=FALSE;
}

bool screenMaker::getAllowOverlap()
{
   return(allowOverlap);
}
//
// Set to allow/disallow overlapping widgets.
//
void screenMaker::setAllowOverlap(bool newVal)
{
   allowOverlap=newVal;
}
//
// A slot to connect mouse pressed events. These get sent by the mock* objects
// so that we can select when in select mode.
//
void screenMaker::mousePressed(QMouseEvent *e)
{   
      viewportMousePressEvent(e);
}

//
// Set up to move a (presumably selected) widget with the mouse.
//
void screenMaker::moveWidget(QWidget *widgetToMove)
{
   Q_ASSERT(widgetToMove != 0);
 
   qDebug("screenMaker: moving %p",widgetToMove);
   selectedWidget=widgetToMove;
   currentScreenState=MOVING;
}

//
// Set up to resize a (presumably selected) widget with the mouse.
//
void screenMaker::resizeWidget(QWidget *widgetToResize)
{

   Q_ASSERT(widgetToResize != 0);

   qDebug("screenMaker: resizing %p",widgetToResize);
   selectedWidget=widgetToResize;
   currentScreenState=RESIZING;
}

//
// Is the cursor currently over a widget? Which one?
// this uses the screenmaker coordinate system.
//
QWidget * screenMaker::onWidget(int currentX,int currentY)
{
   QWidget *whichWidget=0;
   QRect widget_rect;

   whichWidget=fieldList.first();
   while(whichWidget)
   {
      widget_rect=whichWidget->frameGeometry();
      if (widget_rect.contains(currentX,currentY,TRUE))
	 break;		       
      whichWidget=fieldList.next();
   }
   return whichWidget;
}

// 
// Go into Select mode -- select an already created widget
//
void screenMaker::selectMode()
{
   currentScreenState=SELECTING;
}

//
// Put me into drawing mode -- creating widgets.
//
void screenMaker::drawMode()
{
   currentScreenState=DRAWING;
}

//
// Set background pixmap.
//
void screenMaker::setBackground(const QPixmap &newMap)
{
   bgimage=newMap;
   if(bgimage.isNull())
      return;
   setPaletteBackgroundPixmap(bgimage);
}

//
// Get the list of created fields.
//
const WPList & screenMaker::getFieldList()
{
   return fieldList;
}


//
// Set the list of created fields from outside. This also clears the 
// display and sets up the new fields.
//
void screenMaker::setFieldList(const WPList & newFieldList)
{
   clearDrawingField();
   fieldList=newFieldList;
   QWidget *curNode=fieldList.first();
   while(curNode) 
   {
      qDebug("Adding node: %p",curNode);
      addChild(curNode,curNode->x(),curNode->y());
      showChild(curNode);
      curNode=fieldList.next();
   }
}

//
// Clear entire drawing field. Dangerous.
//
void screenMaker::clearDrawingField()
{
   QWidget *curNode=fieldList.first();
   while(curNode)
   {
      curNode=fieldList.take();
      delete(curNode);
   }   
   currentScreenState=DRAWING;
}

//
// Implementation of the pure virtual class 
// "qgridview" method. This draws the borders of a cell. Cell size is  
// defined in the constructor.
//
void screenMaker::paintCell(QPainter *p,int, int)
{
   p->setBrush(blue);
   p->drawLine(cellWidth()-1,0,cellWidth()-1,cellHeight()-1);
   p->drawLine(0,cellHeight()-1,cellWidth()-1,cellHeight()-1);
}

//
// Round a pair of coordinates to the nearest cell boundary.
//
void screenMaker::roundToNearestCell(int &x, int &y)
{
   
   int numCells = x / cellWidth();
   x=cellWidth() * numCells;
   numCells= y / cellHeight();
   y=cellHeight() * numCells;
}

//
// Create a new widget at the mouse current position.
//
void screenMaker::makeNewWidget(QMouseEvent *e)
{
      int thisCol;
      int thisRow;
      bool success=TRUE;
      
      // This is odd but necessary so that the correct place gets
      // highlighted if user has clicked mouse inside a mockEditField.
      QPoint rightPoint=mapFromGlobal(e->globalPos());
      
      viewportToContents(rightPoint.x(),rightPoint.y(),thisRow,thisCol);
      roundToNearestCell(thisRow,thisCol);
      if( ! allowOverlap)
      {
	 if(pointOverlaps(thisRow,thisCol))
	    success=FALSE;
      }

      if(success)
      {
	 selectedRegion = new QFrame(viewport());
	 selectedRegion->setPaletteBackgroundColor(blue);
	 selectedRegion->setPaletteForegroundColor(red);
	 selectedRegion->resize(cellRect().size());
	 addChild(selectedRegion,thisRow,thisCol);
	 showChild(selectedRegion);
	 currentScreenState=DRAGGING;
      }
}


//
// Select an already created widget if it is currently under the mouse pointer.
//
void screenMaker::maybeSelectWidget(QMouseEvent *e)
{
   Q_ASSERT(currentScreenState == SELECTING);

   // The following hideous hack (mapFromGlobal...) is required because
   // the mouse event I am processing may have come from one of the mock*
   // classes. In this case, the e->x() and e->y() coordinates are relative
   // to the edit widget, not the screenmaker widget. Since onWidget works
   // from coordinates mapped to screenmaker, I must re-map them here.
   QPoint myPos(mapFromGlobal(e->globalPos()));

   QWidget *selected=onWidget(myPos.x(),myPos.y());
   if (selected)
   {
      currentScreenState=SELECTED;
      emit widgetSelected(selected);
   }
   
}

//
// Respond to mouse button press -- start to draw if in DRAWING mode,
// or select if in SELECTING mode.
//
void screenMaker::viewportMousePressEvent(QMouseEvent *e)
{

   switch(currentScreenState)     
   {
      case DRAWING:
         makeNewWidget(e);
	 break;
      case SELECTING:
	 maybeSelectWidget(e);
	 break;
      default:
         break;
   }   
}

//
// Respond to mouse button release -- emit selected region if in DRAW mode,
// or selected widget if in SELECT mode. If in SELECT mode and not over a 
// widget, do nothing.
//
void screenMaker::viewportMouseReleaseEvent(QMouseEvent *)
{
   switch(currentScreenState)
   {
   case DRAGGING:
      fieldList.append((QWidget *)selectedRegion);
      emit regionSelected((QWidget *)selectedRegion);
      currentScreenState=DRAWING;
      break;
   case RESIZING:
      qDebug("mouseReleaseEvent: resizing");
      emit widgetResized(selectedWidget);
      currentScreenState=SELECTING;
      break;
   case MOVING:
      emit widgetMoved(selectedWidget);
      currentScreenState=SELECTING;
      break;
   default:
      break;
      
   }

}

//
// Calculate the new size of an object as it is resized or 
// while it is being created.
//
QSize screenMaker::calculateNewSize(int x,int y,QWidget *childWidget)
{
      
   int newx,newy,cx,cy;
   viewportToContents(x,y,newx,newy);
   cx=childX(childWidget);
   cy=childY(childWidget);
   int newWidth=newx - cx;
   int newHeight=newy - cy;

   newWidth=((newWidth / cellWidth()) * cellWidth());
   newHeight=((newHeight / cellHeight()) * cellHeight());
   if (newHeight < cellHeight())
      newHeight=cellHeight();
   if (newWidth < cellWidth())
      newWidth=cellWidth();

   return QSize(newWidth,newHeight);
}


//
// Respond to mouse move (with button pressed). Handle  drawing, resizing, 
// or moving a widget.
// 
void screenMaker::viewportMouseMoveEvent(QMouseEvent *e)
{
  
   QSize newSize;

   int myX=e->x();
   int myY=e->y();

   switch(currentScreenState) 
   {
   case DRAGGING:
      newSize=calculateNewSize(e->x(),e->y(),selectedRegion);
      selectedRegion->resize(newSize);
      break;
   case RESIZING:
      newSize=calculateNewSize(e->x(),e->y(),selectedWidget);
      selectedWidget->resize(newSize);
      break;
   case MOVING:
      roundToNearestCell(myX,myY);
      selectedWidget->move(myX,myY);
      break;
   default:
      break;
   }
}

//
//Remove a widget from the list and the screen. This is a slot.
//
void screenMaker::removeWidget(QWidget *search)
{
   fieldList.remove(search);
   delete search;
}

//
// Replace one widget with another on the drawing screen and in the
// widget list. This is a slot.
//
void screenMaker::replaceWidget(QWidget *search,QWidget *replace)
{

   // Handle identity ( most probably a coding misteak)
   // Don t use an assert, because it might not be one.
   if (search == replace)
      return;

   uint currentX=childX(search);
   uint currentY=childY(search);

   int widgetnum=fieldList.findRef(search);

   if (widgetnum > -1) {
      fieldList.replace(widgetnum,replace);
      delete search; // This also performs the removeChild() call.
   }
   else
      fieldList.append(replace);

   addChild(replace,currentX,currentY);   
   showChild(replace);
}

screenMaker::mouseState screenMaker::currentState()
{
   return currentScreenState;
}

//
// Get the background image, so we can save it if necessary.
//
const QPixmap & screenMaker::getBgImage()
{
   return bgimage;
}

//
// Is this point on any existing widgets?
//
bool screenMaker::pointOverlaps(int x,int y)
{
   QWidget *curNode=fieldList.first();
   QRect wRect;
   bool retVal=FALSE;
   while(curNode)
   {
      wRect=curNode->geometry();
      if (wRect.contains(x,y))
      {
	 retVal=TRUE;
	 break;
      }
      curNode=fieldList.next();
   }
   return retVal;
}
