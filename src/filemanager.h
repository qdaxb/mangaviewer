#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>

template<class T>
class QStack;
template<class T>
class QList;
class FileManager
{
public:
    FileManager();
    virtual QString current();
    virtual QString next();
    virtual QString previous();
    virtual int load(QString fileorpath);
    virtual QList<QString> &list();
    virtual int size();
    virtual bool hasNext();
    virtual bool hasPrevious();
    QString get(int index);
private:
    QList<QString>* fileListInCurrentFolder;
    QStack<QString>* folderStack;
    QStack<int>* fileIndexInFolderStack;
    int currentIndex;
    bool isSuffixAcceptable(QString suffix);
    int loadFromFolder(QString fileorpath);
    int loadFromPreviousFolder();
    QString currentFile;

};

#endif // FILEMANAGER_H
