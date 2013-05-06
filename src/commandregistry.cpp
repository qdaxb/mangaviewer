#include "commandregistry.h"
#include <QMap>
#include <QString>
#include "viewercommand.h"

QMap<QString,ViewerCommand*> registry;
CommandRegistry::CommandRegistry()
{
    defaultCommand=new ViewerEmptyCommand();

}

void CommandRegistry::put(QString key, ViewerCommand *command)
{
    registry[key]=command;
}

ViewerCommand *CommandRegistry::get(QString key)
{
    ViewerCommand *command=registry[key];
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

void CommandRegistry::setDefultCommand(ViewerCommand *command)
{
    this->defaultCommand=command;
}

void CommandRegistry::RegisterCommand(QString name, ViewerCommand *command)
{
    registry[name]=command;
}



