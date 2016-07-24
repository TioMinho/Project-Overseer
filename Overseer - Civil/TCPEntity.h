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
	sf::TcpSocket socket;
	std::string machineName;
	char buffer[200];
	std::size_t received;
	bool connected;

public:
	// ----- Métodos -----
	// Construtor Padrão
	TCPEntity() {
		ip = sf::IpAddress::getLocalAddress();
		socket.setBlocking(true);

		strcpy_s(buffer, "NULL");

		connected = false;
	}

	// Construtor Personalizado
	TCPEntity(std::string machineName) {
		ip = sf::IpAddress::getLocalAddress();
		socket.setBlocking(true);

		this->machineName = machineName;

		strcpy_s(buffer, "NULL");

		connected = false;
	}

	// Estabelece a conexão com o Mainframe
	bool connect() 
	{
		if (!connected){
			if (socket.connect(ip, 2000, sf::milliseconds(500)) != sf::Socket::Disconnected)
			{
				sendData(machineName + "Client");
				receiveData();

				connected = (bufferToString() == (machineName + "ACK"));
				return connected;
			}
		}

		return connected;
	}

	// Desconecta do Mainframe
	void disconnect()
	{
		socket.disconnect();

		connected = false;
	}

	// Verifica o estado da conexão
	bool isConnected()
	{
		return connected;
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