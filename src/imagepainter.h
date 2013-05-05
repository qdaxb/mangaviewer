#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H
#include <QPixmap>

class QPainter;
class QWidget;
class QString;
class QByteArray;
class ImagePainter
{
public:
    ImagePainter(QPainter* painter);
    int drawImage(QPixmap &imageData,QRect imageRect,QRect clientRect);
private:
    QPainter *painter;

};

#endif // IMAGEMANAGER_H
