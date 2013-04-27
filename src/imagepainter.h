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
    enum ResizeMode{NO_RATE=0x20,RATE=0x10,NO_FIT=0x08,FIT_WINDOW=0x03,FIT_IMAGE=0x04,FIT_WINDOW_HEIGHT=0x02,FIT_WINDOW_WIDTH=0x01};
    enum MoveMode{LEFT_TO_RIGHT=0x01,RIGHT_TO_LEFT=0x00,UP_TO_DOWN=0x00,DOWN_TO_UP=0x02,VERTICAL_FIRST=0,HORIZONTAL_FIRST=0x04};
    ImagePainter(QWidget *parent,QPainter* painter);
    inline void loadImage(QByteArray &data){imageData->loadFromData(data);}
    void loadImage(QString data);
    int stepUp(int step=1);
    int stepDown(int step=1);
    int stepLeft(int step=1);
    int stepRight(int step=1);
    int setResizeMode(ResizeMode mode,float rate=1);
    int setWidgetResizeMode();
    int go(bool start=false);
    int back();
    int setMoveMode(int mode);
    int drawImage();

    int moveHorizontal(bool start=false, bool back=false);
    int moveVertical(bool start=false, bool back=false);
    int getResizeMode();
    float getResizeRate();
    void resize();
private:
    QPixmap *imageData;
    QPoint currentPos;
    QPainter *painter;
    QWidget *parent;
    int resizeMode;
    MoveMode moveMode;
    float resizeRate;
    QPixmap resizedImageData;
    QRect imageViewRect;
    QRect targetViewRect;

};

#endif // IMAGEMANAGER_H
