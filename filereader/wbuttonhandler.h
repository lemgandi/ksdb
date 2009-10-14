#ifndef WBUTTONHANDLER_H
#define WBUTTONHANDLER_H
// Create a label widget from widget data (e.g. read from disk)

#include "typedefs.h"
#include "widgethandler.h"

class QWidget;

class wButtonHandler : public widgetHandler 
{
 Q_OBJECT
 public:
   virtual QWidget *makeWidget(const QString &,QSize,QPoint,const fieldVals &);
};


#endif // WBUTTONHANDLER_H
