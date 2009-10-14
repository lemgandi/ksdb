#ifndef WIDGETHANDLER_H
#define WIDGETHANDLER_H

// Widget handler object -- set up and (possibly) handle input from a widget.
// Why not use QWidgetFactory, you ask?  Because each type of widget I create
// requires unique data and calls to set up; QLabels, for example, need to have
// legend text in the create call, and checkboxes likewise. But QLineInput
// objects shouldn t have this. And some of this information is of use
// *only* during creation; there is no way to change a label s text after it
// is created, for example. 

#include <qapplication.h>
#include <qobject.h>
#include "typedefs.h"
#include <qdict.h>

class QWidget;
class QSize;
class QPoint;

class widgetHandler : public QObject {
    Q_OBJECT

 public:
    widgetHandler();
    virtual QWidget *makeWidget(const QString &,QSize,QPoint,const fieldVals &);
 protected:
    void setWidgetSizeShape(QWidget *,QSize,QPoint);
};

typedef QDict<widgetHandler> widgetHandlerDictionary;

#endif //WIDGETHANDLER_H
