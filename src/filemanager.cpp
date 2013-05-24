#include "filemanager.h"
#include <QString>
#include <QDir>
#include <QStack>
#include <QList>
#include <QDebug>
#include "zipfileloader.h"
#include "localfolderloader.h"
FileManager::FileManager()
{
    fileListInCurrentFolder=new QStringList();
    folderStack=new QStack<FolderLoader*>();
    currentFolderLoader=NULL;
}
QString FileManager::nextFolder()
{
    //enter sub folder
    QStringList subFolders=currentFolderLoader->folderList();
    if(!subFolders.empty())
    {
        folderStack->push(currentFolderLoader);
        QString path=subFolders.first();
        load(path);
        return path;
    }

    //enter sibling folder
    while(true){
        //load parent
        if(folderStack->empty())
        {
            QFileInfo folderInfo(currentFolderLoader->path());
            QDir parentFolder=folderInfo.absoluteDir();
            folderStack->push(new LocalFolderLoader(parentFolder.absolutePath()));
        }

        FolderLoader *parent=folderStack->top();
        folderStack->pop();
        QStringList folderList=parent->folderList();

        int index=folderList.indexOf(currentFolderLoader->path());
        QString siblingPath;
        //current at the end
        if(index==folderList.size()-1)
        {
            //calucate parent and push it into stack
            delete currentFolderLoader;
            currentFolderLoader=parent;
            continue;
        }
        else
        {
            siblingPath=folderList.at(index+1);
        }
        load(siblingPath);
        break;
    }

    //enter parent folder
    return currentFolder();

}

QString FileManager::previousFolder()
{
    while(true){
        //load parent
        if(folderStack->empty())
        {
            QFileInfo folderInfo(currentFolderLoader->path());
            QDir parentFolder=folderInfo.absoluteDir();
            folderStack->push(new LocalFolderLoader(parentFolder.absolutePath()));
        }

        FolderLoader *parent=folderStack->top();
        folderStack->pop();
        QStringList folderList=parent->folderList();

        int index=folderList.indexOf(currentFolderLoader->path());
        QString siblingPath;
        //current at the end
        if(index==0)
        {
            //calucate parent and push it into stack
            delete currentFolderLoader;
            currentFolderLoader=parent;
            continue;
        }
        else
        {
            siblingPath=folderList.at(index-1);
        }
        load(siblingPath);
        break;
    }

    //enter parent folder
    return currentFolder();

}

int FileManager::load(QString fileorpath)
{

    //容器初始化

    QFileInfo fileInfo(fileorpath);

    if(fileInfo.isDir())
        loadFromFolder(fileorpath);
    else
    {
        QString ext=fileInfo.suffix();
        if(ZipFileLoader::isZipFile(ext))
        {
            loadFromZipFile(fileorpath);
        }
        else
        {
            QString folder=fileInfo.absolutePath();
            QFileInfo folderInfo(folder);
            QString ext=folderInfo.suffix();
            if(folderInfo.isDir())
            {
                loadFromFolder(folder);
            }
            else if(ZipFileLoader::isZipFile(ext))
            {
                loadFromZipFile(fileorpath);
            }

        }
    }
    return 0;

}
int FileManager::loadFromZipFile(QString path)
{
    currentFolderLoader=new ZipFileLoader(path);
    currentFolderLoader->open();
    folderStack->push(currentFolderLoader);
    fileListInCurrentFolder->clear();
    fileListInCurrentFolder->append(currentFolderLoader->fileList());
    fileListInCurrentFolder->sort();
}

int FileManager::loadFromFolder(QString path)
{
    currentFolderLoader=new LocalFolderLoader(path);
    this->folderStack->push(currentFolderLoader);
    this->fileListInCurrentFolder->clear();
    this->fileListInCurrentFolder->append(currentFolderLoader->fileList());


    return 0;
}

int FileManager::loadFromPreviousFolder()
{
    if(folderStack->size()<=1)
        return -1;
    folderStack->pop();
    QString path=folderStack->top()->path();
    QDir dir(path);

    QFileInfoList fileInfoList=dir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot,QDir::DirsLast|QDir::Name|QDir::IgnoreCase);


    this->fileListInCurrentFolder->clear();

    for(int i=0;i<fileInfoList.size();i++)
    {
        this->fileListInCurrentFolder->append(fileInfoList.at(i).absoluteFilePath());

    }

    return 1;

}

QList<QString> &FileManager::list()
{
    return (QList<QString> &)fileListInCurrentFolder;
}

int FileManager::size()
{
    return fileListInCurrentFolder->size();
}

bool FileManager::hasNext()
{
    return true;
}

bool FileManager::hasPrevious()
{
    return true;
}

QString FileManager::currentFolder()
{
    return folderStack->top()->path();
}
QString FileManager::get(int index)
{
    if(fileListInCurrentFolder->size()-1==index)
        return "";
    return fileListInCurrentFolder->at(index);
}
QByteArray FileManager::loadData(int index)
{
    if(currentFolderLoader!=NULL)
        return currentFolderLoader->loadFile(fileListInCurrentFolder->at(index));
    else
        return QByteArray();
}


int FileManager::get(QString fileName)
{

    return fileListInCurrentFolder->indexOf(fileName);
}

bool FileManager::isSuffixAcceptable(QString suffix)
{
    QString lowersuffix=suffix.toLower();
    return (lowersuffix=="jpeg"||lowersuffix=="jpg"||lowersuffix=="png"||lowersuffix=="bmp");
}
