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
    static void put(QString key,ViewerCommand *command);
    static ViewerCommand *get(QString key);
    static void RegisterCommand(QString name,ViewerCommand *command);
    static bool map(QString to, QString from);
};
template <typename T>
class AutoRegister
{
public :
    AutoRegister(QString name){CommandRegistry::RegisterCommand(name,new T());}
};

#endif // COMMANDREGISTRY_H
