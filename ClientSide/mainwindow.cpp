// https://github.com/enderceliik
// Ender CELIK

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("Welcome!");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '1');
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '2');
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '3');
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '4');
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '5');
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '6');
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '7');
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '8');
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '9');
}

void MainWindow::on_pushButton_0_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '0');
}

void MainWindow::on_pushButton_red_clicked()
{
    ui->groupBox->hide();
}

void MainWindow::on_pushButton_green_clicked()
{
    ui->groupBox->show();
}

void MainWindow::on_pushButton_yellow_clicked()
{
    ui->lineEdit->clear();
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    lockInterface(false);
    getUserName(arg1);
    lockInterface(true);
}
void MainWindow::getUserName(QString userID)
{
    TcpCommunication* tcpCommunicationObj = new TcpCommunication();
    sendDataMap.insert("process", "getUserName");
    sendDataMap.insert("userID", QVariant(userID[4]));
    sendDataMap = tcpCommunicationObj->interface(sendDataMap);
    delete tcpCommunicationObj;
}

void MainWindow::lockInterface(bool state)
{
    ui->pushButton->setEnabled(state);
    ui->pushButton_0->setEnabled(state);
    ui->pushButton_2->setEnabled(state);
    ui->pushButton_3->setEnabled(state);
    ui->pushButton_4->setEnabled(state);
    ui->pushButton_5->setEnabled(state);
    ui->pushButton_6->setEnabled(state);
    ui->pushButton_7->setEnabled(state);
    ui->pushButton_8->setEnabled(state);
    ui->pushButton_9->setEnabled(state);
    ui->pushButton_green->setEnabled(state);
    ui->pushButton_red->setEnabled(state);
    ui->pushButton_yellow->setEnabled(state);
    ui->comboBox->setEnabled(state);
}

