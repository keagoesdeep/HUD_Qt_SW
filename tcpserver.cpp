#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    qServer = new QTcpServer(this);
    // whenever a user connects, it will emit signal
    connect(qServer, SIGNAL(newConnection()), this, SLOT(newConnection()));

}

bool TcpServer::startServer(){
    if(qServer->listen(QHostAddress::Any, 8008))
    {
        Q_EMIT msg("server started");
        return true;
    }
    else
    {
        Q_EMIT msg("server failed");
        return false;
    }
}

void TcpServer::msgReceived()
{
    while (socket->bytesAvailable())
    {
        QString switchResult = "$$DEFAULT$$";
        QString receivedMessage = socket->readAll();

       if(receivedMessage.length() > 2 && receivedMessage.left(1)=="E"){
            int errorNumber = receivedMessage.right(receivedMessage.length() - 2).toInt();
            switch (errorNumber){
                case 0: switchResult = "everything fine"; break;
                case 1: switchResult = "gripper issue"; break;
                case 2: switchResult = "couldn,t connect"; break;
                case 3: switchResult = "invalid message"; break;
                case 4: switchResult = "couldn,t connect to LB"; break;
                case 5: switchResult = "leveling finished"; break;
                case 6: switchResult = "#"; break;
            }
        }
        else// TRYT
            if(receivedMessage.length() > 3 && receivedMessage.startsWith("TR")) {
                switchResult = receivedMessage;
            }
        else
            receivedMessage = "wat iz dis";
        Q_EMIT msg(switchResult);
    }
}

void TcpServer::newConnection()
{
    socket = qServer->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(msgReceived()));
    hasClient = true;
    Q_EMIT msg("S: a new TCP client has connected");
}
