INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/qxtglobal.h \
           $$PWD/qxtglobalshortcut.h \
           $$PWD/qxtglobalshortcut_p.h
SOURCES += $$PWD/qxtglobalshortcut.cpp
win32{
    SOURCES += $$PWD/qxtglobalshortcut_win.cpp
    LIBS += -luser32
}
#unix{
#SOURCES += $$PWD/qxtglobalshortcut_x11.cpp
#QT+=x11extras
#LIBS +=-lX11
#}
mac:SOURCES += $$PWD/qxtglobalshortcut_mac.cpp
mac:LIBS += -framework Carbon -framework CoreFoundation
