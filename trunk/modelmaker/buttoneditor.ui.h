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
void buttonEditor::init()
{
    templateWidget=0;    
}

void buttonEditor::query( const QString &addressedName )
{
   QString myName=QString(name());
   
   qDebug("AddressedName: %s myName: %s",addressedName.latin1(),myName.latin1());
   
   if((addressedName == myName) && (! buttonType.isNull()))
   {
       fields["name"]=myName;
       fields["buttonType"]=buttonType;
       fields["buttonLegend"]=buttonLegend;
       fields["widgetname"]=QString("QPushButton");
       QWidget *theWidget=makeNewWidget();
       emit accepted(fields,theWidget);
       clearFields();
   }
}

//
// Make a new button and send it back to the mainwindow.
//
QWidget * buttonEditor::makeNewWidget()
{
    qDebug("MakeNewWidget");    
    Q_ASSERT(templateWidget != 0);
    
    wEditButtonHandler buttonmaker;
    buttonmaker.setScreenMaker(makerWidget);
    
    QWidget *retVal = buttonmaker.makeWidget(fields["name"],templateWidget->size(),templateWidget->pos(),fields);
    
    return retVal;
}


void buttonEditor::labelTextChanged( const QString &changedText )
{
   buttonLegend=changedText;  
}

void buttonEditor::buttonTypeSelected( const QString & selectedText)
{
    qDebug("Button Type Selected: %s",selectedText.latin1());
   buttonType=selectedText; 
   buttonLegendEdit->setText(selectedText);

}


void buttonEditor::getWidgetTemplate( const QWidget * tw,const screenMaker *s)
{
    qDebug("buttonEditor::getWidgetTemplate tw=%p",tw);
   templateWidget=tw;
   makerWidget=s;
}

void buttonEditor::clearFields()
{
   buttonTypeListBox->clearSelection();
   buttonLegendEdit->clear();
}



void buttonEditor::setData( const fieldVals & widgetData )
{
   qDebug("buttonEditor::setData");
   QString myName=QString(name());
   
   if (widgetData["name"] == myName)
   {
      QListBoxItem *theItem=buttonTypeListBox->findItem(widgetData["buttonType"]);
      buttonTypeListBox->setSelected(theItem,TRUE);
      buttonLegendEdit->setText(widgetData["buttonLegend"]);
   }
}


void buttonEditor::sizeChange( QWidget *, fieldVals * )
{

}
