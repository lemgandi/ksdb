// Implementation of winputwidgethandler --read and instantiate a widget
// from xml file.

#include "winputwidgetmaker.h"

wInputWidgetMaker::wInputWidgetMaker(QWidget *wP,inputHandlerList *oList) : widgetHandler()
{
   parentScreen=wP;
   outInputHandlers=oList;
}
