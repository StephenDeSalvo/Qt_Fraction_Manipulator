#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Fraction.h"
#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void plusEvent();
    void timesEvent();

public:
    explicit MainWindow(QWidget *parent = 0);

    Fraction get_fraction_from_text(QLineEdit* numerator, QLineEdit* denominator, bool* ok);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
