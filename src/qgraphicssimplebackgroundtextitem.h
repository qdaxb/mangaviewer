#ifndef QGRAPHICSSIMPLEBACKGROUNDTEXTITEM_H
#define QGRAPHICSSIMPLEBACKGROUNDTEXTITEM_H
#include <QGraphicsSimpleTextItem>
class QGraphicsSimpleBackgroundTextItem:public QGraphicsSimpleTextItem
{
public:
    QGraphicsSimpleBackgroundTextItem();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // QGRAPHICSSIMPLEBACKGROUNDTEXTITEM_H
