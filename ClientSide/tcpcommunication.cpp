// https://github.com/enderceliik
// Ender CELIK

#include "tcpcommunication.h"
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>

TcpCommunication::TcpCommunication(QObject *parent) : QObject(parent)
{

}

QByteArray TcpCommunication::talkToServer(QByteArray sendData)
{
    QTcpSocket* tcpSocket = new QTcpSocket();
    tcpSocket->connectToHost("127.0.0.1", 9999);
    if(tcpSocket->waitForConnected(3000))
    {
        qDebug() << "Server connection successfull!";
        tcpSocket->write(sendData);
        if(tcpSocket->waitForBytesWritten(2000))
        {
            qDebug() << "Data send Success!";
        }
        else
        {
            tcpSocket->close();
            tcpSocket->deleteLater();
            return QByteArray("didn't send");
        }
        if(tcpSocket->waitForReadyRead(3000))
        {
            sendData.clear();
            sendData = tcpSocket->readAll();
        }
        else
        {
            tcpSocket->close();
            tcpSocket->deleteLater();
            return QByteArray("didn't get");
        }
    }
    else
    {
        tcpSocket->close();
        tcpSocket->deleteLater();
        return QByteArray("didn't connect to server");
    }
    tcpSocket->close();
    tcpSocket->deleteLater();
    return sendData;
}
QMap<QString, QVariant> TcpCommunication::interface(QMap<QString, QVariant> sendDataMap)
{
    QString regularData;
    QString process = sendDataMap.value("process").toString();
    QMap <QString, int> commands = {
            {"getUserName", 1},
            {"stop", 2},
            {"pause", 3},
            {"resume", 4}
        };
        int commandCode = commands[process];
        switch (commandCode) {
            case 1:
                qDebug() << "getUserName";
                regularData = QString("getUsername:'%1'").arg(sendDataMap.value("userID").toString());
                QByteArray regularDataByteArray = regularData.toUtf8();

                regularDataByteArray = talkToServer(regularDataByteArray);
                if(regularDataByteArray == QByteArray("didn't connect to server"))
                {
                    qDebug() << "Error";
                    sendDataMap.clear();
                    sendDataMap.insert("response", "error");
                    return sendDataMap;
                }
                QJsonParseError jsonParseError;
                QJsonDocument jsonDocument = QJsonDocument::fromJson(regularDataByteArray,&jsonParseError);

                if(jsonParseError.error != QJsonParseError::NoError)
                {
                    qDebug() << "JSON Parse error: " << jsonParseError.errorString();
                    sendDataMap.clear();
                    sendDataMap.insert("response", "error");
                    return sendDataMap;
                }
                if(jsonDocument.isObject())
                {
                    QJsonObject jsonObject = jsonDocument.object();
                    sendDataMap.clear();
                    if(jsonObject.value("response").toString() == "true")
                    {

                        sendDataMap.insert("response", "true");
                        sendDataMap.insert("userID", jsonObject.value("userID").toInt());
                        sendDataMap.insert("name", jsonObject.value("name").toString());
                        sendDataMap.insert("surname", jsonObject.value("surname").toString());
                        sendDataMap.insert("balance", jsonObject.value("balance").toDouble());
                        sendDataMap.insert("Iban", jsonObject.value("Iban").toString());
                        sendDataMap.insert("userType", jsonObject.value("userType").toInt());
                    }
                    else
                    {
                        sendDataMap.insert("response", "false");
                    }
                    return sendDataMap;
                }
                break;
        }

}
