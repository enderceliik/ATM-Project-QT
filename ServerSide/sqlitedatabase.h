#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H
#include <QtSql>
#include <QSqlQuery>
#include <QDebug>
#include <QString>

class SQLiteDatabase
{
public:
    SQLiteDatabase();
    ~SQLiteDatabase();
    void defineDatabse();
    QSqlQuery getUsername(int userID);
    QSqlQuery controlPassword(int userID);
    QSqlQuery infoFetch(int userID);
    void moneyProcessAdd(int moneyAmount, QString Iban);
    void moneyProcessSubtract(int moneyAmount, QString Iban);
    QSqlQuery ibanControl(QString receiverIban);
    QString queryString;


private:
    static QSqlDatabase sqliteDatabase;

};

#endif // SQLITEDATABASE_H
