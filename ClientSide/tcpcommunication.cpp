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
            return QByteArray("Data didn't send");
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
            return QByteArray("Data didn't get");
        }
    }
    else
    {
        tcpSocket->close();
        tcpSocket->deleteLater();
        return QByteArray("Client didn't connect to server");
    }
    tcpSocket->close();
    tcpSocket->deleteLater();
    return sendData;
}
QMap<QString, QVariant> TcpCommunication::interface(QMap<QString, QVariant> sendDataMap)
{
    QString regularData;
    QString process = sendDataMap.value("process").toString();
    if(process == "getUsername")
    {
        regularData = QString("getUsername,'%1'").arg(sendDataMap.value("userID").toString());
    }
    else if (process == "controlPassword")
    {
        regularData = QString("controlPassword,%1,%2")
                .arg(sendDataMap.value("userID").toString())
                .arg(sendDataMap.value("password").toString());
    }
    QByteArray regularDataByteArray = regularData.toUtf8();

    regularDataByteArray = talkToServer(regularDataByteArray);
    if(regularDataByteArray == QByteArray("Data didn't send") || regularDataByteArray == QByteArray("Data didn't get") || regularDataByteArray == QByteArray("Client didn't connect to server"))
    {
        qDebug() << "Error";
        sendDataMap.clear();
        sendDataMap.insert("response", QString(regularDataByteArray));
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
            if(process == "getUsername")
            {
                sendDataMap.insert("response", "true");
                sendDataMap.insert("userID", jsonObject.value("userID").toInt());
                sendDataMap.insert("name", jsonObject.value("name").toString());
                sendDataMap.insert("surname", jsonObject.value("surname").toString());
            }
            else if (process == "controlPassword")
            {
                qDebug() << "true";
                sendDataMap.insert("response", "true");
                sendDataMap.insert("userID", jsonObject.value("userID").toInt());
                sendDataMap.insert("name", jsonObject.value("name").toString());
                sendDataMap.insert("surname", jsonObject.value("surname").toString());
                sendDataMap.insert("balance", jsonObject.value("balance").toDouble());
                // qDebug() << sendDataMap.value("balance").toString();
                sendDataMap.insert("Iban", jsonObject.value("Iban").toString());
                sendDataMap.insert("userType", jsonObject.value("userType").toInt());
            }
        }
        else
        {
            sendDataMap.insert("response", "false");
        }
        return sendDataMap;
    }

}
