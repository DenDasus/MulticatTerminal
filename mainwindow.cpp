#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ipControl = new IPCtrl(ui->frameIpControl);
    ipControl->setHostAddr(QHostAddress("228.0.1.1"));

    ui->textEdit->document()->setMaximumBlockCount(1000);

    connect(ui->BtnListen, SIGNAL(pressed()), this, SLOT(listenBtnPressed()));
    connect(ui->BtnStop, SIGNAL(pressed()), this, SLOT(stopBtnPressed()));
}

void MainWindow::newMessage(QByteArray message) {
    ui->textEdit->append(message.data());
}

void MainWindow::listenBtnPressed() {
    receiver = new Receiver(ipControl->getHostAddr(), ui->spinBoxPort->value());
    connect(receiver, SIGNAL(messageReceived(QByteArray)), this, SLOT(newMessage(QByteArray)));
    ui->BtnStop->setEnabled(true);
    ui->BtnListen->setEnabled(false);
    ipControl->setEnabled(false);
    ui->spinBoxPort->setEnabled(false);
}

void MainWindow::stopBtnPressed() {
    if(receiver != nullptr) {
        disconnect(receiver, SIGNAL(messageReceived(QByteArray)), this, SLOT(newMessage(QByteArray)));
        delete receiver;
    }
    ui->BtnStop->setEnabled(false);
    ui->BtnListen->setEnabled(true);
    ipControl->setEnabled(true);
    ui->spinBoxPort->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

