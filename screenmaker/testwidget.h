
#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <qwidget.h>
#include <qcolor.h>
#include <qpopupmenu.h>

#include "screenmaker.h"

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
class testWidget : public QWidget
{
Q_OBJECT

public:
   testWidget(QWidget *parent=0,const char *name=0);

signals:
    void drawMode(void);

public slots:
    void displayMsg(const char *);
    void regionDefined(QWidget *); 
    void newBg();
    void deSelectWidget(QWidget *);
    void selectWidget(QWidget *);
    void toDrawMode();
    void moveItem();
    void resizeItem();
    void itemProperties();
private:
    void makeLabel();
    void makeField();
    void removeCurrentWidget();
    void unselectWidget();
    screenMaker *scrMakerWidget;
    QWidget *currentWidget;
    QColor oldColor;
    QPopupMenu *cutMenu;
};

#endif // TESTWIDGET_H
