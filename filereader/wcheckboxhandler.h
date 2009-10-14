#ifndef WIDGETCHECKBOXHANDLER_H
#define WIDGETCHECKBOXHANDLER_H
// Create a label widget from widget data (e.g. read from disk)

#include "typedefs.h"
#include "widgethandler.h"

class QWidget;

class wCheckboxHandler : public widgetHandler 
{
 Q_OBJECT
 public:
   virtual QWidget *makeWidget(const QString &,QSize,QPoint,const fieldVals &);
};


#endif // WIDGETCHECKBOXHANDLER_H

