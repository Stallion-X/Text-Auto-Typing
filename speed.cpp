#include "speed.h"
#include "ui_speed.h"
#include <QDebug>
#include "mainwindow.h"

Speed::Speed(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Speed)
{
    ui->setupUi(this);
}

Speed::~Speed()
{
    delete ui;
}

void Speed::showspeed()
{
    this->show();
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    this->showNormal();
    ui->verticalSlider->setValue(50);
}

void Speed::on_verticalSlider_sliderReleased()
{
    MainWindow::speed = ui->verticalSlider->value()/100.0*600;
    qDebug()<<MainWindow::speed;
}

void Speed::on_verticalSlider_valueChanged(int value)
{
    MainWindow::speed = value/100.0*600;
    qDebug()<<MainWindow::speed;
}
