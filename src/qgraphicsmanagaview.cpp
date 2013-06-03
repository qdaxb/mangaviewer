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
 #include <QMimeData>
#include <QWidget>
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
    pageManager=new PageManager(&fileManager);
    scrollItem=new QGraphicsGridScrollItem();
    scene.addItem(scrollItem);

    setStyleSheet("background-color:transparent;");
    setAttribute(Qt::WA_TranslucentBackground,true);

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
    int file=setting.value("lastfile").toInt();
    qreal width=setting.value("width").toReal();
    qreal height=setting.value("height").toReal();
    setting.endGroup();
    if((width>0)&&(height>0))
        this->resize(width,height);

    scrollItem->setVisibleArea(this->width(),this->height());
    if(folder!="")
    {
        int rtn=pageManager->setPath(folder);
        if(rtn!=-1)
        {
            scrollItem->setTotalItemCount(pageManager->size());
            init(file);
        }
    }

    setting.beginGroup("general");
    if(setting.value("noborder").toBool())
        this->setWindowFlags(Qt::FramelessWindowHint);
    setting.endGroup();

    updateTitle();
    this->setAcceptDrops(true);
    dblClick=false;
    updateProgressBar();
    ui->progressBar->setTextVisible(false);
    ui->progressBar->setFixedHeight(3);
    altKey=false;
}


int QGraphicsManagaView::load(QString fileorpath)
{
    int rtn=pageManager->setPath(fileorpath);
    if(rtn==-1)
        return -1;
    scrollItem->setTotalItemCount(pageManager->size());
    scrollItem->scrollToCell(0,0,0,0);
    scrollItem->updateView();
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
    updateProgressBar();
}
void QGraphicsManagaView::updateTitle()
{

}

void QGraphicsManagaView::leaveEvent(QEvent *event)
{
    this->setWindowOpacity(0.3);

    this->activateWindow();
    isActiveWindow();
}

void QGraphicsManagaView::enterEvent(QEvent *event)
{
    this->setWindowOpacity(1);

this->activateWindow();

    //this->repaint(this->rect());
}

void QGraphicsManagaView::showMsg(QString &msg, int timeInSecond)
{
}

void QGraphicsManagaView::back(qreal step)
{
    scrollItem->scrollBy(0,100);
    scrollItem->updateView();
    updateProgressBar();
}

void QGraphicsManagaView::nextPage()
{
    scrollItem->scrollToCell(scrollItem->currentRow()+1,0,0,0);
    scrollItem->updateView();
    updateProgressBar();
}

void QGraphicsManagaView::perviousPage()
{
    if(scrollItem->emptyRow(scrollItem->currentRow()-1))
        scrollItem->scrollToCell(scrollItem->currentRow()-2,0,0,0);
    else
        scrollItem->scrollToCell(scrollItem->currentRow()-1,0,0,0);
    scrollItem->updateView();
    updateProgressBar();
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
    QSize size=ui->graphicsView->viewport()->size();
    scene.setSceneRect(QRect(QPoint(0,0),size));
    ui->progressBar->setUpdatesEnabled(true);
    //scene.setSceneRect(QRect(QPoint(0,0),this->size()));
    scrollItem->setVisibleArea(size.width(),size.height());
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

    QString cmd="";
    if(event->modifiers().testFlag(Qt::ControlModifier))
        cmd+="C+";
    if(event->modifiers().testFlag(Qt::ShiftModifier))
        cmd+="S+";
    if(event->modifiers().testFlag(Qt::AltModifier)||altKey)
        cmd+="A+";

    return cmd;
}

void QGraphicsManagaView::updateProgressBar()
{
    ui->progressBar->setMaximum(fileManager.size()-1);
    ui->progressBar->setValue(pageManager->fileIndexOfPage(scrollItem->currentRow()));
    ui->progressBar->setFormat("%v/%m  "+fileManager.currentFolder());
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
    if(event->key()==Qt::Key_AltGr||event->key()==Qt::Key_Alt)
        altKey=false;
    else
        CommandRegistry::get(modCMD(event)+"K"+(QString::number(event->key())))->execute(this);
}

void QGraphicsManagaView::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_AltGr||event->key()==Qt::Key_Alt)
        altKey=true;
}

void QGraphicsManagaView::closeEvent(QCloseEvent *event)
{
    setting.beginGroup("general");
    setting.setValue("noborder",this->windowFlags().testFlag(Qt::FramelessWindowHint));
    setting.endGroup();
    setting.beginGroup("lastread");
    setting.setValue("lastfolder",fileManager.currentFolder());
    setting.setValue("lastfile",scrollItem->currentRow());
    setting.setValue("width",scene.width());
    setting.setValue("height",scene.height());
    setting.endGroup();
}
