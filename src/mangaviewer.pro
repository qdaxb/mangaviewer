#-------------------------------------------------
#
# Project created by QtCreator 2012-08-07T09:58:37
#
#-------------------------------------------------

QT       += core gui
QT += widgets

TARGET =mangaviewer 
TEMPLATE = app


SOURCES += filemanager.cpp \
    main.cpp \
    rarfile.cpp \
    msgpainter.cpp \
    imageloader.cpp \
    viewercommand.cpp \
    commandregistry.cpp \
    keymapper.cpp \
    qgraphicspagedpixmapitem.cpp \
    qgraphicsmanagaview.cpp

HEADERS  +=    filemanager.h \
    rarfile.h \
    msgpainter.h \
    imageloader.h \
    viewercommand.h \
    commandregistry.h \
    keymapper.h \
    qgraphicspagedpixmapitem.h \
    qgraphicsmanagaview.h \
    common.h

FORMS    +=  qgraphicsmanagaview.ui


INCLUDEPATH+= ./include
