//
// Created by amir on 11/01/17.
//


#ifndef PLAYWITHSOCKETS_CLIENTTHREADARGS_H
#define PLAYWITHSOCKETS_CLIENTTHREADARGS_H

#include "TaxiCenter.h"
#include "sockets/Socket.h"

class ClientThreadArgs {
    private:
    TaxiCenter *taxiCenter;
    Socket *server;
    int serverPort;
    int numberOfClients;
    int socketDes;

public:
    int getNumberOfClients();

    void setServer(Socket *server);

    int getSocketDes();

    int getServerPort() ;

    ClientThreadArgs(TaxiCenter *taxiCenter, int socketPort,int numberOfClients);

    ClientThreadArgs(ClientThreadArgs* ClientToCopy,int socketDS);

    TaxiCenter *getTaxiCenter();

    Socket *getServer();

};


#endif //PLAYWITHSOCKETS_CLIENTTHREADARGS_H
