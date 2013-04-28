#include "resizemanager.h"
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
//    if(imageData==NULL||imageData->isNull())
//        return;
//    //get resized image rect
//    QSize imageSize=imageData->size();
//    QSize resizedImageSize(imageSize);
//    QSize windowSize=parent->size();
//    QSize viewPortSize(windowSize);
//    if(resizeMode&(RATE|NO_RATE))
//    {
//        viewPortSize.scale((int)(windowSize.width()/resizeRate),(int)(windowSize.height()/resizeRate),Qt::KeepAspectRatio);
//        resizedImageSize.scale(imageSize.width()*resizeRate,imageSize.height()*resizeRate,Qt::KeepAspectRatio);
//    }
//     //make image source position
//    if(resizeMode&(FIT_WINDOW))
//    {
//        if((resizeMode&FIT_WINDOW)==FIT_WINDOW)
//        {
//            viewPortSize.scale(imageSize.width(),imageSize.height(),Qt::KeepAspectRatio);
//            this->imageViewRect.setSize(viewPortSize);
//            this->targetViewRect.setSize(windowSize);
//        }
//        else
//        {
//            if(resizeMode&FIT_WINDOW_WIDTH)
//            {
//                viewPortSize.scale(imageSize.width(),1,Qt::KeepAspectRatio);
//                this->imageViewRect.setSize(viewPortSize);
//            }
//            else if(resizeMode&FIT_WINDOW_HEIGHT)
//            {
//                viewPortSize.scale(1,imageSize.height(),Qt::KeepAspectRatio);
//                this->imageViewRect.setSize(viewPortSize);
//            }

//            this->targetViewRect.setSize(windowSize);
//        }

//    }
//    else if(resizeMode & (NO_FIT))
//    {

//        this->imageViewRect.setSize(viewPortSize);
//        this->targetViewRect.setSize(windowSize);

//    }
//    else if(resizeMode & (FIT_IMAGE))
//    {
//        this->imageViewRect.setSize(imageSize);



//        if(!parent->isMaximized())
//        {
//            int desktopHeight=QApplication::desktop()->height();
//            int desktopWidth=QApplication::desktop()->width();
//            QSize parentSize(imageSize.width(),imageSize.height());
//            if(desktopHeight<parentSize.height()||desktopWidth<parentSize.width())
//                resizedImageSize.scale(QSize(desktopHeight,desktopWidth),Qt::KeepAspectRatio);
//            parent->resize(resizedImageSize);
//        }
//        this->targetViewRect.setSize(resizedImageSize);


//    }
//    else
//    {
//        qErrnoWarning("error");
//    }





   //make target rect
}

QSize &ResizeManager::getClientSize()
{

}
QSize &ResizeManager::getImageSize()
{

}
