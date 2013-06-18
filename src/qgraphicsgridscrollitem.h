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
    void scrollBy(int x, int offsety);
    QGraphicsPixmapItem *itemAt(int row,int column);
    void setTotalItemCount(int count){mTotalItemCount=count;}
    void setSize(int width,int height){mSize.setWidth(width);mSize.setHeight(height);}
    void setCacheType(CacheModes type){mCacheType=type;}
    void setVisibleArea(int width,int height){mVisibleSize.setWidth(width);mVisibleSize.setHeight(height);}
    void setRowCount(int rowCount){mRowCount=rowCount;}
    void setColumnCount(int columnCount){mColumnCount=columnCount;}
    bool isReachTop();
    bool isReachBottom();
    bool isReachLeft();
    bool isReachRight();
    void setImage(int index, QImage *image);
    void updateView();
    int currentRow(){return mShowingCells.top();}
    bool emptyRow(int row){return rowHeight(row)<=0;}
    virtual void clear();
    void clearImage();
    void prepareResize(){this->mNeedResize=true;}
    void setTransformationMode(Qt::TransformationMode mode){this->mMode=mode;}
    Qt::TransformationMode transformationMode(){return mMode;}
private:
    QGraphicsPixmapItem *getOrCreateItemAt(int row,int column);
    QGraphicsPixmapItem *getCachedItem();
    void prepareLayout(){needLayout=true;}
    void setItemImage(QGraphicsPixmapItem *item,QImage *image);
    void itemWidthTo(QGraphicsPixmapItem *item,int width);
    void calucatePosition();
    int indexOf(int row,int column);
    int indexOf(QPoint point);
    void layout();
    void createShowingItems();
    void createCacheItems();
    QRect showingItemRect();
    int rowHeight(int row);
    void placeToCell(QGraphicsPixmapItem *item,int row,int column);
    bool needLoding();
    void recoveryItems();
    QPoint pointOf(int index);
    QRect mShowingCells;
    QRect mLoadedCells;
    QSize mVisibleSize;
    QSize mSize;
    CacheModes mCacheType;
    int mRowCount;
    int mColumnCount;
    QList<QGraphicsPixmapItem*> mShowingItems;
    QList<QGraphicsPixmapItem*> mCacheItems;
    QMap<int,QImage*> mImages;
    QImage *getImage(int index);
    QMap<int,qreal> rowHeights;
    int mTotalItemCount;
    LayoutMethods mLayoutMethod;
    bool needLayout;
    QRect mScrollArea;
    bool mNeedResize;
    Qt::TransformationMode mMode;

signals:
    void onLoadImage(int imdex);
    void onUnloadImage(int imdex);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(QGraphicsGridScrollItem::CacheModes)
Q_DECLARE_OPERATORS_FOR_FLAGS(QGraphicsGridScrollItem::LayoutMethods)
#endif // QGRAPHICSCACHEDSCROLLITEM_H
