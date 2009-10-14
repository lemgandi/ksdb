#ifndef CHECKBOXEDITORIMPL_H
#define CHECKBOXEDITORIMPL_H

#import "checkboxeditor.h"
#import "editorfields.h"

class checkboxEditorImpl : public checkboxEditor,public editorFields
{
 Q_OBJECT
 public:
 public slots:
   virtual void labelTextChanged( const QString & newLabel );
   virtual void legendEditChanged( const QString & t );
   virtual void checkboxToggled( bool toggleState );
 protected:
   QString labelText;
   bool initialValue;
   QString legendText;

 private:
 
};

#endif // CHECKBOXEDITORIMPL_H
