#ifndef  WINPUTLINEEDITMAKER_H
#define WINPUTLINEEDITMAKER_H

#include "winputwidgetmaker.h"
#include "winputhandler.h"


class wInputLineEditMaker : public wInputWidgetMaker
{
   Q_OBJECT
   public:
      wInputLineEditMaker(QWidget *,inputHandlerList *);
      QWidget * makeWidget(const QString &,QSize,QPoint,const fieldVals &);
};
#endif //  WINPUTLINEEDITMAKER_H

