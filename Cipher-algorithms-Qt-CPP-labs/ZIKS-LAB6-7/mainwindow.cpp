#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonEncrypt_clicked()
{
    QString plainText = ui->lineEditMess->text();
    QRandomGenerator rand(QDateTime::currentDateTime().toTime_t());

    int keyMatrix[3][3] = {
        {112, 111, 112},
        {111, 118, 109},
        {97, 120, 105}
    };

    QString midRes;
    QString encryptedText = "";
    for (int i = 0; i < plainText.size(); i++) { // маскуючі символи
        int numberOfMaskedChars = (i * i + i) % 3;
        midRes = plainText[i];
        for (int j = 0; j < numberOfMaskedChars; j++) {
            int randomChar = rand.bounded(63, 127); // рандомний символ
            midRes.append(QChar(randomChar));
        }
        encryptedText.append(midRes);
    }

    while (encryptedText.size() % 3 != 0) { // вирівнювання повідомлення до кратного 3
        encryptedText.append(" ");
    }

    QString resultMess = "";
    int blockMatrix[1][3];
    int resultMatrix[1][3];
    for (int i = 0; i < encryptedText.size(); i += 3) { // множення блок матриць на ключову матрицю
        for (int j = 0; j < 3; j++) {
            blockMatrix[0][j] = encryptedText[i + j].unicode();
        }

        for (int l = 0; l < 1; l++) {
            for (int j = 0; j < 3; j++) {
                resultMatrix[l][j] = 0;
                for (int k = 0; k < 3; k++) {
                    resultMatrix[l][j] += blockMatrix[l][k] * keyMatrix[k][j];
                }
            }
        }

        for (int j = 0; j < 3; j++) {
            resultMess += QChar(resultMatrix[0][j]);
        }
    }

    ui->lineEditResult->setText(resultMess);
}



void MainWindow::on_pushButtonDecrypt_clicked()
{
    QString encryptedText = ui->lineEditMess->text();

    int keyMatrix[3][3] = { // інверсна матриця (чисельники)
        {-690, 1785, -1117},
        {-1082, 896, 224},
        {1874, -2673, 895}
    };
    int den = 12506; // знаменник інверсної матриці

    QString resultMess = "";
    int blockMatrix[1][3];
    int resultMatrix[1][3];
    for (int i = 0; i < encryptedText.size(); i += 3) { // множення матриць
        for (int j = 0; j < 3; j++) {
            blockMatrix[0][j] = encryptedText[i + j].unicode();
        }

        for (int l = 0; l < 1; l++) {
            for (int j = 0; j < 3; j++) {
                double templ = 0;
                for (int k = 0; k < 3; k++) {
                    templ += static_cast<double>(blockMatrix[l][k]) * static_cast<double>(keyMatrix[k][j]) / static_cast<double>(den);
                }
                resultMatrix[l][j] = round(templ);
            }
        }

        for (int j = 0; j < 3; j++) {
            resultMess += QChar(resultMatrix[0][j]);
        }
    }

    QString resultMessFull = ""; // прибирання маскуючих символів
    int s = 0;
    for (int i = 0; i < resultMess.size(); i++) {
        int numberOfMaskedChars = (s * s + s) % 3;
        resultMessFull += resultMess[i];
        s++;
        for (int j = 0; j < numberOfMaskedChars; j++) {
            i++;
        }
    }

    ui->lineEditResult->setText(resultMessFull);
}
