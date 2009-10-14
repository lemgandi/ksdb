// Implementation for winputlineeditmaker -- create a line edit widget from
// xml file.

#include <qtextedit.h>

#include "winputtexteditmaker.h"
#include "wtexteditinputhandler.h"

wInputTextEditMaker::wInputTextEditMaker(QWidget *w,inputHandlerList *l) : wInputWidgetMaker(w,l)
{
   return;
}

QWidget * wInputTextEditMaker::makeWidget(const QString &,QSize wSize,QPoint wLoc,const fieldVals & meta)
{
   QWidget *retVal = new QTextEdit(parentScreen,meta["fieldname"]);
   setWidgetSizeShape(retVal,wSize,wLoc);
   outInputHandlers->append(new wTextEditInputHandler(retVal));

   return retVal;
}
