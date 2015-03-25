/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: clientsend.cpp - Client sending class
--
-- PROGRAM: Thowis Scallentire Chat
--
-- FUNCTIONS:
-- ClientSend();
-- ~ClientSend();
-- bool setNetwork(char *host, char *port);
-- void setSocket(int sd);
-- void sendtext(QString);
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
----------------------------------------------------------------------------------------------------------------------*/

#include "clientsend.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ClientSend
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: ClientSend::ClientSend()
--
-- PARAMETERS:	void
--
-- RETURNS: void
--
-- NOTES:
-- Constructor for the client sending class.
----------------------------------------------------------------------------------------------------------------------*/
ClientSend::ClientSend()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ~ClientSend
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: ClientSend::~ClientSend()
--
-- PARAMETERS:	void
--
-- RETURNS: void
--
-- NOTES:
-- Destructor for the client sending class.
----------------------------------------------------------------------------------------------------------------------*/
ClientSend::~ClientSend()
{
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
-- INTERFACE: bool ClientSend::setNetwork(char *host, char *port)
--
-- PARAMETERS:	host - IP in dotted decimal notation
--              port - Port number.
--
-- RETURNS: bool - If the network information is valid or not.
--
-- NOTES:
-- Validates the network information.
----------------------------------------------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setSocket
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void ClientSend::setSocket(int _sd)
--
-- PARAMETERS:	_sd - Given socket descriptor
--
-- RETURNS: void
--
-- NOTES:
-- Sets the socket descriptor to the new descriptor.
----------------------------------------------------------------------------------------------------------------------*/
void ClientSend::setSocket(int _sd)
{
    sd = _sd;
    sending = true;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: sendtext
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void ClientSend::sendtext(QString text)
--
-- PARAMETERS:	text - Text to be sent
--
-- RETURNS: void
--
-- NOTES:
-- Transforms given QString to a c pointer and writes it to the socket.
----------------------------------------------------------------------------------------------------------------------*/
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

