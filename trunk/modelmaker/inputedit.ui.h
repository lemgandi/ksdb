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

/*
* This file is part of ksdb
* Copyright (c) Charles Shapiro Sep 2009
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

void inputEditor::init()
{
    wTemplate=0;
    QRegExpValidator *myValidator= new QRegExpValidator(QRegExp("\\w+"),fieldNameEdit,"fieldnamevalidator");
    
    fieldNameEdit->setValidator(myValidator);
}

void inputEditor::nameFieldChanged( const QString & newFieldNameData )
{
   currentNameField=newFieldNameData;
   
}

void inputEditor::query( const QString & addressedName )
{

    QString myname=QString(name());
    
    qDebug("inputEditor::query %s, myname %s",addressedName.latin1(),name());
 
 if( (addressedName == myname) && (! currentNameField.isNull()) )
 {
     QString wType;
     fields["name"]=myname;
     fields["fieldname"]=currentNameField;
     QWidget *newWidget=makeNewWidget(wType);
     fields["widgetname"]=wType;
     fields["datatype"]=QString("char(%1)").arg((newWidget->height() * newWidget->width())/(scrMakerWidget->cellHeight() * scrMakerWidget->cellWidth()) );
     emit accepted(fields,newWidget);
     clearFields();
 }
}


//
// Store widget template.
//
void inputEditor::getWidgetTemplate( const QWidget *wp,const screenMaker *s )
{
  wTemplate=wp;
  scrMakerWidget=s;
}


QWidget * inputEditor::makeNewWidget(QString &widgetType)
{
    Q_ASSERT(wTemplate != 0);
    QWidget *retVal;
    
    wEditLineEditHandler wLineEditMaker;
    wEditTextEditHandler wTextEditMaker;
    wEditHandler *handlerP;
    int cellheight=scrMakerWidget->cellHeight();
    
    if(wTemplate->height() > cellheight)
    {
	handlerP=&wTextEditMaker;
	widgetType=QString("QTextEdit");
    }
    else
    {
	handlerP=&wLineEditMaker;
	widgetType=QString("QLineEdit");
    }
    handlerP->setScreenMaker(scrMakerWidget);
    qDebug("scrMakerWidget: %p fields[\"name\"]: %s wTemplate->height(): %d",
	   scrMakerWidget,(const char *)fields["name"],wTemplate->height() );
    retVal=handlerP->makeWidget(fields["name"],wTemplate->size(),wTemplate->pos(),fields);
    return retVal;
}

void inputEditor::clearFields()
{
    fieldNameEdit->clear();
}



void inputEditor::setData( const fieldVals &widgetData )
{
   qDebug("inputEditor::setData");

   QString myName=QString(name());

   if (myName == widgetData["name"])   
      fieldNameEdit->setText(widgetData["fieldname"]);   
}

//
// Respond to signal that field size has changed -- make sure that
// widget is correct type (QLineEdit for single-line field, QTextEdit for
// multi-line fields.
void inputEditor::sizeChange( QWidget *w, fieldVals *wd )
{
   qDebug("inputeditor::sizeChange fieldname=%s",(const char *)wd->find("name").data());
 QString myName=QString(name());
   if(myName == wd->find("name").data())
   {
      qDebug("inputedit: sizeChange()");
      wTemplate=w;
      fields=*wd;
      QString wType;
      QWidget * theNewWidget = makeNewWidget(wType);
      qDebug("inputedit:sizeChange:new type: %s",(const char *)wType);
      wd->replace("widgetname",wType);
      emit unconditionally_accepted(*wd,theNewWidget);
   }
}
