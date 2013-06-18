#ifndef GOTODIALOG_H
#define GOTODIALOG_H

#include <QDialog>

namespace Ui {
class GotoDialog;
}

class GotoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GotoDialog(QWidget *parent = 0);
    ~GotoDialog();
    void setMax(int max);
    int max();
    int page();
    void setCurrent(int current);
    void focusOnSpin();
private:
    Ui::GotoDialog *ui;
};

#endif // GOTODIALOG_H
