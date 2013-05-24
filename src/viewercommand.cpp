#include "viewercommand.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QTime>
#include "commandregistry.h"
#include "qgraphicsmanagaview.h"
#include <algorithm>
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
        //           viewer->go();
        //           viewer->update();
    }

}

REGISTER_COMMAND(ViewerEmptyCommand)
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
}

REGISTER_COMMAND(ViewerPreviousPageCommand)
void ViewerPreviousPageCommand::execute(QGraphicsManagaView *viewer)
{

}

REGISTER_COMMAND(ViewerScaleUpCommand)
void ViewerScaleUpCommand::execute(QGraphicsManagaView *viewer)
{

    viewer->resize(viewer->width()*1.1,viewer->height()*1.1);
    //viewer->setScale(viewer->getScale()+0.1);
}
REGISTER_COMMAND(ViewerScaleDownCommand)
void ViewerScaleDownCommand::execute(QGraphicsManagaView *viewer)
{

    viewer->resize(viewer->width()*0.9,viewer->height()*0.9);
}
