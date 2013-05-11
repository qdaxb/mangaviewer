#ifndef QGRAPHICSMANAGAVIEW_H
#define QGRAPHICSMANAGAVIEW_H

#include <QWidget>
#include <QGraphicsScene>
#include "common.h"
#include <QQueue>
class QGraphicsPagedPixmapItem;

namespace Ui {
class QGraphicsManagaView;
}

class QGraphicsManagaView : public QWidget
{
    Q_OBJECT
    
public:
    explicit QGraphicsManagaView(QWidget *parent = 0);
    ~QGraphicsManagaView();
    void go(qreal step=1);
    void back(qreal step=1);
    void resizeEvent(QResizeEvent *event);
    void keyReleaseEvent(QKeyEvent *);
private:
    Ui::QGraphicsManagaView *ui;
    QGraphicsScene scene;
    QQueue<QGraphicsPagedPixmapItem*> pageViewers;
};

#endif // QGRAPHICSMANAGAVIEW_H
