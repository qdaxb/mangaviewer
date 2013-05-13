#include "commandregistry.h"
#include <QMap>
#include <QString>
#include "viewercommand.h"

QMap<QString,ViewerCommand*> *registry=NULL;
ViewerCommand *defaultCommand=new ViewerEmptyCommand();
CommandRegistry::CommandRegistry()
{


}

void CommandRegistry::put(QString key, ViewerCommand *command)
{
    (*registry)[key]=command;
}

ViewerCommand *CommandRegistry::get(QString key)
{
    ViewerCommand *command=(*registry)[key];
    if(command)
        return command;
    return defaultCommand;
}

bool CommandRegistry::map(QString to,QString from)
{
    ViewerCommand *command=get(from);
    if(command==defaultCommand)
        return false;
    put(to,command);
    return true;
}


void CommandRegistry::RegisterCommand(QString name, ViewerCommand *command)
{
    if(registry==NULL)
        registry=new QMap<QString,ViewerCommand*>();
    (*registry)[name]=command;
}



