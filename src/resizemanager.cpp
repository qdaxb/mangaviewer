#include "resizemanager.h"
#include <QWidget>
#include <QDebug>
ResizeManager::ResizeManager()
{
}
int ResizeManager::setResizeMode(int resizeMode, float rate)
{

    //    if(mode&(0xF))
    //    {
    //        this->resizeMode=this->resizeMode&(~(0xF));//clear 1111 bit
    //    }

    //    this->resizeMode=this->resizeMode|mode;
    this->resizeMode=resizeMode;
    if(!(resizeMode & (RATE|NO_RATE)))
    {
        this->resizeMode = (NO_RATE|this->resizeMode);
    }
    //    if((mode & RATE) || (mode & NO_RATE))
    //    {
    //        this->resizeMode=this->resizeMode&(~(FIT_WINDOW));//clear fit window bit
    //    }
    //    if(!this->resizeMode&(RATE|NO_RATE))
    //        this->resizeMode=this->resizeMode|NO_RATE;
    //    if(!this->resizeMode&(0xF))
    //        this->resizeMode=this->resizeMode|FIT_IMAGE;
    //    if(mode&RATE)
    //        this->resizeRate=rate;
    //    if(mode&NO_RATE)
    this->resizeRate=rate;
    return 0;
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
    //resize for fit window
    imageSize=image->size();
    clientSize=widget->size();
    int mode=this->resizeMode;
    if(mode&FIT_WINDOW)
    {

        //resize the window

        if(mode&FIT_WINDOW_HEIGHT)
        {
            imageSize.scale(1,clientSize.height(),Qt::KeepAspectRatioByExpanding);
        }
        else if(mode & FIT_WINDOW_WIDTH)
        {
            imageSize.scale(clientSize.width(),1,Qt::KeepAspectRatioByExpanding);
        }
        else
        {
            imageSize.scale(clientSize,Qt::KeepAspectRatio);
        }


    }
    else if (mode & FIT_IMAGE)
    {

        if(mode & RATE)
        {

            clientSize.scale(imageSize * resizeRate,Qt::IgnoreAspectRatio);
        }
        else
        {
            //resize for fit image

            clientSize.scale(imageSize,Qt::IgnoreAspectRatio);
        }
    }

    else
    {
       // qDebug()<<"error resize mode!!!";

    }
    if(widget->size()!=clientSize)
    {
        widget->resize(clientSize);
    }
}

QSize ResizeManager::getClientSize()
{
    return clientSize;
}
QSize ResizeManager:: getImageSize()
{
    return imageSize;
}

void ResizeManager::setImage(QPixmap *image)
{
    this->image=image;
    this->imageSize=image->size();
}

void ResizeManager::setClient(QWidget *widget)
{
    this->widget=widget;
}
