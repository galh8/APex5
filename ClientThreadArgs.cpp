//
// Created by amir on 11/01/17.
//

#include "ClientThreadArgs.h"

TaxiCenter *ClientThreadArgs::getTaxiCenter()  {
    return taxiCenter;
}

Socket *ClientThreadArgs::getServer()  {
    return server;
}


int ClientThreadArgs::getServerPort()  {
    return serverPort;
}


ClientThreadArgs::ClientThreadArgs(TaxiCenter *taxiCenter, int socketPort) : taxiCenter(taxiCenter),
                                                                             serverPort(socketPort){}

void ClientThreadArgs::setSocket(Socket *socket) {
    ClientThreadArgs::server = socket;
}

