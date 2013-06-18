#include "gotodialog.h"
#include "ui_gotodialog.h"

GotoDialog::GotoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GotoDialog)
{
    ui->setupUi(this);

    ui->spinBox->setMinimum(1);
    ui->min->setText("1");
}

GotoDialog::~GotoDialog()
{
    delete ui;
}

void GotoDialog::setMax(int max)
{
    ui->spinBox->setMaximum(max);
    ui->max->setText(QString::number(max));
}

int GotoDialog::page()
{
    return ui->spinBox->value();
}

void GotoDialog::setCurrent(int current)
{
    ui->spinBox->setValue(current);
}

void GotoDialog::focusOnSpin()
{
    ui->spinBox->setFocus();
}
