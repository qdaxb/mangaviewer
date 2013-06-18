#-------------------------------------------------
#
# Project created by QtCreator 2012-08-07T09:58:37
#
#-------------------------------------------------

QT       += core gui xml
QT += widgets

TARGET =mangaviewer 
TEMPLATE = app


SOURCES += filemanager.cpp \
    main.cpp \
    msgpainter.cpp \
    viewercommand.cpp \
    commandregistry.cpp \
    keymapper.cpp \
    qgraphicsmanagaview.cpp \
    localfolderloader.cpp \
    zipfileloader.cpp \
    fex/Zlib_Inflater.cpp \
    fex/Zip7_Extractor.cpp \
    fex/Zip_Extractor.cpp \
    fex/Rar_Extractor.cpp \
    fex/Gzip_Reader.cpp \
    fex/Gzip_Extractor.cpp \
    fex/File_Extractor.cpp \
    fex/fex.cpp \
    fex/Data_Reader.cpp \
    fex/blargg_errors.cpp \
    fex/blargg_common.cpp \
    fex/Binary_Extractor.cpp \
    7z_C/LzmaDec.c \
    7z_C/Bra86.c \
    7z_C/Bcj2.c \
    7z_C/7zStream.c \
    7z_C/7zItem.c \
    7z_C/7zIn.c \
    7z_C/7zHeader.c \
    7z_C/7zExtract.c \
    7z_C/7zDecode.c \
    7z_C/7zCrc.c \
    7z_C/7zBuf.c \
    7z_C/7zAlloc.c \
    unrar/unrar_open.cpp \
    unrar/unrar_misc.cpp \
    unrar/unrar.cpp \
    unrar/unpack20.cpp \
    unrar/unpack15.cpp \
    unrar/unpack.cpp \
    unrar/unicode.cpp \
    unrar/suballoc.cpp \
    unrar/rawread.cpp \
    unrar/rarvmtbl.cpp \
    unrar/rarvm.cpp \
    unrar/model.cpp \
    unrar/getbits.cpp \
    unrar/extract.cpp \
    unrar/encname.cpp \
    unrar/crc.cpp \
    unrar/coder.cpp \
    unrar/arcread.cpp \
    unrar/archive.cpp \
    zlib/inftrees.c \
    zlib/inflate.c \
    zlib/inffast.c \
    zlib/crc32.c \
    zlib/adler32.c \
    qgraphicsgridscrollitem.cpp \
    pagemanager.cpp \
    zlib/zutil.c \
    qgraphicssimplebackgroundtextitem.cpp \
 #   settingsdialog.cpp \
    shortcutmanager.cpp \
    gotodialog.cpp


HEADERS  +=    filemanager.h \
    msgpainter.h \
    viewercommand.h \
    commandregistry.h \
    keymapper.h \
    qgraphicsmanagaview.h \
    common.h \
    folderloader.h \
    localfolderloader.h \
    zipfileloader.h \
    fex/Zlib_Inflater.h \
    fex/Zip7_Extractor.h \
    fex/Zip_Extractor.h \
    fex/Rar_Extractor.h \
    fex/Gzip_Reader.h \
    fex/Gzip_Extractor.h \
    fex/File_Extractor.h \
    fex/fex.h \
    fex/Data_Reader.h \
    fex/blargg_source.h \
    fex/blargg_errors.h \
    fex/blargg_endian.h \
    fex/blargg_config.h \
    fex/blargg_common.h \
    fex/Binary_Extractor.h \
    7z_C/Types.h \
    7z_C/LzmaDec.h \
    7z_C/CpuArch.h \
    7z_C/Bra.h \
    7z_C/Bcj2.h \
    7z_C/7zItem.h \
    7z_C/7zIn.h \
    7z_C/7zHeader.h \
    7z_C/7zExtract.h \
    7z_C/7zDecode.h \
    7z_C/7zCrc.h \
    7z_C/7zBuf.h \
    7z_C/7zAlloc.h \
    unrar/unrar.h \
    unrar/unpack.hpp \
    unrar/unicode.hpp \
    unrar/suballoc.hpp \
    unrar/rawread.hpp \
    unrar/rarvm.hpp \
    unrar/rar.hpp \
    unrar/model.hpp \
    unrar/headers.hpp \
    unrar/getbits.hpp \
    unrar/encname.hpp \
    unrar/compress.hpp \
    unrar/coder.hpp \
    unrar/array.hpp \
    unrar/archive.hpp \
    zlib/zlib.h \
    zlib/zconf.h \
    zlib/inftrees.h \
    zlib/inflate.h \
    zlib/inffixed.h \
    zlib/inffast.h \
    zlib/crc32.h \
    qgraphicsgridscrollitem.h \
    pagemanager.h \
    zlib/zutil.h \
    qgraphicssimplebackgroundtextitem.h \
   # settingsdialog.h \
    shortcutmanager.h \
    gotodialog.h

FORMS    +=  qgraphicsmanagaview.ui \
    gotodialog.ui
   # settingsdialog.ui


INCLUDEPATH+= ./include

include(qxtglobalshortcut/qxtglobalshortcut.pri)

RESOURCES += \
    resources.qrc

