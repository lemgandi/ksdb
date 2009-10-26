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
  * It is a bummer that I cannot use inheritance for the objects which go
  * into the widget stack. but alas the Q_OBJECT macro defines some 
  * routines. Because of the QT inheritance model 
  * ( QT designer object -> QT implementation object), I'd have to use a 
  * mix-in class (multiple inheritance, e.g. 
  * QT designer object + mix-in -> QT implementation object ) to put 
   * common routines into these classes,
  * and that path leads to an ambiguous call compiler error. I've saved 
  * the files: fieldeditors.h, fieldeditors.cpp,checkboxeditorimpl.h, 
  * and checkboxeditorimpl.cpp as an example should someone 
  * smarter than me wish to tackle this problemo in order to remove the 
  * redundant code in the inputEditor,labelEditor,buttonEditor, and 
  * checkboxEditor classes.
  */

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
// Set up widget stack for various objects
//
void fieldEditor::init()
{
    
     //set up QDict name->ptr dictionary between type editor widgets
    // and the names in the fieldTypeListBox + "blank"
    blankEditor *blankFields=new blankEditor(0,"blankeditor");
    fieldEditorStack->addWidget(blankFields);
    stackDict.insert("blank",blankFields);
    
    buttonEditor *buttonFields = new buttonEditor(0,"buttoneditor");
    fieldEditorStack->addWidget(buttonFields);
    stackDict.insert("Button",buttonFields);
        connect(this,SIGNAL(publishReplaceWidget(const QWidget *,const screenMaker *)),buttonFields,SLOT(getWidgetTemplate(const QWidget *,const screenMaker *)));
        connect(this,SIGNAL(setEditData(const fieldVals &)),buttonFields,SLOT(setData(const fieldVals &)));
        connect(this,SIGNAL(valueQuery(const QString &)),buttonFields,SLOT(query(const QString &)));
	connect(this,SIGNAL(widgetSizeChanged(QWidget *,fieldVals *)),buttonFields,SLOT(sizeChange(QWidget *,fieldVals *)));
    connect(buttonFields,SIGNAL(accepted(const  fieldVals &,QWidget *)),this,SLOT(editorValues(const fieldVals &,QWidget *)));
    
    
    inputEditor *inputFields = new inputEditor(0,"inputeditor");
    stackDict.insert("Input",inputFields);
    connect(this,SIGNAL(valueQuery(const QString &)),inputFields,SLOT(query(const QString &)));
    connect(this,SIGNAL(publishReplaceWidget(const QWidget *,const screenMaker *)),inputFields,SLOT(getWidgetTemplate(const QWidget *,const screenMaker *)));
        connect(this,SIGNAL(setEditData(const fieldVals &)),inputFields,SLOT(setData(const fieldVals &)));
	connect(this,SIGNAL(widgetSizeChanged(QWidget *,fieldVals *)),inputFields,SLOT(sizeChange(QWidget *,fieldVals *)));
    connect(inputFields,SIGNAL(accepted(const fieldVals &,QWidget *)),this,SLOT(editorValues(const fieldVals &,QWidget *)));
    // Special hack so that inputfields can respond to sizeChange properly.
    connect(inputFields,SIGNAL(unconditionally_accepted(const fieldVals &,QWidget *)),this,SIGNAL(collectedValues(const fieldVals &,QWidget *)));
    fieldEditorStack->addWidget(inputFields);

    
    labelEditor *labelFields=new labelEditor(0,"labeleditor");
    fieldEditorStack->addWidget(labelFields);
    stackDict.insert("Label",labelFields);
    connect(this,SIGNAL(valueQuery(const QString &)),labelFields,SLOT(query(const QString &)));
        connect(this,SIGNAL(publishReplaceWidget(const QWidget *,const screenMaker *)),labelFields,SLOT(getWidgetTemplate(const QWidget *,const screenMaker *)));
    connect(this,SIGNAL(setEditData(const fieldVals &)),labelFields,SLOT(setData(const fieldVals &)));
	connect(this,SIGNAL(widgetSizeChanged(QWidget *,fieldVals *)),labelFields,SLOT(sizeChange(QWidget *,fieldVals *)));
    connect(labelFields,SIGNAL(accepted(const fieldVals &,QWidget *)),this,SLOT(editorValues(const fieldVals &,QWidget *)));

    checkboxEditor *checkboxFields=new checkboxEditor(0,"checkboxeditor");
    fieldEditorStack->addWidget(checkboxFields);
    stackDict.insert("Checkbox",checkboxFields);
    connect(this,SIGNAL(valueQuery(const QString &)),checkboxFields,SLOT(query(const QString &)));
        connect(this,SIGNAL(publishReplaceWidget(const QWidget *,const screenMaker *)),checkboxFields,SLOT(getWidgetTemplate(const QWidget *,const screenMaker *)));
    connect(this,SIGNAL(setEditData(const fieldVals &)),checkboxFields,SLOT(setData(const fieldVals &)));
	connect(this,SIGNAL(widgetSizeChanged(QWidget *,fieldVals *)),checkboxFields,SLOT(sizeChange(QWidget *,fieldVals *)));
    connect(checkboxFields,SIGNAL(accepted(const fieldVals &,QWidget *)),this,SLOT(editorValues(const fieldVals &,QWidget *)));
 
    // Raise the "blank" widget.
    fieldEditorStack->raiseWidget(stackDict["blank"]);
}

//
// Bring up form for appropriate object info.
//
void fieldEditor::editorPicked( QListBoxItem * chosenItem)
{
    QString chosenText=chosenItem->text();
    // Look up the chosenText in the QDict name->ptr dictionary
    // Raise that widget in the widgetstack.
    QWidget *whichItem=stackDict[chosenText];
    fieldEditorStack->raiseWidget(whichItem);
    emit publishReplaceWidget(replaceWidget,scrmaker);
    
}
// 
// Cancel operation; signal mainWindow to remove the widget from
// screenMaker3.
//
void fieldEditor::reject()
{
    qDebug("fieldEditor: reject");
    emit collectedValues(inputValues,(QWidget *)0);
    QDialog::reject();
}
//
// Accept iff the field editor is filled out.
//
void fieldEditor::accept()
{
  
    QString currentEditorName(fieldEditorStack->visibleWidget()->name());
    qDebug("emit valueQuery %s",currentEditorName.latin1());
    
    emit valueQuery(currentEditorName);
    if (inputValues.isEmpty())
    {
	int action=QMessageBox::warning(this,
		"Oops","Please check the indicated field or quit","Retry","Quit",0,0,1);
	switch(action) 
	{
	case 0:
	    return;
	case 1:
	    reject();
	}
    }
    else {
	sendInputData();	
	QDialog::accept();
    }
    fieldEditorStack->raiseWidget(stackDict["blank"]);
    QListBoxItem *selectedItem = fieldTypeListBox->selectedItem();
    if (selectedItem)
	fieldTypeListBox->setSelected(selectedItem,FALSE);
}



//
// Send data to caller for storage.
//
void fieldEditor::sendInputData()
{
    qDebug("sendInputData: finishedWidget=%p",finishedWidget);
    showInputValues(inputValues);
    emit collectedValues(inputValues,finishedWidget);   
}

void fieldEditor::editorValues( const fieldVals &vals,QWidget *fieldWidget )
{
   finishedWidget=fieldWidget;
   inputValues=vals;
}

void fieldEditor::showInputValues( const fieldVals &showMap ) 
{
    fieldVals::ConstIterator iter;
   
   for( iter=showMap.begin(); iter != showMap.end(); ++iter)
       qDebug("Key: %s Val: %s",(const char *)iter.key(),(const char *)iter.data() );
}


void fieldEditor::setReplaceWidget( const QWidget *w,const screenMaker *s)
{
    qDebug("fieldEditor:setReplaceWidget: %p screenmaker:%p",w,s);
    scrmaker=s;
   replaceWidget=w;
}


void fieldEditor::collectFinishedWidget( QWidget *wp )
{
   finishedWidget=wp;
}
