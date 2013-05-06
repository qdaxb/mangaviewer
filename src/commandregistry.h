#ifndef COMMANDREGISTRY_H
#define COMMANDREGISTRY_H
#include <QMap>
#include <typeinfo>
#include <QString>
class ViewerCommand;

class CommandRegistry
{
public:
    CommandRegistry();
    void put(QString key,ViewerCommand *command);
    ViewerCommand *get(QString key);
    void setDefultCommand(ViewerCommand *command);
    static void RegisterCommand(QString name,ViewerCommand *command);
    bool map(QString to, QString from);
private:
    ViewerCommand *defaultCommand;
};
template <typename T>
class AutoRegister
{
public :
    AutoRegister(QString name){CommandRegistry::RegisterCommand(name,new T());}
};

#endif // COMMANDREGISTRY_H
