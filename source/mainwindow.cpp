/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: mainwindow.cpp - Controls the ui componenets
--
-- PROGRAM: Thowis Scallentire Chat
--
-- FUNCTIONS:
-- MainWindow(QWidget *parent = 0);
-- ~MainWindow();
-- void addtext(QString);
-- void adduser(QString);
-- void removeuser(int);
-- void changeuser(QString, int);
-- void on_sendButton_clicked();
-- void on_networkButton_clicked();
-- void on_setnameButton_clicked();
-- void on_disconnectButton_clicked();
-- void refreshUsers();
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
----------------------------------------------------------------------------------------------------------------------*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "encryption.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: MainWindow
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: MainWindow::MainWindow(QWidget *parent) :
--              QMainWindow(parent),
--              ui(new Ui::MainWindow)
--
-- PARAMETERS:	QWidget *parent		The parent window
--
-- RETURNS: void. - Constructor
--
-- NOTES:
-- Constructor sets up the connections between signals and slots in the ClientSend and ClientReceive
-- classes.
----------------------------------------------------------------------------------------------------------------------*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    enc = new Encryption(this);
    users = new QString[BUFSIZE];
    usersend = 0;
    connected = false;
    clientsend = new ClientSend(enc);
    clientreceive = new ClientReceive(enc);

    ui->disconnectButton->setEnabled(false);

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
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->plainTextEdit->appendPlainText(QString("192.168.0.4"));
    ui->plainTextEdit_2->appendPlainText(QString("5156"));

    ui->textEdit->installEventFilter(new EnterCatch(this));
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ~MainWindow
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: MainWindow::~MainWindow()
--
-- PARAMETERS:	void
--
-- RETURNS: void. - Destructor
--
-- NOTES:
-- Destructor deletes memory at the end.
----------------------------------------------------------------------------------------------------------------------*/
MainWindow::~MainWindow()
{
    delete ui;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: addtext
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void MainWindow::addtext(QString text)
--
-- PARAMETERS:	text - The text to be displayed to the screen
--
-- RETURNS: void
--
-- NOTES:
-- This function adds text to the window. If the text is a chat element, swap in the name.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::addtext(QString text)
{
    QString message;
    QByteArray ba;
    char *c;
    int val;

    ba = text.toLocal8Bit();

    c = ba.data();
    if(text == "Connect")
    {
        connected = true;
        clientsend->setSocket(clientreceive->getSocket());
        return;
    }

    if (c[0] == CHAT)
    {
        if (c[2] == '\0')
            return;
        memcpy(c, c+1, (text.size()-1)/sizeof(char));
        val = (int)c[0];
        message = users[val];
        memcpy(c, c+1, (text.size()-2)/sizeof(char));
        enc->decrypt(c);
        c[text.size()-2] = '\0';
        message += " :\t" + QString::fromLocal8Bit(c);
        text = message;
    }

    chatmodel->appendRow(new QStandardItem(text));
    ui->textEdit->clear();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: adduser
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void MainWindow::adduser(QString name)
--
-- PARAMETERS:	name - Name of user to be added
--
-- RETURNS: void
--
-- NOTES:
-- Adds a name to the end of the array.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::adduser(QString name)
{
    users[usersend] = name;
    usersend++;
    refreshUsers();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: removeuser
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void MainWindow::removeuser(int pos)
--
-- PARAMETERS:	pos - Position of the user in the array
--
-- RETURNS: void
--
-- NOTES:
-- Removes a user from a specified location in the array.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::removeuser(int pos)
{
    users[pos] = "\0";
    refreshUsers();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: changeuser
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void MainWindow::changeuser(QString name, int pos)
--
-- PARAMETERS:	name - New name for the user
--              pos - Position of the user in the array
--
-- RETURNS: void
--
-- NOTES:
-- Renames a user in the array.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::changeuser(QString name, int pos)
{
    users[pos] = name;
    refreshUsers();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: refreshUsers
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void MainWindow::refreshUsers()
--
-- PARAMETERS:	void
--
-- RETURNS: void
--
-- NOTES:
-- Refreshes the listview of users.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::refreshUsers()
{
    usermodel->clear();
    for (int i = 0; i < BUFSIZE; i++)
    {
        if (users[i] != "\0")
            usermodel->appendRow(new QStandardItem(users[i]));
    }
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: on_sendButton_clicked
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void MainWindow::on_sendButton_clicked()
--
-- PARAMETERS:	void
--
-- RETURNS: void
--
-- NOTES:
-- Executes when the send button is clicked. Calls the send message function. Adds the message to the
-- chat view.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::on_sendButton_clicked()
{
    QString text((char)CHAT);
    QString str = ui->textEdit->toPlainText();
    QByteArray ba;
    char *c;

    ba = str.toLocal8Bit();

    c = ba.data();
    enc->encryptt(c);
    text += QString::fromLatin1(c);
    chatmodel->appendRow(new QStandardItem(QString("You:\t") + ui->textEdit->toPlainText()));

    clientsend->sendtext(text);
    ui->textEdit->clear();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: on_networkButton_clicked
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void MainWindow::on_networkButton_clicked()
--
-- PARAMETERS:	void
--
-- RETURNS: void
--
-- NOTES:
-- Executes when the network button is clicked. Validates the network information.
----------------------------------------------------------------------------------------------------------------------*/
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

    clientreceive->moveToThread(&(clientreceive->receiveThread));
    ui->networkButton->setEnabled(false);
    ui->disconnectButton->setEnabled(true);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: on_setnameButton_clicked
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void MainWindow::on_setnameButton_clicked()
--
-- PARAMETERS:	void
--
-- RETURNS: void
--
-- NOTES:
-- Executes when the set name button is clicked. Sets the users name and sends it.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::on_setnameButton_clicked()
{
    QString str;

    name = ui->plainTextEdit_3->toPlainText();
    if (connected)
    {
        str = NAME_CHANGE;
        str += name;
        clientsend->sendtext(str);
    }
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: on_disconnectButton_clicked
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void MainWindow::on_disconnectButton_clicked()
--
-- PARAMETERS:	void
--
-- RETURNS: void
--
-- NOTES:
-- Executes when the disconnect button is clicked. Disconnects the socket.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::on_disconnectButton_clicked()
{

    connected = false;
    clientreceive->setReceiving(false);
    usersend = 0;
    ui->networkButton->setEnabled(true);
}

void MainWindow::on_pushButton_clicked()
{
    enc->exec();
}

