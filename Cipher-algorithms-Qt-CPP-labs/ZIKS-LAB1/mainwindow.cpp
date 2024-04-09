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
    QRegExp regExp1("([1-9]|[12][0-9]|3[0-2])");
    QRegExpValidator *validator1 = new QRegExpValidator(regExp1, ui->lineEditStep);
    ui->lineEditStep->setValidator(validator1);
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
    QString input = ui->lineEditEnter->text(), result;
    int const_var = ui->lineEditStep->text().toInt();
    QString language_list1[33] = {"а", "б", "в" ,"г", "ґ", "д", "е", "є", "ж", "з", "и", "і", "ї", "й", "к", "л",
                                  "м", "н", "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ь", "ю", "я"};
    for(int j = 0; j < input.size(); j++)
    {
        QString c = QString(input[j]);
        for(int i = 0; i < 33; i++)
        {
            if (c == language_list1[i])
            {
                int new_num = (i + const_var) % 33;
                result += language_list1[new_num];
                break;
            }
        }
    }
    ui->lineEditOutput->setText(result);
}
