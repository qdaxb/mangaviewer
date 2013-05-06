#include "imagepainter.h"
#include <QPixmap>
#include <QPainter>
ImagePainter::ImagePainter(QPainter *painter)
{
    this->painter=painter;
}
int ImagePainter::drawImage(QPixmap &imageData,QRect imageRect,QRect clientRect)
{

    painter->drawPixmap(clientRect,(imageData),imageRect);
}



