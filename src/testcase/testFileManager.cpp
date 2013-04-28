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
    m->load(".\\testres");
    ASSERT_EQ(L"test1.bmp",QFileInfo(m->next()).fileName().toStdWString());
    ASSERT_EQ(L"test2-中文.bmp",QFileInfo(m->next()).fileName().toStdWString());
    ASSERT_EQ(L"test2.jpg",QFileInfo((m->next())).fileName().toStdWString());
    ASSERT_EQ(L"test3.bmp",QFileInfo((m->next())).fileName().toStdWString());
    ASSERT_EQ(L"test4.bmp",QFileInfo((m->next())).fileName().toStdWString());
    ASSERT_EQ(L"test3.bmp",QFileInfo((m->previous())).fileName().toStdWString());
    ASSERT_EQ(L"test2.jpg",QFileInfo((m->previous())).fileName().toStdWString());
    ASSERT_EQ(L"test3.bmp",QFileInfo((m->next())).fileName().toStdWString());
    ASSERT_EQ(L"test4.bmp",QFileInfo((m->next())).fileName().toStdWString());
}
TEST_F(TestFileManager, testFolderFileSwitchC)
{
    m->load("c:\\");
    qDebug()<<(m->next());
    qDebug()<<(m->next());
    qDebug()<<(m->next());
    qDebug()<<(m->next());
    qDebug()<<(m->next());
    qDebug()<<(m->next());
    qDebug()<<(m->previous());
    qDebug()<<(m->previous());
    qDebug()<<(m->previous());
}


