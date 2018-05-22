#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class TcpServerThread : public QThread
{
    Q_OBJECT
public:
    explicit TcpServerThread(qintptr ID, QObject *parent = 0);

    void run();

Q_SIGNALS:
    void error(QTcpSocket::SocketError socketerror);

public Q_SLOTS:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};

#endif // TCPSERVERTHREAD_H
