#ifndef RESIZEMANAGER_H
#define RESIZEMANAGER_H

class ResizeManager
{
public:
    enum ResizeMode{NO_RATE=0x20,RATE=0x10,NO_FIT=0x08,FIT_WINDOW=0x03,FIT_IMAGE=0x04,FIT_WINDOW_HEIGHT=0x02,FIT_WINDOW_WIDTH=0x01};
    ResizeManager();
    int setResizeMode(ResizeMode mode,float rate=1);
    int getResizeMode();
    float getResizeRate();
    void resize();
    QPoint &getClientSize();
    QPoint &getImageSize();
private:
    float resizeRate;
    int resizeMode;
};

#endif // RESIZEMANAGER_H
