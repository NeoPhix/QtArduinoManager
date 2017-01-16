#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>
#include <QKeyEvent>

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
    void portGo();

private:
    Ui::MainWindow *ui;
    QSerialPort *port;
    QString *receivedMessage;

protected:
    virtual void keyPressEvent(QKeyEvent *event);
//    char buf[BUF_SIZE];
};

#endif // MAINWINDOW_H
