#ifndef QGRAPHICSMANAGAVIEW_H
#define QGRAPHICSMANAGAVIEW_H

#include <QWidget>
#include <QGraphicsScene>
#include "common.h"
#include <QQueue>
#include "filemanager.h"
#include <QSettings>
#include <QPoint>
#include "pagemanager.h"
#include "qgraphicsgridscrollitem.h"
class QGraphicsPagedPixmapItem;
class QGraphicsTextItem;
class ShortcutManager;

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
    QString currentPath();
    void go(qreal step=-1);
    void back(qreal step=-1);
    void nextPage();
    void perviousPage();
    int gotoPage(int page);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *);
    void resizeEvent(QResizeEvent *event);
    void keyReleaseEvent(QKeyEvent *);
    void keyPressEvent(QKeyEvent *event);
    int load(QString fileorpath);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void setScale(qreal rate);
    void wheelEvent(QWheelEvent *);
    qreal getScale();
    void closeEvent(QCloseEvent *event);
    void updateTitle();
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
    void showMsg(QString msg, int timeInSecond=3);
    void timerEvent(QTimerEvent *event);
    void toggleProgressBar();
    void toggleHelpMessage(bool hide=false);
    void toggleSplitPage();
    void hideMsg();
    bool eventFilter(QObject *obj, QEvent *event);
    int gotoDialog();
private:
    void init(int index=0);
    void updateLayout();
    void adjustPages();
    QString modCMD(QInputEvent *event);
    Ui::QGraphicsManagaView *ui;
    QGraphicsScene scene;
    QQueue<QGraphicsPagedPixmapItem*> pageViewers;
    QQueue<int> pageIndexs;
    FileManager fileManager;
    PageManager *pageManager;
    QGraphicsGridScrollItem *scrollItem;
    bool isLastPage;
    bool isFirstPage;
    qreal rate;
    QSettings setting;
    QPoint dragPosition;
    bool leftAndRightButton;
    bool leftDblClick;
    void updateProgressBar();
    bool altKey;
    QGraphicsSimpleTextItem *msgItem;
    QPoint lastPos;
    QList<int> msgtimer;
    int mouseDblClickTimer;
    qreal backgroundOpacity;
    qreal foregroundOpacity;
    QKeySequence getKeySequence(QKeyEvent *event);
    ShortcutManager *shortcutManager;
    int progressBarHeight;
    int moveDelta;
    qreal moveRate;
    QGraphicsTextItem *helpMessageItem;
    QSize savedSize;
    void showSplitMsg();
private slots:
    void onLoadImage(int index);
    void onUnloadImage(int index);
    void registerGlobalShortcutFailed(QKeySequence& seq);
};

#endif // QGRAPHICSMANAGAVIEW_H
