/************************************************************
* File description: Socket class. creating socket, close 	*
* socket and method prints the errors occurs while			*
* creating sockets, in all the different methods involved	*
************************************************************/

#include "Socket.h"
#include <unistd.h>



#define NONE 0

/***********************************************************************
* function name: Socket												   *
* The Input: none													   *
* The output: none										               *
* The Function operation: creating new Socket object, with the computer*
* ip, and no port number and socket descriptor, 0 backlogs.			   *
***********************************************************************/
Socket::Socket() {
	this->backLog = NONE;
	this->socketDescriptor = NONE;
	this->isServer = true;
	this->port_number = NONE;
}

/***********************************************************************
* function name: ~Socket											   *
* The Input: none													   *
* The output: none										               *
* The Function operation: default destructor					       *
***********************************************************************/
Socket::~Socket() {
	close(this->socketDescriptor);
}

void Socket::setIp_address(const string &ip_address) {
    Socket::ip_address = ip_address;
}





