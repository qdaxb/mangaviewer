#ifndef VIEWRECT_H
#define VIEWRECT_H

class ViewRect
{
public:
    enum MoveMode{LEFT_TO_RIGHT=0x01,RIGHT_TO_LEFT=0x00,UP_TO_DOWN=0x00,DOWN_TO_UP=0x02,VERTICAL_FIRST=0,HORIZONTAL_FIRST=0x04};

    ViewRect();
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
private:

    QPoint currentPos;
    MoveMode moveMode;
    QPixmap resizedImageData;
    QRect imageViewRect;
    QRect targetViewRect;
};

#endif // VIEWRECT_H
