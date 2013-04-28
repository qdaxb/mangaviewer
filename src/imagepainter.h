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
    ImagePainter(QWidget *parent,QPainter* painter);
    int drawImage();


private:
    QPixmap *imageData;
    QPainter *painter;
    QWidget *parent;


};

#endif // IMAGEMANAGER_H
