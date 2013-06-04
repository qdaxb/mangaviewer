#include "qgraphicssimplebackgroundtextitem.h"
#include <QPainter>
QGraphicsSimpleBackgroundTextItem::QGraphicsSimpleBackgroundTextItem()
{
}

void QGraphicsSimpleBackgroundTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawRoundedRect(this->boundingRect(),2,2);
    QGraphicsSimpleTextItem::paint(painter,option,widget);
}
