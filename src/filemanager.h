#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <folderloader.h>
template<class T>
class QStack;
template<class T>
class QList;
#include <QStringList>
class FileManager
{
public:
    FileManager();
    virtual QString currentFolder();
    virtual QString nextFolder();
    virtual QString previousFolder();
    virtual int load(QString fileorpath);
    virtual QList<QString> &list();
    virtual int size();
    virtual bool hasNext();
    virtual bool hasPrevious();
    QString get(int index);
    int get(QString fileName);
    QByteArray loadData(int index);
private:
    QStringList *fileListInCurrentFolder;
    QStack<FolderLoader*>* folderStack;
    bool isSuffixAcceptable(QString suffix);
    int loadFromFolder(QString fileorpath);
    int loadFromPreviousFolder();
    int loadFromZipFile(QString path);
    QString currentFile;
    FolderLoader *currentFolderLoader;
};

#endif // FILEMANAGER_H
