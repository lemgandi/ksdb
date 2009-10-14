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
*
* Copyright (c) Charles Shapiro Sep 2009
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

/*
 * This file is a template ui.h file for adding new widget editors to
 * the modelmaker.  Create your form, then copy/paste this file into
 * the .ui.h slot to start making the signals and slots you will need
 * to create your new widget.  
 * I assume that you have a const QWidget *wTemplate field for the
 * object you are making, a const screenMaker *scrMakerWidget pointer
 * to the screenmaker widget, a fieldVals fields variable to hold the
 * names and values of the information you are passing back to the
 * fieldeditor, and an accepted(const fieldVals &fields,QWidget
 * *widget) signal to send it back.
 */
   
 */

//
// Initialize this widget
//
void myWidgetEditor::init()
{
   /* Initialize any other variables you need to 0 here. */
   wTemplate=0;

}

//
// A field has changed.
// This slot is where you move the values entered by the user into 
// object variables where you can manipulate them. It is also where
// you change values in other fields which may depend on the values entered
// in this field (e.g. legend and name).
//
void myWidgetEditor::fieldChanged(fieldArgs)
{


}
//
// This is the slot which the fieldeditor signals to find out what values
// the user has entered. Every widget editor gets this signal; you reply
// only if it is actually addressed to you through the name passed 
// as the parameter.
//
void myWidgetEditor::query(const QString &addressedName)
{
   QString myName=Qstring(name());
   if ((addressedName == myName) && (/* user has filled out required fields in form */))
   {
      fields["name"]=myName;
      fields["valuename"]=enteredValue;
      fields["widgetname"]=QTNameofmyWidget; /* e.g. "QListBox" */
      QWidget *newWidget=makeNewWidget();
      emit accepted(fields,newWidget);
      clearFields();
   }
}

//
// Slot to store the widget template and pointer to the screenmaker,
// both used to create and size a new widget correctly.
///
void myWidgetEditor::getWidgetTemplate(const QWidget *wp,const screenMaker *s)
{
   wTemplate=wp;
   scrMakerWidget=s;
}
//
//Create the new widget and pass it back.
//
QWidget *myWidgetEditor::makeNewWidget()
{
   Q_ASSERT(wTemplate != 0);
   QWidget *retVal;
   retVal = new myWidget(object variables);
   retVal->reSize(wTemplate->size());
   // The next line may be needed if your widget swallows QMouseEvent signals.
   // See "mockeditfield.h" for details.
   // connect(retVal,SIGNAL(mousePressed(QMouseEvent *)),scrMakerWidget,SLOT(mousePressed(QMouseEvent *)));
   return retVal;
}
//
// Clear the form as needed here.
//
void myWidgetEditor::clearFields()
{
}

//
// This slot sets input form fields with previously entered data. Every
// widget editor hears this signal; you should actually set your fields only
// if it is addressed to you (the widgetData["name"] field is your name).
void myWidgetEditor::setData(const fieldVals &widgetData)
{
   QString myName=QString(name());
   if (myName == widgetData["name"])
   {
      myField->setText(widgetData["dataname"]);
   }
}
