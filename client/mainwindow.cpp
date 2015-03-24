#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    users = new QString[BUFSIZE];
    usersend = 0;
    connected = false;

    ui->disconnectButton->setEnabled(false);

    clientsend = new ClientSend();
    clientreceive = new ClientReceive();

    // ClientSend Signals
    connect(clientsend, SIGNAL(textAdded(QString)), SLOT(addtext(QString)));

    // ClientReceive Signals
    connect(clientreceive, SIGNAL(textAdded(QString)), SLOT(addtext(QString)));

    connect(clientreceive, SIGNAL(userAdded(QString)), SLOT(adduser(QString)));

    connect(clientreceive, SIGNAL(userRemoved(int)), SLOT(removeuser(int)));

    connect(clientreceive, SIGNAL(userChanged(QString, int)), SLOT(changeuser(QString, int)));

    chatmodel = new QStandardItemModel();
    usermodel = new QStandardItemModel();
    ui->listView->setModel(chatmodel);
    ui->listView_2->setModel(usermodel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addtext(QString text)
{
    if(text == "Connect")
    {
        connected = true;
        clientsend->setSocket(clientreceive->getSocket());
        return;
    }
    chatmodel->appendRow(new QStandardItem(text));
    ui->textEdit->clear();
}

void MainWindow::adduser(QString name)
{
    users[usersend++] = name;
    refreshUsers();
}

void MainWindow::removeuser(int pos)
{
    users[pos] = "\0";
    refreshUsers();
}

void MainWindow::changeuser(QString name, int pos)
{
    users[pos] = name;
    refreshUsers();
}

void MainWindow::refreshUsers()
{
    usermodel->clear();
    for (int i = 0; i < BUFSIZE; i++)
    {
        if (users[i] != "\0")
            usermodel->appendRow(new QStandardItem(users[i]));
    }
}


void MainWindow::on_sendButton_clicked()
{
    QString text = CHAT + name + ui->textEdit->toPlainText();
    chatmodel->appendRow(new QStandardItem(QString("You:\t") + ui->textEdit->toPlainText()));

    clientsend->sendtext(text);
    ui->textEdit->clear();
}

void MainWindow::on_networkButton_clicked()
{
    QString ip, port;
    QByteArray ba, ba1;
    char *c, *c1;
    ip = ui->plainTextEdit->toPlainText();
    port = ui->plainTextEdit_2->toPlainText();

    ba = ip.toLocal8Bit();
    ba1 = port.toLocal8Bit();

    c = ba.data();
    c1 = ba1.data();
    if (!(clientsend->setNetwork(c, c1)) || !(clientreceive->setNetwork(c, c1)))
    {
        chatmodel->appendRow(new QStandardItem(QString("Invalid Network Info") ));
    }
    ui->networkButton->setEnabled(false);
    ui->disconnectButton->setEnabled(true);
}

void MainWindow::on_setnameButton_clicked()
{
    QString str;
    name = ui->plainTextEdit_3->toPlainText();
    if (connected)
    {
        str = NAME_CHANGE + " ";
        str += name;
        clientsend->sendtext(str);
    }
}

void MainWindow::on_disconnectButton_clicked()
{
    ui->networkButton->setEnabled(true);
    connected = false;;
    clientreceive->setReceiving(false);
}
