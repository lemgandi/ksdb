// Implementation of checkboxeditorimpl

/*
* Copyright (c) Charles Shapiro Sep 2009
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
void checkboxEditorImpl::init()
{
   widgetTemplate=0;
   initialValue=FALSE;
}

void checkboxEditorImpl::labelTextChanged( const QString & newLabel)
{
   labelText=newLabel;
}
//
// Get legend
//
void checkboxEditorImpl::legendEditChanged(const QString &t)
{
    legendText=t;
}
//
// Called when the "ON" checkbox is toggled. 
//
void checkboxEditorImpl::checkboxToggled(bool toggleState)
{
    initialValue=toggleState;
}
//
// Send back specific field values.
//
void checkboxEditorImpl::editFieldVals(const fieldVals &f)
{
   f["fieldName"]=labelText;
   f["widgetname"]=QString("QRadioButton");   
}

//
// Has the form been filled out correctly?
//
bool checkboxEditorImpl::checkFields()
{
   bool retVal=TRUE;
   if(labelText.isNull())
      retVal=FALSE;
   return retVal;
}

//
//Create widget for screenMaker3
//
QWidget *checkboxEditorImpl::makeNewWidget()
{
    Q_ASSERT(widgetTemplate != 0);
    QWidget *retVal;
    QCheckBox *newWidget = new QCheckBox(labelText,0,labelText.latin1());
    newWidget->setChecked(initialValue);
    newWidget->setText(legendText);
    newWidget->resize(widgetTemplate->size());
    
    retVal=newWidget;
    return retVal;
}

