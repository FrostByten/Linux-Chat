/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: clientreceive.cpp - Client receiving class
--
-- PROGRAM: Thowis Scallentire Chat
--
-- FUNCTIONS:
-- ClientReceive();
-- ~ClientReceive();
-- bool setNetwork(char *host, char *port);
-- int getSocket();
-- void setReceiving(bool);
-- void init();
-- void receive();
-- void namechange(char *buf);
-- void userRemove(char *buf);
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
----------------------------------------------------------------------------------------------------------------------*/

#include "clientreceive.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ClientReceive
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: ClientReceive::ClientReceive()
--
-- PARAMETERS:	void
--
-- RETURNS: void
--
-- NOTES:
-- Client Receive class constructor. Sets up connects.
----------------------------------------------------------------------------------------------------------------------*/
ClientReceive::ClientReceive(Encryption *e)
{
    enc = e;
    connect(&receiveThread, SIGNAL(finished()), SLOT(deleteLater()));

    connect(&receiveThread, SIGNAL(started()), SLOT(init()));
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ~ClientReceive
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: ClientReceive::~ClientReceive()
--
-- PARAMETERS:	void
--
-- RETURNS: void
--
-- NOTES:
-- Client Receive class destructor.
----------------------------------------------------------------------------------------------------------------------*/
ClientReceive::~ClientReceive()
{

}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: init
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void ClientReceive::init()
--
-- PARAMETERS:	void
--
-- RETURNS: void
--
-- NOTES:
-- Initializes the socket descriptor and connects it to the server. Runs on thread start.
----------------------------------------------------------------------------------------------------------------------*/
void ClientReceive::init()
{
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Cannot create socket");
        exit(1);
    }

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

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setNetwork
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: bool ClientReceive::setNetwork(char *host, char *port)
--
-- PARAMETERS:	host - IP in dotted decimal notation
--              port - Port number.
--
-- RETURNS: bool - If the network information is valid or not.
--
-- NOTES:
-- Validates the network information. Starts the receiving thread.
----------------------------------------------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getSocket
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: int ClientReceive::getSocket()
--
-- PARAMETERS:	void
--
-- RETURNS: int - The socket descriptor
--
-- NOTES:
-- Returns the socket descriptor, sets receiving to true.
----------------------------------------------------------------------------------------------------------------------*/
int ClientReceive::getSocket()
{
    receiving = true;
    return sd;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: receive
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void ClientReceive::receive()
--
-- PARAMETERS:	void
--
-- RETURNS: void
--
-- NOTES:
-- Loops forever trying to read from the socket. When a message is received, the first character
-- is read to determine the type of message received.
----------------------------------------------------------------------------------------------------------------------*/
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
            printf("Chat Received\n");
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
        case (DEAD_CONNECTION):
            memcpy(receiveBuf,receiveBuf+1, BUFSIZE-1);
            emit userAdded(QString("\0"));
            break;
        default:
            // Stop the read function from repeating too fast
            sleep(1);
        }
        memset(receiveBuf, 0, BUFSIZE);
    }
    close(sd);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: namechange
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void ClientReceive::namechange(char *buf)
--
-- PARAMETERS:	buf - The message buffer contaning the user and their new name.
--
-- RETURNS: void
--
-- NOTES:
-- Extracts the name and position of the user whose name has been changed.
----------------------------------------------------------------------------------------------------------------------*/
void ClientReceive::namechange(char *buf)
{
    int pos = -1;
    QString newName;

    pos = (int)buf[0];
    memcpy(buf, buf+1, BUFSIZE-2);
    newName = QString::fromLocal8Bit(buf);

    emit userChanged(newName, pos);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: userRemove
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void ClientReceive::userRemove(char *buf)
--
-- PARAMETERS:	buf - The message buffer contaning the user position.
--
-- RETURNS: void
--
-- NOTES:
-- Extracts the name and position of the user whose name has been changed.
----------------------------------------------------------------------------------------------------------------------*/
void ClientReceive::userRemove(char *buf)
{
    int pos = -1;

    pos = (int)buf[0];

    emit userRemoved(pos);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setReceiving
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void ClientReceive::setReceiving(bool val = false)
--
-- PARAMETERS:	val - The value to set receiving to.
--
-- RETURNS: void
--
-- NOTES:
-- End receiving.
----------------------------------------------------------------------------------------------------------------------*/
void ClientReceive::setReceiving(bool val = false)
{
    receiving = val;
    close(sd);
}
