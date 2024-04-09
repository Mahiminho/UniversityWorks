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
    QString message = ui->lineEditMess->text();

    if (message.size() % 2 != 0) {
        message += " ";
    }

    int numRounds = 16;
    QString result = message;

    auto encryptRound = [](const QString& block, int key) { // функція - XOR блоку з ключем
        QString result = block;
        for (int i = 0; i < block.size(); ++i) {
            result[i] = QChar(block.at(i).toLatin1() ^ key);
        }
        return result;
    };

    int blockSize = message.size() / 2;
    QString left = result.mid(0, blockSize);
    QString right = result.mid(blockSize);

    for (int round = 0; round < numRounds; round++) {
        QString newRight = encryptRound(right, 1 << round); // ключ - степінь двійки
        QString temp = left;
        left = right;
        right = temp;

        int minLength = std::min(right.size(), newRight.size());
        for (int i = 0; i < minLength; i++) {
            QChar rightChar = right.at(i);
            QChar newRightChar = newRight.at(i);
            char rightAscii = rightChar.toLatin1();
            char newRightAscii = newRightChar.toLatin1();
            char resultAscii = rightAscii ^ newRightAscii;
            right[i] = QChar(resultAscii);
        }
    }

    result = left + right;
    ui->lineEditResult->setText(result);
}



void MainWindow::on_pushButtonDecrypt_clicked()
{
    QString message = ui->lineEditMess->text();

    int numRounds = 16;
    QString result = message;

    auto encryptRound = [](const QString& block, int key) { // функція - XOR блоку з ключем
        QString result = block;
        for (int i = 0; i < block.size(); ++i) {
            result[i] = QChar(block.at(i).toLatin1() ^ key);
        }
        return result;
    };

    int blockSize = message.size() / 2;
    QString left = result.mid(0, blockSize);
    QString right = result.mid(blockSize);

    for (int round = numRounds - 1; round >= 0; round--) {
        QString newLeft = encryptRound(left, 1 << round); // ключ - степінь двійки
        QString temp = right;
        right = left;
        left = temp;

        int minLength = std::min(left.size(), newLeft.size());
        for (int i = 0; i < minLength; i++) {
            QChar leftChar = left.at(i);
            QChar newLeftChar = newLeft.at(i);
            char leftAscii = leftChar.toLatin1();
            char newLeftAscii = newLeftChar.toLatin1();
            char resultAscii = leftAscii ^ newLeftAscii;
            left[i] = QChar(resultAscii);
        }
    }

    result = left + right;
    ui->lineEditResult->setText(result);
}
