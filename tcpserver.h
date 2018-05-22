#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QtCore/QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include <QThread>


class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);

public Q_SLOTS:
    void newConnection();
    void msgReceived();
    bool startServer();

Q_SIGNALS:
    void msg(QString);

public:
    QTcpSocket *socket;
    bool hasClient = false;

private:
    QTcpServer *qServer;
};

#endif // TCPSERVER_H
