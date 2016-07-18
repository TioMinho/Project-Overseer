#ifndef _TCPENTITY_H_
#define _TCPENTITY_H_

#include <iostream>
#include <fstream>
#include <SFML\Network.hpp>

class TCPEntity
{
protected:
	// ----- Atributos -----
	sf::IpAddress ip;
	std::string machineName;
	sf::TcpSocket socket;
	char buffer[200];
	std::size_t received;

public:
	// ----- Métodos -----
	// Construtor Padrão
	TCPEntity() {
		ip = sf::IpAddress::getLocalAddress();
		socket.setBlocking(true);

		strcpy_s(buffer, "NULL");
	}

	// Construtor Personalizado
	TCPEntity(std::string machineName) {
		ip = sf::IpAddress::getLocalAddress();
		socket.setBlocking(true);

		this->machineName = machineName;

		strcpy_s(buffer, "NULL");
	}

	// Estabelece a conexão com o Mainframe
	bool connect() 
	{
		if (socket.connect(ip, 2000, sf::milliseconds(500)) != sf::Socket::Disconnected)
		{
			return true;
		}

		return false;
	}

	// Desconecta do Mainframe
	void disconnect()
	{
		socket.disconnect();
	}

	// Modifica o Estado de Blocking
	void setBlocking(bool blocking) {
		socket.setBlocking(blocking);
	}

	// Envia dados
	void sendData(std::string data)
	{
		socket.send(data.c_str(), data.length() + 1);
	}

	// Recebe dados
	void receiveData()
	{
		socket.receive(buffer, sizeof(buffer), received);
		while (received < 0)
			socket.receive(buffer, sizeof(buffer), received);
	}

	// Transforma o buffer em Dados diversos
	int bufferToInt()
	{
		return atoi(buffer);
	}

	float bufferToFloat()
	{
		return atof(buffer);
	}

	std::string bufferToString()
	{
		return std::string(buffer);
	}
};

#endif