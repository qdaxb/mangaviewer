#include "imageloader.h"
#include <QPixmap>
ImageLoader::ImageLoader()
{
}
QPixmap *ImageLoader::loadImage(QString path)
{
    QPixmap *image=new QPixmap(path);
    return image;
}
