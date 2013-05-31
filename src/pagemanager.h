#ifndef PAGELOADER_H
#define PAGELOADER_H
#include <QString>
#include <QMap>
#include "filemanager.h"
template <typename T>
class Arrange
{
public:
    void setMin(T min){this->mMin=min;}
    void setMax(T max){this->mMax=max;}
    int contains(T value){
        if(value<mMin)
            return -1;
        if(value>mMax)
            return 1;
        return 0;}
    T min(){return mMin;}
    T max(){return mMax;}
     Arrange(){}
    Arrange(const Arrange<T> &other){this->mMin=other.mMin;this->mMax=other.mMax;}
private:
    T mMin;
    T mMax;

};

class QImage;
class PageManager
{
public:
    enum SplitMode{SPLIT_AUTO=0X1,SPLIT_ALL=0X2,SPLIT_NONE=0X4};
    PageManager(FileManager *fileManager);
    QImage *getImage(int index);
    void releaseImage(int index);
    int size();
    int setPath(QString path);
    int path();
    int setSplitMode(SplitMode mode);
    int setColumnCount(int count);
private:
    FileManager *mFileManager;
    SplitMode mSplitMode;
    int mColumnCount;
    int mPageCount;
    int mInitilzed;
    QMap<int,QImage*> mImages;
    QMap<int,Arrange<int> > mPageArrangeOfFile;
    int pageIndexOfFile(int fileIndex);
    void loadFromFile(int fileIndex);
    int fileIndexOfPage(int pageIndex);
    int calucatePageCount(int fileIndex);
};

#endif // PAGELOADER_H
