#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QHostAddress>

class QLabel;
class QPushButton;
class QUdpSocket;

class Receiver : public QObject
{
    Q_OBJECT

public:
    Receiver(QHostAddress groupAddress, uint16_t port);
    ~Receiver();

signals:
    void messageReceived(QByteArray message);

private slots:
    void processPendingDatagrams();

private:
    QLabel *statusLabel;
    QPushButton *quitButton;

    QUdpSocket *udpSocket = nullptr;
    QHostAddress groupAddress;
    uint16_t port;
};

#endif
