// Implementation for ksdb database.
//

#include <qstringlist.h>
#include <qregexp.h>
#include <qsqlindex.h>
#include <qsqlrecord.h>

#include "datainterface.h"
//
//Create.
//
dataInterface::dataInterface(QString dbT,QString dbN)
{
   currentDB=0;
   currentQ=0;
   dbName=dbN;
   lastError="Oops.";
   qDebug("dbT: %s dbN: %s",(const char *)dbT,(const char *)dbN);
   if(! dbT.isNull() && (! dbN.isNull()) )
      makeNewCurrentDB(dbT,dbN);
   return;
}

// 
// Convenience function to create a table if it is not present.
//
bool dataInterface::makeSetTable(QString tableName,const colValues &cols)
{
   bool status=TRUE;

   if(! setTable(tableName))
      status=makeTable(tableName,cols);
   return status;
}

//
// Close my database.
//
void dataInterface::closeDB()
{
   qDebug("Closing database.");
   if(currentDB)
      currentDB->close();
}

void dataInterface::setOrder(const QStringList &newOrder)
{
   if( newOrder.count() )
      readOrder=newOrder;
   else
      readOrder=QStringList("_ID");

   if(currentQ)
      currentQ->setSort(QSqlIndex::fromStringList(readOrder,currentQ));
}

//
// Throw away search patterns.
//
void dataInterface::unSetSearch()
{
   makeNewCursor();
   if(readOrder.count())
      currentQ->setSort(QSqlIndex::fromStringList(readOrder,currentQ));
}

//
// Set "order by" string appended to search.
//
QString dataInterface::selectOrderString(const QStringList &fieldNames)
{
   QString retVal;
   if(fieldNames.count())
   {
      retVal=" order by ";
      QStringList::ConstIterator iter;
      for(iter=fieldNames.constBegin();iter != fieldNames.constEnd();++iter)
      {
	 retVal.append(*iter);
	 retVal.append(",");
      }
      retVal.setLength(retVal.length()-1); // Remove extra comma
   }
   return retVal;
}

// 
// Get the order string. ("order by...")
//
const QStringList & dataInterface::getOrder()
{
   return readOrder;
}
//
// What type of db are we on?
//
QString dataInterface::getDBType()
{
   QString retVal;
   if(currentDB)
      retVal=currentDB->driverName();
   return retVal;
}

//
// Destructor -- nb that currentDB is destroyed elsewhere.
//
dataInterface::~dataInterface()
{

   delete currentQ;
   closeDB();
   return; // currentDB is owned by QT; they take care of deleting it.
}

//
// Create a new database connection.
//
void dataInterface::makeNewCurrentDB(QString drivername,QString dbName)
{
   currentDB = QSqlDatabase::addDatabase(drivername);

   if(! dbName.isNull()) 
   {
      qDebug("dbName: %s",(const char *)dbName);
      currentDB->setDatabaseName(dbName);
      qDebug("dbName is now %s",(const char *)currentDB->databaseName());
   }

   qDebug("Make new current drivername:%s db:%p",
    (const char *)drivername,currentDB);
}

//
// Open database.
//
bool dataInterface::openDB(QString dbn,QString uname,QString upass)
{
   bool retVal=FALSE;
   if(currentDB)
   {
      if(! dbn.isNull())      
	 currentDB->setDatabaseName(dbn);

      qDebug("currentDB->databaseName=%s",(const char *)currentDB->databaseName());      
      if(! uname.isNull())
	 retVal=currentDB->open(uname,upass);
      else
	 retVal=currentDB->open();
   }

   qDebug("Open database %p name %s uname %s upass %s return %d",currentDB,
	  (const char *)dbName,(const char *)uname,(const char *)upass,
   retVal);

   if(! retVal) 
   {
      lastError=currentDB->lastError().text();
      QString myError;
      getLastError(myError);
      qDebug("Oops: %s",(const char *)myError);
   }
   return retVal;      
}

//
// Get data from currentRec into a colValues output envelope.
//
bool dataInterface::currentRecToColValues(QSqlCursor *cP,colValues & outEnvelope)
{
   //If currentRec is not valid, output nothing.
   outEnvelope.clear();
   qDebug("currentRecToColValues");
   bool status=TRUE;
   if(! cP)
      status = FALSE;
   if(status)
   {
      if(cP->isValid())
      {
	 for(unsigned int ii=0;(ii<cP->count());++ii)
	 
	    outEnvelope.insert(cP->fieldName(ii),cP->field(ii)->value().toString());
      }
      else
	 status=FALSE;
   }
   return status;
}

//
// Get a record by value
//
void dataInterface::getRecord(colValues &qVals,bool *retP)
{
   bool status=TRUE;
   colValues::iterator iter;
   QString selectStr="(";
   QString selectItemStr;
   for(iter=qVals.begin();iter != qVals.end();++iter)
   {
      selectItemStr="(";
      selectItemStr += iter.key();
      selectItemStr +=  " = ";
      selectItemStr += "\"";
      selectItemStr += iter.data();
      selectItemStr += "\"";
      selectItemStr += ")";
      if(selectStr.length() > 1)
	 selectStr.append (" and ");
      selectStr.append(selectItemStr);
   }
   selectStr.append(")");
   if(readOrder.count())
      selectStr.append(selectOrderString(readOrder));
   qDebug("selectStr: %s",(const char *)selectStr);
   makeNewCursor();
   currentQ->select(selectStr);
   status=currentQ->first();
   currentRecToColValues(currentQ,qVals);
   if(retP)
      *retP=status;
   return;
}

//
// Change values in an existing record.
//
void dataInterface::setRecord(const colValues &,bool *)
{
   return;
}
//
// Set the current table name (there can be only one)
// This is also called by makeTable(). Succeeds iff the table actually
// exists in the opened database.
//
bool dataInterface::setTable(QString theT)
{
   bool retVal=TRUE;
   if(! isValid())
      retVal=FALSE;
   if(retVal)
   {
      QRegExp tableFinder(QString("^%1$").arg(theT));
      QStringList foundTables = currentDB->tables().grep(tableFinder);
      if(foundTables.isEmpty())
      {
	 lastError=QString("Table %1 not found in database %2").arg(theT).arg(currentDB->databaseName());
	 retVal=FALSE;
      }
   }
   if(retVal)
   {
      tableName=theT;
      makeNewCursor();
   }
   return retVal;
}
//
// Append a new record to the db.
//
void dataInterface::appendRecord(const colValues &newVals, bool * retValP)
{
   bool status=TRUE;
   if(! isValid())
      status=FALSE;

   if(status)
   {
      if(tableName.isNull())
      {
	 lastError="No tablename to add a record to";
	 status=FALSE;
      }
   }   
   if(status)
   {
      QSqlQuery dbQ;
      QString cols=QStringList(newVals.keys()).join(", ");
      QString myQuery=QString("INSERT INTO %1 (").arg(tableName);
      myQuery += cols;
      myQuery += ") VALUES (:";
      QString binds=QStringList(newVals.keys()).join(", :");
      myQuery += binds;
      myQuery += ");";
      qDebug("myQuery: %s",(const char *)myQuery);

      //This automagically uses our default db, kept in currentDB.
      dbQ.prepare(myQuery);
      QString bindStr;
      colValues::ConstIterator iter;
      for(iter=newVals.constBegin();iter != newVals.constEnd(); ++iter)
      {
	 bindStr=":";
	 bindStr += iter.key();
	 dbQ.bindValue(bindStr,iter.data());
	 qDebug("Data: %s",(const char *)iter.data());
      }
      status=dbQ.exec();      
      if(! status)
	 lastError=currentDB->lastError().text();
   }

   if(retValP)
      *retValP=status;
   return;
}

//
// Get the first record by serial ID
//
void dataInterface::getFirstRecord(colValues &v,bool *r)
{
   bool status=getARecord(v,FIRST);
   if(r)
      *r=status;
}

//
// Get the last record by serial ID
//
void dataInterface::getLastRecord(colValues &v,bool *r)
{
   bool status=getARecord(v,LAST);
   if(r)
      *r=status;

}

//
// Get the next record.
//
void dataInterface::getNextRecord(colValues &v,bool *r)
{
   bool status=getARecord(v,NEXT);
   if(r)
      *r=status;
}
//
// Delete and new() the cursor. This appears to be the only way to
// get rid of a filter once applied on a cursor.
//
void dataInterface::makeNewCursor()
{
   qDebug("makeNewCursor: tableName=%s currentDB=%p",(const char *)tableName,currentDB);

   delete currentQ; // Should always be either null (after create) or valid.
   currentQ=new QSqlCursor(tableName,TRUE,currentDB);
   currentQ->setPrimaryIndex(currentQ->index("_ID"));
}
//
// Retrieve the next/prev/first/last record from the db
//
bool dataInterface::getARecord(colValues &outRec, enum fetchType t)
{
   bool status=TRUE;
   if(! isValid())   
      status=FALSE;
   if(status)
   {
      switch(t)
      {
      case NEXT:
	 status=currentQ->next();
	 break;
      case PREV:
	 status=currentQ->prev();
	 break;
      case FIRST:
	 unSetSearch();
	 currentQ->select();
	 status=currentQ->first();
	 break;
      default: // LAST
	 unSetSearch();
	 currentQ->select();
	 status=currentQ->last();
	 break;
      }
   }

   if(status)   
      status=currentRecToColValues(currentQ,outRec);   
   else   
      lastError=currentDB->lastError().text();

   return status;
}

//
// Retrieve the previous record from the db
//
void dataInterface::getPrevRecord(colValues &v,bool *r)
{
   bool status=getARecord(v,PREV);
   if(r)
      *r=status;
}

//
// Is this interface working? (e.g. has a current database which is 
// open)
bool dataInterface::isValid()
{
   bool retVal=TRUE;

   if(! currentDB)
   {
      lastError="No database interface";
      retVal=FALSE;
   }
   if(retVal)
   {
      if(! currentDB->isOpen())
      {
	 lastError=QString("Database interface %1 has not been opened")
          .arg(getDBType());
	 retVal=FALSE;
      }
   }
   return retVal;
}

//
// Create db table; value key = colname, value data = coltype
// Assume database is available and open.
//
bool dataInterface::makeTable(QString tableName,
const colValues & colParams)
{
   bool retVal=TRUE;

   if(! isValid())
      retVal=FALSE;
   if(retVal)
   {

      QString tableCmd;

      //OUCH! Incompatible SQL in sqlite driver!
      if("QSQLITE" == getDBType())
	 tableCmd= QString("create table %1 (_ID integer primary key")
          .arg(tableName);
      else
	 tableCmd = QString("create table %1 (_ID serial").arg(tableName);

      QString colSpec;
      colValues::ConstIterator it;
      for(it=colParams.constBegin();it != colParams.constEnd();++it)
      {
	 colSpec = QString(", %1 %2").arg(it.key()).arg(it.data());
	 tableCmd += colSpec;
      }
      tableCmd +=");";
      qDebug("Make Table: %s",(const char *)tableCmd);
      if( ! currentDB->exec(tableCmd).isActive())
      {     
	 lastError=currentDB->lastError().text();
	 retVal=FALSE;
      }           
      else // Set table name iff we have successfully  created it.
	 setTable(tableName); 
   }
   return retVal;
}

void dataInterface::deleteRecord(QString recNum,bool *retValP)
{
   bool retVal=deleteARecord(recNum);
   if(retValP)
      *retValP=retVal;
}
//
// Get the first record without killing find, order.
//
bool dataInterface::unOrder()
{
   bool retVal=isValid();
   if(retVal)   
   {
      setOrder(QStringList());
      currentQ->select();
   }
   return retVal;
}
//
// Delete a record from the database (probably by ID)
//
bool dataInterface::deleteARecord(QString recNum)
{
   bool status=TRUE;
   if (! isValid())
      status=FALSE;
   if(status)
   {
      QSqlQuery dbQ;
      QString delQuery=QString("delete from %1 where _ID=%2")
	 .arg(tableName)
	 .arg(recNum);
      qDebug("Delete query: %s",(const char *)delQuery);
      dbQ.prepare(delQuery);
      status=dbQ.exec();
      if(! status)
	 lastError=currentDB->lastError().text();
   }
   return status;
}

//
// Update a record already in the database.
//
void dataInterface::updateRecord(const colValues &upData,bool *retVal)
{
   bool status=TRUE;
   QSqlCursor updateCursor(tableName,TRUE,currentDB);
   QString selectStr=QString("_ID=")+upData["_ID"];
   updateCursor.select(selectStr);
   if(updateCursor.first())
   {
      QSqlRecord *editBuf=updateCursor.primeUpdate();
      colValues::ConstIterator iter;
      for(iter=upData.constBegin();iter != upData.constEnd();++iter)
      {
	 if(iter.key() != "_ID") 
	 {
	    qDebug("Set editBuf (%s,%s)",(const char *)iter.key(),
		   (const char *)iter.data());
	    editBuf->setValue(iter.key(),iter.data());	 
	 }
      }
      status=updateCursor.update();
   }
   else
      status=FALSE;
   if(! status)
      lastError=currentDB->lastError().text();

   if(retVal)
      *retVal=status;
}
//
// Get the last bad thing that happened.
//
void dataInterface::getLastError(QString &errorStr) const
{
   errorStr=lastError;
}
