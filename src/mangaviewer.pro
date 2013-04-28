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
    viewrect.cpp \
    resizemanager.cpp \
    imageloader.cpp

HEADERS  += mainwindow.h \
    filemanager.h \
    mainwindow.h \
    rarfile.h \
    msgpainter.h \
    imagepainter.h \
    viewrect.h \
    resizemanager.h \
    imageloader.h

FORMS    += mainwindow.ui


INCLUDEPATH+= ./include
