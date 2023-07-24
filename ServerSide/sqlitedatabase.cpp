#include "sqlitedatabase.h"
QSqlDatabase SQLiteDatabase::sqliteDatabase;
SQLiteDatabase::SQLiteDatabase()
{
    if(!sqliteDatabase.isValid())
    {
        sqliteDatabase = QSqlDatabase::addDatabase("QSQLITE");
        sqliteDatabase.setDatabaseName("AtmProjectSQLiteDatabase.db");
        if(sqliteDatabase.open())
        {
            qDebug() << "The database could not opened!";
        }

    }
}
SQLiteDatabase::~SQLiteDatabase()
{
    sqliteDatabase.close();
}

void SQLiteDatabase::defineDatabse()
{
    if(!sqliteDatabase.open())
    {    
        sqliteDatabase.open();
    }
    QSqlQuery query(sqliteDatabase);
    query.prepare("CREATE TABLE users ("
                  "userID INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "password INT,"
                  "name VARCHAR(50),"
                  "surname VARCHAR(50),"
                  "balance INT,"
                  "Iban VARCHAR(26),"
                  "userType INT"
                  ");");
    if(query.exec())
    {
        qDebug() << "users table CREATED succesfully!";
    }
    queryString = QString("INSERT INTO users (password, "
                              "name, "
                              "surname, "
                              "balance, "
                              "Iban, "
                              "userType) "
                              "values (%1, '%2', '%3', %4, '%5', %6);")
                          .arg(1111)
                          .arg("Ender")
                          .arg("Çelik")
                          .arg(19500)
                          .arg("TR 29296161")
                          .arg(0);
        query.prepare(queryString);
        if(query.exec())
        {
            qDebug() << "users table INSERT succesfully!";
        }
        queryString = QString("INSERT INTO users (password, "
                                  "name, "
                                  "surname, "
                                  "balance, "
                                  "Iban, "
                                  "userType) "
                                  "values (%1, '%2', '%3', %4, '%5', %6);")
                              .arg(1234)
                              .arg("Ahmet")
                              .arg("Demir")
                              .arg(18000)
                              .arg("TR 38383838")
                              .arg(0);
            query.prepare(queryString);
            if(query.exec())
            {
                qDebug() << "users table INSERT succesfully!";
            }
}

QSqlQuery SQLiteDatabase::getUsername(int userID)
{
    if(!sqliteDatabase.isOpen())
    {
        sqliteDatabase.open();
    }
    QSqlQuery query(sqliteDatabase);
    queryString = QString("SELECT userID, name, surname from USERS where userID = %1").arg(userID);
    query.prepare(queryString);
    query.exec();
    query.next();
    return query;
}

QSqlQuery SQLiteDatabase::controlPassword(int userID)
{
    if(!sqliteDatabase.isOpen())
    {
        sqliteDatabase.open();
    }
    QSqlQuery query(sqliteDatabase);
    queryString = QString("SELECT password from USERS where userID = %1").arg(userID);
    query.prepare(queryString);
    query.exec();
    query.next();
    return query;
}

QSqlQuery SQLiteDatabase::infoFetch(int userID)
{
    if(!sqliteDatabase.open())
    {
        sqliteDatabase.open();
    }
    QSqlQuery query(sqliteDatabase);
    queryString = QString("SELECT userID, name, surname, balance, Iban, userType FROM users WHERE userID = %1").arg(userID);
    query.prepare(queryString);
    query.exec();
    query.next();
    return query;
}

void SQLiteDatabase::moneyProcessAdd(int moneyAmount, QString Iban)
{
    if(!sqliteDatabase.open()) sqliteDatabase.open();
    QSqlQuery query(sqliteDatabase);
    queryString  = QString("UPDATE users SET balance = balance + %1 where Iban = '%2';").arg(moneyAmount).arg(Iban);
    query.prepare(queryString);
    query.exec();
}

void SQLiteDatabase::moneyProcessSubtract(int moneyAmount, QString Iban)
{
    if(!sqliteDatabase.open()) sqliteDatabase.open();
    QSqlQuery query(sqliteDatabase);
    queryString = QString("UPDATE users SET balance = balance - %1 where Iban = '%2';").arg(moneyAmount).arg(Iban);
    query.prepare(queryString);
    query.exec();
}

QSqlQuery SQLiteDatabase::ibanControl(QString receiverIban)
{
    if(!sqliteDatabase.isOpen()) sqliteDatabase.open();
    QSqlQuery query(sqliteDatabase);
    queryString = QString("SELECT name, surname FROM users where Iban = '%1';").arg(receiverIban);
    query.prepare(queryString);
    query.exec();
    query.next();
    return query;
}
