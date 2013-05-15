#include "qgraphicspagedpixmapitem.h"
#include <QGraphicsScene>
#include "common.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
QGraphicsPagedPixmapItem::QGraphicsPagedPixmapItem(QGraphicsItem *parent) :
    QGraphicsItem(parent),splitMode(Manga::SPLIT_AUTO),splittedPages(),image(NULL)
{
    for(int i=0;i<2;i++)
    {
        QGraphicsPixmapItem *newItem=new QGraphicsPixmapItem(this);
        splittedPages.append(newItem);
    }

}

QRectF QGraphicsPagedPixmapItem::boundingRect() const
{
    if(image==NULL)
        return QRectF();
    else
        return QRectF(0,0,this->pageSize.width(),this->pageSize.height()*pageCount);

}

void QGraphicsPagedPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(int i=0;i<2;i++)
    {
       // splittedPages.at(i)->paint(painter,option,widget);
    }
}

void QGraphicsPagedPixmapItem::setImage(QPixmap *image)
{
    if(image==NULL)
        return;
    this->image=image;
    for(int i=0;i<2;i++)
    {
        splittedPages.at(i)->setPixmap((QPixmap&)(*image));
    }
    updateImage();
}

QSize QGraphicsPagedPixmapItem::getPageSize()
{
    return pageSize;
}

QSize QGraphicsPagedPixmapItem::getFullSize()
{
    if(image==NULL)
        return QSize(0,0);
    return QSize(pageSize.width()*this->scale(),pageSize.height()*pageCount*this->scale());
}

QSize QGraphicsPagedPixmapItem::getBaseSize()
{
    if(image==NULL)
            return QSize(0,0);
        return QSize(pageSize.width(),pageSize.height()*pageCount);
}

QSize QGraphicsPagedPixmapItem::getImageSize()
{
    if(image==NULL)
        return QSize();
    return image->size();
}

void QGraphicsPagedPixmapItem::updateImage()
{

    doSplitPage();
}

bool QGraphicsPagedPixmapItem::needSplit()
{
    if(image->height()<image->width())
        return true;
    return false;
}

void QGraphicsPagedPixmapItem::doSplitPage()
{
    prepareGeometryChange();
    pageSize.setHeight(image->height());
    if(!needSplit())
    {
        pageCount=1;
        pageSize.setWidth(image->width());
        splittedPages.first()->setY(0);
        splittedPages.first()->setPixmap((QPixmap &)*image);
        return;
    }
    pageCount=2;
    pageSize.setWidth(image->width()/2);

    //splittedPages.first()->setPos(splittedPages.first()->mapToItem(this,0,0));
    splittedPages.first()->setY(0);
//    splittedPages.first()->pixmap()
    splittedPages.first()->setPixmap(image->copy(pageSize.width(),0,pageSize.width(),pageSize.height()));
    splittedPages.last()->setY(pageSize.height());
    //delete &splittedPages.last()->pixmap();
    splittedPages.last()->setPixmap(image->copy(0,0,pageSize.width(),pageSize.height()));

}


