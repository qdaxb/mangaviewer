#include "mangaviewer.h"

MangaViewer::MangaViewer()
{
}
MangaViewer::MangaViewer(imagePainter *painter)
{
    this->imagePainter=painter;
}
void MangaViewer::setPath(QString path)
{
    fileManager.load(path);
    currentImage=imageLoader.loadImage(fileManager.current());

}
void MangaViewer::draw()
{
    resizeManager.resize();

    imagePainter.drawImage((QPixmap &)*currentImage,pageViewer.getImageViewRect(),pageViewer.getClientRect());
}
