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


ClientThreadArgs::ClientThreadArgs(TaxiCenter *taxiCenter, int socketPort,int numberOfClients) :
        taxiCenter(taxiCenter),
        serverPort(socketPort),
        numberOfClients(numberOfClients){}

void ClientThreadArgs::setSocket(Socket *socket) {
    ClientThreadArgs::server = socket;
}

int ClientThreadArgs::getNumberOfClients(){
    return numberOfClients;
}

