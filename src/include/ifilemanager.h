#ifndef IFILEMANAGER_H
#define IFILEMANAGER_H
#include <string>
#include <list>
namespace axb{

class IFileManager{
public:
    virtual std::wstring current();
    virtual std::wstring next();
    virtual std::wstring previous();
    virtual int load(std::wstring fileorpath);
    virtual std::list<std::wstring> list();
    virtual int size();

};
}
#endif
