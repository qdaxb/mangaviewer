#include "filemanager.h"
#include <QString>
#include <QDir>
#include <QStack>
#include <QList>
#include <QDebug>


FileManager::FileManager()
{
    fileListInCurrentFolder=new QList<QString>();
    fileIndexInFolderStack=new QStack<int>();
    folderStack=new QStack<QString>();
    currentIndex=0;
}
QString FileManager::current()
{
    if(folderStack->isEmpty()||currentIndex==-1)
        return "";
    return fileListInCurrentFolder->at(currentIndex);
}

 QString FileManager::next()
{
    //     qDebug()<<"next:";
    //如果当前路径下有下一个文件，那么取该文件并判断类型
    if(currentIndex<fileListInCurrentFolder->size()-1)
    {
        currentIndex++;
        QString fileName=fileListInCurrentFolder->at(currentIndex);
        QFileInfo fileInfo(fileName);
        //如果文件已修改
        if(!fileInfo.exists())
        {
            return next();
        }
        //若是文件夹则展开并读入当前文件夹
        if(fileInfo.isDir())
        {
            //            qDebug()<<"folder:"<<fileInfo.absoluteFilePath();
            this->loadFromFolder(fileInfo.absoluteFilePath());
            return next();
        }
        else
        {
            QString suffix=fileInfo.completeSuffix();
            if(suffix=="rar")
            {
                //todo do as folder
            }
            else if(suffix=="zip")
            {
                //todo do as folder
            }
            else if(suffix=="7z")
            {
                //todo do as folder
            }
            else if(isSuffixAcceptable(suffix))
            {
                currentFile=fileName;
                return current();
            }
            else //不可接受的文件类型，继续下一个文件
            {
                return next();
            }
            //todo remove this while finished
            return next();
        }

    }
    //如果当前路径下已到结尾,那么查找是否存在下一个可用目录
    else if(loadFromPreviousFolder()>-1)
    {
        return next();
    }
    else
    {
        currentIndex=fileListInCurrentFolder->indexOf(currentFile);
        return "";
    }

}

QString FileManager::previous()
{
    //如果是当前路径的第一个文件，则退回到上级目录
    if(currentIndex<=0)
    {
        //无上级目录则返回空
        if(loadFromPreviousFolder()==-1)
        {
            currentIndex=fileListInCurrentFolder->indexOf(currentFile);
            return "";
        }
        return previous();
    }
    else
    {
        currentIndex--;
        QString fileName=fileListInCurrentFolder->at(currentIndex);
        QFileInfo fileInfo(fileName);
        //如果文件已修改
        if(!fileInfo.exists())
        {
            return previous();
        }
        //若是文件夹则展开并读入当前文件夹
        if(fileInfo.isDir())
        {
            this->loadFromFolder(fileInfo.absoluteFilePath());
            currentIndex=fileListInCurrentFolder->size();
            return previous();
        }
        else
        {
            QString suffix=fileInfo.completeSuffix();
            if(suffix=="rar")
            {
                //todo do as folder
            }
            else if(suffix=="zip")
            {
                //todo do as folder
            }
            else if(suffix=="7z")
            {
                //todo do as folder
            }
            else if(isSuffixAcceptable(suffix))
            {
                currentFile=fileName;
                return current();
            }
            else //不可接受的文件类型，继续下一个文件
            {
                return previous();
            }
            //todo remove this while finished
            return previous();
        }
        return "";

    }



}

int FileManager::load(QString fileorpath)
{

    //容器初始化
    this->folderStack->clear();
    this->fileIndexInFolderStack->clear();
    loadFromFolder(fileorpath);
    return 0;

}
int FileManager::loadFromFolder(QString path)
{
    QDir dir(path);
    QFileInfoList fileInfoList=dir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot,QDir::DirsLast|QDir::Name|QDir::IgnoreCase);
    if(!this->folderStack->isEmpty())
    {
        this->fileIndexInFolderStack->push(currentIndex);
    }
    this->folderStack->push(path);
    this->fileListInCurrentFolder->clear();

    for(int i=0;i<fileInfoList.size();i++)
    {
        this->fileListInCurrentFolder->append(fileInfoList.at(i).absoluteFilePath());

    }

    this->currentIndex=-1;
    return 0;
}

int FileManager::loadFromPreviousFolder()
{
    if(folderStack->size()<=1)
        return -1;
    folderStack->pop();
    QString path=folderStack->top();
    QDir dir(path);

    QFileInfoList fileInfoList=dir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot,QDir::DirsLast|QDir::Name|QDir::IgnoreCase);


    this->fileListInCurrentFolder->clear();

    for(int i=0;i<fileInfoList.size();i++)
    {
        this->fileListInCurrentFolder->append(fileInfoList.at(i).absoluteFilePath());

    }

    this->currentIndex=fileIndexInFolderStack->pop();
    return 1;

}

QList<QString> FileManager::list()
{

}

int FileManager::size()
{
return 0;
}
bool FileManager::isSuffixAcceptable(QString suffix)
{
    QString lowersuffix=suffix.toLower();
    return (lowersuffix=="jpeg"||lowersuffix=="jpg"||lowersuffix=="png"||lowersuffix=="bmp");
}
