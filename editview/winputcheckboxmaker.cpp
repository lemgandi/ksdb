// Implementation for winputlineeditmaker -- create a line edit widget from
// xml file.

#include <qcheckbox.h>

#include "winputcheckboxmaker.h"
#include "wcheckboxeditinputhandler.h"

wInputCheckBoxMaker::wInputCheckBoxMaker(QWidget *w,inputHandlerList *l) : wInputWidgetMaker(w,l)
{
   return;
}

QWidget * wInputCheckBoxMaker::makeWidget(const QString &,QSize wSize,QPoint wLoc,const fieldVals & meta)
{
   QWidget *retVal = new QCheckBox(meta["legend"],parentScreen,meta["fieldname"]);
   setWidgetSizeShape(retVal,wSize,wLoc);
   bool defaultState=FALSE;
   if("TRUE" == meta["initialValue"])
      defaultState=TRUE;
   outInputHandlers->append(new wCheckBoxEditInputHandler(retVal,defaultState));

   return retVal;
}
