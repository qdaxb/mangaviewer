#ifndef RARREADER_H
#define RARREADER_H
#include <QStringList>
class RarFile
{
public:
    RarFile();
    QStringList readFileList();
    int open(QString rarFileName);
    int close();
    QByteArray readFile(QString zippedFileName);
};

#endif // RARREADER_H
