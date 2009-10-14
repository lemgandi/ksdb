#ifndef MOCKEDITFIELD_H
#define MOCKEDITFIELD_H

// These objects are just like their Q* counterparts, except that they
// pass QMousePressEvents out as signals.  This enables me to select them 
// properly when the screenmaker is in select mode. 
// Otherwise their mouse event handlers swallow the
// click and I never see the event.

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
#include <qwidget.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qcheckbox.h>

class mockCheckBoxField: public QCheckBox
{
  Q_OBJECT
  public:
     mockCheckBoxField(const QString &,QWidget *,const char *n=0);
     void mousePressEvent(QMouseEvent *);
 signals:
     void mousePressed(QMouseEvent *);

};
class mockTextEditField: public QTextEdit
{
   Q_OBJECT

public:
   mockTextEditField(const QString &contents,const QString &context="",QWidget *parent=0,const char *name=0);
   // Why is this not QWidget s MousePressEvent? I do not know. MousePressEvent
   // never gets called on QTextEdit objects.
   void contentsMousePressEvent(QMouseEvent *);

signals:
   void mousePressed(QMouseEvent *);
   void mouseMoved(QMouseEvent *);
};

class mockPushButtonField: public QPushButton
{
   Q_OBJECT

public:
   mockPushButtonField(const QString &,QWidget *parent=0,const char *name=0);
   void mousePressEvent(QMouseEvent *);

 signals:
   void mousePressed(QMouseEvent *);

};


class mockLineEditField: public QLineEdit
{
   Q_OBJECT

public:
   mockLineEditField(const QString &contents,QWidget *parent=0,const char *name=0);
   void mousePressEvent(QMouseEvent *);


signals:
   void mousePressed(QMouseEvent *);
   void mouseMoved(QMouseEvent *);
};

#endif // MOCKEDITFIELD_H
