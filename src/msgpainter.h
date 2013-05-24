#ifndef MSGPAINTER_H
#define MSGPAINTER_H
#include <QWidget>
#include <QFont>
class QStringList;
class QFont;
class MsgEntry{
public:
    MsgEntry(){
        this->bgColor=Qt::black;
        this->fgColor=Qt::white;
        this->isShow=false;
        this->listMessageMargin=3;
        this->font=QFont("宋体",10);
    }

    QStringList message;
    Qt::GlobalColor bgColor;
    Qt::GlobalColor fgColor;
    bool isShow;
    int listMessageMargin;
    QFont font;

};

class MsgPainter
{
public:
    enum PositionFlag{ALL=-1,TOP=0x01,CENTER=0x02,BOTTOM=0x04};
    MsgPainter(QWidget *parent, QPainter *painter);
    int toggleMessage(PositionFlag position);
    bool isShowMessage(PositionFlag flag);
    int showMessage(QString message,PositionFlag position);
    int showListMessage(QStringList messages,PositionFlag position);
    void hideMessage(int position);
    void clearMessage(PositionFlag potition);
    void drawMessage();
    void setBgColor(PositionFlag position=MsgPainter::ALL,Qt::GlobalColor style=Qt::black);
    void setFgColor(PositionFlag position=MsgPainter::ALL,Qt::GlobalColor style=Qt::white);
    void setFont(PositionFlag position,QFont font);
    int setMessage(QString message, MsgPainter::PositionFlag position);
private:
    MsgEntry topMessage;
    MsgEntry centerMessage;
    MsgEntry bottomMessage;
    QWidget *parent;
    QPainter *painter;
    void drawTopMessage();
    void drawCenterMessage();
    void drawBottomMessage();
    QRect calculateTextPixelSize(const MsgEntry& text);
    QRect calculateTextBgRect(PositionFlag flag,const QRect& parentRect, const MsgEntry &textRect);

};

#endif // MSGPAINTER_H
