#-------------------------------------------------
#
# Project created by QtCreator 2012-08-07T09:58:37
#
#-------------------------------------------------

QT       += core gui
QT += widgets
QgreaterThan(QT_MAJOR_VERSION, 4) {
QT *= widgets
QT *= printsupport
QT += widgets
}
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
    paveviewer.cpp \
    viewercommand.cpp \
    commandregistry.cpp \
    keymapper.cpp \
    qgraphicspagedpixmapitem.cpp \
    qgraphicsmanagaview.cpp

HEADERS  += mainwindow.h \
    filemanager.h \
    mainwindow.h \
    rarfile.h \
    msgpainter.h \
    imagepainter.h \
    resizemanager.h \
    imageloader.h \
    mangaviewer.h \
    pageviewer.h \
    viewercommand.h \
    commandregistry.h \
    keymapper.h \
    qgraphicspagedpixmapitem.h \
    qgraphicsmanagaview.h \
    common.h

FORMS    += mainwindow.ui \
    qgraphicsmanagaview.ui


INCLUDEPATH+= ./include
