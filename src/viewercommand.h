#ifndef VIEWERCOMMAND_H
#define VIEWERCOMMAND_H
#include <QObject>

class MangaViewer;
/*
  A macro that used to declare new commands
  */

class ViewerCommand:public QObject
{
public:
    ViewerCommand();
    virtual void execute(MangaViewer *viewer)=0;
protected:
    MangaViewer *viewer;
};

#define REGISTER_COMMAND(name)\
static AutoRegister<name> name(#name);

#define DECLARE_COMMAND(name)\
class name  : public ViewerCommand \
{\
public:\
    name (){}\
    virtual void execute(MangaViewer *context);\
};


DECLARE_COMMAND(ViewerOpenFileCommand)
DECLARE_COMMAND(ViewerEmptyCommand)
DECLARE_COMMAND(ViewerGoCommand)
DECLARE_COMMAND(ViewerBackCommand)
DECLARE_COMMAND( ViewerNextPageCommand )
DECLARE_COMMAND( ViewerPreviousPageCommand )
#endif // VIEWERCOMMAND_H
