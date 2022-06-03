#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    setWindowTitle("关于");
}

About::~About()
{
    delete ui;
}

void About::showabout()
{
    this->show();
}
