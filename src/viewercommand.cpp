#include "viewercommand.h"
#include "mangaviewer.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
ViewerCommand::ViewerCommand()
{
}
void ViewerOpenFileCommand::execute()
{
        QString dir =QFileDialog::getExistingDirectory(0, tr("Open Directory"),
                                                       "",
                                                      QFileDialog::ShowDirsOnly
                                                      );
       if(dir=="")
        {
            return;
        }
        else
        {
           this->viewer->setPath(dir);
           this->viewer->go();
           this->viewer->update();
         }

}
void ViewerEmptyCommand::execute()
{
    qDebug()<<"execute an empty command!";

}
