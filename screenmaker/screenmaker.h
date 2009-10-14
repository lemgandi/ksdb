/*
 * This widget puts a field on the screen and lets you define areas on it for 
 * data input.
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
#ifndef SCREENMAKER_H
#define SCREENMAKER_H

#include <qwidget.h>
#include <qgridview.h>
#include <qpixmap.h>
#include <qptrlist.h>

class QRect;
class QLabel;
class QFrame;
class QSize;


typedef QPtrList<QWidget> WPList;

class screenMaker : public QGridView
{
    Q_OBJECT


public:
    enum mouseState { DRAWING,DRAGGING,SELECTING,SELECTED,MOVING,RESIZING};
    screenMaker( QWidget *parent = 0,const char *name=0);
    void viewportMousePressEvent(QMouseEvent *);
    void viewportMouseReleaseEvent(QMouseEvent *);
    void viewportMouseMoveEvent(QMouseEvent *);
    const WPList & getFieldList();
    void setFieldList(const WPList &);
    void makeNewWidget(QMouseEvent *);
    void maybeSelectWidget(QMouseEvent *);
    const QPixmap &getBgImage();
    void setAllowOverlap(bool);
    bool getAllowOverlap();

 signals:
    void regionSelected(QWidget *);
    void widgetSelected(QWidget *);
    void widgetResized(QWidget *);
    void widgetMoved(QWidget *);

 public slots:    
    enum mouseState currentState();
    void selectMode();
    void drawMode();
    void moveWidget(QWidget *);
    void resizeWidget(QWidget *);    
    void replaceWidget(QWidget *,QWidget *);
    void removeWidget(QWidget *);
    void clearDrawingField();
    void setBackground(const QPixmap &);
    void mousePressed(QMouseEvent *);

 protected:
    bool pointOverlaps(int,int);
    void paintCell(QPainter *,int,int);
    void roundToNearestCell(int &,int &);
    QSize minimumSize;

private:
    bool allowOverlap;
    static const unsigned int LISTSIZE=25;
    WPList fieldList;
    QSize calculateNewSize(int,int,QWidget *);
    QWidget *selectedWidget;
    QFrame *selectedRegion;    
    QWidget *onWidget(int,int);
    mouseState currentScreenState;
    QPixmap bgimage;
};
#endif
