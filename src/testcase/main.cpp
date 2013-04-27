#include "gtest/gtest.h"
#include <QtGui/QApplication>
using namespace std;

int main(int argc, char** argv) {
    QApplication a(argc, argv);
testing::InitGoogleTest(&argc, argv);

// Runs all tests using Google Test.

return RUN_ALL_TESTS();

}

