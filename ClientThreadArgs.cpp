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

ClientThreadArgs::ClientThreadArgs(TaxiCenter *taxiCenter,Socket* serverSocket,
                                   int numberOfClients):
        taxiCenter(taxiCenter),
        server(serverSocket),
        numberOfClients(numberOfClients){}

void ClientThreadArgs::setServer(Socket *socket) {
    ClientThreadArgs::server = socket;
}

int ClientThreadArgs::getNumberOfClients(){
    return numberOfClients;
}

int ClientThreadArgs::getSocketDes(){
    return socketDes;
}

ClientThreadArgs::ClientThreadArgs(ClientThreadArgs* ClientToCopy,int socketDS) {
    taxiCenter = ClientToCopy->getTaxiCenter();
    numberOfClients = ClientToCopy->numberOfClients;
    socketDes = socketDS;
    server = ClientToCopy->getServer();
}

