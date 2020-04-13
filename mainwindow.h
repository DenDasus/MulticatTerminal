#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ipctrl.h"
#include "receiver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Receiver* receiver = nullptr;
    IPCtrl* ipControl = nullptr;

private slots:
    void newMessage(QByteArray message);
    void listenBtnPressed();
    void stopBtnPressed();
};
#endif // MAINWINDOW_H
