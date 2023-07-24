// https://github.com/enderceliik
// Ender CELIK

#include "tcpserver.h"
#include "sqlitedatabase.h"

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
    QJsonObject jsonObject;
    QStringList receiveDataList;
    if(receiveData.contains("getUsername"))
    {
        receiveDataList = receiveData.split(',');
        receiveData = receiveDataList[1];
        SQLiteDatabase* db = new SQLiteDatabase();
        QString logFileName = "log.ini";
        QFile logFile(logFileName);
        if (logFile.exists())
        {
            qDebug() << "Database already created!";
        }
        else
        {
            qDebug() << "Log file created!";

            if (logFile.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream stream(&logFile);
                stream << "Log process started: " << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << endl;
                logFile.close();

                db->defineDatabse();
            }
            else
            {
                qWarning() << "Log file didn't created!";
            }
        }
        QSqlQuery query = db->getUsername(receiveData.toInt());
        delete db;
        if(!query.value(0).toString().isEmpty() && !query.value(1).toString().isEmpty() && !query.value(2).toString().isEmpty())
        {

            jsonObject["response"] = "true";
            jsonObject["userID"] = query.value(0).toInt();
            jsonObject["name"] = query.value(1).toString();
            jsonObject["surname"] = query.value(2).toString();
        }
        else jsonObject["response"] = "false";
    }
    else if (receiveData.contains("controlPassword"))
    {
        receiveDataList = receiveData.split(',');
        QString userID = receiveDataList[1];
        QString password = receiveDataList[2];
        SQLiteDatabase* db = new SQLiteDatabase();
        QSqlQuery query = db->controlPassword(userID.toInt());
        delete db;
        if(password == query.value(0).toString())
        {
            SQLiteDatabase* db = new SQLiteDatabase();
            QString userID = receiveDataList[1];
            QSqlQuery query = db->infoFetch(userID.toInt());
            delete db;
            jsonObject["response"] = "true";
            jsonObject["userID"] = query.value(0).toInt();
            jsonObject["name"] = query.value(1).toString();
            jsonObject["surname"] = query.value(2).toString();
            jsonObject["balance"] = query.value(3).toInt();
            jsonObject["Iban"] = query.value(4).toString();
            jsonObject["userType"] = query.value(5).toInt();
        }
        else
        {
            jsonObject["response"] = "false";
        }
    }
    else if (receiveData.contains("ibanControl"))
    {
        receiveDataList = receiveData.split(',');
        QString receiverIban = receiveDataList[1];
        SQLiteDatabase* db = new SQLiteDatabase();
        QSqlQuery query = db->ibanControl(receiverIban);
        if(query.value(0).toString().isEmpty() || query.value(0).toString().isEmpty())
        {
            jsonObject["response"] = "false";
        }
        else
        {
            jsonObject["response"] = "true";
            jsonObject["name"] = query.value(0).toString();
            jsonObject["surname"] = query.value(1).toString();
        }

    }
    else if (receiveData.contains("depositPage") || receiveData.contains("withDrawalPage") || receiveData.contains("moneyTransferPage"))
    {
        receiveDataList = receiveData.split(',');
        QString process = receiveDataList[0];
        QString moneyAmount = receiveDataList[1];
        QString Iban = receiveDataList[2];
        QString userID = receiveDataList[3];
        SQLiteDatabase* db = new SQLiteDatabase();
        if(process == "depositPage")
        {
            db->moneyProcessAdd(moneyAmount.toInt(), Iban);
        }
        else if (process == "withDrawalPage")
        {
            db->moneyProcessSubtract(moneyAmount.toInt(), Iban);
        }
        else if (process == "moneyTransferPage")
        {
            QString receiverIban = receiveDataList[4];
            db->moneyProcessAdd(moneyAmount.toInt(),receiverIban);
            db->moneyProcessSubtract(moneyAmount.toInt(), Iban);
        }

        QSqlQuery query = db->infoFetch(userID.toInt());
        delete db;
        jsonObject["response"] = "true";
        jsonObject["userID"] = query.value(0).toInt();
        jsonObject["name"] = query.value(1).toString();
        jsonObject["surname"] = query.value(2).toString();
        jsonObject["balance"] = query.value(3).toInt();
        jsonObject["Iban"] = query.value(4).toString();
        jsonObject["userType"] = query.value(5).toInt();
    }
    else if (receiveData.contains("infoFetch"))
    {
        receiveDataList = receiveData.split(',');
        QString userID = receiveDataList[1];
        SQLiteDatabase* db = new SQLiteDatabase();
        QSqlQuery query = db->infoFetch(userID.toInt());
        delete db;
        jsonObject["response"] = "true";
        jsonObject["userID"] = query.value(0).toInt();
        jsonObject["name"] = query.value(1).toString();
        jsonObject["surname"] = query.value(2).toString();
        jsonObject["balance"] = query.value(3).toInt();
        jsonObject["Iban"] = query.value(4).toString();
        jsonObject["userType"] = query.value(5).toInt();
    }
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
