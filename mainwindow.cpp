#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>
#include <QString>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    port = new QSerialPort();
    port->setBaudRate(9600);

    ui->setupUi(this);
    ui->textBrowser->append("Hello, world!");

    connect(ui->comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(portChanged(QString)));
    connect(port, SIGNAL(readyRead()), this, SLOT(portReadyRead()));
    connect(ui->pushButton_Send, SIGNAL(clicked(bool)), this, SLOT(portWriteMessage()));
    connect(ui->pushButton_Go, SIGNAL(clicked(bool)), this, SLOT(portGo()));

    QList<QSerialPortInfo> avPorts =  QSerialPortInfo::availablePorts();

    for (auto iter = avPorts.begin(); iter != avPorts.end(); ++iter)
    {
        ui->comboBox->addItem(iter->portName());
//        if (QString::compare(iter->description(), "Arduino Uno", Qt::CaseSensitive) == 0)
//        {
//            emit ui->comboBox->currentTextChanged(iter->portName());
//        }
    }
}

MainWindow::~MainWindow()
{
    port->close();
    delete port;
    delete ui;
}

void MainWindow::portChanged(QString portName)
{
    if (port->isOpen())
        port->close();
    port->setPortName(portName);
    port->open(QIODevice::ReadWrite);
    ui->textBrowser->append("Serial port " + portName + " is opened in read/write mode");
}

void MainWindow::portReadyRead()
{
    Sleep(1000);
    int n = port->bytesAvailable();
    QString str(port->readAll());
    ui->textBrowser->append("Arduino answered: " + str);
}

void MainWindow::portWriteMessage()
{
    if (port->isOpen())
    {
        QString str = ui->lineEdit->text();
        ui->textBrowser->append("I said: " + str);
        ui->lineEdit->setText("");
        port->write(str.toLatin1().data(), str.toLatin1().size());
    }
    else
    {
        ui->textBrowser->append("The COM-port is closed. Please choose the correct COM-port.");
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if (key == Qt::Key_Enter && ui->lineEdit->isActiveWindow())
    {
        emit ui->pushButton_Send->clicked();
    }
}


void MainWindow::portGo()
{
    int x = ui->spinBox_CoordsX->value();
    int y = ui->spinBox_CoordsY->value();

    if (port->isOpen())
    {
        QString str = ui->lineEdit->text();
        ui->textBrowser->append("Arduino goes to new position!");
        port->write(str.toLatin1().data(), str.toLatin1().size());
    }
    else
    {
        ui->textBrowser->append("The COM-port is closed. Please choose the correct COM-port.");
    }
}











