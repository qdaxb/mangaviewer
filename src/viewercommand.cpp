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
#include <QWidget>
#include <QIcon>
#include <QDir>
#include <QUrl>
#include "common.h"

#include <QDesktopWidget>
ViewerCommand::ViewerCommand()
{
}
bool fileNameSort(const QString &str1, const QString &str2)
{
    if(str1.length()==str2.length())
    {
        return str1<str2;
    }
    return str1.length()<str2.length();
}
REGISTER_COMMAND(ViewerOpenFileCommand)
void ViewerOpenFileCommand::execute(QGraphicsManagaView *viewer)
{
    QString path=viewer->currentPath();
    QString file;
    QList<QUrl> urls;


    if(!path.isEmpty())
    {

        QFileInfo fileInfo(path);
        QDir parent(fileInfo.absoluteDir());

        if(parent.exists())
        {
            qDebug()<<parent;
            path=parent.absolutePath();
            QStringList list=parent.entryList(QDir::AllEntries|QDir::NoDotAndDotDot,QDir::LocaleAware|QDir::Name);
            qSort(list.begin(),list.end(),fileNameSort);
            int i=list.indexOf(fileInfo.fileName());
            if(i!=-1)
            {
                file=list.at(i);
                if(fileInfo.isDir())
                {

                    if(i>0)
                        urls<<QUrl::fromLocalFile(parent.absoluteFilePath(list.at(i-1)));
                    urls<<QUrl::fromLocalFile(parent.absoluteFilePath(list.at(i)));
                    if(i!=list.size()-1)
                        urls<<QUrl::fromLocalFile(parent.absoluteFilePath(list.at(i+1)));

                }
            }
        }


    }
    QFileDialog dialog(0,("Open File"),
                       path,
                       QObject::tr("Supported types (*.png *.jpg *.jpeg *.bmp *.zip *.rar *.7z)"));
    dialog.setOption(QFileDialog::DontUseNativeDialog);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.selectFile(file);

    dialog.setSidebarUrls(urls);
    if(dialog.exec())
    {
        QStringList dir =dialog.selectedFiles();
        if(dir.isEmpty())
            return;
        viewer->load(dir.first());
        viewer->activateWindow();
    }

}
REGISTER_COMMAND(ViewerToggleHideCommand)
void ViewerToggleHideCommand::execute(QGraphicsManagaView *viewer)
{

    if(viewer->isHidden())
        viewer->show();
    else
        viewer->hide();

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
    msgBox.setIconPixmap(QPixmap(":/icon/images/icon.jpg"));
    msgBox.setWindowTitle("Confirm");
    msgBox.setText("Do you want to exit MangaViewer?");
    msgBox.setInformativeText("");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No );
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if(ret==QMessageBox::Yes)
        viewer->close();
}

REGISTER_COMMAND(ViewerToggleTitleCommand)
void ViewerToggleTitleCommand::execute(QGraphicsManagaView *viewer)
{
    qDebug()<<viewer->windowFlags();
    if(viewer->windowFlags().testFlag(Qt::FramelessWindowHint))
        viewer->setWindowFlags(viewer->windowFlags()&(~Qt::FramelessWindowHint));
    else
        viewer->setWindowFlags((viewer->windowFlags()|Qt::FramelessWindowHint)&(~(Qt::WindowTitleHint|0x1|0x1000|0x200|0x4000|0x8000|0x80000000)));
    viewer->show();
}

REGISTER_COMMAND(ViewerToggleOntopCommand)
void ViewerToggleOntopCommand::execute(QGraphicsManagaView *viewer)
{

    if(viewer->windowFlags().testFlag(Qt::WindowStaysOnTopHint))
        viewer->setWindowFlags(viewer->windowFlags()&~Qt::WindowStaysOnTopHint);
    else
        viewer->setWindowFlags(viewer->windowFlags()|Qt::WindowStaysOnTopHint);
    viewer->show();
    viewer->isActiveWindow();
}

REGISTER_COMMAND(ViewerHeightScaleUpCommand)
void ViewerHeightScaleUpCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->showNormal();
    viewer->resize(viewer->width(),viewer->height()*1.05);
}

REGISTER_COMMAND(ViewerHeightScaleDownCommand)
void ViewerHeightScaleDownCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->showNormal();
    viewer->resize(viewer->width(),viewer->height()*0.95);
}

REGISTER_COMMAND(ViewerWidthScaleDownCommand)
void ViewerWidthScaleDownCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->showNormal();
    viewer->resize(viewer->width()*0.95,viewer->height());
}

REGISTER_COMMAND(ViewerWidthScaleUpCommand)
void ViewerWidthScaleUpCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->showNormal();
    viewer->resize(viewer->width()*1.05,viewer->height());
}

REGISTER_COMMAND(ViewerToggleProgressBarCommand)
void ViewerToggleProgressBarCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->toggleProgressBar();
}
REGISTER_COMMAND(ViewerToggleHelpMessageCommand)
void ViewerToggleHelpMessageCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->toggleHelpMessage();
}
REGISTER_COMMAND(ViewerToggleSplitPageCommand)
void ViewerToggleSplitPageCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->toggleSplitPage();
}
REGISTER_COMMAND(ViewerGotoPageCommand)
void ViewerGotoPageCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->gotoPage(viewer->gotoDialog()<<1);
}
REGISTER_COMMAND(ViewerTransformationModeCommand)
void ViewerTransformationModeCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->toggleTransformMode();
}
REGISTER_COMMAND(ViewerFitImageCommand)
void ViewerFitImageCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->showNormal();
    viewer->fitImage();
}
REGISTER_COMMAND(ViewerFullImageCommand)
void ViewerFullImageCommand::execute(QGraphicsManagaView *viewer)
{
    viewer->showNormal();
    viewer->showFullScreen();
}
