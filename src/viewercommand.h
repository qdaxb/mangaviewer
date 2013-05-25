#ifndef VIEWERCOMMAND_H
#define VIEWERCOMMAND_H
#include <QObject>

class QGraphicsManagaView;
/*
  A macro that used to declare new commands
  */

class ViewerCommand
{
public:
    ViewerCommand();
    virtual void execute(QGraphicsManagaView *viewer)=0;
};
#define DECLARE_COMMAND(name)\
    class name  : public ViewerCommand \
    {\
    public:\
        name (){}\
        virtual void execute(QGraphicsManagaView *context);\
    };
#define REGISTER_COMMAND(name)\
    DECLARE_COMMAND(name)\
   static AutoRegister<name> name(#name);




//DECLARE_COMMAND(ViewerOpenFileCommand)
DECLARE_COMMAND(ViewerEmptyCommand)
//DECLARE_COMMAND(ViewerGoCommand)
//DECLARE_COMMAND(ViewerBackCommand)
//DECLARE_COMMAND( ViewerNextPageCommand )
//DECLARE_COMMAND( ViewerPreviousPageCommand )
//DECLARE_COMMAND( ViewerScaleUpCommand )
//DECLARE_COMMAND( ViewerScaleDownCommand )
//DECLARE_COMMAND( ViewerCloseCommand )
//DECLARE_COMMAND( ViewerToggleTitleCommand )
#endif // VIEWERCOMMAND_H
