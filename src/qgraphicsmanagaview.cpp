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
#include <QTextCodec>
#include "qgraphicssimplebackgroundtextitem.h"
QGraphicsManagaView::QGraphicsManagaView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGraphicsManagaView),scene(),pageViewers(),pageIndexs(),fileManager(),rate(1),
    setting(QApplication::applicationDirPath ()+"/settings.ini",QSettings::IniFormat)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setAcceptDrops(false);
    ui->graphicsView->setMouseTracking(true);
    setMouseTracking(true);
    this->setAcceptDrops(true);
    setStyleSheet("background-color:transparent;");
    setAttribute(Qt::WA_TranslucentBackground,true);
    scene.setBackgroundBrush(QBrush(Qt::black));
    setting.beginGroup("keys");
    pageManager=new PageManager(&fileManager);
    scrollItem=new QGraphicsGridScrollItem();
    scene.addItem(scrollItem);
    msgItem=new QGraphicsSimpleBackgroundTextItem();
    scene.addItem(msgItem);
    leftDblClick=false;

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


    setting.beginGroup("general");
    if(setting.value("noborder").toBool())
        this->setWindowFlags(Qt::FramelessWindowHint);
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

        int rtn=load(folder);
        if(rtn!=-1)
        {
            scrollItem->setTotalItemCount(pageManager->size());
            init(file);
        }
    }
    else
    {
        showMsg("Axb's MangaViewer - double click to load file.",-1);
    }
    leftAndRightButton=false;
    updateProgressBar();
    ui->progressBar->setTextVisible(false);
    ui->progressBar->setFixedHeight(3);
    altKey=false;
}


int QGraphicsManagaView::load(QString fileorpath)
{
    if(fileorpath=="")
        return -1;
    scrollItem->clear();
    int rtn=pageManager->setPath(fileorpath);

    if(rtn==-1)
    {
        showMsg("Can not load path: "+fileorpath,5);
        return -1;
    }
    int size=pageManager->size();
    if(size==0)
    {
        showMsg("Folder has no images: "+fileorpath,5);
        return -1;
    }
    scrollItem->setTotalItemCount(size);
    scrollItem->scrollToCell(0,0,0,0);
    scrollItem->updateView();
    showMsg("Loaded Folder:"+fileManager.currentFolder());
    updateProgressBar();
    return 0;
}

void QGraphicsManagaView::mouseMoveEvent(QMouseEvent *event)
{
    if(leftAndRightButton)
    {
        int offsetX=std::abs(lastPos.x()-event->x());

        if(offsetX>50)
        {
            if(event->modifiers().testFlag(Qt::ControlModifier))

                scrollItem->scrollBy(0,offsetX);
            else
                scrollItem->scrollBy(0,-offsetX);
            scrollItem->updateView();
            lastPos=event->pos();
            updateProgressBar();

        }
        else if(offsetX<0)
        {
            lastPos=event->pos();

        }

    }

    if ((!event->buttons().testFlag(Qt::LeftButton))&&(event->buttons().testFlag(Qt::RightButton))) {

        move(event->globalPos() - dragPosition);

    }
}

void QGraphicsManagaView::mouseReleaseEvent(QMouseEvent *event)
{
    if(!leftAndRightButton)

        CommandRegistry::get(modCMD(event)+"M"+(QString::number(event->button())))->execute(this);
}
void QGraphicsManagaView::mousePressEvent(QMouseEvent *event)
{
    if ((!event->buttons().testFlag(Qt::LeftButton))&&(event->buttons().testFlag(Qt::RightButton))) {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
    }
    else if((event->buttons().testFlag(Qt::LeftButton))&&(!event->buttons().testFlag(Qt::RightButton))) {
        if(leftDblClick)
        {
            CommandRegistry::get(modCMD(event)+"MD1")->execute(this);
            leftDblClick=false;
        }
        else
        {
            mouseDblClickTimer=startTimer(500);
            leftDblClick=true;

        }
    }
    else if ((event->buttons().testFlag(Qt::LeftButton))&&(event->buttons().testFlag(Qt::RightButton))) {


        event->accept();
        leftAndRightButton=true;
        showMsg("Start mouse move mode.");
        ui->progressBar->setStyleSheet("QProgressBar::chunk {background-color: #05B8CC;}");
        lastPos=event->pos();

    }
    else
    {

    }

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

void QGraphicsManagaView::showMsg(QString msg, int timeInSecond)
{
    msgItem->setText(msg);
    msgItem->setVisible(true);
    if(timeInSecond>0)
    msgtimer=this->startTimer(timeInSecond*1000);
}

void QGraphicsManagaView::timerEvent(QTimerEvent *event)
{
    int timerid=event->timerId();
    if(timerid==msgtimer)
    {
        msgItem->setVisible(false);
        killTimer(timerid);
    }
    else if(timerid==mouseDblClickTimer)
    {
        leftDblClick=false;
        if(leftAndRightButton)
        {
        ui->progressBar->setStyleSheet("QProgressBar::chunk {background-color: grey;}");

        leftAndRightButton=false;
        showMsg("Stop mouse move mode.");
        }
        killTimer(timerid);
    }
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

    ui->progressBar->setMaximum(fileManager.size());

    ui->progressBar->setValue(pageManager->fileIndexOfPage(scrollItem->currentRow())+1);
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
    event->accept();
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
