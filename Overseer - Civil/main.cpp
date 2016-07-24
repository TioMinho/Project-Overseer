#include <iostream>

#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Civil.h"
#include "TCPEntity.h"
#include "..\Overseer - GUI\Display.h"

int main()
{
	FreeConsole();

	// Objeto de TCPEntity e de Civil (e de um Timer)
	TCPEntity client("Civil");
	Civil thisCivil;

	// Inicialização da Janela
	sf::RenderWindow janela(sf::VideoMode(320, 480), "Overseer - Civil", sf::Style::Close);
	Display* actualDisplay;		// Ponteiro para o atual display em funcionamento

	// Displays do Civil: Login, Cadastro, Principal, Informar Delito, Escrever B.O., Esperar Policial, Visualizar Regiões Críticas
	Display display[7];

	// Display 0 - Tela de Login
	display[0].addButton(100, 350, 100, 50, "Login");
	display[0].addButton(225, 350, 100, 50, "Sign-up");
	
	display[0].addTextBox(160, 120, 200, "Usuario: ", sf::Text::Bold);
	display[0].addTextBox(160, 150, 200, 21, true);
	display[0].addTextBox(160, 175, 200, "Senha: ", sf::Text::Bold);
	display[0].addTextBox(160, 205, 200, 16, true, true);
	// -___-__-__
	// Display 1 - Tela de Cadastro
	display[1].addButton(100, 400, 100, 30, "Sign-in");
	display[1].addButton(225, 400, 100, 30, "Cancel");

	display[1].addTextBox(160, 30, 200, "Nome de Usuário: ", sf::Text::Bold);
	display[1].addTextBox(160, 60, 200, 21, true);
	display[1].addTextBox(160, 90, 200, "Senha: ", sf::Text::Bold);
	display[1].addTextBox(160, 120, 200, 16, true, true);
	display[1].addTextBox(160, 180, 200, "CPF: ", sf::Text::Bold);
	display[1].addTextBox(160, 210, 200, 21, true);
	display[1].addTextBox(160, 240, 200, "Nome Completo: ", sf::Text::Bold);
	display[1].addTextBox(160, 270, 200, 21, true);
	display[1].addTextBox(160, 300, 200, "E-Mail: ", sf::Text::Bold);
	display[1].addTextBox(160, 330, 200, 21, true);
	// -___-__-__
	// Display 2 - Princial
	display[2].addButton(160, 100, 200, 100, "Informar\n  Delito");
	display[2].addButton(160, 210, 200, 70, "Regioes Críticas");
	display[2].addButton(160, 300, 200, 50, "Configuracões");
	display[2].addButton(160, 380, 200, 50, "Logout");
	// -___-__-__
	// Display 3 - Informar Delito
	display[3].addButton(100, 450, 100, 30, "Enviar");
	display[3].addButton(225, 450, 100, 30, "Cancelar");
	
	display[3].addTextBox(140, 50, 200, "Selecione uma Opção Abaixo:", sf::Text::Bold);
	display[3].addCheckBox(50, 100, "Furto");
	display[3].addCheckBox(50, 140, "Assalto");
	display[3].addCheckBox(50, 180, "Invasão");
	display[3].addCheckBox(50, 220, "Agressão");
	display[3].addCheckBox(50, 260, "Agressão Grave");
	display[3].addCheckBox(50, 300, "Homicídio");
	display[3].addTextBox(130, 340, 200, "Esse Delito esta Ocorrendo Agora?", sf::Text::Bold);
	display[3].addCheckBox(150, 380, "Sim");
	// -___-__-__
	// Display 4 - B.O. Online
	display[4].addButton(100, 400, 100, 30, "Enviar");
	display[4].addButton(225, 400, 100, 30, "Cancelar");

	display[4].addTextBox(160, 40, 200, "CPF da Vítima: ", sf::Text::Bold);
	display[4].addTextBox(160, 70, 200, 21, true);
	display[4].addTextBox(160, 100, 200, "Nome da Vítima: ", sf::Text::Bold);
	display[4].addTextBox(160, 130, 200, 21, true);
	display[4].addTextBox(160, 160, 200, "Cidade: ", sf::Text::Bold);
	display[4].addTextBox(160, 190, 200, 21, true);
	display[4].addTextBox(160, 220, 200, "Tipo de Ocorrência: ", sf::Text::Bold);
	display[4].addTextBox(160, 250, 200, 21, true);
	display[4].addTextBox(160, 280, 200, "Descrição Breve: ", sf::Text::Bold);
	display[4].addTextBox(160, 310, 200, 21, true);
	// -___-__-__
	// Display 5 - Aguardar Policial
	display[5].addButton(165, 400, 100, 50, "OK");

	display[5].addTextBox(140, 40, 200, "Atendimento Policial a Caminho!", sf::Text::Bold);
	
	display[5].addTextBox(160, 120, 200, "Viatura: ", sf::Text::Bold);
	display[5].addTextBox(160, 150, 200, 21, false);
	display[5].addTextBox(160, 180, 200, "Policial: ", sf::Text::Bold);
	display[5].addTextBox(160, 210, 200, 21, false);
	display[5].addTextBox(160, 240, 200, "Tempo Estimado: ", sf::Text::Bold);
	display[5].addTextBox(160, 270, 200, 21, false);
	// -___-__-__

	// Estados iniciais:
	bool connected = false;
	actualDisplay = &display[0];

	// Program Loop
	while (janela.isOpen())
	{
		sf::Event e;
		while (janela.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				janela.close();

			actualDisplay->textBoxWriting(&e);
		}

		// Try to connect
		client.connect();

		// Funcionalidades do Display de Login --------------------------------------------------------------------
		if (actualDisplay == &display[0])
		{
			if (actualDisplay->checkButton(0, &janela))
			{
				if (actualDisplay->getText(1) == "" || actualDisplay->getText(3) == "") 
				{
					actualDisplay->setText(1, "!!! Campos Vazio !!!");
					actualDisplay->setText(3, "");
				}
				else
				{
					client.sendData("civil");

					while (client.bufferToString() != "CivilACK") client.receiveData();
					client.sendData("login");

					while (client.bufferToString() != "civilRequestLogin") client.receiveData();
					client.sendData(actualDisplay->getText(1));

					while (client.bufferToString() == "civilRequestLogin") client.receiveData();

					if (client.bufferToString() == "ERRORLogin")
					{
						actualDisplay->setText(1, "!!! Login Inválido !!!");
						actualDisplay->setText(3, "");
					}
					else
					{
						while (client.bufferToString() != "civilRequestPassword") client.receiveData();
						client.sendData(actualDisplay->getText(3));

						while (client.bufferToString() == "civilRequestPassword") client.receiveData();

						if (client.bufferToString() == "ERRORPassword")
						{
							actualDisplay->setText(1, "!!! Senha Inválida !!!");
							actualDisplay->setText(3, "");
						}
						else if (client.bufferToString() == "LoginAccepted") {
							actualDisplay->setText(3, "");

							actualDisplay = &display[2];
						}
					}
				}
			}
		
			if (actualDisplay->checkButton(1, &janela))
				actualDisplay = &display[1];
		}
		// --------------------------------------------------------------------------------------------------------
		// Funcionalidades do Display de Cadastro -----------------------------------------------------------------
		else if (actualDisplay == &display[1])
		{
			if (actualDisplay->checkButton(0, &janela))
			{
				bool allFilled = true;
				for (int i = 0; i < 5; i++) {
					if (actualDisplay->getText((i * 2) + 1) == ""){
						allFilled = false;
						actualDisplay->setText((i * 2) + 1, "!!! Campo Vazio !!!");
					}
				}

				if (allFilled) 
				{
					client.sendData("civil");

					while (client.bufferToString() != "CivilACK") client.receiveData();
					client.sendData("register");

					while (client.bufferToString() != "civilRequestUsername") client.receiveData();
					client.sendData(actualDisplay->getText(1));

					while (client.bufferToString() == "civilRequestUsername") client.receiveData();

					if (client.bufferToString() == "ERRORUsername")
					{
						std::cout << "Teste 8" << std::endl;
						actualDisplay->setText(1, "!!! Login Indisponível !!!");
						actualDisplay->setText(3, "");
						actualDisplay->setText(5, "");
						actualDisplay->setText(7, "");
						actualDisplay->setText(9, "");
					}
					else
					{
						for (int i = 0; i < 4; i++)
						{
							while (client.bufferToString() != "civilRequestDataRegister") client.receiveData();
							
							client.sendData(actualDisplay->getText((i * 2) + 3));
							
							while (client.bufferToString() != "civilPrepareData") client.receiveData();
						}

						actualDisplay->setText(1, "");
						actualDisplay->setText(3, "");
						actualDisplay->setText(5, "");
						actualDisplay->setText(7, "");
						actualDisplay->setText(9, "");

						actualDisplay = &display[0];
					}
				}
			}

			if (actualDisplay->checkButton(1, &janela))
			{
				actualDisplay->setText(1, "");
				actualDisplay->setText(3, "");
				actualDisplay->setText(5, "");
				actualDisplay->setText(7, "");
				actualDisplay->setText(9, "");

				actualDisplay = &display[0];
			}
		}
		// --------------------------------------------------------------------------------------------------------
		// Funcionalidades do Display do Menu Principal -----------------------------------------------------------
		else if (actualDisplay == &display[2])
		{
			if (actualDisplay->checkButton(0, &janela))
			{
				actualDisplay = &display[3];
				actualDisplay->setCheckBox(0, true);
				actualDisplay->setCheckBox(6, true);
			}

			if (actualDisplay->checkButton(3, &janela))
				actualDisplay = &display[0];
		}
		// --------------------------------------------------------------------------------------------------------
		// Funcionalidades do Display de Informar Delito ----------------------------------------------------------
		else if (actualDisplay == &display[3])
		{
			if (actualDisplay->checkButton(0, &janela))
			{
				bool valido = false;
				std::string ocorrencias = "";
				for (int i = 0; i < 6; i++) {
					if (actualDisplay->checkBox(i)) {
						ocorrencias += actualDisplay->getLabel(i) + '\n';
						valido = true;
					}
				}

				if (!valido)
				{
					for (int i = 0; i < 7; i++)
						actualDisplay->setCheckBox(i, false);

					actualDisplay->setCheckBox(0, true);
					actualDisplay->setCheckBox(6, true);
				}
				else
				{
					if (!actualDisplay->checkBox(6))
						actualDisplay = &display[4];
					else
					{
						actualDisplay = &display[5];

						client.sendData("civil");

						while (client.bufferToString() != "CivilACK") client.receiveData();
						client.sendData("inform");

						while (client.bufferToString() != "civilRequestDataInform") client.receiveData();
						client.sendData("05982144371");
						while (client.bufferToString() != "civilPrepareData") client.receiveData();

						while (client.bufferToString() != "civilRequestDataInform") client.receiveData();
						client.sendData("Relampago Marquinhos");
						while (client.bufferToString() != "civilPrepareData") client.receiveData();
						
						while (client.bufferToString() != "civilRequestDataInform") client.receiveData();
						client.sendData(ocorrencias);
						while (client.bufferToString() != "civilPrepareData") client.receiveData();

						// Vamos nos Desconectar do Servidor para ele enviar as mensagens para os
						// outros Nós

						while (1) 
						{
							client.connect();
							client.sendData("CivilClient");
							client.receiveData();

							if (client.bufferToString() == "CivilACK")
								break;
							else
								client.disconnect();
						}

						client.receiveData();

						if (client.bufferToString() == "ERRORRequestRejected")
						{
							actualDisplay->setText(0, "     !!! Pedido Negado !!!");
							actualDisplay->setText(2, "");
							actualDisplay->setText(4, "");
							actualDisplay->setText(6, "");
						}
						else if (client.bufferToString() == "CivilInformACK")
						{ 
							for (int i = 0; i < 3; i++)
							{
								client.sendData("civilRequestDataInform");

								client.receiveData();
								actualDisplay->setText(2 + (2 * i), client.bufferToString());

								client.sendData("civilPrepareData");
							}
						}
					}
				}
			}

			if (actualDisplay->checkButton(1, &janela)) {
				for(int i = 0; i < 7; i++) 
					actualDisplay->setCheckBox(i, false);

				actualDisplay = &display[2];
			}
			
		}
		// --------------------------------------------------------------------------------------------------------
		// Funcionalidades do Display de Cadastrar B.O. -----------------------------------------------------------
		else if (actualDisplay == &display[4])
		{
			if (actualDisplay->checkButton(0, &janela))
			{
				bool allFilled = true;
				for (int i = 0; i < 5; i++) {
					if (actualDisplay->getText((i * 2) + 1) == ""){
						allFilled = false;
						actualDisplay->setText((i * 2) + 1, "!!! Campo Vazio !!!");
					}
				}

				if (allFilled)
				{
					client.sendData("civil");

					while (client.bufferToString() != "CivilACK") client.receiveData();
					client.sendData("boletim");
					
					for (int i = 0; i < 5; i++)
					{
						while (client.bufferToString() != "civilRequestDataBoletim") client.receiveData();

						client.sendData(actualDisplay->getText((i * 2) + 1));

						while (client.bufferToString() != "civilPrepareData") client.receiveData();
					}

					actualDisplay->setText(1, "");
					actualDisplay->setText(3, "");
					actualDisplay->setText(5, "");
					actualDisplay->setText(7, "");
					actualDisplay->setText(9, "");

					actualDisplay = &display[2];
				}
			}

			if (actualDisplay->checkButton(1, &janela))
			{
				actualDisplay->setText(1, "");
				actualDisplay->setText(3, "");
				actualDisplay->setText(5, "");
				actualDisplay->setText(7, "");
				actualDisplay->setText(9, "");

				actualDisplay = &display[2];
			}
		}
		// --------------------------------------------------------------------------------------------------------
		// Funcionalidades do Display de Cadastrar B.O. -----------------------------------------------------------
		else if (actualDisplay == &display[5])
		{
			if (actualDisplay->checkButton(0, &janela))
				actualDisplay = &display[2];
		}

		// --------------------------------------------------------------------------------------------------------

		actualDisplay->draw(&janela);
		janela.display();
		janela.clear(sf::Color::White);
	}

	return 0;
}