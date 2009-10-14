//
// Implementation of wedithandler -- widget makers for modelmaker.
//
#include <qobject.h>

#include "wedithandler.h"
#include "screenmaker.h"

/*
* Copyright Charles Shapiro Sep 2009
*
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
wEditHandler::wEditHandler(const screenMaker *s) : widgetHandler()
{
   theScreenMaker=s;
}

void wEditHandler::setScreenMaker(const screenMaker *sm)
{
   theScreenMaker=sm;
}

//
// 
// Connect mousepressed event to screenmaker. This way we can 
// select the widget properly when in select mode.
//
void wEditHandler::connectWidget(QWidget *w)
{
   if(theScreenMaker)
      connect(w,SIGNAL(mousePressed(QMouseEvent *)),theScreenMaker,SLOT(mousePressed(QMouseEvent *)));

}
