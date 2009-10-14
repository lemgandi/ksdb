TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

unix:LIBS	+= -lqui

unix:INCLUDEPATH	+= ../filereader ../screenmaker

HEADERS	+= typedefs.h \
	filesaver.h \
	weditbuttonhandler.h \
	weditcheckboxhandler.h \
	wedithandler.h \
	weditlineedithandler.h \
	wedittextedithandler.h \
	../screenmaker/screenmaker.h \
	../filereader/ksdbfilereader.h \
	../filereader/ksdbxmlparser.h \
	../screenmaker/mockeditfield.h \
	../filereader/widgethandler.h \
	../filereader/wlabelhandler.h

SOURCES	+= main.cpp \
	filesaver.cpp \
	weditbuttonhandler.cpp \
	weditcheckboxhandler.cpp \
	wedithandler.cpp \
	weditlineedithandler.cpp \
	wedittextedithandler.cpp \
	../filereader/ksdbfilereader.cpp \
	../filereader/ksdbxmlparser.cpp \
	../screenmaker/screenmaker.cpp \
	../screenmaker/mockeditfield.cpp \
	../filereader/wlabelhandler.cpp \
	../filereader/widgethandler.cpp

FORMS	= mainwindow.ui \
	fieldeditor.ui \
	labeledit.ui \
	inputedit.ui \
	buttoneditor.ui \
	blankeditor.ui \
	checkboxeditor.ui

IMAGES	= images/filenew \
	images/fileopen \
	images/filesave \
	images/print \
	images/undo \
	images/redo \
	images/editcut \
	images/editcopy \
	images/editpaste \
	images/searchfind \
	images/select.png \
	images/draw.png

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}



