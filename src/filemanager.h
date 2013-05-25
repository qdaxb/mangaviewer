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
    static bool isSuffixAcceptable(QString suffix);
private:
    QStringList *fileListInCurrentFolder;
    QStack<FolderLoader*>* folderStack;
    int loadFromFolder(QString fileorpath);
    int loadFromZipFile(QString path);
    QString currentFile;
    FolderLoader *currentFolderLoader;
};

#endif // FILEMANAGER_H
