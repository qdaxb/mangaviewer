#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class MainWindow;
}
class QPainter;
class QPixmap;
class FileManager;
class MsgPainter;
class ImagePainter;
class QDragEnterEvent;
class QDragMoveEvent;
class MangaViewer;
class CommandRegistry;
class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event);
    virtual void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void dropEvent(QDropEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *);
private:
    Ui::MainWindow *ui;
    MangaViewer *viewer;
    QPainter *painter;
    MsgPainter *msgPainter;
    void openLoadFolderDialog();
    void toogleHelpMessage();
    void toogleFileMessage();
    QPoint dragPosition;
    CommandRegistry *commandRegistry;
    void showScaleMessage();
    QTimer *mouseClickTimer;
    int mouseButton;
protected slots:
    void mouseClick();
};

#endif // MAINWINDOW_H
