#include "pageviewer.h"
#include <QDebug>
int PageViewer::setMoveMode(int mode)
{
    this->moveMode=(MoveMode)mode;
    return moveMode;
}

int PageViewer::go(bool start)
{
    if(isPageFinished())
        return -1;
    if(isHorizontalFinished())
    {
        moveVertical();
        initHorizontal();
    }
    else
    {
        moveHorizontal();
    }

//    if(isPageFinished())
//        return -1;
    return 0;
}

int PageViewer::back()
{
    if(isPageFinished(true))
        return -1;
    if(isHorizontalFinished(true))
    {
        moveVertical(true);
        initHorizontal(true);
    }
    else
    {
        moveHorizontal(true);
    }

//    if(isPageFinished(true))
//        return -1;
    return 0;
}

int PageViewer::moveVertical(bool back)
{
    if(((bool)(this->moveMode&UP_TO_DOWN))^back)
    {
        if(this->stepDown(this->targetViewRect.height())==this->imageViewRect.bottom())
            return -1;
        return 0;
    }
    else
    {
        if(this->stepUp(this->targetViewRect.height())==0)
            return -1;
        return 0;
    }
}


int PageViewer::moveHorizontal(bool back)
{
    if(((bool)(this->moveMode&LEFT_TO_RIGHT))^back)
    {
        if(this->stepRight(this->targetViewRect.width())==this->imageViewRect.right())
            return -1;
        return 0;
    }
    else
    {
        if(this->stepLeft(this->targetViewRect.width())==0)
            return -1;
        return 0;
    }


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
    this->imageSize.setHeight(100);
    this->imageSize=size;
    this->imageViewRect.setSize(size);
}
void PageViewer::setClientSize(QSize size)
{
    this->clientSize=size;
    this->targetViewRect.setSize(size);
}
void PageViewer::initVertical(bool back){
    if(targetViewRect.height()>imageViewRect.height())
    {
        targetViewRect.moveTop((imageViewRect.height()-targetViewRect.height())>>1);
        return;
    }
    if(((bool)(this->moveMode&UP_TO_DOWN))^back)
     {
         targetViewRect.moveTop(0);
     }
     else
     {
         targetViewRect.moveBottom(imageViewRect.bottom());
     }
}
void PageViewer::initHorizontal(bool back){
    if(targetViewRect.width()>imageViewRect.width())
    {
        targetViewRect.moveLeft((imageViewRect.width()-targetViewRect.width())>>1);
        return;
    }
    if(((bool)(this->moveMode&LEFT_TO_RIGHT))^back)
    {
        targetViewRect.moveLeft(0);
    }
    else
    {
        targetViewRect.moveRight(imageViewRect.right());
    }
}
void PageViewer::newPage()
{
    initVertical();
    initHorizontal();

}
bool PageViewer::isHorizontalFinished(bool back)
{
    if(targetViewRect.height()>imageViewRect.height())
    {
        return true;
    }
    if(((bool)(this->moveMode&LEFT_TO_RIGHT))^back)
    {
        if(targetViewRect.right()<imageViewRect.right())
            return false;
    }
    else
    {
        if(targetViewRect.left()>0)
            return false;
    }
    return true;
}

bool PageViewer::isVerticalFinished(bool back)
{
    if(targetViewRect.width()>imageViewRect.width())
    {
        return true;
    }
    if(((bool)(this->moveMode&UP_TO_DOWN))^back)
    {
        if(targetViewRect.bottom()<imageViewRect.bottom())
            return false;
    }
    else
    {
        if(targetViewRect.top()>0)
            return false;
    }
    return true;
}

bool PageViewer::isPageFinished(bool back)
{
   return isVerticalFinished(back)&&isHorizontalFinished(back);

}
