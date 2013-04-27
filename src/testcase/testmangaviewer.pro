
QT       += core


TARGET =testmangaviewer
TEMPLATE = app

SOURCES += main.cpp \
    testFileManager.cpp

INCLUDEPATH+= ./include ../include ../
LIBS += -L../../src/testcase/lib -lgtest
OBJECTS += ../debug/filemanager.o
