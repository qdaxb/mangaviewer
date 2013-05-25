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
    void setImage(QImage *image);
    QSize getPageSize();
    QSize getFullSize();
    QSize getBaseSize();
    QSize getImageSize();
    QImage *getImage(){return image;}
    void setFilePath(QString filePath){this->filePath=filePath;}
    QString getFilePath(){return filePath;}
    void updateImage();
    void detimeRects();
    QSize getFullPageSize();
private:
    bool needSplit();
    QString filePath;
    void doSplitPage();
    int splitMode;
    int pageCount;
    int currentIndex;
    QList<QGraphicsPixmapItem*> splittedPages;
    QImage *image;
    QPixmap *pixmap;
    QSize pageSize;
signals:
    
public slots:
    
};

#endif // QGRAPHICSPAGEDPIXMAPITEM_H
