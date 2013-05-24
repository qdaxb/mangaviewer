#ifndef LOCALFOLDERLOADER_H
#define LOCALFOLDERLOADER_H
#include "folderloader.h"
#include <QString>
#include <QDir>
class LocalFolderLoader : public FolderLoader
{
public:
    LocalFolderLoader(QString path);
    virtual QStringList fileList();
    virtual QStringList folderList();
    virtual int open();
    virtual int open(QString path);
    virtual int close();
    virtual QByteArray loadFile(QString fileName);
    virtual QString path();
    virtual ~LocalFolderLoader();
private:
    QDir *folder;
};

#endif // LOCALFOLDERLOADER_H
