#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_

#include "TCPEntity.h"

class TCPServer : public TCPEntity
{
private:
	// ----- Atributos -----
	sf::TcpListener listener;

public:
	// ----- M�todos -----
	// Construtor Padr�o
	TCPServer() 
	{
		this->machineName = "Server";

		listener.listen(2000);
	}

	// Cria uma conex�o
	bool acceptConnection(std::string clientName)
	{
		listener.accept(socket);

		receiveData();

		if (bufferToString() == (clientName + "Client")) {
			sendData(clientName + "ACK");
			return true;
		}
		else {
			sendData("notPermitted");
			return false;
		}
	}

};

#endif