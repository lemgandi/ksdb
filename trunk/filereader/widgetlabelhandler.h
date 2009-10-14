#ifndef WIDGETLABELHANDLER_H
#define WIDGETLABELHANDLER_H
// Create a label widget from widget data (e.g. read from disk)

#include "typedefs.h"
#include "widgethandler.h"

class QWidget;

class widgetLabelHandler : public widgetHandler 
{
 public:
   widgetLabelHandler();
   ~widgetLabelHandler();
   virtual QWidget *makeWidget(const QString &,QSize,QPoint,const fieldVals &);
};


#endif // WIDGETLABELHANDLER_H
