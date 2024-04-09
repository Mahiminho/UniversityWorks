#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <bitset>
#include <QMessageBox>
#include <QRegExpValidator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonWrite_clicked();

    void on_pushButtonRead_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
