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
    a=0;
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setAcceptDrops(false);
    scene.setBackgroundBrush(QBrush(Qt::black));
    setting.beginGroup("keys");
    pageManager=new PageManager(&fileManager);
    scrollItem=new QGraphicsGridScrollItem();
    scene.addItem(scrollItem);

    connect(scrollItem,SIGNAL(onLoadImage(int)),this,SLOT(onLoadImage(int)));
connect(scrollItem,SIGNAL(onUnloadImage(int)),this,SLOT(onUnloadImage(int)));
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
    if((width>0)&&(height>0))
        this->resize(width,height);

    scrollItem->setVisibleArea(this->width(),this->height());
    if(folder!="")
    {
        pageIndexs.clear();
        pageManager->setPath(folder);
        scrollItem->setTotalItemCount(pageManager->size());
    }
    if(file!="")
    {
        int index=fileManager.get(file);
        if(index!=-1)
            init(index);
    }
    else
        init();


    updateTitle();
    this->setAcceptDrops(true);
    dblClick=false;


}


int QGraphicsManagaView::load(QString fileorpath)
{
    pageManager->setPath(fileorpath);
    scrollItem->scrollToCell(0,0,0,0);
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
    scrollItem->scrollToCell(index,0,0,0);
    scrollItem->updateView();
}

void QGraphicsManagaView::adjustPages()
{


}

QGraphicsManagaView::~QGraphicsManagaView()
{
    delete ui;
}

void QGraphicsManagaView::go(qreal step)
{
   scrollItem->scrollBy(0,-100);
   scrollItem->updateView();
}
void QGraphicsManagaView::updateTitle()
{

}

void QGraphicsManagaView::back(qreal step)
{
   scrollItem->scrollBy(0,100);
   scrollItem->updateView();
}

void QGraphicsManagaView::nextPage()
{

}

void QGraphicsManagaView::perviousPage()
{

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
    scrollItem->setVisibleArea(this->width(),this->height());
scrollItem->updateView();
}


void QGraphicsManagaView::setScale(qreal rate)
{

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

void QGraphicsManagaView::onLoadImage(int index)
{
    scrollItem->setImage(index,pageManager->getImage(index));
}

void QGraphicsManagaView::onUnloadImage(int index)
{
    pageManager->releaseImage(index);
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
