#include "msgpainter.h"
#include <QWidget>
#include <QPainter>
#include <QDebug>

MsgPainter::MsgPainter(QWidget *parent, QPainter *painter)
{
    this->painter=painter;
    this->parent=parent;
}

int MsgPainter::toggleMessage(MsgPainter::PositionFlag position)
{
    bool isShow=true;
    if(position&TOP)
    {
        isShow=isShow&&topMessage.isShow;
    }
    if(position&CENTER)
    {
        isShow=isShow&&centerMessage.isShow;
    }
    if(position&BOTTOM)
    {
        isShow=isShow&&bottomMessage.isShow;
    }
    if(position&TOP)
    {
        topMessage.isShow=!isShow;
    }
    if(position&CENTER)
    {
        centerMessage.isShow=!isShow;
    }
    if(position&BOTTOM)
    {
        bottomMessage.isShow=!isShow;
    }
    return 0;
}

bool MsgPainter::isShowMessage(MsgPainter::PositionFlag position)
{
    if(position&TOP)
    {
        return topMessage.isShow;
    }
    if(position&CENTER)
    {
        return centerMessage.isShow;
    }
    if(position&BOTTOM)
    {
        return bottomMessage.isShow;
    }
}

int MsgPainter::showMessage(QString message, MsgPainter::PositionFlag position)
{
    setMessage(message,position);
    if(position&TOP)
    {
        topMessage.isShow=true;
    }
    if(position&CENTER)
    {
        centerMessage.isShow=true;
    }
    if(position&BOTTOM)
    {
        bottomMessage.isShow=true;
    }
    return 0;
}
int MsgPainter::setMessage(QString message, MsgPainter::PositionFlag position)
{
    if(position&TOP)
    {
        topMessage.message.clear();
        topMessage.message.append(message);
    }
    if(position&CENTER)
    {
        centerMessage.message.clear();
        centerMessage.message.append(message);
    }
    if(position&BOTTOM)
    {
        bottomMessage.message.clear();
        bottomMessage.message.append(message);
    }
    return 0;
}

int MsgPainter::showListMessage(QStringList messages, MsgPainter::PositionFlag position)
{
    if(position&TOP)
    {
        topMessage.message.clear();
        topMessage.message.append(messages);
        topMessage.isShow=true;
    }
    if(position&CENTER)
    {
        centerMessage.message.clear();
        centerMessage.message.append(messages);
        centerMessage.isShow=true;
    }
    if(position&BOTTOM)
    {
        bottomMessage.message.clear();
        bottomMessage.message.append(messages);
        bottomMessage.isShow=true;
    }
    return 0;
}

void MsgPainter::hideMessage(int position)
{
    if(position&TOP)
    {
        topMessage.isShow=false;
    }
    if(position&CENTER)
    {
        centerMessage.isShow=false;
    }
    if(position&BOTTOM)
    {
        bottomMessage.isShow=false;
    }
}

void MsgPainter::drawMessage()
{
    if(topMessage.isShow)
    {
        drawTopMessage();
    }
    if(centerMessage.isShow)
    {
        drawCenterMessage();
    }
    if(bottomMessage.isShow)
    {
        drawBottomMessage();
    }

}

void MsgPainter::setBgColor(MsgPainter::PositionFlag position, Qt::GlobalColor style)
{
    if(position&TOP)
    {
        topMessage.bgColor=style;
    }
    if(position&CENTER)
    {
        centerMessage.bgColor=style;
    }
    if(position&BOTTOM)
    {
        bottomMessage.bgColor=style;
    }
}

void MsgPainter::setFgColor(MsgPainter::PositionFlag position, Qt::GlobalColor style)
{
    if(position&TOP)
    {
        topMessage.fgColor=style;
    }
    if(position&CENTER)
    {
        centerMessage.fgColor=style;
    }
    if(position&BOTTOM)
    {
        bottomMessage.fgColor=style;
    }
}

void MsgPainter::drawTopMessage()
{
    if(topMessage.message.isEmpty())
        return;

    painter->fillRect(calculateTextBgRect(TOP,parent->rect(),topMessage),topMessage.bgColor);
    painter->setFont(topMessage.font);
    painter->setPen(topMessage.fgColor);
    painter->drawText(1,topMessage.font.pointSize(),topMessage.message.first());
}

void MsgPainter::drawCenterMessage()
{
    if(centerMessage.message.isEmpty())
        return;
    QStringList messageList=centerMessage.message;
    QRect msgRect=calculateTextBgRect(CENTER,parent->rect(),centerMessage);

    painter->fillRect(msgRect,centerMessage.bgColor);
    painter->setFont(centerMessage.font);
    painter->setPen(centerMessage.fgColor);
    for(int i=0;i<messageList.size();i++)
    {
        painter->drawText(msgRect.left()+2,msgRect.top()-painter->fontMetrics().xHeight()+1+painter->fontMetrics().lineSpacing()*(i+1),centerMessage.message.at(i));
    }
}

void MsgPainter::drawBottomMessage()
{
    if(bottomMessage.message.isEmpty())
        return;

    painter->fillRect(calculateTextBgRect(BOTTOM,parent->rect(),bottomMessage),bottomMessage.bgColor);

    painter->setPen(bottomMessage.fgColor);
    painter->setFont(bottomMessage.font);
    painter->drawText(1,parent->height()-3,bottomMessage.message.first());

}

QRect MsgPainter::calculateTextPixelSize(const MsgEntry &entry)
{

    if(entry.message.isEmpty())
        return QRect();
    QFontMetrics fm(entry.font,painter->device());

    int maxWidth=0;
    int height=(fm.lineSpacing())*entry.message.size();
    for(int i=0;i<entry.message.size();i++)
    {
        int width=fm.width(entry.message.at(i));
        if(width>maxWidth)
            maxWidth=width;
    }

    return QRect(0,0,maxWidth,height);



}

QRect MsgPainter::calculateTextBgRect(MsgPainter::PositionFlag position, const QRect &parentRect,const MsgEntry &entry)
{
    QRect textRect=calculateTextPixelSize(entry);

    if(position&TOP)
    {
        textRect.setTop(0);
        textRect.setLeft(0);
        textRect.setWidth(parentRect.width());
        textRect.setHeight(textRect.height()+2);
    }
    if(position&CENTER)
    {

        textRect.moveTop((parentRect.height()-textRect.height())/2-2);
        textRect.moveLeft((parentRect.width()-textRect.width())/2-2);
        textRect.setWidth(textRect.width()+4);
        textRect.setHeight(textRect.height()+4);

    }
    if(position&BOTTOM)
    {
        textRect.setWidth(parentRect.width());
        textRect.moveBottom(parentRect.height());
        textRect.moveLeft(0);
        textRect.setHeight(textRect.height()+2);
    }

    return textRect;
}

void MsgPainter::setFont(MsgPainter::PositionFlag position, QFont font)
{
    if(position&TOP)
    {
        topMessage.font=font;
    }
    if(position&CENTER)
    {
        centerMessage.font=font;
    }
    if(position&BOTTOM)
    {
        bottomMessage.font=font;
    }
}
