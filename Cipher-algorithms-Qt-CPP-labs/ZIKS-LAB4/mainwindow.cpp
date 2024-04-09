#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegExp regex("^[a-z ]*$");
    QRegExpValidator *validator = new QRegExpValidator(regex, ui->lineEditMess);
    ui->lineEditMess->setValidator(validator);
    QRegExp regex1("^(?:100|[1-9][0-9]?)$");
    QRegExpValidator *validator1 = new QRegExpValidator(regex1, ui->lineEditSize);
    ui->lineEditSize->setValidator(validator1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonWrite_clicked()
{
    QString bmpFilePath = ui->lineEditBMP->text();
    QString message = ui->lineEditMess->text();
    ui->lineEditSize->setText(QString::number(message.size()));
    std::fstream bmpFile(bmpFilePath.toStdString(), std::ios::in | std::ios::out | std::ios::binary);

    if (!bmpFile.is_open()) {
        QMessageBox::critical(nullptr, "Помилка", "Неможливо відкрити файл!");
        return;
    }

    bmpFile.seekp(54); // перехід до 54-ого байту, бо попередні критично важливі

    std::string binaryMessage = message.toStdString(); // перетворення текстового повідомлення в бінарний фоормат
    for (char& c : binaryMessage) {
        std::bitset<8> binaryChar(c); // конвертація кожного символу в байт
        for (int i = 0; i < 8; ++i) {
            char bmpData;
            bmpFile.read(&bmpData, sizeof(char)); // читання байту зоюраження
            bmpData &= 0xFE; // зміна найменш важливого біту в байті
            bmpData |= binaryChar[i]; // на біт поточного символу який ми шифруємо
            bmpFile.seekp(-1, std::ios::cur); // назад на байт, щоб перезаписати новий байт
            bmpFile.write(&bmpData, sizeof(char)); // запис байту в файл
        }
    }

    bmpFile.close();
    QMessageBox::information(nullptr, "Інформація", "Повідомлення зашифровано в файл.");
    ui->lineEditMess->clear();
}

void MainWindow::on_pushButtonRead_clicked()
{
    QString bmpFilePath = ui->lineEditBMP->text();;
    std::ifstream bmpFile(bmpFilePath.toStdString(), std::ios::binary);

    if (!bmpFile.is_open()) {
        QMessageBox::critical(nullptr, "Помилка", "Неможливо відкрити файл!");
        return;
    }

    bmpFile.seekg(54); // перехід до 54-ого байту, бо попередні критично важливі

    std::string decryptedMessage;
    char bmpData;
    std::bitset<8> bitBuffer;
    int bitCount = 0;
    while (bmpFile.read(&bmpData, sizeof(char))) {
        bitBuffer[bitCount++] = bmpData & 1; // зберігання найменш важливого біта в бітовому буфері
        if (bitCount == 8) { // якщо зібрано 8 бітів
            decryptedMessage += char(bitBuffer.to_ulong()); // декодування і додавання символу до розшифрованого повідомлення
            bitBuffer.reset(); // очищення буфера
            bitCount = 0; // скидання лічильника
        }
    }

    bmpFile.close();

    QString res = QString::fromStdString(decryptedMessage);
    int size = ui->lineEditSize->text().toInt();
    res = res.left(size);
    ui->lineEditMess->setText(res);
    QMessageBox::information(nullptr, "Інформація", "Повідомлення розшифровано.");
}
