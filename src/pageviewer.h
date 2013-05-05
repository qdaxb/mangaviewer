#ifndef VIEWRECT_H
#define VIEWRECT_H
#include <QPoint>
#include <QRect>
#include <QPixmap>
#include <QSize>
class PageViewer
{
public:
    enum MoveMode{LEFT_TO_RIGHT=0x01,RIGHT_TO_LEFT=0x02,UP_TO_DOWN=0x04,DOWN_TO_UP=0x08,VERTICAL_FIRST=0x10,HORIZONTAL_FIRST=0x20};

    PageViewer();
    int stepUp(int step=1);
    int stepDown(int step=1);
    int stepLeft(int step=1);
    int stepRight(int step=1);
    int setWidgetResizeMode();
    int go(bool start=false);
    int back();
    int setMoveMode(int mode);
    int moveHorizontal(bool start=false, bool back=false);
    int moveVertical(bool start=false, bool back=false);
    QRect &getTargetViewRect();
    QRect &getImageViewRect();
    void setImageSize(QSize size);
    void setClientSize(QSize size);
    void newPage();
private:
    QSize imageSize;
    QSize clientSize;
    QPoint currentPos;
    MoveMode moveMode;
    QPixmap resizedImageData;
    QRect imageViewRect;
    QRect targetViewRect;
};

#endif // VIEWRECT_H
