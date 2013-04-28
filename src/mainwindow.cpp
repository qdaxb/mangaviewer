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
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->painter=new QPainter(this);

    this->msgPainter=new MsgPainter(this,painter);
    this->msgPainter->setFont(MsgPainter::CENTER,QFont("Arial",14));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete painter;
    delete msgPainter;

}

void MainWindow::paintEvent(QPaintEvent *)
{
    painter->begin(this);
//    imagePainter->drawImage();
    msgPainter->drawMessage();
    painter->end();



}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
//    qDebug()<<event->key();
//    switch (event->key())
//    {

//    case Qt::Key_Space :
//    {
//        if(imagePainter->go()==-1)
//        {
//            next();
//        }
//        else
//        {
//            msgPainter->hideMessage(MsgPainter::BOTTOM|MsgPainter::TOP);
//        }
//        this->update();
//        break;
//    }
//    case Qt::Key_Backspace :
//    {
//        if(imagePainter->back()==-1)
//        {
//            previous();
//        }
//        else
//        {
//            msgPainter->hideMessage(MsgPainter::BOTTOM);
//        }
//        this->update();
//        break;
//    }
//    case Qt::Key_Up:imagePainter->stepUp(5);this->update();break;
//    case Qt::Key_Down:imagePainter->stepDown(5);this->update();break;
//    case Qt::Key_Left:imagePainter->stepLeft(5);this->update();break;
//    case Qt::Key_Right:imagePainter->stepRight(5);this->update();break;
//    case Qt::Key_O:openLoadFolderDialog();this->update();break;
//    case Qt::Key_V:toogleFileMessage();this->update();break;
//    case Qt::Key_1:{
//        if(event->modifiers()==Qt::AltModifier)
//        {
//            imagePainter->setResizeMode(ImagePainter::RATE,0.5);
//            showScaleMessage();
//            this->update();
//        }
//        break;
//    }

//    case Qt::Key_2:{
//        if(event->modifiers()==Qt::AltModifier)
//        {
//            imagePainter->setResizeMode(ImagePainter::RATE,1);
//            showScaleMessage();
//            this->update();
//        }
//        break;
//    }
//    case Qt::Key_3:if(event->modifiers()==Qt::AltModifier){imagePainter->setResizeMode(ImagePainter::RATE,1.5);showScaleMessage();this->update();}break;
//    case Qt::Key_4:if(event->modifiers()==Qt::AltModifier){imagePainter->setResizeMode(ImagePainter::RATE,2);showScaleMessage();this->update();}break;
//    case Qt::Key_Q:imagePainter->setResizeMode(ImagePainter::FIT_WINDOW_HEIGHT);showScaleMessage();this->update();break;
//    case Qt::Key_H:toogleHelpMessage();this->update();break;
//    case Qt::Key_E:{imagePainter->setResizeMode(ImagePainter::FIT_WINDOW_WIDTH);showScaleMessage();this->update();}break;
//    case Qt::Key_W:{imagePainter->setResizeMode(ImagePainter::FIT_WINDOW);showScaleMessage();this->update();}break;
//    case Qt::Key_QuoteLeft:
//    {
//        if(event->modifiers()==Qt::AltModifier)
//        {
//            imagePainter->setResizeMode(ImagePainter::NO_FIT);
//            showScaleMessage();
//        }
//        else
//        {
//            imagePainter->setResizeMode(ImagePainter::FIT_IMAGE);
//            showScaleMessage();
//        }
//        this->update();
//        break;
//    }
//    case Qt::Key_F:if(this->isMaximized())this->showNormal();else this->showMaximized();break;
//    }

}
void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
//    dragPosition=event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

//    if(event->buttons()!=Qt::LeftButton)
//        return;
//    QPoint newPosition=event->pos();
//    imagePainter->stepRight(newPosition.x()-dragPosition.x());
//    imagePainter->stepDown(newPosition.y()-dragPosition.y());

}
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
//    dragPosition=event->pos();
}



void MainWindow::showEvent(QShowEvent *)
{
    toogleHelpMessage();
}


void MainWindow::next()
{
//    QString next=fileManager->next();
//    if(next!="")
//    {
//        imagePainter->loadImage(next);
//        //this->current->load(next);
//        //this->resize(QSize(this->current->width()/2,this->current->height()/2));
//    }
//    msgPainter->showMessage(fileManager->current(),MsgPainter::BOTTOM);
}
void MainWindow::previous()
{
//    QString previous=fileManager->previous();
//    if(previous!="")
//    {
//        imagePainter->loadImage(previous);
//        //this->current->load(previous);
//        //this->resize(QSize(this->current->width()/2,this->current->height()/2));
//    }
//    msgPainter->showMessage(fileManager->current(),MsgPainter::BOTTOM);
}

void MainWindow::openLoadFolderDialog()
{
//    QString dir =QFileDialog::getExistingDirectory(this, tr("Open Directory"),
//                                                   "",
//                                                   QFileDialog::ShowDirsOnly
//                                                   );
//    if(dir=="")
//    {
//        return;
//    }
//    else
//    {
//        this->fileManager->load(dir);
//        //this->current->load(fileManager->next());
//        imagePainter->loadImage(fileManager->next());
//        msgPainter->hideMessage(MsgPainter::CENTER);
//        msgPainter->showMessage(fileManager->current(),MsgPainter::BOTTOM);
//        showScaleMessage();
//    }
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
