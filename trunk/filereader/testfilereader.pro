
TEMPLATE = app
LANGUAGE = C++

CONFIG += qt warn_on release

unix:LIBS += -lqui
unix:INCLUDEPATH += ../modelmaker

HEADERS += ksdbfilereader.h ksdbxmlparser.h ../modelmaker/typedefs.h \
widgethandler.h wlabelhandler.h wlineedithandler.h \
wtextedithandler.h wcheckboxhandler.h wbuttonhandler.h

SOURCES += testfilereader.cpp ksdbxmlparser.cpp ksdbfilereader.cpp \
widgethandler.cpp wlabelhandler.cpp wlineedithandler.cpp \
wtextedithandler.cpp wcheckboxhandler.cpp wbuttonhandler.cpp

