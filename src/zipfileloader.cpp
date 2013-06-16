#include "zipfileloader.h"
#include "fex/fex.h"
#include <QString>
#include <QTextCodec>
#include <QDebug>
ZipFileLoader::ZipFileLoader(QString zipFileName)
{
    this->zipFileName=zipFileName;
    currentIndex=0;
    isOpend=false;
}
ZipFileLoader::~ZipFileLoader()
{
    close();
}

bool ZipFileLoader::isZipFile(QString ext)
{
    return ext=="zip"||ext=="rar"||ext=="7z";
}

QStringList ZipFileLoader::fileList()
{
    if(zippedFileNames.isEmpty())
    {while(!fex_done(fex))
        {
            const char *cha=fex_name(fex);
            QString name=QString::fromLatin1(cha);
            zippedFileNames.append(name);
            fex_next(fex);
            currentIndex++;
        }
    }
    return zippedFileNames;
}

int ZipFileLoader::open()
{
    if(isOpend)
        return 0;
    char* path=fex_wide_to_path( zipFileName.toStdWString().data() );
    const char *rtn=fex_open( &fex, path );

    fex_free_path( path );
    if(rtn==NULL)
    {
        isOpend=true;
        return 0;
    }
    else
    {
        qDebug()<<rtn;
        return -1;
    }
}
int ZipFileLoader::open(QString path)
{
    this->zipFileName=path;
    if(isOpend)
        close();
    return open();
}
int ZipFileLoader::close()
{
    fex_close(fex);
    isOpend=false;
    return 0;
}

QByteArray ZipFileLoader::loadFile(QString zippedFileName)
{
    int index=zippedFileNames.indexOf(zippedFileName);
    if(currentIndex>index)
    {
        fex_rewind(fex);
        currentIndex=0;
    }
    for(;currentIndex<index;currentIndex++)
    {
        fex_next(fex);
    }
    const void *out;
    fex_data(fex,&out);
    QByteArray array;
    array.append((char*)out,fex_size(fex));
    return array;
}


QStringList ZipFileLoader::folderList()
{
    return QStringList();
}
