#include "qgraphicsgridscrollitem.h"
#include <QDebug>
QGraphicsGridScrollItem::QGraphicsGridScrollItem(QGraphicsItem *parent):QGraphicsItem(parent),mShowingCells(),mShowingItems(),mCacheItems(),mVisibleSize(),mColumnCount(1),rowHeights()
{
    this->setFlag(this->ItemClipsChildrenToShape);
    mShowingCells.setTop(0);
    mShowingCells.setHeight(0);
    prepareLayout();
    mTotalItemCount=0;
}

QRectF QGraphicsGridScrollItem::boundingRect() const
{
    return QRectF(QPointF(),this->mVisibleSize);
}


QGraphicsPixmapItem *QGraphicsGridScrollItem::itemAt(int row, int column)
{
    int index=indexOf(row,column);
    for(int i=0;i<mShowingItems.size();i++)
    {
        if(mShowingItems.at(i)->data(0).toInt()==index)
            return mShowingItems.at(i);
    }
    //    for(int i=0;i<mCacheItems.size();i++)
    //    {
    //        if(mCacheItems.at(i)->data(0).toInt()==index)
    //            return mCacheItems.at(i);
    //    }
    return NULL;
}


void QGraphicsGridScrollItem::recoveryItems()
{
    for(int i=mLoadedCells.top();i<mShowingCells.top();i++)
    {
        for(int j=0;j<mColumnCount;j++)
        {
            QGraphicsPixmapItem *item=itemAt(i,j);
            if(item!=NULL)
            {
                  item->setZValue(0);
                item->setData(2,indexOf(i,j));
                mShowingItems.removeOne(item);
                if(!mCacheItems.contains(item))
                    mCacheItems.append(item);
            }
        }
    }
    for(int i=mShowingCells.bottom()+1;i<=mLoadedCells.bottom();i++)
    {
        for(int j=0;j<mColumnCount;j++)
        {
            QGraphicsPixmapItem *item=itemAt(i,j);
            if(item!=NULL)
            {
                 item->setZValue(0);
                item->setData(2,indexOf(i,j));
                mShowingItems.removeOne(item);
                if(!mCacheItems.contains(item))
                mCacheItems.append(item);
            }
        }
    }
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
    qreal columnWidth=mVisibleSize.width()/mColumnCount;
    for(int row=mShowingCells.top();row<=mShowingCells.bottom();row++)
    {
        for(int j=0;j<mColumnCount;j++)
        {
            int column=mLayoutMethod.testFlag(RIGHT_TO_LEFT)?mColumnCount-j:j;
            QGraphicsPixmapItem *item=getOrCreateItemAt(row,column);
            if(item->data(1).toInt()==1)
            {
                QImage *image=getImage(indexOf(row,column));
                if(image==NULL||image->isNull())
                {

                    image=new QImage(QSize(this->mVisibleSize.width(),1),QImage::Format_RGB16);
                }
                item->setPixmap(QPixmap::fromImage(*image));
                item->setData(1,0);
                //itemWidthTo(item,columnWidth);
            }
        }
    }
    needLayout=false;
}

QGraphicsPixmapItem *QGraphicsGridScrollItem::getCachedItem()
{
    if(mCacheItems.empty())
        return new QGraphicsPixmapItem(this);
    else
    {
        QGraphicsPixmapItem *item=mCacheItems.first();
        emit onUnloadImage(item->data(2).toInt());
        mImages.remove(item->data(2).toInt());
        mCacheItems.removeFirst();
        return item;
    }
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
    item->setScale(width/item->boundingRect().width());
}

void QGraphicsGridScrollItem::calucatePosition()
{
    int row=mShowingCells.top();
    mShowingCells.setBottom(row);
    int height=rowHeight(row);
    mScrollArea.setHeight(height);
    row--;

    if(row<0&&mScrollArea.top()>0)
    {
        mScrollArea.setTop(0);
    }
    //make area.top<0 and remove bottom invisible cells
    while(((mScrollArea.top()>0) && (row >= 0)))
    {
        int height=rowHeight(row);
        if(mScrollArea.top()>mVisibleSize.height())
        {
            mShowingCells.setBottom(mShowingCells.top()-1);
            mScrollArea.setBottom(mScrollArea.top());
        }
        mScrollArea.setTop(mScrollArea.top()-height);
        mShowingCells.setTop(row);
        row--;
    }
    row=mShowingCells.bottom()+1;
    //make area.bottom>scrollarea.height and remove top invisible cells
    while(mScrollArea.bottom()<mVisibleSize.height() && (row<mTotalItemCount))
    {
        int height=rowHeight(row);
        if(mScrollArea.bottom()<0 && mShowingCells.height()>0)
        {
            mShowingCells.setTop(mShowingCells.bottom()+1);
            mScrollArea.setTop(mScrollArea.bottom());
        }
        mScrollArea.setBottom(mScrollArea.bottom()+height);
        mShowingCells.setBottom(row);
        row++;
    }
    if(row==mTotalItemCount&&mScrollArea.bottom()<mVisibleSize.height())
    {
        if(mScrollArea.height()<mVisibleSize.height())
            mScrollArea.moveTop((mVisibleSize.height()-mScrollArea.height())/2);
        mScrollArea.moveBottom(mVisibleSize.height());
        row=mShowingCells.top()-1;
        while((mScrollArea.top()>0) && (row >= 0))
        {
            int height=rowHeight(row);
            mScrollArea.setTop(mScrollArea.top()-height);
            mShowingCells.setTop(row);
            row--;
        }
    }

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
    ypos=mScrollArea.top();
    int columnWidth=mVisibleSize.width()/mColumnCount;
    for(int i=mShowingCells.top();i<=mShowingCells.bottom();i++)
    {
        for(int j=0;j<mColumnCount;j++)
        {
            int column=mLayoutMethod.testFlag(RIGHT_TO_LEFT)?mColumnCount-j:j;
            int xpos=column*columnWidth;
            QGraphicsPixmapItem *item=getOrCreateItemAt(i,j);

            if(item==NULL)
            {
                qDebug()<<"error getting item!";
                continue;
            }
            item->setZValue(1);
            //item->setOpacity(0.4);
            item->setPos(xpos,ypos);
            itemWidthTo(item,mVisibleSize.width());
        }
        ypos+=rowHeight(i);
    }
}


void QGraphicsGridScrollItem::setImage( int index,QImage *image)
{
    mImages[index]=image;
}

void QGraphicsGridScrollItem::updateView()
{

    if(mTotalItemCount==0)
        return;
    calucatePosition();
    createShowingItems();
    layout();
    recoveryItems();
    mLoadedCells=mShowingCells;
}

void QGraphicsGridScrollItem::clear()
{

    QList<QGraphicsItem *> items=this->childItems();
    for(int i=0;i<items.size();i++)
    {
        delete items.at(i);
    }

    mImages.clear();
    rowHeights.clear();
    mShowingItems.clear();
    mCacheItems.clear();
    mTotalItemCount=0;
}


void QGraphicsGridScrollItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

void QGraphicsGridScrollItem::scrollToCell(int row, int column, int offsetx, int offsety)
{
    row=std::max(row,0);
    row=std::min(row,mTotalItemCount/mColumnCount);
    mShowingCells.setTop(row);
    mShowingCells.setHeight(0);
    prepareLayout();
    mScrollArea.setLeft(offsetx);
    mScrollArea.setTop(offsety);
    //recoveryItems();
}

void QGraphicsGridScrollItem::scrollBy(int offsetx, int offsety)
{

    mScrollArea.setLeft(offsetx);
    mScrollArea.setTop(mScrollArea.top()+offsety);
}


QRect QGraphicsGridScrollItem::showingItemRect()
{
    return mScrollArea;
}

int QGraphicsGridScrollItem::rowHeight(int row)
{
    qreal columnWidth=mVisibleSize.width()/mColumnCount;
//    if(rowHeights.contains(row))
//        return rowHeights[row]*columnWidth;
//    else
    {
        qreal height=0;


        for(int i=0;i<mColumnCount;i++)
        {
            int column=mLayoutMethod.testFlag(RIGHT_TO_LEFT)?mColumnCount-i:i;
            QImage *image=getImage(indexOf(row,column));
            if(image==NULL||image->isNull())
            {
                height=0;
                break;
            }

            height=std::max(((qreal)image->height()/image->width()),(qreal)0);
        }
        rowHeights[row]=height;
        return height*columnWidth;
    }
}
