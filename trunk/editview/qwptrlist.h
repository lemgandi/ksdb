#ifndef QWPTRLIST_H
#define QWPTRLIST_H

#include <qwidget.h>

#include <qptrlist.h>

typedef QPtrList<QWidget> qptrlistw;


// A pointer list of widgets pointers, able to be sorted from top L to 
// bottom R

class QWPtrList : public qptrlistw
{
 public:
   QWPtrList();
 protected:
   int compareItems(QPtrCollection::Item a,QPtrCollection::Item b);
   int compareWidgets(QWidget *a,QWidget *b);
};

#endif //QWPTRLIST_H
