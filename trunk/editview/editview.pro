TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

unix:INCLUDEPATH	+= ../filereader ../modelmaker:../datainterface ../filereader ../modelmaker ../database ../filereader

HEADERS	+= /home/devel/ksdb/filereader/widgethandler.h \
	/home/devel/ksdb/filereader/ksdbfilereader.h \
	/home/devel/ksdb/filereader/ksdbxmlparser.h \
	/home/devel/ksdb/filereader/wbuttonhandler.h \
	/home/devel/ksdb/filereader/wcheckboxhandler.h \
	/home/devel/ksdb/filereader/wlabelhandler.h \
	/home/devel/ksdb/filereader/wlineedithandler.h \
	/home/devel/ksdb/filereader/wtextedithandler.h \
	winputhandler.h \
	wlineeditinputhandler.h \
	wtexteditinputhandler.h \
	wcheckboxeditinputhandler.h \
	winputwidgetmaker.h \
	winputlineeditmaker.h \
	winputtexteditmaker.h \
	winputcheckboxmaker.h \
	winputbuttonmaker.h \
	wbuttoninputhandler.h \
	/home/devel/ksdb/database/datainterface.h

SOURCES	+= /home/devel/ksdb/filereader/widgethandler.cpp \
	/home/devel/ksdb/filereader/ksdbfilereader.cpp \
	/home/devel/ksdb/filereader/ksdbxmlparser.cpp \
	/home/devel/ksdb/filereader/wbuttonhandler.cpp \
	/home/devel/ksdb/filereader/wcheckboxhandler.cpp \
	/home/devel/ksdb/filereader/wlabelhandler.cpp \
	/home/devel/ksdb/filereader/wlineedithandler.cpp \
	/home/devel/ksdb/filereader/wtextedithandler.cpp \
	main.cpp \
	winputhandler.cpp \
	wlineeditinputhandler.cpp \
	wtexteditinputhandler.cpp \
	wcheckboxeditinputhandler.cpp \
	winputwidgetmaker.cpp \
	winputlineeditmaker.cpp \
	winputtexteditmaker.cpp \
	winputcheckboxmaker.cpp \
	winputbuttonmaker.cpp \
	wbuttoninputhandler.cpp \
	/home/devel/ksdb/database/datainterface.cpp

FORMS	= mainwindow.ui \
	settingsform.ui

IMAGES	= images/filenew \
	images/fileopen \
	images/filesave \
	images/print \
	images/undo \
	images/redo \
	images/editcut \
	images/editcopy \
	images/editpaste \
	images/searchfind

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}

