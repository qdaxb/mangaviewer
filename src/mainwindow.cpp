#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPaintEVENT>
#include <QDebug>
#include <QFileDialog>
#include <QPaintEngine>
#include "filemanager.h"
#include "msgpainter.h"
#include "imagepainter.h"
#include "mangaviewer.h"
#include "commandregistry.h"
#include "viewercommand.h"
#include "pageviewer.h"
#include <QSettings>
#include <QUrl>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    commandRegistry=new CommandRegistry();
    this->painter=new QPainter(this);
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
            commandRegistry->map(valueList.at(j),"Viewer"+key+"Command");
        }
    }
    this->msgPainter=new MsgPainter(this,painter);
    this->msgPainter->setFont(MsgPainter::CENTER,QFont("Arial",14));
    this->viewer=new MangaViewer(this,painter);
    this->update();
    mouseClickTimer = new QTimer(this);
    connect(mouseClickTimer, SIGNAL(timeout()), this, SLOT(mouseClick()));
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete painter;
    delete msgPainter;

}
void MainWindow::wheelEvent(QWheelEvent *event)
{
    int delta=event->delta();
    if(delta>0)
         commandRegistry->get("Wup")->execute(viewer);
    else
        commandRegistry->get("Wdown")->execute(viewer);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    qDebug()<<"resize";
    viewer->getResizeManager()->resize();
    viewer->getPage()->setClientSize(this->size());
    viewer->getPage()->newPage();

}

void MainWindow::dropEvent(QDropEvent *event)
{
    if(!event->mimeData()->hasUrls())
        return;
    qDebug()<<event->mimeData()->urls().first().toString().remove("file:///");
    viewer->loadPath(event->mimeData()->urls().first().toString().remove("file:///"));
    viewer->go();
    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    qDebug()<<"draw";
    painter->begin(this);
//    imagePainter->drawImage();
    viewer->draw();
    //msgPainter->drawMessage();
    painter->end();



}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{

}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<event->key();
    commandRegistry->get("K"+(QString::number(event->key())))->execute(viewer);
}
void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
    event->mimeData();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    qDebug()<<event->button();
    commandRegistry->get("M"+(QString::number(event->button())))->execute(viewer);
    //mouseButton=(int)event->button();
    //mouseClickTimer->start();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{


}


void MainWindow::showEvent(QShowEvent *)
{
    toogleHelpMessage();
}


void MainWindow::openLoadFolderDialog()
{

}
void MainWindow::toogleHelpMessage()
{
    if(msgPainter->isShowMessage(MsgPainter::CENTER))
    {
        msgPainter->hideMessage(MsgPainter::CENTER);
    }
    else
    {

        QStringList helpMessage;
        helpMessage<<tr("========================");
        helpMessage<<tr("MangaViewer by axb (≧▽≦)y");
        helpMessage<<tr("========================");
        helpMessage<<tr("space:next backspace:previous ");
        helpMessage<<tr("h:toggle help message");
        helpMessage<<tr("o:open a file or folder");
        helpMessage<<tr("v:toggle file name bar");
        helpMessage<<tr("w:image fit window");
        helpMessage<<tr("q:image fit window height");
        helpMessage<<tr("e:image fit window width");
        helpMessage<<tr("Alt+1-4:scale to rate 0.5-2");
        helpMessage<<tr("`:window fit image alt+`:no fit");
        helpMessage<<tr("f:toggle full screen");
        msgPainter->setFgColor(MsgPainter::CENTER,Qt::white);
        msgPainter->showListMessage(helpMessage,MsgPainter::CENTER);
        update();
    }
}

void MainWindow::toogleFileMessage()
{
//    if(fileManager->current()!="")
//        msgPainter->toggleMessage(MsgPainter::BOTTOM);
//    update();
}
void MainWindow::showScaleMessage()
{
//    int mode=imagePainter->getResizeMode();
//    QString str;
//    if(mode&ImagePainter::FIT_IMAGE)
//    {
//        str.append(tr("window fit image,"));
//    }else if(mode & ImagePainter::FIT_WINDOW)
//    {
//        if((mode & ImagePainter::FIT_WINDOW)==ImagePainter::FIT_WINDOW)
//            str.append(tr("image fit window"));
//        else if(mode & ImagePainter::FIT_WINDOW_HEIGHT)
//            str.append(tr("image fit window height"));
//        else if(mode & ImagePainter::FIT_WINDOW_WIDTH)
//            str.append(tr("image fit window width"));
//    }
//    float rate=imagePainter->getResizeRate();
//    if(mode & (ImagePainter::FIT_IMAGE|ImagePainter::NO_FIT))
//    {
//        str.append(tr("scale:%1%").arg(rate*100));

//    }
    //    msgPainter->showMessage(str,MsgPainter::TOP);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    mouseClickTimer->stop();
    //commandRegistry->get("MD"+(QString::number(event->button())))->execute(viewer);
}

void MainWindow::mouseClick()
{
//mouseClickTimer->stop();
    commandRegistry->get("M"+(QString::number(mouseButton)))->execute(viewer);
}
