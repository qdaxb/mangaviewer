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
#include "viewercommand.h"
#include "qgraphicsmanagaview.h"
#include "ui_qgraphicsmanagaview.h"
#include "qgraphicspagedpixmapitem.h"
#include "zipfileloader.h"
#include <QMimeData>
#include <QWidget>
#include <QTextCodec>
#include "qgraphicssimplebackgroundtextitem.h"
#include "shortcutmanager.h"
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
    progressBarHeight=3;

    shortcutManager=ShortcutManager::getInstance();
    shortcutManager->setViewer(this);
    shortcutManager->loadFromXmlFile(QApplication::applicationDirPath ()+"/shortcuts.xml");

    scene.setBackgroundBrush(QBrush(Qt::black));
    pageManager=new PageManager(&fileManager);
    scrollItem=new QGraphicsGridScrollItem();
    scene.addItem(scrollItem);
    msgItem=new QGraphicsSimpleBackgroundTextItem();
    scene.addItem(msgItem);
    leftDblClick=false;

    connect(scrollItem,SIGNAL(onLoadImage(int)),this,SLOT(onLoadImage(int)));
    connect(scrollItem,SIGNAL(onUnloadImage(int)),this,SLOT(onUnloadImage(int)));



    setting.beginGroup("general");
    if(setting.value("noborder").toBool())
        this->setWindowFlags(Qt::FramelessWindowHint);
    backgroundOpacity=std::max(0.1,setting.value("backgroundOpacity").toReal());
    foregroundOpacity=std::max(0.1,setting.value("foregroundOpacity").toReal());
    moveDelta=setting.value("moveDelta").toReal();
    moveRate=setting.value("moveRate").toReal();
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
        offsetX+=std::abs(lastPos.y()-event->y());
        if(offsetX>moveDelta)
        {
            if(event->modifiers().testFlag(Qt::ControlModifier))

                scrollItem->scrollBy(0,offsetX*moveRate);
            else
                scrollItem->scrollBy(0,-offsetX*moveRate);
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
    {
        QString command=modCMD(event)+"M"+(QString::number(event->button()));
        shortcutManager->getCommand(command.toUpper())->execute(this);
    }
}
void QGraphicsManagaView::mousePressEvent(QMouseEvent *event)
{
    if ((!event->buttons().testFlag(Qt::LeftButton))&&(event->buttons().testFlag(Qt::RightButton))) {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
    }
    else if((event->buttons().testFlag(Qt::LeftButton))&&(!event->buttons().testFlag(Qt::RightButton))) {
        if(leftDblClick)
        {
            QString command=modCMD(event)+"MD1";
            shortcutManager->getCommand(command.toUpper())->execute(this);
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

QString QGraphicsManagaView::currentPath()
{
    return fileManager.currentFolder();
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
    this->setWindowOpacity(backgroundOpacity);

    this->activateWindow();
    isActiveWindow();
}

void QGraphicsManagaView::enterEvent(QEvent *event)
{
    this->setWindowOpacity(foregroundOpacity);

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

void QGraphicsManagaView::toggleProgressBar()
{
    progressBarHeight=progressBarHeight==3?18:3;
    ui->progressBar->setTextVisible(progressBarHeight==18);
    updateLayout();
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
   updateLayout();
}

void QGraphicsManagaView::updateLayout()
{
    QSize newSize=size();
    ui->graphicsView->resize(newSize.width(),newSize.height()-progressBarHeight);
    ui->progressBar->move(0,newSize.height()-(progressBarHeight));
    ui->progressBar->setFixedHeight(progressBarHeight);
    ui->progressBar->setFixedWidth(newSize.width());
    ui->progressBar->setTextVisible(progressBarHeight==18);
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
        cmd+="CTRL+";
    if(event->modifiers().testFlag(Qt::ShiftModifier))
        cmd+="SHIFT+";
    if(event->modifiers().testFlag(Qt::AltModifier)||altKey)
        cmd+="ALT+";

    return cmd;
}

void QGraphicsManagaView::updateProgressBar()
{

    ui->progressBar->setMaximum(fileManager.size());

    ui->progressBar->setValue(pageManager->fileIndexOfPage(scrollItem->currentRow())+1);
    ui->progressBar->setFormat("%v/%m  "+fileManager.currentFolder());
}

QKeySequence QGraphicsManagaView::getKeySequence(QKeyEvent *event)
{

    int keyInt = event->key();
    Qt::Key key = static_cast<Qt::Key>(keyInt);
    if(key == Qt::Key_unknown){

        return QKeySequence();
    }
    // the user have clicked just and only the special keys Ctrl, Shift, Alt, Meta.
    if(key == Qt::Key_Control ||
            key == Qt::Key_Shift ||
            key == Qt::Key_Alt ||
            key == Qt::Key_Meta)
    {
        return QKeySequence();
    }

    // check for a combination of user clicks
    Qt::KeyboardModifiers modifiers = event->modifiers();

    if(modifiers & Qt::ShiftModifier)
        keyInt += Qt::SHIFT;
    if(modifiers & Qt::ControlModifier)
        keyInt += Qt::CTRL;
    if(modifiers & Qt::AltModifier)
        keyInt += Qt::ALT;
    if(modifiers & Qt::MetaModifier)
        keyInt += Qt::META;
    qDebug()<<QKeySequence(keyInt).toString(QKeySequence::NativeText);
    return QKeySequence(keyInt).toString(QKeySequence::NativeText);
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
        shortcutManager->getCommand(modCMD(event)+"WUP")->execute(this);
    else
        shortcutManager->getCommand(modCMD(event)+"WDOWN")->execute(this);
}

void QGraphicsManagaView::keyReleaseEvent(QKeyEvent *event)
{
    qDebug()<<getKeySequence(event).toString();
    event->accept();
    if(event->key()==Qt::Key_AltGr||event->key()==Qt::Key_Alt)
        altKey=false;
    else
        shortcutManager->getCommand(getKeySequence(event).toString().toUpper())->execute(this);
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
    setting.setValue("backgroundOpacity",backgroundOpacity);
    setting.setValue("foregroundOpacity",foregroundOpacity);
    setting.endGroup();
    setting.beginGroup("lastread");
    setting.setValue("lastfolder",fileManager.currentFolder());
    setting.setValue("lastfile",scrollItem->currentRow());
    setting.setValue("width",scene.width());
    setting.setValue("height",scene.height());
    setting.endGroup();
}
