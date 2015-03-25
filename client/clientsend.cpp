#include "clientsend.h"

#include <QMutex>

QMutex mutex;

ClientSend::ClientSend()
{

}

ClientSend::~ClientSend()
{

}

bool ClientSend::setNetwork(char *host, char *port)
{
    int p;

    if (port[0] < 48 || port[1] > 57)
        return false;

    if ((p = atoi(port)) < 1)
        return false;
    bzero((char *)&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(p);
    if ((hp = gethostbyname(host)) == NULL)
    {
        printf("Unknown server address\n");
        return false;
    }
    bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);

    return true;
}

void ClientSend::setSocket(int _sd)
{
    sd = _sd;
    sending = true;
}

void ClientSend::sendtext(QString text)
{
    QByteArray ba;
    char *c;
    ba = text.toLocal8Bit();
    c = ba.data();
    if (sending)
    {
        ::send(sd, c, text.size(), 0);
    }
    else
    {
        emit textAdded(QString("Server not connected"));
    }
}

