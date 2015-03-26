#ifndef CLIENTRECEIVE_H
#define CLIENTRECEIVE_H

#include <QObject>
#include <QThread>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include "mainwindow.h"
#include "encryption.h"

#define BUFSIZE 1024

class MainWindow;
class Encyrption;

class ClientReceive : public QObject
{
    Q_OBJECT

public:
    ClientReceive(Encryption *e);

    ~ClientReceive();

    bool setNetwork(char *host, char *port);

    int getSocket();

    void setReceiving(bool);

    QThread receiveThread;

private slots:
    void init();

signals:
    void textAdded(QString);

    void userAdded(QString);

    void userRemoved(int);

    void userChanged(QString, int);

private:
    int sd;
    bool receiving;
    struct hostent	*hp;
    struct sockaddr_in server; 
    Encryption *enc;

    void receive();
    void namechange(char *buf);
    void userRemove(char *buf);
};

#endif // CLIENTRECEIVE_H
