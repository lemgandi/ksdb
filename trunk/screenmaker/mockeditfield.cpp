//
// Implementation for mockeditfield -- an edit field which passes mouse
// presses on.
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
#import <qlineedit.h>
#import <qtextedit.h>
#import <qpoint.h>
#import <qevent.h>

#import "mockeditfield.h"


mockLineEditField::mockLineEditField(const QString &contents,QWidget *parent,const char *name) : QLineEdit(contents,parent,name)
{
   //Do nothing here.
}

void mockLineEditField::mousePressEvent(QMouseEvent *e)
{
   QLineEdit::mousePressEvent(e);
   emit mousePressed(e);
}


mockTextEditField::mockTextEditField(const QString &contents,const QString &context,QWidget *parent, const char *name) : QTextEdit(contents,context,parent,name)
{
   // Do nothing here.
}

//
// Emit mouse pressed event when we get a mouse press.
//
void mockTextEditField::contentsMousePressEvent(QMouseEvent *e)
{
   QTextEdit::contentsMousePressEvent(e);
   emit mousePressed(e);
}

mockPushButtonField::mockPushButtonField(const QString &lt,QWidget *p,const char *n) : QPushButton(lt,p,n)
{
}

void mockPushButtonField::mousePressEvent(QMouseEvent *e)
{
   QPushButton::mousePressEvent(e);
   emit mousePressed(e);
}

mockCheckBoxField::mockCheckBoxField(const QString &t,QWidget *w,const char *n): QCheckBox(t,w,n)
{
}

void mockCheckBoxField::mousePressEvent(QMouseEvent *e)
{
   QCheckBox::mousePressEvent(e);
   emit mousePressed(e);
}
