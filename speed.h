#ifndef SPEED_H
#define SPEED_H

#include <QDialog>

namespace Ui {
class Speed;
}

class Speed : public QDialog
{
    Q_OBJECT

public:
    explicit Speed(QWidget *parent = nullptr);
    ~Speed();

private slots:
    void showspeed();

    void on_verticalSlider_sliderReleased();

    void on_verticalSlider_valueChanged(int value);

private:
    Ui::Speed *ui;
};

#endif // SPEED_H
