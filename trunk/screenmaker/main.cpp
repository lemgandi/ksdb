#include <qapplication.h>
#include <qlayout.h>
#include <qpushbutton.h>

#include "screenmaker.h"
#include "testwidget.h"

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

// Main line for test application

int main( int argc, char ** argv )
{
   QApplication app( argc, argv );
   app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
   testWidget *t = new testWidget(0,"TestWdget");
   t->show();
   return app.exec();
}
