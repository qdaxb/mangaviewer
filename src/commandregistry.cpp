#include "commandregistry.h"
#include <QMap>
#include <QString>
#include "viewercommand.h"
CommandRegistry::CommandRegistry()
{
    registry=new QMap<QString,ViewerCommand*>();
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

void CommandRegistry::setDefultCommand(ViewerCommand *command)
{
    this->defaultCommand=command;
}
