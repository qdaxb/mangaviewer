#include "resizemanager.h"
#include <QWidget>
ResizeManager::ResizeManager()
{
}
int ResizeManager::setResizeMode(ResizeManager::ResizeMode mode, float rate)
{

    if(mode&(0xF))
    {
        this->resizeMode=this->resizeMode&(~(0xF));//clear 1111 bit
    }

    this->resizeMode=this->resizeMode|mode;
    if((mode & RATE) || (mode & NO_RATE))
    {
        this->resizeMode=this->resizeMode&(~(FIT_WINDOW));//clear fit window bit
    }
    if(!this->resizeMode&(RATE|NO_RATE))
        this->resizeMode=this->resizeMode|NO_RATE;
    if(!this->resizeMode&(0xF))
        this->resizeMode=this->resizeMode|FIT_IMAGE;
    if(mode&RATE)
        this->resizeRate=rate;
    if(mode&NO_RATE)
        this->resizeRate=1;
}
int ResizeManager::getResizeMode()
{
    return resizeMode;
}

float ResizeManager::getResizeRate()
{
    return resizeRate;
}
void ResizeManager::resize()
{

}

QSize &ResizeManager::getClientSize()
{
    return widget->size();
}
QSize &ResizeManager:: getImageSize()
{

}

void ResizeManager::setImage(QPixmap *image)
{
    this->image=image;
}

void ResizeManager::setClient(QWidget *widget)
{
    this->widget=widget;
}
