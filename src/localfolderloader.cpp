
#include "localfolderloader.h"
#include <QDebug>
LocalFolderLoader::LocalFolderLoader(QString path)
{
    folder=new QDir(path);
}

QStringList LocalFolderLoader::fileList()
{
    return folder->entryList(QDir::Files);
}

int LocalFolderLoader::open()
{
    //do nothing
}

int LocalFolderLoader::open(QString path)
{
    delete folder;
    folder=new QDir(path);
}

int LocalFolderLoader::close()
{
    //do nothing
}

QByteArray LocalFolderLoader::loadFile(QString fileName)
{
    QFile file(folder->absoluteFilePath(fileName));
    file.open(QIODevice::ReadOnly);
    QByteArray array=file.readAll();
    file.close();
    qDebug()<<fileName;
    return array;
}

QString LocalFolderLoader::path()
{
    return folder->absolutePath();
}

LocalFolderLoader::~LocalFolderLoader()
{
    delete folder;
}


QStringList LocalFolderLoader::folderList()
{
    return folder->entryList(QDir::Dirs|QDir::NoDotAndDotDot);
}
