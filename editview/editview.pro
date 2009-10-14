TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

unix:INCLUDEPATH	+= ../filereader ../modelmaker:../datainterface ../filereader ../modelmaker ../database ../filereader

HEADERS	+= ../filereader/widgethandler.h \
	../filereader/ksdbfilereader.h \
	../filereader/ksdbxmlparser.h \
	../filereader/wbuttonhandler.h \
	../filereader/wcheckboxhandler.h \
	../filereader/wlabelhandler.h \
	../filereader/wlineedithandler.h \
	../filereader/wtextedithandler.h \
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
	../database/datainterface.h

SOURCES	+= ../filereader/widgethandler.cpp \
	../filereader/ksdbfilereader.cpp \
	../filereader/ksdbxmlparser.cpp \
	../filereader/wbuttonhandler.cpp \
	../filereader/wcheckboxhandler.cpp \
	../filereader/wlabelhandler.cpp \
	../filereader/wlineedithandler.cpp \
	../filereader/wtextedithandler.cpp \
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
	../database/datainterface.cpp

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

