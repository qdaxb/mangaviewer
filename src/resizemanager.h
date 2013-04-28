#ifndef RESIZEMANAGER_H
#define RESIZEMANAGER_H
#include <QSize>
class QPixmap;
class QWidget;
class ResizeManager
{
public:
    enum ResizeMode{NO_RATE=0x20,RATE=0x10,NO_FIT=0x08,FIT_WINDOW=0x03,FIT_IMAGE=0x04,FIT_WINDOW_HEIGHT=0x02,FIT_WINDOW_WIDTH=0x01};
    ResizeManager();
    int setResizeMode(ResizeMode mode,float rate=1);
    int getResizeMode();
    float getResizeRate();
    QSize &getClientSize();
    QSize &getImageSize();
    void setImage(QPixmap *image);
    void setClient(QWidget *widget);
    void resize();
private:
    float resizeRate;
    int resizeMode;
    QPixmap *image;
    QWidget *widget;
};

#endif // RESIZEMANAGER_H
