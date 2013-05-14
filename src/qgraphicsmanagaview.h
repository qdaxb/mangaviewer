#ifndef QGRAPHICSMANAGAVIEW_H
#define QGRAPHICSMANAGAVIEW_H

#include <QWidget>
#include <QGraphicsScene>
#include "common.h"
#include <QQueue>
#include "filemanager.h"
#include <QSettings>
class QGraphicsPagedPixmapItem;

namespace Ui {
class QGraphicsManagaView;
}
class QInputEvent;
class QGraphicsManagaView : public QWidget
{
    Q_OBJECT
    
public:
    explicit QGraphicsManagaView(QWidget *parent = 0);
    ~QGraphicsManagaView();
    void go(qreal step=0);
    void back(qreal step=0);
    void resizeEvent(QResizeEvent *event);
    void keyReleaseEvent(QKeyEvent *);
    int load(QString fileorpath);
    void mousePressEvent(QMouseEvent *);
    void setScale(qreal rate);
    void wheelEvent(QWheelEvent *);
    qreal getScale();
    void closeEvent(QCloseEvent *event);
    void updateTitle();
private:
    void init(int index=0);
    void adjustPages();
    QString modCMD(QInputEvent *event);
    Ui::QGraphicsManagaView *ui;
    QGraphicsScene scene;
    QQueue<QGraphicsPagedPixmapItem*> pageViewers;
    QQueue<int> pageIndexs;
    FileManager fileManager;
    bool isLastPage;
    bool isFirstPage;
    qreal rate;
    QSettings setting;
};

#endif // QGRAPHICSMANAGAVIEW_H
