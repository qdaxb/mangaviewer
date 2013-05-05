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
class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    virtual void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
private:
    Ui::MainWindow *ui;
    MangaViewer *viewer;
    QPainter *painter;
    MsgPainter *msgPainter;
    void openLoadFolderDialog();
    void toogleHelpMessage();
    void toogleFileMessage();
    QPoint dragPosition;
void showScaleMessage();
};

#endif // MAINWINDOW_H
