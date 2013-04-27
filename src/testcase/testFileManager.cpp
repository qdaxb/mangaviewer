#include "gtest/gtest.h"
#include "filemanager.h"
#include <QString>
#include <QDebug>
#include <QFileInfo>
#include <QTextCodec>
class TestFileManager : public ::testing::Test {
public:
    FileManager *m;
virtual void SetUp() {
        m=new FileManager();

}



};
TEST_F(TestFileManager, testFolderFileSwitch)
{
    m->load(L".\\testres");
    ASSERT_EQ(L"test1.bmp",QFileInfo(QString::fromStdWString(m->next())).fileName().toStdWString());
    ASSERT_EQ(L"test2-中文.bmp",QFileInfo(QString::fromStdWString(m->next())).fileName().toStdWString());
    ASSERT_EQ(L"test2.jpg",QFileInfo(QString::fromStdWString(m->next())).fileName().toStdWString());
    ASSERT_EQ(L"test3.bmp",QFileInfo(QString::fromStdWString(m->next())).fileName().toStdWString());
    ASSERT_EQ(L"test4.bmp",QFileInfo(QString::fromStdWString(m->next())).fileName().toStdWString());
    ASSERT_EQ(L"test3.bmp",QFileInfo(QString::fromStdWString(m->previous())).fileName().toStdWString());
    ASSERT_EQ(L"test2.jpg",QFileInfo(QString::fromStdWString(m->previous())).fileName().toStdWString());
    ASSERT_EQ(L"test3.bmp",QFileInfo(QString::fromStdWString(m->next())).fileName().toStdWString());
    ASSERT_EQ(L"test4.bmp",QFileInfo(QString::fromStdWString(m->next())).fileName().toStdWString());
}
TEST_F(TestFileManager, testFolderFileSwitchC)
{
    m->load(L"c:\\");
    qDebug()<<QString::fromStdWString(m->next());
    qDebug()<<QString::fromStdWString(m->next());
    qDebug()<<QString::fromStdWString(m->next());
    qDebug()<<QString::fromStdWString(m->next());
    qDebug()<<QString::fromStdWString(m->next());
    qDebug()<<QString::fromStdWString(m->next());
    qDebug()<<QString::fromStdWString(m->previous());
    qDebug()<<QString::fromStdWString(m->previous());
    qDebug()<<QString::fromStdWString(m->previous());
}


