#include "viewercommand.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QTime>
#include "commandregistry.h"
#include "qgraphicsmanagaview.h"
#include <algorithm>
#include <QApplication>
#include <QMessageBox>
ViewerCommand::ViewerCommand()
{
}
REGISTER_COMMAND(ViewerOpenFileCommand)
void ViewerOpenFileCommand::execute(QGraphicsManagaView *viewer)
{
    QString dir =QFileDialog::getOpenFileName(0, ("Open Directory"),
                                              "",
                                              QObject::tr("Supported types (*.png *.jpg *.bmp *.zip *.rar *.7z)")
                                              );

    if(dir=="")
    {
        return;
    }
    else
    {
        viewer->load(dir);
    }

}

void ViewerEmptyCommand::execute(QGraphicsManagaView *viewer)
{
    //todo change the method to show a message on screen
    qDebug()<<"execute an empty command!";

}

REGISTER_COMMAND(ViewerGoCommand)
void ViewerGoCommand::execute(QGraphicsManagaView *viewer)
{

    viewer->go();
}

REGISTER_COMMAND(ViewerBackCommand)
void ViewerBackCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->back();
}

REGISTER_COMMAND(ViewerNextPageCommand)
void ViewerNextPageCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->nextPage();
}

REGISTER_COMMAND(ViewerPreviousPageCommand)
void ViewerPreviousPageCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->perviousPage();
}

REGISTER_COMMAND(ViewerScaleUpCommand)
void ViewerScaleUpCommand::execute(QGraphicsManagaView *viewer)
{

    viewer->resize(viewer->width()*1.05,viewer->height()*1.05);
    //viewer->setScale(viewer->getScale()+0.1);
}
REGISTER_COMMAND(ViewerScaleDownCommand)
void ViewerScaleDownCommand::execute(QGraphicsManagaView *viewer)
{

    viewer->resize(viewer->width()*0.95,viewer->height()*0.95);
}
REGISTER_COMMAND(ViewerCloseCommand)
void ViewerCloseCommand::execute(QGraphicsManagaView *viewer)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Confirm");
    msgBox.setText("Do you want to exit MangaViewer?");
    msgBox.setInformativeText("");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No );
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if(ret==QMessageBox::Yes)
        QApplication::activeWindow()->close();
}

REGISTER_COMMAND(ViewerToggleTitleCommand)
void ViewerToggleTitleCommand::execute(QGraphicsManagaView *viewer)
{
    QWidget *window=QApplication::activeWindow();
    if(window->windowFlags()&Qt::FramelessWindowHint)
        window->setWindowFlags(Qt::Widget);
    else
        window->setWindowFlags(Qt::FramelessWindowHint);
    window->show();
}

REGISTER_COMMAND(ViewerHeightScaleUpCommand)
void ViewerHeightScaleUpCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->resize(viewer->width(),viewer->height()*1.05);
}

REGISTER_COMMAND(ViewerHeightScaleDownCommand)
void ViewerHeightScaleDownCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->resize(viewer->width(),viewer->height()*0.95);
}

REGISTER_COMMAND(ViewerWidthScaleDownCommand)
void ViewerWidthScaleDownCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->resize(viewer->width()*0.95,viewer->height());
}

REGISTER_COMMAND(ViewerWidthScaleUpCommand)
void ViewerWidthScaleUpCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->resize(viewer->width()*1.05,viewer->height());
}
