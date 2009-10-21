/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

//
// Get name of table for form
//
void settingsForm::tableNameChanged( const QString & tn )
{
    tableName=tn;
}

// 
// Get database we will be using.
//
void settingsForm::dbiSelected( QListBoxItem *it)
{

    if(it)
       dbiName=it->text();    
}

void settingsForm::commitPressed()
{
    bool status=TRUE;
    if(dbiName.isNull())
    {
	noDBI();
	status=FALSE;
    }
    if(tableName.isNull() && (status))
    {
	noTable();
	status=FALSE;
    }    
    if(status)
    {
       emit newDBParams(tableName,databaseName,dbiName);
	accept();
    }
}
//
// Display complaint if no table name entered.
//
void settingsForm::noTable()
{
    QMessageBox::information(this,"Missing Table Name",
			     "I do not see a table name. Enter one in the \"Table Name\" field  or use the \"Quit\" button to exit this form.",QMessageBox::Ok);
}
//
// Display complaint if no database interface entered.
//
void settingsForm::noDBI()
{
    QMessageBox::information(this,"Missing Database Type",
			     "I do not see a database type. Choose one in the \"Database Interface\" field or use the \"Quit\" button to exit this form.",QMessageBox::Ok);
}

void settingsForm::noDBName()
{
   QMessageBox::information(this,"Missing Database Name",
			     "I do not see a database name. Enter one in the \"Database Name\"s field  or use the \"Quit\" button to exit this form.",QMessageBox::Ok);
}

void settingsForm::dbNameChanged(const QString &newName)
{
    databaseName=newName;
}
void settingsForm::exec()
{
    tableName=(const char *)0;
    dbiName=(const char *)0;
    QDialog::exec();
}


void settingsForm::changeValues( QString tn, QString dbn, QString dbin)
{
   // tableName=tn;
   //   databaseName=dbn;
   // dbiName=dbin;
   lineEdiTableName->setText(tn);
   lineEditDBName->setText(dbn);
   qDebug("dbin: %s",(const char *)dbin);
   ListBoxDBI->setSelected(ListBoxDBI->findItem(dbin),TRUE);
}
