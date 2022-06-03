#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Windows.h>
#include <QtConcurrent>
#include <QDebug>
#include<QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static bool isTab;
    static int choose;
    static bool isFucked;
    static int speed;
    static bool isTesting;
    static bool isAuto;

signals:
    void emitsignal();
    void emitabout();
    void emitsettings();
    void emitspeed();
    void emitfirst();

private slots:
    void on_pushButton_clicked();

    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_actionSettings_triggered();

    void on_pushButton_2_clicked();

    bool isSuc();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    HWND hEdit;
    int first;
    void SendKeyString(QString str);
    void newwindow();
    void newwindow1();
    QSettings* cfg;
};
#endif // MAINWINDOW_H
