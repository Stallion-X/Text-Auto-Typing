#ifndef FIRST_H
#define FIRST_H

#include <QDialog>
#include <QThread>
#include <QtConcurrent>

namespace Ui {
class First;
}

class First : public QDialog
{
    Q_OBJECT

public:
    explicit First(QWidget *parent = nullptr);
    ~First();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::First *ui;

    void timer();

    QFuture<void> f1;
};

#endif // FIRST_H
