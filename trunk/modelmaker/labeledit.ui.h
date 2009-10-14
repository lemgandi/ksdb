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
void labelEditor::init()
{
    templateWidget=0;
}
void labelEditor::labelTextChanged( const QString &newText )
{
   currentTextField=newText;
}

void labelEditor::query( const QString & addressedName)
{
   QString myName=QString(name());
   if ((addressedName == myName) && (! currentTextField.isNull()))   {
       fields["name"]=myName;
       fields["labelText"]=currentTextField;
       fields["widgetname"]=QString("QLabel"); 
       QWidget *newWidget=makeNewWidget();
       emit accepted(fields,newWidget);
       clearFields();
   }
}

QWidget * labelEditor::makeNewWidget()
{
    Q_ASSERT(templateWidget != 0);
    
    wLabelHandler labelMaker;
    
    QWidget *retVal = labelMaker.makeWidget(fields["name"],templateWidget->size(),templateWidget->pos(),fields);
    
    return retVal;
}

void labelEditor::getWidgetTemplate( const QWidget *wp,const screenMaker *)
{
   templateWidget=wp;
}

void labelEditor::clearFields()
{
    labelTextEdit->clear();
}



void labelEditor::setData( const fieldVals & widgetData)
{

   qDebug("labelEditor::setData");
   QString myName = QString(name());
   if (widgetData["name"] == myName)
   {
      labelTextEdit->setText(widgetData["labelText"]);
   }
}
