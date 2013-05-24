#ifndef FOLDERLOADER_H
#define FOLDERLOADER_H
#include <QString>
class FolderLoader
{
public:
    virtual QStringList fileList()=0;
    virtual QStringList folderList()=0;
    virtual int open()=0;
    virtual int open(QString path)=0;
    virtual int close()=0;
    virtual QByteArray loadFile(QString fileName)=0;
    virtual QString path()=0;
    virtual ~FolderLoader(){}

};

#endif // FOLDERLOADER_H
