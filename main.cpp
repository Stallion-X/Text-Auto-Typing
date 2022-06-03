#include "mainwindow.h"
#include "dialog.h"
#include "about.h"
#include "settings.h"
#include "speed.h"
#include "first.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Dialog d;
    About ab;
    Settings st;
    Speed sp;
    First fs;
//连接各信号和槽函数 实现界面切换
    QObject::connect(&w,SIGNAL(emitsignal()),&d, SLOT(showing()));
    QObject::connect(&w,SIGNAL(emitabout()),&ab, SLOT(showabout()));
    QObject::connect(&w,SIGNAL(emitsettings()),&st, SLOT(showsettings()));
    QObject::connect(&w,SIGNAL(emitspeed()),&sp, SLOT(showspeed()));
//读取ini配置文件 判断是否为首次打开
    QSettings* cfg = new QSettings("Config.ini", QSettings::IniFormat);
    int first = cfg->value("Use/First").toInt();
    cfg->sync();
    if (first==0)
    {
        fs.show();
    }
    w.show();
    qApp->quit();
    return a.exec();
}
