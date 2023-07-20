#ifndef TCPCOMMUNICATION_H
#define TCPCOMMUNICATION_H

#include <QObject>
#include <QVariant>
class TcpCommunication : public QObject
{
    Q_OBJECT
public:
    explicit TcpCommunication(QObject *parent = nullptr);
    QMap<QString, QVariant> interface(QMap<QString, QVariant> sendDataMap);
    QByteArray talkToServer(QByteArray);
signals:

private:
    QMap<QString, QVariant> sendDataMap;

public slots:
};

#endif // TCPCOMMUNICATION_H
