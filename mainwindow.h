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
    void portChangeDelay();
    void portGetCoords();
    void portGetDelay();


private:
    Ui::MainWindow *ui;
    QSerialPort *port;
    QString receivedMessage;

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    bool changeDelay(const QString& message);
    bool changeCoords(const QString& message);
};

#endif // MAINWINDOW_H
