#include "pageviewer.h"
#include <QDebug>
PageViewer::PageViewer()
{
}
int PageViewer::setMoveMode(int mode)
{
    this->moveMode=(MoveMode)mode;
    return moveMode;
}

int PageViewer::go(bool start)
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
        imageViewRect.moveTop(0);
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

int PageViewer::back()
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

int PageViewer::moveVertical(bool start,bool back)
{

//    int movePos=-1;
//    int moveMode=this->moveMode;
//    if(back)
//        moveMode=~moveMode;
//    if(moveMode&DOWN_TO_UP)
//    {
//        if(start)
//        {
//            imageViewRect.moveBottom(imageData->height());
//            movePos=imageViewRect.top();
//        }
//        else
//        {
//            if(imageViewRect.top()>0)
//            {
//                imageViewRect.translate(0,qMax(-imageViewRect.top(),(int)(-parent->height()*resizeRate+10)));
//                movePos=imageViewRect.top();
//            }
//        }
//    }
//    else
//    {
//        if(start)
//        {
//            imageViewRect.moveTop(0);
//            movePos=imageViewRect.top();
//            debugRect(imageViewRect);
//            debugRect(imageData->rect());
//        }
//        else
//        {

//            if(imageViewRect.bottom()<imageData->height()-1)
//            {
//                imageViewRect.translate(0,qMin((int)(parent->height()*resizeRate-10),imageData->height()-imageViewRect.bottom()));
//                movePos=imageViewRect.top();
//            }
//        }
//    }
//    return movePos;
}


int PageViewer::moveHorizontal(bool start,bool back)
{


//    int movePos=-1;
//    int moveMode=this->moveMode;
//    if(back)
//        moveMode=~moveMode;
//    if(moveMode&LEFT_TO_RIGHT)
//    {

//        if(start)
//        {
//            imageViewRect.moveLeft(0);
//            movePos=imageViewRect.left();

//        }
//        else
//        {
//            if(imageViewRect.right()<imageData->width()-1)
//            {
//                imageViewRect.translate(qMin(imageData->width()-imageViewRect.right(),(int)(parent->width()*resizeRate-10)),0);
//                movePos=imageViewRect.left();
//            }
//        }
//    }
//    else
//    {

//        if(start)
//        {
//            imageViewRect.moveRight(imageData->width()-1);
//            movePos=imageViewRect.left();

//        }
//        else
//        {

//            if(imageViewRect.left()>0)
//            {
//                imageViewRect.translate(qMax((int)(10-parent->width()*resizeRate),-imageViewRect.left()),0);
//                movePos=imageViewRect.left();
//            }
//        }
//    }
//    return movePos;
}

int PageViewer::stepUp(int step)
{
    int newTop=targetViewRect.top()-step;
    newTop=newTop<0?0:newTop;
    targetViewRect.moveTop(newTop);
    return newTop;
}

int PageViewer::stepDown(int step)
{
    int newBottom=targetViewRect.bottom()+step;
    newBottom=newBottom>imageViewRect.bottom()?imageViewRect.bottom():newBottom;
    targetViewRect.moveBottom(newBottom);
    return newBottom;
}

int PageViewer::stepLeft(int step)
{
    int newLeft=targetViewRect.left()-step;
    newLeft=newLeft<0?0:newLeft;
    targetViewRect.moveLeft(newLeft);
    return newLeft;
}

int PageViewer::stepRight(int step)
{
    int newRight=targetViewRect.right()+step;
    newRight=newRight>imageViewRect.right()?imageViewRect.right():newRight;
    targetViewRect.moveRight(newRight);
    return newRight;
}

QRect &PageViewer::getTargetViewRect()
{
    return targetViewRect;
}

QRect &PageViewer::getImageViewRect()
{
    return imageViewRect;
}
void PageViewer::setImageSize(QSize size)
{
    this->imageSize=size;
    this->imageViewRect.setSize(size);
}
void PageViewer::setClientSize(QSize size)
{
    this->clientSize=size;
    this->targetViewRect.setSize(size);
}

void PageViewer::newPage()
{
    if(this->moveMode&LEFT_TO_RIGHT)
    {
        targetViewRect.moveLeft(0);
    }
    else
    {
        targetViewRect.moveRight(imageViewRect.right());
    }
    if(this->moveMode&UP_TO_DOWN)
    {
        targetViewRect.moveTop(0);
    }
    else
    {
        targetViewRect.moveBottom(imageViewRect.bottom());
    }
}
