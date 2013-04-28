#include "imageloader.h"
#include <QPixmap>
ImageLoader::ImageLoader()
{
}
QPixmap *loadImage(QString path)
{
    QPixmap *image=new QPixmap(path);
    return image;
}
