#include "qgraphicsmanagaview.h"
#include "ui_qgraphicsmanagaview.h"
#include "qgraphicspagedpixmapitem.h"
#include <QGraphicsScene>
#include <QBrush>
#include <QDebug>
#include <QPixmap>
#include "filemanager.h"
#include "commandregistry.h"
#include <QKeyEvent>
#include "viewercommand.h"
#include <QSettings>
#include <QApplication>
#include <algorithm>
QGraphicsManagaView::QGraphicsManagaView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGraphicsManagaView),scene(),pageViewers(),pageIndexs(),fileManager(),rate(1)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    scene.setBackgroundBrush(QBrush(Qt::black));
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QSettings setting(QApplication::applicationDirPath ()+"/settings.ini",QSettings::IniFormat);
    setting.beginGroup("keys");
    QStringList list=setting.childKeys();
    for(int i=0;i<list.size();i++)
    {
        QString key=list.at(i);
        QString value=setting.value(key).toString();
        QStringList valueList=value.split("|");
        for(int j=0;j<valueList.size();j++)
        {
            CommandRegistry::map(valueList.at(j),"Viewer"+key+"Command");
        }
    }

}


int QGraphicsManagaView::load(QString fileorpath)
{
    pageIndexs.clear();
    fileManager.load(fileorpath);
    init();
}

void QGraphicsManagaView::init()
{
    int pageCount=0;
    qreal totalHeight=0;
    isFirstPage=true;
    isLastPage=fileManager.size()==1;
    while(totalHeight<scene.height()||pageCount<=1)
    {
        QString file=fileManager.get(pageCount);
        if(file=="")
            break;
        QPixmap *image;
        if(pageViewers.size()<=pageCount)
        {
            QGraphicsPagedPixmapItem *pageViewer=new QGraphicsPagedPixmapItem();

            //todo split mode
            pageViewer->setPageSplitMode(Manga::SPLIT_AUTO);
            scene.addItem(pageViewer);
            image=new QPixmap(file);
            pageViewer->setImage(image);
            pageViewer->setFilePath(file);
            pageViewers.push_back(pageViewer);

        }
        else
        {

            image=pageViewers.at(pageCount)->getImage();
            if(image==NULL)
            {
                image=new QPixmap();
            }
            image->load(file);
            pageViewers.at(pageCount)->setImage(image);
            pageViewers.at(pageCount)->setFilePath(file);

        }
        pageIndexs.push_back(pageCount);
        pageCount++;
        totalHeight+=pageViewers.last()->getFullSize().height();

    }
    if(pageCount<pageViewers.size())
    {
        int totalSize=pageViewers.size();
        for(int i=pageCount;i<totalSize;i++)
        {
            scene.removeItem(pageViewers.last());
            pageViewers.removeLast();
        }
    }

    adjustPages();

}

void QGraphicsManagaView::adjustPages()
{
    if(pageViewers.isEmpty())
        return;
    pageViewers.first()->setX((scene.width() - pageViewers.first()->getFullSize().width())/2);
    if(pageViewers.first()->y()>0)
        pageViewers.first()->setY(0);
    qreal ypos=pageViewers.first()->getFullSize().height();
    for(int i=1;i<pageViewers.size();i++)
    {

        pageViewers.at(i)->setX((scene.width() - pageViewers.at(i)->getFullSize().width())/2);
        pageViewers.at(i)->setY(ypos);
        ypos+=pageViewers.at(i)->getFullSize().height();
    }
}

QGraphicsManagaView::~QGraphicsManagaView()
{
    delete ui;
}

void QGraphicsManagaView::go(qreal step)
{
    if(pageViewers.size()==0)
        return;
    if(step==0)
        step=0.3;
    bool needNextPage=false;
    qreal distance=isLastPage?scene.height()-pageViewers.last()->getFullSize().height()-pageViewers.last()->y():-scene.height()*step;
    distance=std::max(distance,-scene.height()*step);
    for(int i=0;i<pageViewers.size();i++)
    {

        pageViewers.at(i)->moveBy(0,distance);
        if(pageViewers.at(i)->y()+pageViewers.at(i)->getFullSize().height()<0)
            needNextPage=true;
    }
    if(needNextPage && ( ! isLastPage ) )
    {
        isFirstPage=false;
        QGraphicsPagedPixmapItem *item=pageViewers.first();
        pageViewers.pop_front();
        pageIndexs.pop_front();
        //todo load next
        int lastIndexInView=pageIndexs.last();
        QString file=fileManager.get(lastIndexInView+1);
        if(file=="")
            isLastPage=true;
        item->getImage()->load(file);
        item->updateImage();
        item->setFilePath(file);
        item->setY(pageViewers.last()->y()+pageViewers.last()->getFullSize().height());
        item->setX((scene.width() - item->getFullSize().width())/2);
        pageIndexs.push_back(lastIndexInView+1);
        pageViewers.push_back(item);
    }
}

void QGraphicsManagaView::back(qreal step)
{
    if(pageViewers.size()==0)
        return;
    if(step==0)
        step=0.3;
    bool needNextPage=false;
    qreal distance=isFirstPage?-pageViewers.first()->y():scene.height()*step;
    distance=std::min(distance,scene.height()*step);
    for(int i=0;i<pageViewers.size();i++)
    {
        pageViewers.at(i)->moveBy(0,distance);
        if(pageViewers.at(i)->y()>scene.height())
            needNextPage=true;
    }
    if(needNextPage &&(!isFirstPage))
    {

        isLastPage=false;
        QGraphicsPagedPixmapItem *item=pageViewers.last();
        pageViewers.pop_back();
        pageIndexs.pop_back();
        //todo load previous
        int index=pageIndexs.first();
        QString file=fileManager.get(index-1);
        qDebug()<<file<<"  "<<index;
        item->getImage()->load(file);
        item->updateImage();
        item->setFilePath(file);
        item->setY(pageViewers.first()->y()-item->getFullSize().height());
        item->setX((scene.width() - item->getFullSize().width())/2);

        if(index==1)
            isFirstPage=true;
        pageViewers.push_front(item);
        pageIndexs.push_front(index-1);
    }
}

void QGraphicsManagaView::resizeEvent(QResizeEvent *event)
{
    scene.setSceneRect(QRect(QPoint(0,0),this->size()));
    for(int i=0;i<pageViewers.size();i++){
        pageViewers.at(i)->setPos((scene.width()- pageViewers.at(i)->getPageSize().width())/2, pageViewers.at(i)->y());
    }

}
void QGraphicsManagaView::mousePressEvent(QMouseEvent *event)
{
    CommandRegistry::get(modCMD(event)+"M"+(QString::number(event->button())))->execute(this);
}

void QGraphicsManagaView::setScale(qreal rate)
{
    this->rate=rate;
    for(int i=0;i<pageViewers.size();i++)
    {
        qreal fitrate=scene.width()/pageViewers.at(i)->getBaseSize().width();
        pageViewers.at(i)->setScale(rate==-1?fitrate:std::min(rate,fitrate));
    }
    adjustPages();
}
qreal QGraphicsManagaView::getScale( )
{
   return rate;
}
QString QGraphicsManagaView::modCMD(QInputEvent *event)
{
    if(event->modifiers().testFlag(Qt::NoModifier))
        return "";
    QString cmd="";
    if(event->modifiers().testFlag(Qt::ControlModifier))
        cmd+="C+";
    if(event->modifiers().testFlag(Qt::ShiftModifier))
        cmd+="S+";
    if(event->modifiers().testFlag(Qt::AltModifier))
        cmd+="A+";
    return cmd;
}

void QGraphicsManagaView::wheelEvent(QWheelEvent *event)
{
    QString base="";
    if(event->delta()>0)
        CommandRegistry::get(modCMD(event)+"Wup")->execute(this);
    else
         CommandRegistry::get(modCMD(event)+"Wdown")->execute(this);
}

void QGraphicsManagaView::keyReleaseEvent(QKeyEvent *event)
{
    qDebug()<<event->key();
    CommandRegistry::get(modCMD(event)+"K"+(QString::number(event->key())))->execute(this);
}
