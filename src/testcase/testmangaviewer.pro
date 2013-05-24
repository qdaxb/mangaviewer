
QT       += core gui


TARGET =testmangaviewer
TEMPLATE = app

SOURCES += main.cpp \
    ../zipfile.cpp

INCLUDEPATH+= ./include ../include ../
LIBS +=  -L. -lfex

OBJECTS+=debug/zlib/*.o
