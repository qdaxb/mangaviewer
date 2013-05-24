#include "gtest/gtest.h"
#include <QDebug>

#include "zipfile.h"
int main(int argc, char** argv) {
    ZipFile *zipfile;
        zipfile=new ZipFile("啊.zip");
        zipfile->open();
qDebug()<<zipfile->readFileList();
qDebug()<<zipfile->readFile(zipfile->readFileList().at(0))<<"a";
qDebug()<<zipfile->readFile(zipfile->readFileList().at(3))<<"b";
qDebug()<<"C";
return 0;

}

