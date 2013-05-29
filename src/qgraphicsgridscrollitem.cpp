#include "qgraphicsgridscrollitem.h"
#include <QDebug>
QGraphicsGridScrollItem::QGraphicsGridScrollItem(QGraphicsItem *parent):QGraphicsItem(parent),mShowingCells(),mShowingItems(),mCacheItems(),mScrollArea(),mColumnCount(1)
{
    this->setFlag(this->ItemClipsChildrenToShape);
}

QRectF QGraphicsGridScrollItem::boundingRect() const
{
    return QRectF(QPointF(),this->mScrollArea);
}


QGraphicsPixmapItem *QGraphicsGridScrollItem::itemAt(int row, int column)
{
    int index=indexOf(row,column);
    for(int i=0;i<mShowingItems.size();i++)
    {
        if(mShowingItems.at(i)->data(0).toInt()==index)
            return mShowingItems.at(i);
    }
    for(int i=0;i<mCacheItems.size();i++)
    {
        if(mCacheItems.at(i)->data(0).toInt()==index)
            return mCacheItems.at(i);
    }
    return NULL;
}


void QGraphicsGridScrollItem::recoveryItems()
{
    mCacheItems.append(mShowingItems);
    mShowingItems.clear();
}

QPoint QGraphicsGridScrollItem::pointOf(int index)
{
    int row=0;
    int column=0;
    row=index/mColumnCount;
    if(mLayoutMethod.testFlag(RIGHT_TO_LEFT))
    {
        column=index%mColumnCount;
    }
    else
    {
        column=index-index%mColumnCount;
    }
    return QPoint(row,column);
}

QImage *QGraphicsGridScrollItem::getImage(int index)
{
    if(mImages.contains(index))
        return mImages[index];
    else
    {
        emit onLoadImage(index);
    }
    if(mImages.contains(index))
        return mImages[index];
    return NULL;
}


void QGraphicsGridScrollItem::placeToCell(QGraphicsPixmapItem *item, int row, int column)
{
    Q_ASSERT(0);
}


void QGraphicsGridScrollItem::createShowingItems()
{
    int row=mShowingCells.top();
    qreal columnWidth=mScrollArea.width()/mColumnCount;
    qreal totalHeight=0;
    qreal areaHeight=mScrollArea.height();
    while(totalHeight<areaHeight)
    {
        for(int i=0;i<mColumnCount;i++)
        {

            int column=mLayoutMethod.testFlag(RIGHT_TO_LEFT)?mColumnCount-i:i;
            QGraphicsPixmapItem *item=getOrCreateItemAt(row,column);
            if(item->data(1).toInt()==1)
            {
                QImage *image=getImage(indexOf(row,column));
                if(image==NULL)
                {
                    image=new QImage(QSize(1,1),QImage::Format_RGB16);
                }
                item->setPixmap(QPixmap::fromImage(*image));
                item->setData(1,0);
                itemWidthTo(item,columnWidth);
            }
        }
        totalHeight+=mapRectToItem(this, itemAt(row,0)->boundingRect()).height();
        mShowingCells.setBottom(row);
        row++;
    }
    layout();
}


QGraphicsPixmapItem *QGraphicsGridScrollItem::getCachedItem()
{
    if(mCacheItems.empty())
        return new QGraphicsPixmapItem(this,this->scene());
    else
        return mCacheItems.first();
}


QGraphicsPixmapItem *QGraphicsGridScrollItem::getOrCreateItemAt(int row, int column)
{
    QGraphicsPixmapItem *item=itemAt(row,column);
    if(item!=NULL)
    {
        return item;
    }
    else
    {
        item=getCachedItem();
        //placeToCell(item,row,column);
        item->setData(1,1);
        item->setData(0,indexOf(row,column));
        mShowingItems.append(item);
        return item;
    }
}


void QGraphicsGridScrollItem::itemWidthTo(QGraphicsPixmapItem *item, int width)
{
    qDebug()<<item->boundingRect().width();
    item->setScale(width/item->boundingRect().width());
}

int QGraphicsGridScrollItem::indexOf(int row, int column)
{
    if(mLayoutMethod.testFlag(RIGHT_TO_LEFT))
        return (row+1)*mColumnCount-column;
    else
        return row*mColumnCount+column;
}

int QGraphicsGridScrollItem::indexOf(QPoint point)
{
    return indexOf(point.x(),point.y());
}

void QGraphicsGridScrollItem::layout()
{
    int xpos,ypos;
    //xpos=mOffset.x();
    ypos=mOffset.y();
    int columnWidth=mScrollArea.width()/mColumnCount;
    for(int i=mShowingCells.top();i<mShowingCells.height();i++)
    {
        int maxHeight=0;
        for(int j=mShowingCells.left();j<mShowingCells.width();j++)
        {

            int column=mLayoutMethod.testFlag(RIGHT_TO_LEFT)?mColumnCount-j:j;
            int xpos=column*columnWidth;
            QGraphicsItem *item=itemAt(i,j);
            if(item==NULL)
            {
                qDebug()<<"error getting item!";
                continue;
            }
            item->setPos(xpos,ypos);
            maxHeight=std::max(maxHeight,(int)mapRectToItem(this,item->boundingRect()).height());

        }
        ypos+=maxHeight;
    }
}


void QGraphicsGridScrollItem::setImage( int index,QImage *image)
{
    mImages[index]=image;
}


void QGraphicsGridScrollItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

void QGraphicsGridScrollItem::scrollToCell(int row, int column, int offsetx, int offsety)
{
    mShowingCells.setTop(row);
    mShowingCells.setHeight(0);
    mOffset.setX(offsetx);
    mOffset.setY(offsety);
    //recoveryItems();
    createShowingItems();

}
