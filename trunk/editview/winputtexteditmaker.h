#ifndef  WINPUTTEXTEDITMAKER_H
#define WINPUTTEXTEDITMAKER_H

#include "winputwidgetmaker.h"
#include "winputhandler.h"


class wInputTextEditMaker : public wInputWidgetMaker
{
   Q_OBJECT
   public:
      wInputTextEditMaker(QWidget *,inputHandlerList *);
      QWidget * makeWidget(const QString &,QSize,QPoint,const fieldVals &);
};
#endif //  WINPUTTEXTEDITMAKER_H

