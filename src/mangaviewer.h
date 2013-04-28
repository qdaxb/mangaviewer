#ifndef MANGAVIEWER_H
#define MANGAVIEWER_H

#include "filemanager.h"
#include "imageloader.h"
#include "imagepainter.h"
#include "resizemanager.h"
#include "pageviewer.h"
class MangaViewer
{
public:
    MangaViewer(QWidget *parent,QPainter *painter);
    void setPath(QString path);
    void draw();
    void go();
    void back();
    ResizeManager *getResizeManager();
    void setResizeMode(ResizeManager::ResizeMode mode,float rate=1);
private:
    MangaViewer();
    FileManager *fileManager;
    ImageLoader *imageLoader;
    ImagePainter *imagePainter;
    QPixmap *currentImage;
    ResizeManager *resizeManager;
    PageViewer *pageViewer;
};

#endif // MANGAVIEWER_H
