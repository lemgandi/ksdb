#include <qapplication.h>
#include <qstring.h>
#include <qstringlist.h>

#include "datainterface.h"

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

void printRecord(const char *context,colValues p)
{
   qDebug("Record: %s",context);
   colValues::iterator iter;
   for(iter=p.begin();iter != p.end();++iter)   
      qDebug("Field %s value %s",(const char *)iter.key(),(const char *)iter.data());   
}
void reportError(const char *context, const dataInterface & IF)
{

   QString myErr=context;
   myErr += ": ";
   QString the_error;
   IF.getLastError(the_error);
   myErr += the_error;
   qDebug("%s",(const char *)myErr);
   
}
// Main line for test application

int main( int argc, char ** argv )
{
   QApplication app( argc, argv );
   colValues params;
   QString recName="Marcus Garvey";
   QString tableName="Onest";

   dataInterface myIF("QMYSQL3","ksdbtest"); // This also works.

   // dataInterface myIF("QSQLITE","./myDB.sqlite"); // This also works.
   bool retVal=myIF.openDB();
   if(retVal)
   {
      params.clear();
      params.insert("Name","char(80)");
      params.insert("Height","int");
      params.insert("Weight","int");
      params.insert("Funny","boolean");
      retVal=myIF.makeSetTable(tableName,params);
      if(! retVal)	 
	 reportError("makeTable",myIF);	 
   }
   if(retVal)
   {
      params.clear();
      params.insert("Name",recName);
      params.insert("Height","175");
      params.insert("Weight","64");
      params.insert("Funny","False");
      myIF.appendRecord(params,&retVal);
      params["Name"]="Jim Smith";
      qDebug("Params [Name] = %s",(const char *)params["Name"]);
      myIF.appendRecord(params,&retVal);
      params["Name"]="Harpo Marx";
      params["Funny"]="1";
      myIF.appendRecord(params,&retVal);
      params["Name"]="Jellyroll Morton";
      params["Height"]="130";
      params["Weight"]="85";
      myIF.appendRecord(params,&retVal);
   }
   if(! retVal)
      reportError("Append",myIF);
   if(retVal)
   {
      params.clear();
      params.insert("Name",recName);
      myIF.getRecord(params,&retVal);
      printRecord("get record",params);
   }
   if(retVal)
   {
      myIF.getNextRecord(params,&retVal);
      printRecord("next",params);
      myIF.getNextRecord(params,&retVal);
      printRecord("next",params);
      myIF.getPrevRecord(params,&retVal);
      printRecord("prev",params);
      myIF.getFirstRecord(params,&retVal);
      printRecord("first",params);
      myIF.getNextRecord(params,&retVal);
      printRecord("next",params);

      myIF.getLastRecord(params,&retVal);
      printRecord("last",params);
      myIF.getPrevRecord(params,&retVal);
      printRecord("prev",params);

      params["Name"]="Letitia M. Jereboam";
      printRecord("Update",params);
      myIF.updateRecord(params,&retVal);
      if(! retVal)
	 reportError("Update",myIF);
   }
}
