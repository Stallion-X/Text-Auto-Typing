#include "settings.h"
#include "ui_settings.h"
#include "mainwindow.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setWindowTitle("设置");
    groupButton1=new QButtonGroup(this);
    groupButton1->addButton(ui->radioButton1,1);
    groupButton1->addButton(ui->radioButton2,2);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::showsettings()
{
    this->show();
}

void Settings::on_pushButton_clicked()
{
    if (ui->checkBox->isChecked())
    {
        MainWindow::isTab = true;
    }
    else
    {
        MainWindow::isTab = false;
    }
    switch(groupButton1->checkedId())
    {
        case 1:
            MainWindow::choose=1;
            break;
        case 2:
            MainWindow::choose=2;
            break;
    }
    if (ui->checkBox_2->isChecked())
    {
        MainWindow::isFucked = true;
    }
    else
    {
        MainWindow::isAuto = false;
        ui->checkBox_4->setChecked(false);
        MainWindow::isFucked = false;
    }
    if (ui->checkBox_3->isChecked())
    {
        MainWindow::isTesting = true;
    }
    else
    {
        MainWindow::isTesting = false;
    }
    if (ui->checkBox_4->isChecked())
    {
        MainWindow::isAuto = true;
    }
    else
    {
        MainWindow::isAuto = false;
    }
    this->close();
}
