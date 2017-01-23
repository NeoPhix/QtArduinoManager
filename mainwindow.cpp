#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>
#include <QString>
#include <QTime>

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
    connect(ui->pushButton_ChangeDelay, SIGNAL(clicked(bool)), this, SLOT(portChangeDelay()));
    connect(ui->pushButton_GetCoords, SIGNAL(clicked(bool)), this, SLOT(portGetCoords()));
    connect(ui->pushButton_GetDelay, SIGNAL(clicked(bool)), this, SLOT(portGetDelay()));

    QList<QSerialPortInfo> avPorts =  QSerialPortInfo::availablePorts();

    for (auto iter = avPorts.begin(); iter != avPorts.end(); ++iter)
    {
        ui->comboBox->addItem(iter->portName());
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
    QString str(port->readAll());
    receivedMessage += str;
    if (*(str.end()-1) == '\n')
    {
        *(receivedMessage.end()-1) = ' ';
        *(receivedMessage.end()-2) = ' ';
        switch ((receivedMessage.begin()->toLatin1()))
        {
        case 'P':    //Current position is returned
            changeCoords(receivedMessage);
            *(receivedMessage.begin()) = ':';
            *(receivedMessage.begin()+1) = ' ';
            ui->textBrowser->append("Current position" + receivedMessage);
            break;
        case 'C':    //Current delay is returned
            changeDelay(receivedMessage);
            *(receivedMessage.begin()) = ':';
            *(receivedMessage.begin()+1) = ' ';
            ui->textBrowser->append("Current delay" + receivedMessage);
            break;
        default:
            ui->textBrowser->append(receivedMessage);
            break;
        }
        receivedMessage.clear();
    }
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
        QString str = "G " + QString::number(x) + " " + QString::number(y) + "!";
        ui->textBrowser->append(str);
        port->write(str.toLatin1().data(), str.toLatin1().size());
    }
    else
    {
        ui->textBrowser->append("The COM-port is closed. Please choose the correct COM-port.");
    }
}

void MainWindow::portChangeDelay()
{
    int delay = ui->spinBox_Delay->value();

    if (port->isOpen())
    {
        QString str = "D " + QString::number(delay) + "!";
        ui->textBrowser->append(str);
        port->write(str.toLatin1().data(), str.toLatin1().size());
    }
    else
    {
        ui->textBrowser->append("The COM-port is closed. Please choose the correct COM-port.");
    }
}

void MainWindow::portGetCoords()
{
    if (port->isOpen())
    {
        QString str = "P!";
        ui->textBrowser->append(str);
        port->write(str.toLatin1().data(), str.toLatin1().size());
    }
    else
    {
        ui->textBrowser->append("The COM-port is closed. Please choose the correct COM-port.");
    }
}



void MainWindow::portGetDelay()
{
    if (port->isOpen())
    {
        QString str = "C!";
        ui->textBrowser->append(str);
        port->write(str.toLatin1().data(), str.toLatin1().size());
    }
    else
    {
        ui->textBrowser->append("The COM-port is closed. Please choose the correct COM-port.");
    }
}

void MainWindow::changeDelay(const QString& message)
{

}

void MainWindow::changeCoords(const QString& message)
{

}













