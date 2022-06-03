#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:
    void showsettings();

    void on_pushButton_clicked();

private:
    Ui::Settings *ui;
    QButtonGroup *groupButton1;
};

#endif // SETTINGS_H
