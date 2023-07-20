#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);

signals:

private:
    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket;

private slots:
    void newConnection();
    void onReadyRead();
public slots:
};

#endif // TCPSERVER_H
