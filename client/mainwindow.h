#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <vector>
#include "clientsend.h"
#include "clientreceive.h"
#include "shared.h"


class ClientReceive;
class ClientSend;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ClientSend *clientsend;
    ClientReceive *clientreceive;

    QString name;

private slots:
    void addtext(QString);

    void adduser(QString);

    void removeuser(int);

    void changeuser(QString, int);

    void on_sendButton_clicked();

    void on_networkButton_clicked();

    void on_setnameButton_clicked();

    void on_disconnectButton_clicked();

signals:
    void send(QString);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *chatmodel;
    QStandardItemModel *usermodel;
    QString *users;
    int usersend;
    bool connected;
    void refreshUsers();
};

#endif // MAINWINDOW_H
