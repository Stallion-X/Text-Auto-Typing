#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("倒计时");
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::showing()
{
    this->show();
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    this->showNormal();
    QtConcurrent::run(this,&Dialog::timer);
}
void Dialog::timer()
{
    ui->label_3->setText("2");
    QThread::msleep(1000);
    ui->label_3->setText("1");
    QThread::msleep(1000);
    this->close();
}
