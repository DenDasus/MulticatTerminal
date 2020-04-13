#include "receiver.h"

#include <QtNetwork>
#include <QUdpSocket>

#include "receiver.h"

Receiver::Receiver(QHostAddress groupAddress, uint16_t port)
{
    this->port = port;
    this->groupAddress = groupAddress;

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress(QHostAddress::AnyIPv4), port);
    udpSocket->joinMulticastGroup(groupAddress);

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

void Receiver::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());

        emit messageReceived(datagram);
    }
}

Receiver::~Receiver() {
    if(udpSocket) {
        udpSocket->leaveMulticastGroup(groupAddress);
        udpSocket->close();
        delete udpSocket;
    }
}
