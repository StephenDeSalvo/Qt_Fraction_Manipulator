#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Fraction.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QObject::connect(ui->pushButton, SIGNAL(clicked(bool)), ui->label, SLOT(clear()));
    //ui->label->setText("s;lkfajds;lfkas");

    QObject::connect(ui->plusButton, SIGNAL(clicked(bool)),this,SLOT(plusEvent()));
    QObject::connect(ui->timesButton, SIGNAL(clicked(bool)),this,SLOT(timesEvent()));
}


Fraction MainWindow::get_fraction_from_text(QLineEdit* numerator, QLineEdit* denominator, bool* ok) {

    int num = numerator->text().toInt(ok);

    // if first line edit is numerical
    if(ok) {
        int den = denominator->text().toInt(ok);

        // if secodn line edit is numerical
        if(ok)
            return Fraction(num, den);
    }

    return Fraction(0,1);
}

void MainWindow::plusEvent() {

    // get lhs fraction
    bool ok;
    Fraction lhs_fraction = get_fraction_from_text(ui->lhs_numerator, ui->lhs_denominator, &ok);

    // if lhs is valid fraction entry ...
    if(ok) {

        // get rhs fraction
        Fraction rhs_fraction = get_fraction_from_text(ui->rhs_numerator, ui->rhs_denominator, &ok);

        // if rhs is valid fraction entry as well ...
        if(ok) {
            // perform the arithmetic
            lhs_fraction += rhs_fraction;

            // assign the numerator and denominator to the text.
            ui->numerator_label  ->setText( QString::number(lhs_fraction[0]) );
            ui->denominator_label->setText( QString::number(lhs_fraction[1]) );
        }
    }

}

void MainWindow::timesEvent() {

    // get lhs fraction
    bool ok;
    Fraction lhs_fraction = get_fraction_from_text(ui->lhs_numerator, ui->lhs_denominator, &ok);

    // if lhs is valid fraction entry ...
    if(ok) {

        // get rhs fraction
        Fraction rhs_fraction = get_fraction_from_text(ui->rhs_numerator, ui->rhs_denominator, &ok);

        // if rhs is valid fraction entry as well ...
        if(ok) {
            // perform the arithmetic
            lhs_fraction *= rhs_fraction;

            // assign the numerator and denominator to the text.
            ui->numerator_label  ->setText( QString::number(lhs_fraction[0]) );
            ui->denominator_label->setText( QString::number(lhs_fraction[1]) );
        }
    }

}



MainWindow::~MainWindow()
{
    delete ui;
}
