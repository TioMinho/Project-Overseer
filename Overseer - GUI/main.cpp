#include <iostream>
#include <SFML\Graphics.hpp>

#include "Button.h"
#include "TextBox.h"
#include "CheckBox.h"

int main()
{
	sf::RenderWindow janela(sf::VideoMode(320, 480), "Teste", sf::Style::Close);

	Button teste;
	teste.create(100, 100, 100, 50, "Click");
	TextBox test2;
	test2.create(200, 250, 300, 25, false, true);
	CheckBox teste3;
	teste3.create(160, 300, "Opcao 1");

	test2.setText("Teste");

	while (janela.isOpen())
	{
		sf::Event e;
		while (janela.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				janela.close();

			test2.textEntered(&e);
		}

		teste.checkClick(&janela);
		test2.checkTextBox(&janela);
		teste3.checkClick(&janela);

		teste.draw(&janela);
		test2.draw(&janela);
		teste3.draw(&janela);
		janela.display();
		janela.clear(sf::Color::White);
	}

	return 0;
}