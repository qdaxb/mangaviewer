#ifndef VIEWERCOMMAND_H
#define VIEWERCOMMAND_H
#include <QObject>
class MangaViewer;
class ViewerCommand:public QObject
{
public:
    ViewerCommand(MangaViewer *viewer){this->viewer=viewer;}
    virtual void execute()=0;
protected:
    MangaViewer *viewer;
private:
    ViewerCommand();
};

class ViewerOpenFileCommand : public ViewerCommand
{
public:
    ViewerOpenFileCommand(MangaViewer *viewer):ViewerCommand(viewer){}
    virtual void execute();
};

class ViewerEmptyCommand : public ViewerCommand
{
public:
    ViewerEmptyCommand(MangaViewer *viewer):ViewerCommand(viewer){}
    virtual void execute();
};

#endif // VIEWERCOMMAND_H
