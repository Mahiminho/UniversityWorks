#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRegExp regExp("[а-яіїєґ ]+");
    QRegExpValidator *validator = new QRegExpValidator(regExp, ui->lineEditEnter);
    ui->lineEditEnter->setValidator(validator);
    QRegExp regExp2("");
    QRegExpValidator *validator2 = new QRegExpValidator(regExp2, ui->lineEditOutput);
    ui->lineEditOutput->setValidator(validator2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString row1, row2, row3, input = ui->lineEditEnter->text(), result;
    for (int i = 0; i < input.size(); i+=3) {
        row1 += input[i + 0];
        row2 += input[i + 1];
        row3 += input[i + 2];
    }
    if (input.size() % 3 == 2) {
        row3.chop(1);
    } else if (input.size() % 3 == 1) {
        row2.chop(1);
        row3.chop(1);
    }
    result = row1 + row2 + row3;
    ui->lineEditOutput->setText(result);
}
