#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tcpcommunication.h>
#include <QVariant>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_0_clicked();
    void on_pushButton_ok_clicked();
    void on_pushButton_exit_clicked();
    void on_pushButton_cancel_clicked();
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_pushButton_withdrawal_clicked();
    void on_pushButton_deposit_clicked();
    void on_pushButton_transfer_clicked();
    void on_pushButton_exit_2_clicked();
    void on_pushButton_cancel_2_clicked();
    void on_pushButton_cancel_3_clicked();
    void on_pushButton_ok_3_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_50_clicked();
    void on_pushButton_100_clicked();
    void on_pushButton_200_clicked();
    void on_pushButton_ok_2_clicked();
    void moneyProcessFunc();

private:
    Ui::MainWindow *ui;
    void getUserName(QString userID);
    void controlPassword();
    QMap<QString, QVariant> sendDataMap;
    void lockInterface(bool state);
    QString currentPage;
};

#endif // MAINWINDOW_H
