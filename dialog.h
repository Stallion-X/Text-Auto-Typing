#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QThread>
#include <QtConcurrent>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    void timer();

private slots:
    void showing();
};

#endif // DIALOG_H
