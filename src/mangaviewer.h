#ifndef MANGAVIEWER_H
#define MANGAVIEWER_H

#include "filemanager.h"
#include "imageloader.h"
#include "imagepainter.h"
#include "resizemanager.h"
#include "pageviewer.h"

class CommandRegistry;
class QWidget;
class MangaViewer
{
public:
    MangaViewer(QWidget *parent,QPainter *painter);
    void setPath(QString path);
    void draw();
    void go();
    void back();
    void update();
    FileManager *getFileManager(){return fileManager;}
    QWidget *getWidget(){return parent;}
    ResizeManager *getResizeManager(){return resizeManager;}
    PageViewer *getPage(){return pageViewer;}
    void setResizeMode(ResizeManager::ResizeMode mode,float rate=1);
private:
    MangaViewer();
    FileManager *fileManager;
    ImageLoader *imageLoader;
    ImagePainter *imagePainter;
    QPixmap *currentImage;
    ResizeManager *resizeManager;
    PageViewer *pageViewer;
    QWidget *parent;


};

#endif // MANGAVIEWER_H
