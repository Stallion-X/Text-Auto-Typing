#include "first.h"
#include "ui_first.h"

First::First(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::First)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = this->windowFlags();
    this->setWindowFlags(flags | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    this->setWindowFlags(Qt::WindowSystemMenuHint);
    this->setWindowModality(Qt::ApplicationModal);
    ui->pushButton->setEnabled(false);
    QSettings* cfg = new QSettings("Config.ini", QSettings::IniFormat);
    int first = cfg->value("Use/First").toInt();
    cfg->sync();
    if (first==0)
    {
        f1 = QtConcurrent::run(this,&First::timer);
    }
}

First::~First()
{
    delete ui;
}

void First::on_pushButton_clicked()
{
    QSettings* cfg = new QSettings("Config.ini", QSettings::IniFormat);
    cfg->setValue("Use/First", 1);
    cfg->sync();
    this->close();
}

void First::timer()
{
    ui->pushButton->setText("10");
    QThread::msleep(1000);
    ui->pushButton->setText("9");
    QThread::msleep(1000);
    ui->pushButton->setText("8");
    QThread::msleep(1000);
    ui->pushButton->setText("7");
    QThread::msleep(1000);
    ui->pushButton->setText("6");
    QThread::msleep(1000);
    ui->pushButton->setText("5");
    QThread::msleep(1000);
    ui->pushButton->setText("4");
    QThread::msleep(1000);
    ui->pushButton->setText("3");
    QThread::msleep(1000);
    ui->pushButton->setText("2");
    QThread::msleep(1000);
    ui->pushButton->setText("1");
    QThread::msleep(1000);
    ui->pushButton->setEnabled(true);
    ui->pushButton->setText("同意");
}

void First::on_pushButton_2_clicked()
{
    f1.cancel();
    this->close();
    qApp->quit();
}
