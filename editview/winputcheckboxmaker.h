#ifndef  WINPUTCHECKBOXMAKER_H
#define WINPUTCHECKBOXMAKER_H

#include "winputwidgetmaker.h"
#include "winputhandler.h"


class wInputCheckBoxMaker : public wInputWidgetMaker
{
   Q_OBJECT
   public:
      wInputCheckBoxMaker(QWidget *,inputHandlerList *);
      QWidget * makeWidget(const QString &,QSize,QPoint,const fieldVals &);
};
#endif //  WINPUTCHECKBOXMAKER_H

