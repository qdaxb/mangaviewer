#ifndef QGRAPHICSPAGEDPIXMAPITEM_H
#define QGRAPHICSPAGEDPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include "common.h"
#include <QSize>
#include <QList>
class QGraphicsPagedPixmapItem : public QGraphicsItem
{
public:
    explicit QGraphicsPagedPixmapItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPageSplitMode(int mode){this->splitMode=mode;}
    int getPageCount(){return pageCount;}
    void setImage(QPixmap *image);
    QSize getPageSize();
    QSize getFullSize();
    QSize getImageSize();
private:
    bool needSplit();
    void doSplitPage();
    int splitMode;
    int pageCount;
    int currentIndex;
    QList<QGraphicsPixmapItem*> splittedPages;
    QPixmap *image;
    QSize pageSize;
signals:
    
public slots:
    
};

#endif // QGRAPHICSPAGEDPIXMAPITEM_H
