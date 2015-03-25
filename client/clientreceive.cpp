#include "clientreceive.h"

ClientReceive::ClientReceive()
{
    moveToThread(&receiveThread);

    connect(&receiveThread, SIGNAL(finished()), SLOT(deleteLater()));

    connect(&receiveThread, SIGNAL(started()), SLOT(init()));
}

ClientReceive::~ClientReceive()
{

}

void ClientReceive::init()
{
    int flags;
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Cannot create socket");
        exit(1);
    }
    flags = fcntl(sd, F_GETFL, 0);
    flags &= !O_NONBLOCK;
    fcntl(sd, F_SETFL, flags);
    if (::connect (sd, (struct sockaddr *)&server, (socklen_t)sizeof(server)) == -1)
    {
        fprintf(stderr, "Can't connect to server\n");
        emit textAdded(QString("Error\tCould not connect to server"));
        return;
    }
    emit textAdded(QString("Connect"));
    receiving = true;
    receive();
}

bool ClientReceive::setNetwork(char *host, char *port)
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
    if (!receiveThread.isRunning())
        receiveThread.start();
    return true;
}

int ClientReceive::getSocket()
{
    receiving = true;
    return sd;
}

void ClientReceive::receive()
{
    char receiveBuf[BUFSIZE];
    QString str;
    int val;

    while(receiving)
    {
        if ((val = read(sd, receiveBuf, BUFSIZE)) /*(sd, receiveBuf, BUFSIZE, 0))*/ == -1)
        {
            emit textAdded(QString("Error, Receive failed"));
            break;
        }
        switch (receiveBuf[0])
        {
        case (CONNECTION):
            memcpy(receiveBuf,receiveBuf+1, BUFSIZE-1);
            emit userAdded(QString::fromLocal8Bit(receiveBuf));
            break;
        case (CHAT):
            memcpy(receiveBuf,receiveBuf+1, BUFSIZE-1);
            str = QString::fromLocal8Bit(receiveBuf);
            emit textAdded(str);
            break;
        case (NAME_CHANGE):
            memcpy(receiveBuf,receiveBuf+1, BUFSIZE-1);
            namechange(receiveBuf);
            break;
        case (DISCONNECTION):
            memcpy(receiveBuf,receiveBuf+1, BUFSIZE-1);
            userRemove(receiveBuf);
            break;
        default:
            // Stop the read function from repeating too fast
            sleep(1);
        }
        memset(receiveBuf, 0, BUFSIZE);
    }
    close(sd);
}

void ClientReceive::namechange(char *buf)
{
    QString str = str = QString::fromLocal8Bit(buf);
    int pos = -1;
    QString newName;
    std::string value = "";

    for (QString::iterator it = str.begin(); it != str.end(); it++)
    {
        if (it == NULL)
            break;
        if (*it != ' ')
        {
            value += (*it).toLatin1();
        }
        else
        {
            pos = atoi(value.c_str());
        }
    }
    newName = QString::fromStdString(value);
    emit userChanged(newName, pos);
}

void ClientReceive::userRemove(char *buf)
{
    QString str = str = QString::fromLocal8Bit(buf);
    int pos = -1;
    std::string value = "";

    for (QString::iterator it = str.begin(); it != str.end(); it++)
    {
        if (it == NULL)
        {
            pos = atoi(value.c_str());
            break;
        }
        if (*it != ' ')
        {
            value += (*it).toLatin1();
        }
        else
        {
            pos = atoi(value.c_str());
        }
    }
    emit userRemoved(pos);
}

void ClientReceive::setReceiving(bool val)
{
    printf("Set\n");
    receiving = val;
}
