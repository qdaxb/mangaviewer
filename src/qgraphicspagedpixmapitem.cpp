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
    this->setAcceptDrops(false);
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
}

void QGraphicsPagedPixmapItem::setImage(QImage *image)
{
    if(image==NULL)
        return;
    this->image=image;
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

void QGraphicsPagedPixmapItem::detimeRects(){
//    QRgb *pixel=(QRgb*)image->bits();
//    pixel+=image->width();
//    pixel+=image->width();
//    pixel+=image->width();



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
        splittedPages.first()->setPixmap(QPixmap::fromImage(*image));
        return;
    }
    pageCount=2;
    pageSize.setWidth(image->width()/2);
    splittedPages.first()->setY(0);

    splittedPages.first()->setPixmap(QPixmap::fromImage(image->copy(pageSize.width(),0,pageSize.width(),pageSize.height())));
    splittedPages.last()->setY(pageSize.height());
    splittedPages.last()->setPixmap(QPixmap::fromImage(image->copy(0,0,pageSize.width(),pageSize.height())));

}


