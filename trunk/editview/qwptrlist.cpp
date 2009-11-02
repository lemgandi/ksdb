//
// Implementation for qwptrlist, a list to sort widgets from upper left to 
// lower right.

#import "qwptrlist.h"

QWPtrList::QWPtrList() : qptrlistw()
{
}

// 
// Compare a pair of items, assume they are QWidget *
//
int QWPtrList::compareItems(QPtrCollection::Item a,QPtrCollection::Item b)
{
   int retVal;

   // Oh my god this is bad. Appears to be the Only Way though.
   // dynamic_cast apparently does not work on void * pointers.
   QWidget * itmA = (QWidget *)a;
   QWidget * itmB = (QWidget *)b;

   if(itmA && itmB)
      retVal=compareWidgets(itmA,itmB);
   else
      retVal=qptrlistw::compareItems(a,b);

   return retVal;

}

//
// Compare a pair of widgets by location in order to set tab order.
//
int QWPtrList::compareWidgets(QWidget *a,QWidget *b)
{
   int retVal=0;
   //   qDebug("Compare x:%d y:%d to x:%d y:%d",a->x(),a->y(),b->x(),b->y());

   if( a->y() > b->y() )
      retVal=1;
   else if (a->y() < b->y() )
      retVal=-1;
   else if (a->x() > b->x())
      retVal=1;
   else if (a->x() < b->x())
      retVal=-1;

   return retVal;
}
