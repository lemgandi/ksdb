#ifndef WLINEEDITHANDLER_H
#define WLINEEDITHANDLER_H

#include "typedefs.h"
#include "widgethandler.h"

class QWidget;

class wLineEditHandler : public widgetHandler
{
  Q_OBJECT
 public:
   QWidget *makeWidget(const QString &,QSize,QPoint,const fieldVals &);
};

#endif //WLINEEDITHANDLER_H

