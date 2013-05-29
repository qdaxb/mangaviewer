#ifndef QGRAPHICSCACHEDSCROLLITEM_H
#define QGRAPHICSCACHEDSCROLLITEM_H
#include <QGraphicsItem>
#include <QPoint>
#include <QRect>
#include <QSize>
#include <QList>
#include <QObject>
class QGraphicsGridScrollItem:public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    enum CacheMode{CACHE_UP=0x0,
                   CACHE_DOWN=0x1,
                   CACHE_LEFT=0x2,
                   CACHE_RIGHT=0x4};
    enum LayoutMethod{LEFT_TO_RIGHT=0x0,
                     RIGHT_TO_LEFT=0x1,
                     UP_TO_DOWN=0x2,
                     DOWN_TO_UP=0x4};

    Q_DECLARE_FLAGS( CacheModes, CacheMode)
    Q_DECLARE_FLAGS( LayoutMethods, LayoutMethod)
    QGraphicsGridScrollItem(QGraphicsItem *parent=0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void scrollToCell(int row,int column,int offsetx,int offsety);
    void scrollBy(int x,int y);
    QGraphicsPixmapItem *itemAt(int row,int column);
    void setTotalItemCount(int count){mTotalItemCount=count;}
    void setSize(int width,int height){mSize.setWidth(width);mSize.setHeight(height);}
    void setCacheType(CacheModes type){mCacheType=type;}
    void setScrollArea(int width,int height){mScrollArea.setWidth(width);mScrollArea.setHeight(height);}
    void setRowCount(int rowCount){mRowCount=rowCount;}
    void setColumnCount(int columnCount){mColumnCount=columnCount;}
    bool isReachTop();
    bool isReachBottom();
    bool isReachLeft();
    bool isReachRight();
    void setImage(int index, QImage *image);
private:
    QGraphicsPixmapItem *getOrCreateItemAt(int row,int column);
    QGraphicsPixmapItem *getCachedItem();
    void setItemImage(QGraphicsPixmapItem *item,QImage *image);
    void itemWidthTo(QGraphicsPixmapItem *item,int width);
    int indexOf(int row,int column);
    int indexOf(QPoint point);
    void layout();
    void createShowingItems();
    void createCacheItems();
    void placeToCell(QGraphicsPixmapItem *item,int row,int column);
    bool needLoding();
    void recoveryItems();
    QPoint pointOf(int index);
    QPoint mOffset;
    QRect mShowingCells;
    QRect mLoadedCells;
    QSize mScrollArea;
    QSize mSize;
    CacheModes mCacheType;
    int mRowCount;
    int mColumnCount;
    QList<QGraphicsPixmapItem*> mShowingItems;
    QList<QGraphicsPixmapItem*> mCacheItems;
    QMap<int,QImage*> mImages;
    QImage *getImage(int index);
    int mTotalItemCount;
    LayoutMethods mLayoutMethod;
signals:
    void onLoadImage(int imdex);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(QGraphicsGridScrollItem::CacheModes)
Q_DECLARE_OPERATORS_FOR_FLAGS(QGraphicsGridScrollItem::LayoutMethods)
#endif // QGRAPHICSCACHEDSCROLLITEM_H
