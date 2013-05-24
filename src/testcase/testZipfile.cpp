#include "gtest/gtest.h"
#include "zipfile.h"
#include <QString>
#include <QDebug>
class TestZipfile : public ::testing::Test {
public:
    ZipFile *zipfile;
virtual void SetUp() {
        zipfile=new ZipFile("demo.zip");

}



};

TEST_F(TestZipfile, testList)
{

}


