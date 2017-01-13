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
    Socket *socket;
    int socketPort;
public:
    void setSocket(Socket *socket);

    int getSocketPort() ;

    ClientThreadArgs(TaxiCenter *taxiCenter, int socketPort);

    TaxiCenter *getTaxiCenter() ;

    Socket *getSocket() ;


};


#endif //PLAYWITHSOCKETS_CLIENTTHREADARGS_H
