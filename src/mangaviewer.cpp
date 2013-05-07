#include "mangaviewer.h"
#include <QWidget>
MangaViewer::MangaViewer()
{
}
MangaViewer::MangaViewer(QWidget *parent, QPainter *painter)
{
    this->imagePainter=new ImagePainter(painter);
    this->fileManager=new FileManager();
    this->imageLoader=new ImageLoader();
    this->resizeManager=new ResizeManager();
    this->parent=parent;
    this->pageViewer=new PageViewer();
    resizeManager->setClient(parent);
    pageViewer->setClientSize(parent->size());
    pageViewer->setMoveMode(PageViewer::RIGHT_TO_LEFT|PageViewer::UP_TO_DOWN);
    resizeManager->setResizeMode(ResizeManager::NO_RATE);
    currentImage=NULL;
}
void MangaViewer::setPath(QString path)
{
    fileManager->load(path);
}
void MangaViewer::draw()
{
    //resizeManager->resize();
    if(currentImage==NULL)
        return;
    //resizeManager->resize();
   // pageViewer->setImageSize(resizeManager->getImageSize());


    imagePainter->drawImage((QPixmap &)*currentImage,pageViewer->getTargetViewRect(),parent->rect());

}

void MangaViewer::go()
{
    if(currentImage==NULL||currentImage->isNull()||pageViewer->go()==-1)
    {
        QString nextFile=fileManager->next();
        if(nextFile=="")
            return;
        currentImage=imageLoader->loadImage(nextFile);
        resizeManager->setImage(currentImage);
        resizeManager->resize();
        pageViewer->setImageSize(resizeManager->getImageSize());
        pageViewer->newPage();
    }
}

void MangaViewer::back()
{
    if(currentImage==NULL||currentImage->isNull()||pageViewer->back()==-1)
    {
        QString previousFile=fileManager->previous();
        if(previousFile=="")
            return;
        currentImage=imageLoader->loadImage(previousFile);
        resizeManager->setImage(currentImage);
        resizeManager->resize();
        pageViewer->setImageSize(resizeManager->getImageSize());
        pageViewer->newPage();
    }
}

void MangaViewer::update()
{
    QString currentFile=fileManager->current();
    if(currentFile=="")
        return;
    currentImage=imageLoader->loadImage(currentFile);
    resizeManager->setImage(currentImage);
    resizeManager->resize();
    pageViewer->setImageSize(resizeManager->getImageSize());
}
