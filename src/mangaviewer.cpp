#include "mangaviewer.h"

MangaViewer::MangaViewer()
{
}
MangaViewer::MangaViewer(QWidget *parent, QPainter *painter)
{
    this->imagePainter=new ImagePainter(painter);
    this->fileManager=new FileManager();
    this->imageLoader=new ImageLoader();

}
void MangaViewer::setPath(QString path)
{
    fileManager->load(path);
    currentImage=imageLoader->loadImage(fileManager->current());

}
void MangaViewer::draw()
{
    //resizeManager->resize();

    imagePainter->drawImage((QPixmap &)*currentImage,pageViewer->getImageViewRect(),pageViewer->getClientRect());
}
