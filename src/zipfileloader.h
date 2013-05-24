#ifndef RARREADER_H
#define RARREADER_H
#include <QStringList>
#include <QString>
#include "folderloader.h"
#include "fex/fex.h"
class ZipFileLoader:public FolderLoader
{
public:
    ZipFileLoader(QString zipFileName);
    QStringList fileList();
    QStringList folderList();
    int open(QString path);
    int open();
    int close();
    QByteArray loadFile(QString fileName);
    QString path(){return zipFileName;}
    virtual ~ZipFileLoader();
    static bool isZipFile(QString ext);
private:
    fex_t* fex;
    QString zipFileName;
    QStringList zippedFileNames;
    QByteArray currentFile;
    int currentIndex;
    bool isOpend;
};

#endif // RARREADER_H
