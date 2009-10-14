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
	/home/devel/ksdb/screenmaker/screenmaker.h \
	/home/devel/ksdb/filereader/ksdbfilereader.h \
	/home/devel/ksdb/filereader/ksdbxmlparser.h \
	/home/devel/ksdb/screenmaker/mockeditfield.h \
	/home/devel/ksdb/filereader/widgethandler.h \
	/home/devel/ksdb/filereader/wlabelhandler.h

SOURCES	+= main.cpp \
	filesaver.cpp \
	weditbuttonhandler.cpp \
	weditcheckboxhandler.cpp \
	wedithandler.cpp \
	weditlineedithandler.cpp \
	wedittextedithandler.cpp \
	/home/devel/ksdb/filereader/ksdbfilereader.cpp \
	/home/devel/ksdb/filereader/ksdbxmlparser.cpp \
	/home/devel/ksdb/screenmaker/screenmaker.cpp \
	/home/devel/ksdb/screenmaker/mockeditfield.cpp \
	/home/devel/ksdb/filereader/wlabelhandler.cpp \
	/home/devel/ksdb/filereader/widgethandler.cpp

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



