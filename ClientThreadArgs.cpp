//
// Created by amir on 11/01/17.
//

#include "ClientThreadArgs.h"

TaxiCenter *ClientThreadArgs::getTaxiCenter()  {
    return taxiCenter;
}

Socket *ClientThreadArgs::getSocket()  {
    return socket;
}


int ClientThreadArgs::getSocketPort()  {
    return socketPort;
}


ClientThreadArgs::ClientThreadArgs(TaxiCenter *taxiCenter, int socketPort) : taxiCenter(taxiCenter),
                                                                                             socketPort(socketPort){}

void ClientThreadArgs::setSocket(Socket *socket) {
    ClientThreadArgs::socket = socket;
}

