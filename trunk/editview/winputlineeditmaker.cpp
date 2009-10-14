// Implementation for winputlineeditmaker -- create a line edit widget from
// xml file.

#include <qlineedit.h>

#include "winputlineeditmaker.h"
#include "wlineeditinputhandler.h"

wInputLineEditMaker::wInputLineEditMaker(QWidget *w,inputHandlerList *l) : wInputWidgetMaker(w,l)
{
   return;
}

QWidget * wInputLineEditMaker::makeWidget(const QString &,QSize wSize,QPoint wLoc,const fieldVals & meta)
{
   QWidget *retVal = new QLineEdit(parentScreen,meta["fieldname"]);
   setWidgetSizeShape(retVal,wSize,wLoc);
   outInputHandlers->append(new wLineEditInputHandler(retVal));

   return retVal;
}
