#ifndef WTEXTEDITHANDLER_H
#define WTEXTEDITHANDLER_H


#include "typedefs.h"
#include "widgethandler.h"

class QWidget;

class wTextEditHandler : public widgetHandler
{
 Q_OBJECT
 public:
   QWidget *makeWidget(const QString &,QSize,QPoint,const fieldVals &);
};

#endif //WTEXTEDITHANDLER_H

