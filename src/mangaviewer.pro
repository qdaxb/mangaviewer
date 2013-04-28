#-------------------------------------------------
#
# Project created by QtCreator 2012-08-07T09:58:37
#
#-------------------------------------------------

QT       += core gui testlib

TARGET =mangaviewer 
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    filemanager.cpp \
    main.cpp \
    rarfile.cpp \
    msgpainter.cpp \
    imagepainter.cpp \
    resizemanager.cpp \
    imageloader.cpp \
    mangaviewer.cpp \
    paveviewer.cpp

HEADERS  += mainwindow.h \
    filemanager.h \
    mainwindow.h \
    rarfile.h \
    msgpainter.h \
    imagepainter.h \
    resizemanager.h \
    imageloader.h \
    mangaviewer.h \
    pageviewer.h

FORMS    += mainwindow.ui


INCLUDEPATH+= ./include
