#ifndef  WINPUTBUTTONMAKER_H
#define WINPUTBUTTONMAKER_H

#include "winputwidgetmaker.h"
#include "winputhandler.h"


class wInputButtonMaker : public wInputWidgetMaker
{
   Q_OBJECT
   public:
      wInputButtonMaker(QWidget *,inputHandlerList *);
      QWidget * makeWidget(const QString &,QSize,QPoint,const fieldVals &);
};
#endif //  WINPUTBUTTONMAKER_H

