#include <QGraphicsScene>
#include <QBrush>
#include <QDebug>
#include <QPixmap>
#include <QKeyEvent>
#include <QSettings>
#include <QApplication>
#include <algorithm>
#include <QUrl>
#include <QFileInfo>
#include "filemanager.h"
#include "commandregistry.h"
#include "viewercommand.h"
#include "qgraphicsmanagaview.h"
#include "ui_qgraphicsmanagaview.h"
#include "qgraphicspagedpixmapitem.h"
#include "zipfileloader.h"
QGraphicsManagaView::QGraphicsManagaView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGraphicsManagaView),scene(),pageViewers(),pageIndexs(),fileManager(),rate(1),
    setting(QApplication::applicationDirPath ()+"/settings.ini",QSettings::IniFormat)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setAcceptDrops(false);
    scene.setBackgroundBrush(QBrush(Qt::black));
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
    setting.endGroup();
    setting.beginGroup("lastread");
    QString folder=setting.value("lastfolder").toString();
    QString file=setting.value("lastfile").toString();
    qreal width=setting.value("width").toReal();
    qreal height=setting.value("height").toReal();
    setting.endGroup();
    if(folder!="")
    {
        pageIndexs.clear();
        fileManager.load(folder);
    }
    if(file!="")
    {
        int index=fileManager.get(file);
        if(index!=-1)
            init(index);
    }
    else
        init();
    if((width>0)&&(height>0))
        this->resize(width,height);
    updateTitle();
    this->setAcceptDrops(true);
    dblClick=false;
}


int QGraphicsManagaView::load(QString fileorpath)
{
    pageIndexs.clear();
    int rtn=fileManager.load(fileorpath);
    if(rtn!=0)
    {
        return -1;
    }
    QFileInfo file(fileorpath);
    int index=fileManager.get(file.fileName());
    if(index!=-1)
        init(index);
    else
        init();
    return 0;
}

void QGraphicsManagaView::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons().testFlag(Qt::LeftButton))&&(event->buttons().testFlag(Qt::RightButton))) {

        move(event->globalPos() - dragPosition);

    }
}

void QGraphicsManagaView::mouseReleaseEvent(QMouseEvent *event)
{
    if(!dblClick)

        CommandRegistry::get(modCMD(event)+"M"+(QString::number(event->button())))->execute(this);
}
void QGraphicsManagaView::mousePressEvent(QMouseEvent *event)
{

    if ((event->buttons().testFlag(Qt::LeftButton))&&(event->buttons().testFlag(Qt::RightButton))) {

        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
        dblClick=true;

    }
    else
        dblClick=false;
}


void QGraphicsManagaView::init(int index)
{
    if(fileManager.size()==0)
    {
        for(int i=0;i<pageViewers.size();i++)
        {
            delete pageViewers.at(i);
        }
        pageViewers.clear();
        return;
    }
    int pageCount=index;
    qreal totalHeight=0;
    isFirstPage=index==0;
    isLastPage=fileManager.size()==1;
    while(totalHeight<scene.height()||pageCount<=index+1)
    {
        QString file=fileManager.get(pageCount);
        if(file=="")
            break;
        QImage *image;
        if(pageViewers.size()<=pageCount-index)
        {
            QGraphicsPagedPixmapItem *pageViewer=new QGraphicsPagedPixmapItem();
            qDebug()<<"init page";
            //todo split mode
            pageViewer->setPageSplitMode(Manga::SPLIT_AUTO);
            scene.addItem(pageViewer);
            image=new QImage();
            image->loadFromData(fileManager.loadData(pageCount));
            pageViewer->setImage(image);
            pageViewer->setFilePath(file);
            pageViewers.push_back(pageViewer);

        }
        else
        {

            image=pageViewers.at(pageCount-index)->getImage();
            if(image==NULL)
            {
                image=new QImage();
            }
            image->loadFromData(fileManager.loadData(pageCount));
            pageViewers.at(pageCount-index)->setImage(image);
            pageViewers.at(pageCount-index)->setFilePath(file);

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
            delete pageViewers.last();
            pageViewers.removeLast();
        }
    }
    if(pageCount==0)
        return;

    adjustPages();
    updateTitle();
}

void QGraphicsManagaView::adjustPages()
{
    if(pageViewers.isEmpty())
        return;
    for(int i=0;i<pageViewers.size();i++)
    {
        pageViewers.at(i)->setScale(scene.width()/pageViewers.at(i)->getBaseSize().width());
    }

    if(pageViewers.first()->y()>0)
        pageViewers.first()->setY(0);
    qreal ypos=pageViewers.first()->getFullSize().height()+pageViewers.first()->y();
    for(int i=1;i<pageViewers.size();i++)
    {
        pageViewers.at(i)->setY(ypos);
        ypos+=pageViewers.at(i)->getFullSize().height();
    }
    go(0);

}

QGraphicsManagaView::~QGraphicsManagaView()
{
    delete ui;
}

void QGraphicsManagaView::go(qreal step)
{
    if(pageViewers.size()==0)
        return;
    bool needNextPage=false;
    if(step==-1)
        step=scene.height()*0.2;
    qreal distance=0;
    distance=isLastPage?scene.height()-pageViewers.last()->getFullSize().height()-pageViewers.last()->y():-step;
    distance=std::max(distance,-step);
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
        qDebug()<<file;
        if(file=="")
            isLastPage=true;
        item->getImage()->loadFromData(fileManager.loadData(lastIndexInView+1));

        item->updateImage();
        item->setFilePath(file);
        item->setY(pageViewers.last()->y()+pageViewers.last()->getFullSize().height());
        item->setX((scene.width() - item->getFullSize().width())/2);
        pageIndexs.push_back(lastIndexInView+1);
        pageViewers.push_back(item);
    }
    updateTitle();
}
void QGraphicsManagaView::updateTitle()
{
    if(fileManager.size()==0)
        this->setWindowTitle("axb's MangaViewer");
    else
        this->setWindowTitle(QString::number(pageIndexs.first()+1)+"/"+QString::number(fileManager.size()+1)+" "+fileManager.currentFolder());
}

void QGraphicsManagaView::back(qreal step)
{
    if(pageViewers.size()==0)
        return;
    if(step==-1)
        step=scene.height()*0.2;
    bool needNextPage=false;
    qreal distance=isFirstPage?-pageViewers.first()->y():step;
    distance=std::min(distance,step);
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
        item->getImage()->loadFromData(fileManager.loadData(index-1));

        item->updateImage();
        item->setFilePath(file);
        item->setY(pageViewers.first()->y()-item->getFullSize().height());
        item->setX((scene.width() - item->getFullSize().width())/2);

        if(index==1)
            isFirstPage=true;
        pageViewers.push_front(item);
        pageIndexs.push_front(index-1);
    }
    updateTitle();
}

void QGraphicsManagaView::nextPage()
{
    // int pageCount=pageViewers.first()->getPageCount();
    QGraphicsPagedPixmapItem *v=(QGraphicsPagedPixmapItem*)scene.itemAt(1,1);
    v=(QGraphicsPagedPixmapItem*)v->parentItem();
    QGraphicsPagedPixmapItem *v1=pageViewers.first();
    QGraphicsPagedPixmapItem *v2=pageViewers.last();
    int pageHeight=v->getPageSize().height();
    int pageWidth=v->getPageSize().width();
    int ypos=v->y();
    int step=pageHeight-std::abs(ypos)%pageHeight;
    if(step==0)
        step=pageHeight;
    go(step);
}

void QGraphicsManagaView::perviousPage()
{
    back(pageViewers.first()->y()+pageViewers.first()->getPageSize().height());
}

void QGraphicsManagaView::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        QUrl url=event->mimeData()->urls().first();
        QString path=url.toLocalFile();
        QFile file(path);
        if(file.exists())
        {
            load(path);
        }
    }

}

void QGraphicsManagaView::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        QUrl url=event->mimeData()->urls().first();
        if(url.isLocalFile())
        {
            QString path=url.toLocalFile();
            QFileInfo file(path);
            if(file.isDir())
            {

                event->acceptProposedAction();
            }
            QString suffix=url.toLocalFile().split('.').last();
            if(FileManager::isSuffixAcceptable(suffix)||ZipFileLoader::isZipFile(suffix))
                event->acceptProposedAction();
        }
    }
}

void QGraphicsManagaView::resizeEvent(QResizeEvent *event)
{
    scene.setSceneRect(QRect(QPoint(0,0),this->size()));
    adjustPages();

}


void QGraphicsManagaView::setScale(qreal rate)
{
    this->rate=rate;
    for(int i=0;i<pageViewers.size();i++)
    {
        qreal fitrate=scene.width()/pageViewers.at(i)->getBaseSize().width();
        pageViewers.at(i)->setScale(rate==-1?fitrate:std::min(rate,fitrate));
    }
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

void QGraphicsManagaView::closeEvent(QCloseEvent *event)
{
    if(pageViewers.size()==0)
        return;
    setting.beginGroup("lastread");
    setting.setValue("lastfolder",fileManager.currentFolder());
    setting.setValue("lastfile",pageViewers.first()->getFilePath());
    setting.setValue("width",scene.width());
    setting.setValue("height",scene.height());
    setting.endGroup();
}
