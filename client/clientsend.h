#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "mainwindow.h"

#define BUFSIZE 1024

class MainWindow;

class ClientSend : public QObject
{
    Q_OBJECT

public:
    ClientSend();

    ~ClientSend();

    bool setNetwork(char *host, char *port);

    void setSocket(int sd);

    void sendtext(QString);

signals:
    void textAdded(QString);

private:
    int sd;
    bool sending;
    struct hostent	*hp;
    struct sockaddr_in server;

};

#endif // CLIENT_H
