
#include "gtest/gtest.h"
#include "resizemanager.h"
#include <QWidget>
#include <QPixmap>
#include <QImage>
class TestResizeManager : public ::testing::Test {
public:
    ResizeManager *rm;
    virtual void SetUp() {

        rm=new ResizeManager();
    }
};
TEST_F(TestResizeManager, testResize)
{
    QWidget *widget=new QWidget();
    widget->setBaseSize(100,100);
    rm->setClient(widget);

    QPixmap *image=new QPixmap(200,200);
    rm->setImage(image);
    rm->setResizeMode(ResizeManager::FIT_IMAGE);
    rm->resize();
    EXPECT_EQ(rm->getClientSize().width(),200);
    EXPECT_EQ(rm->getClientSize().height(),200);

    rm->setResizeMode(ResizeManager::FIT_IMAGE|ResizeManager::RATE,2);
    rm->resize();
    EXPECT_EQ(rm->getClientSize().width(),400);
    EXPECT_EQ(rm->getClientSize().height(),400);

    rm->setResizeMode(ResizeManager::FIT_IMAGE);
    rm->resize();
    EXPECT_EQ(rm->getClientSize().width(),200);
    EXPECT_EQ(rm->getClientSize().height(),200);

    widget->resize(1024,768);
    rm->setResizeMode(ResizeManager::FIT_WINDOW);
    rm->resize();
    EXPECT_EQ(rm->getImageSize().width(),768);
    EXPECT_EQ(rm->getImageSize().height(),768);

    rm->setResizeMode(ResizeManager::FIT_WINDOW_WIDTH);
    rm->resize();
    EXPECT_EQ(rm->getImageSize().width(),1024);
    EXPECT_EQ(rm->getImageSize().height(),1024);

    rm->setResizeMode(ResizeManager::FIT_WINDOW_HEIGHT);
    rm->resize();
    EXPECT_EQ(rm->getImageSize().width(),768);
    EXPECT_EQ(rm->getImageSize().height(),768);
}
