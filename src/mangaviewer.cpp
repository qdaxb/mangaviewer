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
    pageViewer->setClientSize(parent->size());
    pageViewer->setMoveMode(PageViewer::RIGHT_TO_LEFT|PageViewer::UP_TO_DOWN);
    resizeManager->setResizeMode(ResizeManager::NO_RATE);
    currentImage=NULL;
}
void MangaViewer::setPath(QString path)
{
    fileManager->load(path);
    resizeManager->setClient(parent);
}
void MangaViewer::draw()
{
    //resizeManager->resize();
    imagePainter->drawImage((QPixmap &)*currentImage,pageViewer->getTargetViewRect(),parent->rect());
}

void MangaViewer::go()
{
    if(currentImage==NULL||currentImage->isNull()||pageViewer->go()==-1)
    {
        currentImage=imageLoader->loadImage(fileManager->next());
        resizeManager->setImage(currentImage);
        resizeManager->resize();
        pageViewer->setImageSize(resizeManager->getImageSize());
        pageViewer->newPage();
    }
}

void MangaViewer::back()
{
}
