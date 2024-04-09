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

template <typename T>
T MainWindow::findMostCommon(const QVector<T>& vector) {
    QMap<T, int> counter;
    for (const T& element : vector) {
        counter[element]++;
    }
    T mostCommon = 0;
    int maxCount = 0;
    for (auto it = counter.constBegin(); it != counter.constEnd(); ++it) {
        if (it.value() > maxCount) {
            maxCount = it.value();
            mostCommon = it.key();
        }
    }
    return mostCommon;
}

void MainWindow::on_pushButton_clicked()
{
    QString readFile = ui->lineEditRead->text();
    QString writeFile = ui->lineEditWrite->text();

    QMap<QString, double> frequencyMap = {
            {"a", 0.08167}, {"b", 0.01492}, {"c", 0.02782}, {"d", 0.04253}, {"e", 0.12702},
            {"f", 0.02228}, {"g", 0.02015}, {"h", 0.06094}, {"i", 0.06966}, {"j", 0.00153},
            {"k", 0.00772}, {"l", 0.04025}, {"m", 0.02406}, {"n", 0.06749}, {"o", 0.07507},
            {"p", 0.01929}, {"q", 0.00095}, {"r", 0.05987}, {"s", 0.06327}, {"t", 0.09056},
            {"u", 0.02758}, {"v", 0.00978}, {"w", 0.02360}, {"x", 0.00150}, {"y", 0.01974}, {"z", 0.00074}
        };

    QMap<QString, double> countMap = {
            {"a", 0}, {"b", 0}, {"c", 0}, {"d", 0}, {"e", 0},
            {"f", 0}, {"g", 0}, {"h", 0}, {"i", 0}, {"j", 0},
            {"k", 0}, {"l", 0}, {"m", 0}, {"n", 0}, {"o", 0},
            {"p", 0}, {"q", 0}, {"r", 0}, {"s", 0}, {"t", 0},
            {"u", 0}, {"v", 0}, {"w", 0}, {"x", 0}, {"y", 0}, {"z", 0}
        };

    double numOfSymbols = 0;

    QFile file(readFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Помилка", "Не вдалося відкрити файл.");
        return;
    }
    QTextStream in1(&file);
    while (!in1.atEnd()) {
        QChar character;
        in1 >> character;
        if (!character.isNull() && character.isLetter()) {
            QString letter = QString(character);
            if (countMap.contains(letter)) {
                countMap[letter]++;
                numOfSymbols++;
            }
        }
    }
    file.close();

    for (auto& key : countMap.keys()) {
        countMap[key] /= numOfSymbols;
    }

    QVector<QString> sortedFrequency;
    while (!frequencyMap.isEmpty()) {
        QString maxKey;
        double maxValue = -1.0;

        for (auto it = frequencyMap.constBegin(); it != frequencyMap.constEnd(); ++it) {
            if (it.value() > maxValue) {
                maxKey = it.key();
                maxValue = it.value();
            }
        }

        sortedFrequency.append(maxKey);
        frequencyMap.remove(maxKey);
    }

    QVector<QString> sortedCount;
    while (!countMap.isEmpty()) {
        QString maxKey;
        double maxValue = -1.0;

        for (auto it = countMap.constBegin(); it != countMap.constEnd(); ++it) {
            if (it.value() > maxValue) {
                maxKey = it.key();
                maxValue = it.value();
            }
        }

        sortedCount.append(maxKey);
        countMap.remove(maxKey);
    }

    QVector<QString> alphabet = {
        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
        "k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
        "u", "v", "w", "x", "y", "z"
    };

    QVector<int> offset;
    for (int i = 0; i < sortedCount.size(); i++) {
        QString encrLetter = sortedCount[i];
        QString clearLetter = sortedFrequency[i];

        int encrIndex = alphabet.indexOf(encrLetter);
        int clearIndex = alphabet.indexOf(clearLetter);

        int diff = encrIndex - clearIndex;
        if (diff < 0)
            diff += 26;

        offset.append(diff);
    }

    int mostCommon = findMostCommon(offset);

    QFile inputFile(readFile);
    QFile outputFile(writeFile);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Помилка", "Не вдалося відкрити файл.");
        return;
    }
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Помилка", "Не вдалося відкрити файл.");
        return;
    }
    QTextStream in(&inputFile);
    QTextStream out(&outputFile);

    while (!in.atEnd()) {
        QChar character;
        in >> character;
        QString letter = QString(character);
        if (sortedCount.contains(letter)) {
            int ind = alphabet.indexOf(letter);
            ind -= mostCommon;
            if (ind < 0)
                ind += 26;
            out << alphabet[ind];
        } else {
            out << letter;
        }
    }

    inputFile.close();
    outputFile.close();
    QMessageBox::information(this, "Інформація", "Файл розшифровано.");
}
