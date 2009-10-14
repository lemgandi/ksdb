// Implementation for winputlineeditmaker -- create a line edit widget from
// xml file.

#include <qpushbutton.h>

#include "winputbuttonmaker.h"
#include "wbuttoninputhandler.h"

wInputButtonMaker::wInputButtonMaker(QWidget *w,inputHandlerList *l) : wInputWidgetMaker(w,l)
{
   return;
}

QWidget * wInputButtonMaker::makeWidget(const QString &,QSize wSize,QPoint wLoc,const fieldVals & meta)
{
   QWidget *retVal = new QPushButton(meta["buttonLegend"],parentScreen,meta["fieldname"]);
   setWidgetSizeShape(retVal,wSize,wLoc);
   qDebug("meta[\"buttonType\"]=%s Number of items in meta: %d", (const char *)meta["buttonType"],meta.count() );
   outInputHandlers->append(new wButtonInputHandler(retVal,parentScreen,meta));

   return retVal;
}
