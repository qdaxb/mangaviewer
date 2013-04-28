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
    int drawImage(QPixmap &imageData,const QRect &imageRect,QRect &clientRect);


private:
    QPixmap *imageData;
    QPainter *painter;
    QWidget *parent;


};

#endif // IMAGEMANAGER_H
