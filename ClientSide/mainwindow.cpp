// https://github.com/enderceliik
// Ender CELIK

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox_2->hide();
    ui->groupBox_3->hide();
    ui->groupBox_4->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '1');
    ui->lineEdit_2->setText(ui->lineEdit_2->text() + '1');
    ui->lineEdit_3->setText(ui->lineEdit_3->text() + '1');
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '2');
    ui->lineEdit_2->setText(ui->lineEdit_2->text() + '2');
    ui->lineEdit_3->setText(ui->lineEdit_3->text() + '2');
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '3');
    ui->lineEdit_2->setText(ui->lineEdit_2->text() + '3');
    ui->lineEdit_3->setText(ui->lineEdit_3->text() + '3');
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '4');
    ui->lineEdit_2->setText(ui->lineEdit_2->text() + '4');
    ui->lineEdit_3->setText(ui->lineEdit_3->text() + '4');
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '5');
    ui->lineEdit_2->setText(ui->lineEdit_2->text() + '5');
    ui->lineEdit_3->setText(ui->lineEdit_3->text() + '5');
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '6');
    ui->lineEdit_2->setText(ui->lineEdit_2->text() + '6');
    ui->lineEdit_3->setText(ui->lineEdit_3->text() + '6');
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '7');
    ui->lineEdit_2->setText(ui->lineEdit_2->text() + '7');
    ui->lineEdit_3->setText(ui->lineEdit_3->text() + '7');
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '8');
    ui->lineEdit_2->setText(ui->lineEdit_2->text() + '8');
    ui->lineEdit_3->setText(ui->lineEdit_3->text() + '8');
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '9');
    ui->lineEdit_2->setText(ui->lineEdit_2->text() + '9');
    ui->lineEdit_3->setText(ui->lineEdit_3->text() + '9');
}

void MainWindow::on_pushButton_0_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + '0');
    ui->lineEdit_2->setText(ui->lineEdit_2->text() + '0');
    ui->lineEdit_3->setText(ui->lineEdit_3->text() + '0');
}

void MainWindow::on_pushButton_exit_clicked()
{
    sendDataMap.clear();
    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox->setEnabled(true);
    ui->label->setText("");
}

void MainWindow::on_pushButton_ok_clicked()
{
    if(sendDataMap.value("name").toString().isEmpty() || ui->lineEdit->text().length() < 4)
    {
        return;
    }
    else
    {
        lockInterface(false);
        controlPassword();
        lockInterface(true);
        ui->comboBox->setEnabled(false);
    }
}

void MainWindow::on_pushButton_cancel_clicked()
{
    QString newText = ui->lineEdit->text();
    newText.chop(1);
    ui->lineEdit->setText(newText);
}

void MainWindow::controlPassword()
{
    TcpCommunication* tcpCommunicationObj = new TcpCommunication();
    sendDataMap.insert("process", "controlPassword");
    sendDataMap.insert("password", ui->lineEdit->text());
    sendDataMap = tcpCommunicationObj->interface(sendDataMap);
    if(sendDataMap.value("response").toString() == "true")
    {
        ui->label_nameSurname->setText(sendDataMap.value("name").toString() + " " + sendDataMap.value("surname").toString());
        ui->label_balance->setText(sendDataMap.value("balance").toString() + " ₺");
        ui->label_iban->setText(sendDataMap.value("Iban").toString());

        ui->groupBox->hide();
        ui->groupBox_2->show();
    }
    else if (sendDataMap.value("response").toString() == "Data didn't send" || sendDataMap.value("response").toString() == "Data didn't get" || sendDataMap.value("response").toString() == "Client didn't connect to server")
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        QString errorMessage = QString("Your request could not be fulfilled: %1").arg(sendDataMap.value("response").toString());
        msgBox.setText(errorMessage);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    delete tcpCommunicationObj;
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    lockInterface(false);
    getUserName(arg1.toInt());
    lockInterface(true);
}

void MainWindow::getUserName(int userID)
{
    if(ui->comboBox->currentIndex() == -1)
    {
        return;
    }
    TcpCommunication* tcpCommunicationObj = new TcpCommunication();
    sendDataMap.insert("process", "getUsername");
    sendDataMap.insert("userID", userID);
    sendDataMap = tcpCommunicationObj->interface(sendDataMap);
    if(sendDataMap.value("response").toString() == "true")
    {
        ui->label->setText(sendDataMap.value("name").toString() + " " + sendDataMap.value("surname").toString() + " Welcome!\n Enter the password");
    }
    else if (sendDataMap.value("response").toString() == "Data didn't send" || sendDataMap.value("response").toString() == "Data didn't get" || sendDataMap.value("response").toString() == "Client didn't connect to server")
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        QString errorMessage = QString("Your request could not be fulfilled: %1").arg(sendDataMap.value("response").toString());
        msgBox.setText(errorMessage);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
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
    ui->pushButton_ok->setEnabled(state);
    ui->pushButton_exit->setEnabled(state);
    ui->pushButton_cancel->setEnabled(state);
    ui->comboBox->setEnabled(state);

}

void MainWindow::on_pushButton_exit_2_clicked()
{
    sendDataMap.clear();
    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox->setEnabled(true);
    ui->label->setText("");
    ui->groupBox_2->hide();
    ui->groupBox->show();
}

void MainWindow::on_pushButton_cancel_2_clicked()
{
    ui->lineEdit_2->clear();
    ui->groupBox_3->hide();
    ui->groupBox_2->show();
}

void MainWindow::on_pushButton_withdrawal_clicked()
{
    sendDataMap.insert("process", "infoFetch");
    TcpCommunication* tcpCommunication = new TcpCommunication();
    sendDataMap = tcpCommunication->interface(sendDataMap);
    currentPage = "withDrawalPage";
    ui->label_6->setText("Please select the \n amount you wish to\nwithdraw or enter it\nusing the keypad");
    ui->label_balance_2->setText(sendDataMap.value("balance").toString() + " ₺");
    ui->label_iban_2->setText(sendDataMap.value("Iban").toString());
    ui->lineEdit_2->clear();
    ui->groupBox_2->hide();
    ui->groupBox_3->show();
}

void MainWindow::on_pushButton_deposit_clicked()
{
    sendDataMap.insert("process", "infoFetch");
    TcpCommunication* tcpCommunication = new TcpCommunication();
    sendDataMap = tcpCommunication->interface(sendDataMap);
    currentPage = "depositPage";
    ui->label_6->setText("Please select the\namount you wish\nto deposit or enter it\nusing the keypad.");
    ui->label_iban_2->setText(sendDataMap.value("Iban").toString());
    ui->label_balance_2->setText(sendDataMap.value("balance").toString() + " ₺");
    ui->lineEdit_2->clear();
    ui->groupBox_2->hide();
    ui->groupBox_3->show();
}

void MainWindow::on_pushButton_transfer_clicked()
{
    currentPage = "moneyTransferPage";
    ui->lineEdit_3->clear();
    ui->groupBox_2->hide();
    ui->groupBox_4->show();
}

void MainWindow::on_pushButton_cancel_3_clicked()
{
    currentPage = "mainPage";
    ui->groupBox_4->hide();
    ui->groupBox_2->show();
}



void MainWindow::on_pushButton_10_clicked()
{
    ui->lineEdit_2->setText("10");
}

void MainWindow::on_pushButton_20_clicked()
{
    ui->lineEdit_2->setText("20");
}

void MainWindow::on_pushButton_50_clicked()
{
    ui->lineEdit_2->setText("50");
}

void MainWindow::on_pushButton_100_clicked()
{
    ui->lineEdit_2->setText("100");
}

void MainWindow::on_pushButton_200_clicked()
{
    ui->lineEdit_2->setText("200");
}


void MainWindow::on_pushButton_ok_3_clicked()
{
    qDebug() << sendDataMap.value("Iban");
    qDebug() << ui->lineEdit_3->text();
    if(ui->lineEdit_3->text().isEmpty() || sendDataMap.value("Iban").toString() == "TR "+ui->lineEdit_3->text()) return;
    ui->lineEdit_3->setEnabled(false);
    ui->pushButton_ok_3->setEnabled(false);
    TcpCommunication* tcpCommunicationObj = new TcpCommunication();
    sendDataMap.insert("process", "ibanControl");
    sendDataMap.insert("receiverIban", "TR " + ui->lineEdit_3->text());
    sendDataMap = tcpCommunicationObj->interface(sendDataMap);
    if(sendDataMap.value("response").toString() == "true")
    {
        currentPage = "moneyTransferPage";
        ui->label_6->setText("Please select the\namount you wish\nto send or enter it\nusing the keypad.");
        ui->label_balance_2->setText(sendDataMap.value("balance").toString() + " ₺");
        ui->label_iban_2->setText(sendDataMap.value("name").toString()+ " " + sendDataMap.value("surname").toString());
        ui->lineEdit_2->clear();
        ui->groupBox_4->hide();
        ui->groupBox_3->show();
    }
    else if (sendDataMap.value("response").toString() == "Data didn't send" || sendDataMap.value("response").toString() == "Data didn't get" || sendDataMap.value("response").toString() == "Client didn't connect to server")
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        QString errorMessage = QString("Your request could not be fulfilled: %1").arg(sendDataMap.value("response").toString());
        msgBox.setText(errorMessage);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    delete tcpCommunicationObj;
    ui->lineEdit_3->setEnabled(true);
    ui->pushButton_ok_3->setEnabled(true);
}

void MainWindow::on_pushButton_ok_2_clicked()
{
    if(currentPage == "withDrawalPage" || currentPage == "moneyTransferPage")
    {
        if(ui->lineEdit_2->text().toInt() == 0 || ui->lineEdit_2->text().toInt() > sendDataMap.value("balance").toInt())
        {
            qDebug("Uygun degerler giriniz!");
            return;
        }
    }

    TcpCommunication* tcpCommunicationObj = new TcpCommunication();
    sendDataMap.insert("process", currentPage);
    sendDataMap.insert("moneyAmount", ui->lineEdit_2->text().toInt());
    sendDataMap = tcpCommunicationObj->interface(sendDataMap);
    if(sendDataMap.value("response").toString() == "true")
    {
        currentPage = "mainPage";
        ui->label_balance->setText(sendDataMap.value("balance").toString() + " ₺");
        ui->label_iban->setText(sendDataMap.value("Iban").toString());
        ui->groupBox_3->hide();
        ui->groupBox_2->show();
    }
    else if (sendDataMap.value("response").toString() == "Data didn't send" || sendDataMap.value("response").toString() == "Data didn't get" || sendDataMap.value("response").toString() == "Client didn't connect to server")
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        QString errorMessage = QString("Your request could not be fulfilled: %1").arg(sendDataMap.value("response").toString());
        msgBox.setText(errorMessage);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
}

