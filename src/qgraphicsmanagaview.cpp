#include "qgraphicsmanagaview.h"
#include "ui_qgraphicsmanagaview.h"
#include "qgraphicspagedpixmapitem.h"
#include <QGraphicsScene>
#include <QBrush>
#include <QDebug>
#include <QPixmap>


QGraphicsManagaView::QGraphicsManagaView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGraphicsManagaView),scene(),pageViewers()
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    scene.setBackgroundBrush(QBrush(Qt::black));
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    {
        QGraphicsPagedPixmapItem *pageViewer=new QGraphicsPagedPixmapItem();
        pageViewer->setPageSplitMode(Manga::SPLIT_AUTO);
        QPixmap *map=new QPixmap();
        map->load("/home/axb/test.jpg");
        scene.addItem(pageViewer);
        pageViewer->setImage(map);
        pageViewers.push_back(pageViewer);
    }
    {
        QGraphicsPagedPixmapItem *pageViewer=new QGraphicsPagedPixmapItem();
        pageViewer->setPageSplitMode(Manga::SPLIT_AUTO);
        QPixmap *map=new QPixmap();
        map->load("/home/axb/test1.jpg");
        scene.addItem(pageViewer);
        pageViewer->setImage(map);
        pageViewer->setY(pageViewers.last()->y()+pageViewers.last()->getFullSize().height());
        qDebug()<<"a"<<pageViewers.last()->y();
        qDebug()<<"c"<<pageViewers.last()->getFullSize().height();
        qDebug()<<"b"<<pageViewer->y();
        pageViewers.push_back(pageViewer);
    }
}

void QGraphicsManagaView::keyReleaseEvent(QKeyEvent *)
{
    go(0.1);
}

QGraphicsManagaView::~QGraphicsManagaView()
{
    delete ui;
}

void QGraphicsManagaView::go(qreal step)
{
    bool needNextPage=false;
    qreal distance=-scene.height()*step;
    for(int i=0;i<pageViewers.size();i++)
    {
        pageViewers.at(i)->moveBy(0,distance);
        if(pageViewers.at(i)->y()+pageViewers.at(i)->getFullSize().height()<0)
            needNextPage=true;
    }
    if(needNextPage)
    {
        QGraphicsPagedPixmapItem *item=pageViewers.first();
        pageViewers.pop_front();
        //todo load next
        item->setY(pageViewers.last()->y()+pageViewers.last()->getFullSize().height());

        pageViewers.push_back(item);
    }
}

void QGraphicsManagaView::back(qreal step)
{
}

void QGraphicsManagaView::resizeEvent(QResizeEvent *event)
{
    scene.setSceneRect(QRect(QPoint(0,0),this->size()));
    for(int i=0;i<pageViewers.size();i++){
        pageViewers.at(i)->setPos((scene.width()- pageViewers.at(i)->getPageSize().width())/2, pageViewers.at(i)->y());
    }

}
