
#include "gtest/gtest.h"
#include "pageviewer.h"
#include <QSize>
class TestPageViewer : public ::testing::Test {
public:
    PageViewer *pv;
    virtual void SetUp() {

        pv=new PageViewer();
        pv->setClientSize(QSize(200,200));
        pv->setImageSize(QSize(510,320));
    }
};
TEST_F(TestPageViewer, testNewPage)
{

    pv->setMoveMode(PageViewer::LEFT_TO_RIGHT|PageViewer::UP_TO_DOWN);
    pv->newPage();
    ASSERT_EQ(pv->getTargetViewRect().top(),0);
    ASSERT_EQ(pv->getTargetViewRect().left(),0);
    ASSERT_EQ(pv->getTargetViewRect().right(),199);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),199);

    pv->setMoveMode(PageViewer::RIGHT_TO_LEFT|PageViewer::UP_TO_DOWN);
    pv->newPage();
    ASSERT_EQ(pv->getTargetViewRect().top(),0);
    ASSERT_EQ(pv->getTargetViewRect().left(),310);
    ASSERT_EQ(pv->getTargetViewRect().right(),509);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),199);

    pv->setMoveMode(PageViewer::RIGHT_TO_LEFT|PageViewer::DOWN_TO_UP);
    pv->newPage();
    ASSERT_EQ(pv->getTargetViewRect().top(),120);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),319);
    ASSERT_EQ(pv->getTargetViewRect().left(),310);
    ASSERT_EQ(pv->getTargetViewRect().right(),509);

    pv->setMoveMode(PageViewer::LEFT_TO_RIGHT|PageViewer::DOWN_TO_UP);
    pv->newPage();
    ASSERT_EQ(pv->getTargetViewRect().top(),120);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),319);
    ASSERT_EQ(pv->getTargetViewRect().left(),0);
    ASSERT_EQ(pv->getTargetViewRect().right(),199);
}

TEST_F(TestPageViewer, testStep)
{
    pv->setMoveMode(PageViewer::LEFT_TO_RIGHT|PageViewer::DOWN_TO_UP);
    pv->newPage();
    ASSERT_EQ(pv->getTargetViewRect().top(),120);
    pv->stepUp(119);
    ASSERT_EQ(pv->getTargetViewRect().top(),1);
    pv->stepUp(1);
    ASSERT_EQ(pv->getTargetViewRect().top(),0);
    pv->stepUp(1);
    ASSERT_EQ(pv->getTargetViewRect().top(),0);
    pv->stepUp(1);
    ASSERT_EQ(pv->getTargetViewRect().top(),0);

    ASSERT_EQ(pv->getTargetViewRect().left(),0);
    pv->stepRight(309);
    ASSERT_EQ(pv->getTargetViewRect().left(),309);
    pv->stepRight(1);
    ASSERT_EQ(pv->getTargetViewRect().left(),310);
    pv->stepRight(1);
    ASSERT_EQ(pv->getTargetViewRect().left(),310);
    pv->stepRight(1);
    ASSERT_EQ(pv->getTargetViewRect().left(),310);

    pv->stepDown(1);
    ASSERT_EQ(pv->getTargetViewRect().top(),1);
    pv->stepDown(118);
    ASSERT_EQ(pv->getTargetViewRect().top(),119);
    pv->stepDown(1);
    ASSERT_EQ(pv->getTargetViewRect().top(),120);
    pv->stepDown(1);
    ASSERT_EQ(pv->getTargetViewRect().top(),120);
    pv->stepDown(1);
    ASSERT_EQ(pv->getTargetViewRect().top(),120);
    pv->stepUp(119);
    ASSERT_EQ(pv->getTargetViewRect().top(),1);

    pv->stepLeft(1);
    ASSERT_EQ(pv->getTargetViewRect().left(),309);
    pv->stepLeft(308);
    ASSERT_EQ(pv->getTargetViewRect().left(),1);
    pv->stepLeft(1);
    ASSERT_EQ(pv->getTargetViewRect().left(),0);
    pv->stepLeft(1);
    ASSERT_EQ(pv->getTargetViewRect().left(),0);
    pv->stepLeft(1);
    ASSERT_EQ(pv->getTargetViewRect().left(),0);
    pv->stepRight(309);
    ASSERT_EQ(pv->getTargetViewRect().left(),309);
}
TEST_F(TestPageViewer, testGoAndBack)
{
    pv->setMoveMode(PageViewer::RIGHT_TO_LEFT|PageViewer::UP_TO_DOWN);
    pv->newPage();
    ASSERT_EQ(pv->getTargetViewRect().top(),0);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),199);
    ASSERT_EQ(pv->getTargetViewRect().left(),310);
    ASSERT_EQ(pv->getTargetViewRect().right(),509);

    ASSERT_EQ(pv->go(),0);
    ASSERT_EQ(pv->getTargetViewRect().top(),0);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),199);
    ASSERT_EQ(pv->getTargetViewRect().left(),110);
    ASSERT_EQ(pv->getTargetViewRect().right(),309);

    ASSERT_EQ(pv->go(),0);
    ASSERT_EQ(pv->getTargetViewRect().top(),0);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),199);
    ASSERT_EQ(pv->getTargetViewRect().left(),0);
    ASSERT_EQ(pv->getTargetViewRect().right(),199);

    ASSERT_EQ(pv->go(),0);
    ASSERT_EQ(pv->getTargetViewRect().top(),120);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),319);
    ASSERT_EQ(pv->getTargetViewRect().left(),310);
    ASSERT_EQ(pv->getTargetViewRect().right(),509);

    ASSERT_EQ(pv->go(),0);
    ASSERT_EQ(pv->getTargetViewRect().top(),120);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),319);
    ASSERT_EQ(pv->getTargetViewRect().left(),110);
    ASSERT_EQ(pv->getTargetViewRect().right(),309);

    ASSERT_EQ(pv->go(),0);
    ASSERT_EQ(pv->getTargetViewRect().top(),120);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),319);
    ASSERT_EQ(pv->getTargetViewRect().left(),0);
    ASSERT_EQ(pv->getTargetViewRect().right(),199);

    ASSERT_EQ(pv->go(),-1);
    ASSERT_EQ(pv->getTargetViewRect().top(),120);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),319);
    ASSERT_EQ(pv->getTargetViewRect().left(),0);
    ASSERT_EQ(pv->getTargetViewRect().right(),199);


    ASSERT_EQ(pv->back(),0);
    ASSERT_EQ(pv->getTargetViewRect().top(),120);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),319);
    ASSERT_EQ(pv->getTargetViewRect().left(),200);
    ASSERT_EQ(pv->getTargetViewRect().right(),399);

    ASSERT_EQ(pv->back(),0);
    ASSERT_EQ(pv->getTargetViewRect().top(),120);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),319);
    ASSERT_EQ(pv->getTargetViewRect().left(),310);
    ASSERT_EQ(pv->getTargetViewRect().right(),509);

    ASSERT_EQ(pv->back(),0);
    ASSERT_EQ(pv->getTargetViewRect().top(),0);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),199);
    ASSERT_EQ(pv->getTargetViewRect().left(),0);
    ASSERT_EQ(pv->getTargetViewRect().right(),199);

    ASSERT_EQ(pv->back(),0);
    ASSERT_EQ(pv->getTargetViewRect().top(),0);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),199);
    ASSERT_EQ(pv->getTargetViewRect().left(),200);
    ASSERT_EQ(pv->getTargetViewRect().right(),399);

    ASSERT_EQ(pv->back(),0);
    ASSERT_EQ(pv->getTargetViewRect().top(),0);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),199);
    ASSERT_EQ(pv->getTargetViewRect().left(),310);
    ASSERT_EQ(pv->getTargetViewRect().right(),509);

    ASSERT_EQ(pv->back(),-1);
    ASSERT_EQ(pv->getTargetViewRect().top(),0);
    ASSERT_EQ(pv->getTargetViewRect().bottom(),199);
    ASSERT_EQ(pv->getTargetViewRect().left(),310);
    ASSERT_EQ(pv->getTargetViewRect().right(),509);


    pv->setClientSize(QSize(100,130));
    pv->setImageSize(QSize(80,90));
    pv->newPage();
//    ASSERT_EQ(pv->go(),-1);

    ASSERT_EQ(pv->getTargetViewRect().left(),-10);
    ASSERT_EQ(pv->getTargetViewRect().top(),-20);
    ASSERT_EQ(pv->go(),-1);
    ASSERT_EQ(pv->getTargetViewRect().left(),-10);
    ASSERT_EQ(pv->getTargetViewRect().top(),-20);
    ASSERT_EQ(pv->back(),-1);
    ASSERT_EQ(pv->getTargetViewRect().left(),-10);
    ASSERT_EQ(pv->getTargetViewRect().top(),-20);
}
