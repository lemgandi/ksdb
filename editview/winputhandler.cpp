//
// Implementation file for winputhandler -- ancestor for input
// handlers.


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

#include <qwidget.h>

#include "winputhandler.h"

//
// Create. Dirty is false until someone edits the widget we are handling.
//
wInputHandler::wInputHandler(QWidget *theW)
{
   inputWidget=theW;
   Dirty=FALSE;
}

//
// If someone has edited data, then we now have data.
// 
bool wInputHandler::hasData()
{
   return Dirty;
}

//
// Decide what widget we are handling.
//
void wInputHandler::setWidget(QWidget *newW)
{
   inputWidget=newW;
}

//
// Return the original widget we were set up with 
// so that we can use it as an index to the metadata dictionary.
//
QWidget *wInputHandler::getWidget()
{
   return inputWidget;
}
