#include <iostream>

#include <SFML/Graphics.hpp>
#include "DataManager.h"
#include "../Overseer - Civil/TCPServer.h"

int main()
{
	TCPServer server;
	DataManager manager;

	bool isCivil = false;

	std::string message;

	sf::Clock timer;
	timer.restart();

	while (1)
	{
		// Se não houver uma ligação Cliente-Atendente-Policial, o Server busca realizá-la
		while (!isCivil)
			isCivil = server.acceptConnection("Civil");
		
		// Espera mensagem. Recebe e Armazena em "std::string message"
		server.receiveData();
		message = server.bufferToString();

		// Verifica quem enviou a mensagem
		if (message == "civil")
		{
			// Envia mensagem de "ACK" da operacao e espera próxima mensagem
			// ACKCivil = "CivilACK"
			server.sendData("CivilACK");
			
			while (server.bufferToString() == "civil") server.receiveData();
			message = server.bufferToString();

			if (message == "login")
			{
				// Envia um "request" do nome do usuário e salva a informação em message
				server.sendData("civilRequestLogin");

				server.receiveData();
				message = server.bufferToString();

				bool accept = false;
				for (int i = 0; i < manager.getQuantidade("data/registers.txt"); i++)
					if (manager.getData("data/registers.txt", i, 0) == message)
						accept = true;

				// Se o usuário tiver digitado um Login inválido, retornar esse aviso
				if (!accept){
					server.sendData("ERRORLogin");
				}
				else
				{
					// Enviar request de senha e salvar a informação em message
					server.sendData("civilRequestPassword");

					server.receiveData();
					message = server.bufferToString();

					accept = false;
					for (int i = 0; i < manager.getQuantidade("data/registers.txt"); i++)
						if (manager.getData("data/registers.txt", i, 1) == message)
							accept = true;

					if (!accept)
						server.sendData("ERRORPassword");
					else
						server.sendData("LoginAccepted");
				}
			}
			else if (message == "register")
			{
				// Envia um request para nome de usuário e salva a informação em Message
				server.sendData("civilRequestUsername");
				
				server.receiveData();
				message = server.bufferToString();

				bool accept = true;
				for (int i = 0; i < manager.getQuantidade("data/registers.txt"); i++)
					if (manager.getData("data/registers.txt", i, 0) == message)
						accept = false;

				if (!accept)
					server.sendData("ERRORUsername");
				else
				{
					manager.salvar("data/registers.txt", message);

					// Envia um request para cada um dos campos
					for (int i = 0; i < 4; i++)
					{
						server.sendData("civilRequestDataRegister");
						
						server.receiveData();
						message = server.bufferToString();

						manager.salvar("data/registers.txt", message, (i==3));

						server.sendData("civilPrepareData");
					}
				}
			}
			else if (message == "inform")
			{
				// Envia os seguintes requests: CPF, nome e tipoOcorrencia
				std::string info[3];
				for (int i = 0; i < 3; i++)
				{
					// Envia request de dado
					server.sendData("civilRequestDataInform");

					server.receiveData();
					message = server.bufferToString();

					manager.salvar("data/crimes.txt", message, (i == 2));
					info[i] = message;

					server.sendData("civilPrepareData");
				}

				// Civil irá aguardar a ACK "CivilInformACK"
				// Enviar Request para Atendente
				while (!server.acceptConnection("Atendente"));

				for (int i = 0; i < 3; i++)
				{
					while (message != "atendenteRequestDataInform")
					{
						server.receiveData();
						message = server.bufferToString();
					}

					server.sendData(info[i]);

					while (message != "atendentePrepareData")
					{
						server.receiveData();
						message = server.bufferToString();
					}
				}

				server.receiveData();
				message = server.bufferToString();
				
				// Envia Confirmacao para Civil
				if (message == "rejected") {
					while (!server.acceptConnection("Civil"));

					server.sendData("ERRORRequestRejected");
				}
				else if (message == "accepted")
				{
					// Envia ACK para Policial
					while (!server.acceptConnection("Policial"));

					// Envia informações do Civil para Policial
					for (int i = 0; i < 3; i++)
					{
						while (message != "policialRequestDataInform")
						{
							server.receiveData();
							message = server.bufferToString();
						}

						server.sendData(info[i]);

						while (message != "policialPrepareData")
						{
							server.receiveData();
							message = server.bufferToString();
						}
					}

					// Recebe info do Policial
					for (int i = 0; i < 2; i++)
					{
						// Envia request de dado
						server.sendData("policialRequestDataInform");

						server.receiveData();
						message = server.bufferToString();

						info[i] = message;

						server.sendData("policialPrepareData");
					}

					info[2] = "2h00m";

					while (!server.acceptConnection("Civil"));
					server.sendData("CivilInformACK");

					for (int i = 0; i < 3; i++)
					{
						while (message != "civilRequestDataInform")
						{
							server.receiveData();
							message = server.bufferToString();
						}

						server.sendData(info[i]);

						while (message != "civilPrepareData")
						{
							server.receiveData();
							message = server.bufferToString();
						}
					}
				}
			}
			else if (message == "boletim")
			{
				// Envia um request para cada um dos campos
				for (int i = 0; i < 5; i++)
				{
					server.sendData("civilRequestDataBoletim");

					server.receiveData();
					message = server.bufferToString();

					manager.salvar("data/boletins.txt", message, (i == 4));

					server.sendData("civilPrepareData");
				}
			}
			else if (message == "maps")
			{

			}
		}
		else if (message == "policial"){}
	}

	system("pause");
	return 0;
}