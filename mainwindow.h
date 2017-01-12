#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>

//#define BUF_SIZE 256

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void portChanged(QString portName);
    void portReadyRead();
    void portWriteMessage();

private:
    Ui::MainWindow *ui;
    QSerialPort *port;
//    char buf[BUF_SIZE];
};

#endif // MAINWINDOW_H
