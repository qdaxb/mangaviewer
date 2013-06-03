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
    if(!fileInfo.exists())
        return -1;
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
    QStringList files=currentFolderLoader->fileList();
    for(int i=0;i<files.size();i++)
    {
        if(isSuffixAcceptable( files.at(i).split('.').last()))
        fileListInCurrentFolder->append(files.at(i));
    }

    fileListInCurrentFolder->sort();
}

int FileManager::loadFromFolder(QString path)
{
    currentFolderLoader=new LocalFolderLoader(path);
    this->folderStack->push(currentFolderLoader);
    this->fileListInCurrentFolder->clear();
    QStringList files=currentFolderLoader->fileList();
    for(int i=0;i<files.size();i++)
    {
        if(isSuffixAcceptable( files.at(i).split('.').last()))
        fileListInCurrentFolder->append(files.at(i));
    }

    return 0;
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
    if(currentFolderLoader==NULL)
        return "";
    return currentFolderLoader->path();
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
