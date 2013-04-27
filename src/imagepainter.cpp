#include "imagepainter.h"
#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#define debugRect(rect) qDebug()<<"debug "+QString(#rect)<<(rect).left()<<(rect).right()<<(rect).top()<<(rect).bottom();
#define debugSize(size) qDebug()<<"debug "+QString(#size)<<(size).width()<<(size).height();
ImagePainter::ImagePainter(QWidget *parent,QPainter *painter)
{

    this->parent=parent;
    this->painter=painter;
    this->imageData=new QPixmap();
    resizedImageData=NULL;
    this->setMoveMode(RIGHT_TO_LEFT|UP_TO_DOWN);
    this->resizeMode=FIT_IMAGE|NO_RATE;
    this->resizeRate=1;

}

void ImagePainter::loadImage(QString data)
{
    imageData->load(data);
    resize();
    go(true);
}

int ImagePainter::stepUp(int step)
{

    currentPos.setY(currentPos.y()+step);
}

int ImagePainter::stepDown(int step)
{
   currentPos.setY(currentPos.y()-step);
}

int ImagePainter::stepLeft(int step)
{
currentPos.setX(currentPos.x()+step);
}

int ImagePainter::stepRight(int step)
{
currentPos.setX(currentPos.x()-step);
}

int ImagePainter::setResizeMode(ImagePainter::ResizeMode mode, float rate)
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
    resize();
    this->go(true);
    //resize();
    //makeViewRect();
}



int ImagePainter::moveVertical(bool start,bool back)
{

    int movePos=-1;
    int moveMode=this->moveMode;
    if(back)
        moveMode=~moveMode;
    if(moveMode&DOWN_TO_UP)
    {
        if(start)
        {
            imageViewRect.moveBottom(imageData->height());
            movePos=imageViewRect.top();
        }
        else
        {
            if(imageViewRect.top()>0)
            {
                imageViewRect.translate(0,qMax(-imageViewRect.top(),(int)(-parent->height()*resizeRate+10)));
                movePos=imageViewRect.top();
            }
        }
    }
    else
    {
        if(start)
        {
            imageViewRect.moveTop(0);
            movePos=imageViewRect.top();
            debugRect(imageViewRect);
            debugRect(imageData->rect());
        }
        else
        {

            if(imageViewRect.bottom()<imageData->height()-1)
            {
                imageViewRect.translate(0,qMin((int)(parent->height()*resizeRate-10),imageData->height()-imageViewRect.bottom()));
                movePos=imageViewRect.top();
            }
        }
    }
    return movePos;
}

int ImagePainter::getResizeMode()
{
    return resizeMode;
}

float ImagePainter::getResizeRate()
{
    return resizeRate;
}

int ImagePainter::moveHorizontal(bool start,bool back)
{


    int movePos=-1;
    int moveMode=this->moveMode;
    if(back)
        moveMode=~moveMode;
    if(moveMode&LEFT_TO_RIGHT)
    {

        if(start)
        {
            imageViewRect.moveLeft(0);
            movePos=imageViewRect.left();

        }
        else
        {
            if(imageViewRect.right()<imageData->width()-1)
            {
                imageViewRect.translate(qMin(imageData->width()-imageViewRect.right(),(int)(parent->width()*resizeRate-10)),0);
                movePos=imageViewRect.left();
            }
        }
    }
    else
    {

        if(start)
        {
            imageViewRect.moveRight(imageData->width()-1);
            movePos=imageViewRect.left();

        }
        else
        {

            if(imageViewRect.left()>0)
            {
                imageViewRect.translate(qMax((int)(10-parent->width()*resizeRate),-imageViewRect.left()),0);
                movePos=imageViewRect.left();
            }
        }
    }
    return movePos;
}

int ImagePainter::go(bool start)
{
    if(start)
    {
        moveHorizontal(true);
        moveVertical(true);
    }else if(moveMode&VERTICAL_FIRST)
    {
        int endMove=moveVertical();
        if(endMove==-1)
        {
            endMove=moveHorizontal();
            if(endMove!=-1)
                moveVertical(true);
            else
                return -1;
        }
    }
    else
    {

        int endMove=moveHorizontal();
        qDebug()<<"end move"<<endMove<<start;
        if(endMove==-1)
        {
            endMove=moveVertical();
            if(endMove!=-1)
                moveHorizontal(true);
            else
                return -1;
        }
    }
    return 0;
}

int ImagePainter::back()
{
    if(moveMode&VERTICAL_FIRST)
    {
        int endMove=moveVertical(false,true);
        if(endMove==-1)
        {
            endMove=moveHorizontal(false,true);
            if(endMove!=-1)
                moveVertical(true,true);
            else
                return -1;
        }
    }
    else
    {

        int endMove=moveHorizontal(false,true);
        if(endMove==-1)
        {
            endMove=moveVertical(false,true);
            if(endMove!=-1)
                moveHorizontal(true,true);
            else
                return -1;
        }
    }
    return 0;
}

int ImagePainter::setMoveMode(int mode)
{
    this->moveMode=(MoveMode)mode;
}

int ImagePainter::drawImage()
{
    resize();
    painter->drawPixmap(targetViewRect,(QPixmap&)*(imageData),imageViewRect);
}



void ImagePainter::resize()
{
    if(imageData==NULL||imageData->isNull())
        return;
    //get resized image rect
    QSize imageSize=imageData->size();
    QSize resizedImageSize(imageSize);
    QSize windowSize=parent->size();
    QSize viewPortSize(windowSize);
    if(resizeMode&(RATE|NO_RATE))
    {
        viewPortSize.scale((int)(windowSize.width()/resizeRate),(int)(windowSize.height()/resizeRate),Qt::KeepAspectRatio);
        resizedImageSize.scale(imageSize.width()*resizeRate,imageSize.height()*resizeRate,Qt::KeepAspectRatio);
    }
     //make image source position
    if(resizeMode&(FIT_WINDOW))
    {
        if((resizeMode&FIT_WINDOW)==FIT_WINDOW)
        {
            viewPortSize.scale(imageSize.width(),imageSize.height(),Qt::KeepAspectRatio);
            this->imageViewRect.setSize(viewPortSize);
            this->targetViewRect.setSize(windowSize);
        }
        else
        {
            if(resizeMode&FIT_WINDOW_WIDTH)
            {
                viewPortSize.scale(imageSize.width(),1,Qt::KeepAspectRatioByExpanding);
                this->imageViewRect.setSize(viewPortSize);
            }
            else if(resizeMode&FIT_WINDOW_HEIGHT)
            {
                viewPortSize.scale(1,imageSize.height(),Qt::KeepAspectRatioByExpanding);
                this->imageViewRect.setSize(viewPortSize);
            }

            this->targetViewRect.setSize(windowSize);
        }

    }
    else if(resizeMode & (NO_FIT))
    {

        this->imageViewRect.setSize(viewPortSize);
        this->targetViewRect.setSize(windowSize);

    }
    else if(resizeMode & (FIT_IMAGE))
    {
        this->imageViewRect.setSize(imageSize);



        if(!parent->isMaximized())
        {
            int desktopHeight=QApplication::desktop()->height();
            int desktopWidth=QApplication::desktop()->width();
            QSize parentSize(imageSize.width(),imageSize.height());
            if(desktopHeight<parentSize.height()||desktopWidth<parentSize.width())
                resizedImageSize.scale(QSize(desktopHeight,desktopWidth),Qt::KeepAspectRatio);
            parent->resize(resizedImageSize);
        }
        this->targetViewRect.setSize(resizedImageSize);


    }
    else
    {
        qErrnoWarning("error");
    }





   //make target rect
}

