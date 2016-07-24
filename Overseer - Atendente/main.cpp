#include <iostream>

#include <Windows.h>
#include <SFML/Graphics.hpp>
#include "..\Overseer - Civil\TCPEntity.h"
#include "..\Overseer - GUI\Display.h"

int main()
{
	FreeConsole();

	// Objeto de TCPEntity e de Civil
	TCPEntity client("Atendente");
	sf::Clock timer;

	// Inicialização da Janela
	sf::RenderWindow janela(sf::VideoMode(320, 480), "Overseer - Atendente", sf::Style::Close);
	Display actualDisplay;		// Ponteiro para o atual display em funcionamento

	// Display
	actualDisplay.addButton(100, 430, 100, 30, "Aceitar");
	actualDisplay.addButton(225, 430, 100, 30, "Recusar");

	actualDisplay.addTextBox(140, 40, 200, "Pedido de Atendimento Policial!", sf::Text::Bold);

	actualDisplay.addTextBox(160, 100, 200, "CPF: ", sf::Text::Bold);
	actualDisplay.addTextBox(160, 130, 200, 21, false);
	actualDisplay.addTextBox(160, 160, 200, "Nome: ", sf::Text::Bold);
	actualDisplay.addTextBox(160, 190, 200, 21, false);
	actualDisplay.addTextBox(160, 220, 200, "Ocorrências: ", sf::Text::Bold);
	actualDisplay.addTextBox(160, 250, 200, 21, false);

	// Conexão

	// Program Loop
	while (janela.isOpen())
	{
		sf::Event e;
		while (janela.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				janela.close();

			actualDisplay.textBoxWriting(&e);
		}

		// Try to connect
		client.connect();
			
		if (client.bufferToString() == "AtendenteACK")
		{
			for (int i = 0; i < 3; i++)
			{
				client.sendData("atendenteRequestDataInform");

				client.receiveData();
				actualDisplay.setText(2 + (2 * i), client.bufferToString());

				client.sendData("atendentePrepareData");
			}

			timer.restart();
			while (timer.getElapsedTime().asSeconds() < 1800)
			{
				if (actualDisplay.checkButton(0, &janela)) {
					client.sendData("accepted");
					break;
				}
				else if (actualDisplay.checkButton(1, &janela)) {
					client.sendData("rejected");
				}

				actualDisplay.draw(&janela);
				janela.display();
				janela.clear(sf::Color::White);
			}

			actualDisplay.setText(2, "");
			actualDisplay.setText(4, "");
			actualDisplay.setText(6, "");
		}
		else
			client.disconnect();


		actualDisplay.draw(&janela);
		janela.display();
		janela.clear(sf::Color::White);
	}

	return 0;
}