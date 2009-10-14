#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H

//
// Handle the interface between view and database.
//

#include <qobject.h>
#include <qstring.h>
#include <qmap.h>

#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qsqlcursor.h>


typedef QMap<QString,QString> colValues;
typedef QValueList<QString> colNames;
typedef QValueList<QString> colVals;

class dataInterface : public QObject
{
 Q_OBJECT

 public:
   enum fetchType { NEXT,PREV,FIRST,LAST};
   dataInterface(QString dbType=0,QString dbName=0);
   ~dataInterface();
   QString getDBType();
   bool openDB(QString dbn=0,QString uname=0,QString upass=0);
   bool makeSetTable(QString,const colValues &);
   void closeDB(); 
   bool isValid();
   bool setTable(QString name);
   bool makeTable(QString name, const colValues &);
   bool getARecord(colValues &,enum fetchType);

 public slots:
   void getRecord(colValues &,bool *retVal=0);
   void setRecord(const colValues &,bool *retVal=0);
   void appendRecord(const colValues &,bool *retVal=0);
   void updateRecord(const colValues &,bool *retVal=0);
   void getNextRecord(colValues &,bool *retVal=0);
   void getPrevRecord(colValues &,bool *retVal=0);
   void getFirstRecord(colValues &,bool *retVal=0);
   void getLastRecord(colValues &,bool *retVal=0);

   void getLastError(QString &) const;

 signals:   
   void recordGotten(const colValues &);

 protected:
   QSqlCursor *currentQ;
   void makeNewCurrentDB(QString,QString dbn="");
   void makeNewCursor();
   bool currentRecToColValues(QSqlCursor *,colValues &);
   QSqlDatabase *currentDB;
   QString dbName;
   QString tableName;
   QString lastError;
};




#endif // DATAINTERFACE_H
