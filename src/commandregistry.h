#ifndef COMMANDREGISTRY_H
#define COMMANDREGISTRY_H
#include <QMap>
class QString;
class ViewerCommand;

class CommandRegistry
{
public:
    CommandRegistry();
    void put(QString key,ViewerCommand *command);
    ViewerCommand *get(QString key);
    void setDefultCommand(ViewerCommand *command);
private:
    QMap<QString,ViewerCommand*> *registry;
    ViewerCommand *defaultCommand;
};

#endif // COMMANDREGISTRY_H
