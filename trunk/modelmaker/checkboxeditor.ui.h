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
// Gee Whiz, you'd think these could be subclasses of an ancestor class. But
// alas see fieldeditor.ui.h for an explanation of why not. 
//

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
//
//Init -- set variables as needed.

void checkboxEditor::init()
{
    widgetTemplate=0;
    initialValue=FALSE;
    QRegExpValidator * tNameValidator = new QRegExpValidator(QRegExp("\\w+"),nameEditField,"tableNameValidator");
    nameEditField->setValidator(tNameValidator);
}
void checkboxEditor::labelTextChanged( const QString & newLabel)
{
   labelText=newLabel;
   legendEdit->setText(newLabel);
}
//
// Get legend
//
void checkboxEditor::legendEditChanged(const QString &t)
{
    legendText=t;
}
//
// Called when the "ON" checkbox is toggled. 
//
void checkboxEditor::checkboxToggled(bool toggleState)
{
    initialValue=toggleState;
}

//
// Ask for values.
//
void checkboxEditor::query(const QString &addrName)
{
    qDebug("checkboxEditor::query");
    QString myName=QString(name());
    if( (addrName == myName) && (! labelText.isNull()) )
    {
	fields["name"]=myName;
	fields["fieldname"]=labelText;
	fields["legend"]=legendText;
	fields["widgetname"]=QString("QCheckBox");
	fields["datatype"]=QString("boolean");
	if (initialValue)
	   fields["initialValue"]=QString("TRUE");
	else
	   fields["initialValue"]=QString("FALSE");
	QWidget *myWidget=makeNewWidget();
	emit accepted(fields,myWidget);
	clearFields();
    }
}

//
// Receive widget template.
//
void checkboxEditor::getWidgetTemplate(const QWidget *w,const screenMaker *s)
{
    qDebug("checkboxEditor::getWidgetTemplate: w=%p s=%p",w,s);
    widgetTemplate=w;    
    screenmakerWidget=s;
}

//
//Create widget for screenMaker3
//
QWidget *checkboxEditor::makeNewWidget()
{
    Q_ASSERT(widgetTemplate != 0);
    wEditCheckboxHandler checkboxMaker;
    checkboxMaker.setScreenMaker(screenmakerWidget);
    QWidget *retVal=checkboxMaker.makeWidget(fields["name"],widgetTemplate->size(),widgetTemplate->pos(),fields);
        
    return retVal;
}

void checkboxEditor::clearFields()
{
    nameEditField->clear();
    legendEdit->clear();
    checkBoxState->setChecked(FALSE);
}

void checkboxEditor::setData(const fieldVals &widgetData)
{
    qDebug("checkboxEditor::setData");
    QString myName=QString(name());
    if (widgetData["name"] == myName)
    {
       // Member variables should get set with setText from the 
       // appropriate slots.
       nameEditField->setText(widgetData["fieldName"]);
       legendEdit->setText(widgetData["legend"]);
       bool iVal=FALSE;
       if (widgetData["initialValue"]=="TRUE")
	  iVal=TRUE;
       checkBoxState->setChecked(iVal);
    }
}
