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
public:
    void setSocket(Socket *socket);

    int getServerPort() ;

    ClientThreadArgs(TaxiCenter *taxiCenter, int socketPort);

    TaxiCenter *getTaxiCenter() ;

    Socket *getServer() ;


};


#endif //PLAYWITHSOCKETS_CLIENTTHREADARGS_H
