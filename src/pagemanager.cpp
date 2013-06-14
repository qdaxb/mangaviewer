#include "pagemanager.h"
#include <QImage>
#include <QDebug>
PageManager::PageManager(FileManager *fileManager):mPageArrangeOfFile(),mImages()
{
    this->mFileManager=fileManager;
    mColumnCount=2;
    mPageCount=-1;
    mSplitMode=SPLIT_AUTO;
}

QImage *PageManager::getImage(int index)
{
    if(mImages.contains(index))
        return mImages[index];
    else
    {
        loadFromFile(fileIndexOfPage(index));
    }
    return mImages[index];
}

void PageManager::releaseImage(int index)
{
    if(mImages.contains(index))
    {
        delete mImages[index];
        mImages.remove(index);
    }

}


int PageManager::size()
{
    if(mSplitMode==SPLIT_NONE)
        return mFileManager->size();
    return mFileManager->size()*mColumnCount;
}

int PageManager::setPath(QString path)
{

    if(mImages.size()>0)
    {
        clear();
    }
    int rtn=mFileManager->load(path);
    if(rtn==-1)
    {
        mInitilzed=false;
        return -1;
    }
    else
    {
        mInitilzed=true;
        return 0;
    }
}


void PageManager::loadFromFile(int fileIndex)
{
    int imageIndex=fileIndex;
    QByteArray data=mFileManager->loadData(fileIndex);
    if(data.isNull()||data.isEmpty())
        return;
    QImage image;
    image.loadFromData(data);

    qreal columnWidth=image.width()/mColumnCount;
    int startIndex=pageIndexOfFile(fileIndex);
    for(int i=0;i<mColumnCount;i++)
    {
        if(mImages.contains(startIndex+i))
        {
            qDebug()<<"a";
            continue;
        }
        if(image.width()>image.height())
            mImages[startIndex+i]=new QImage(image.copy(QRect((mColumnCount-i-1)*columnWidth,0,columnWidth,image.height())));
        else
        {
            if(i==0)
                 mImages[startIndex+i]=new QImage(image);
            else
                mImages[startIndex+i]=new QImage();
        }
    }

}


int PageManager::pageIndexOfFile(int fileIndex)
{
    if(mSplitMode==SPLIT_NONE)
        return fileIndex;
    else
        return fileIndex*mColumnCount;
}

int PageManager::fileIndexOfPage(int pageIndex)
{
    if(mSplitMode==SPLIT_NONE)
        return pageIndex;
    else
        return pageIndex/mColumnCount;
}

void PageManager::clear()
{
    QList<QImage*> images=mImages.values();
    for(int i=0;i<images.size();i++)
    {
        delete images.at(i);
    }
    mImages.clear();
}


int PageManager::calucatePageCount(int fileIndex)
{


    if(mSplitMode==SPLIT_ALL)
        return mColumnCount;
    if(mSplitMode==SPLIT_AUTO)
    {
        QImage image;
        QByteArray data=mFileManager->loadData(fileIndex);
        image.loadFromData(data);
        if(image.isNull())
            return 1;
        return image.width()>image.height()?mColumnCount:1;
    }
    if(mSplitMode==SPLIT_NONE)
        return 1;
    Q_ASSERT(0);

}
