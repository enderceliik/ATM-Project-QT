// https://github.com/enderceliik
// Ender CELIK

#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
    if(!tcpServer->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Server could not started!";
    } else
    {
        qDebug() << "Server started!";
    }
}

void TcpServer::newConnection()
{
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
}

void TcpServer::onReadyRead()
{
    tcpSocket = qobject_cast<QTcpSocket*>(sender());
    QString receiveData = QString(tcpSocket->readAll());
    if(receiveData.contains("getUsername"))
    {
        qDebug() << "sql query...";
        QJsonObject jsonObject;
        jsonObject["response"] = "true";
        jsonObject["userID"] = "61612929";
        QJsonDocument jsonDocument(jsonObject);
        QByteArray jsonDataByteArray = jsonDocument.toJson();
        tcpSocket->write(jsonDataByteArray);
        if(tcpSocket->waitForBytesWritten(2000))
        {
            qDebug() << "Data send to client";
        } else
        {
            qDebug() << "Data didn't send to client";
        }

    }


}
