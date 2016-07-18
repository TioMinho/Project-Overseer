#ifndef _CHECKBOX_H_
#define _CHECKBOX_H_

#include <SFML\Graphics.hpp>

class CheckBox
{
private:
	// ----- Atributos -----
	sf::RectangleShape box, selected;
	sf::Text label;
	sf::Font font;
	sf::Clock timer;
	bool isActive;

public:
	// ----- Métodos -----
	// Construtor Padrão
	CheckBox()
	{
		selected.setSize(sf::Vector2f(10, 10));
		selected.setFillColor(sf::Color::Black);

		box.setSize(sf::Vector2f(15, 15));
		box.setFillColor(sf::Color::White);
		box.setOutlineThickness(1);
		box.setOutlineColor(sf::Color(0, 0, 0, 50));

		font.loadFromFile("res/roboto.ttf");

		label.setFont(font);
		label.setColor(sf::Color::Black);
		label.setCharacterSize(14);

		isActive = false;

		timer.restart();
	}

	// Criador
	void create(float positionX, float positionY, std::string text)
	{
		box.setPosition(positionX - 15, positionY - 15);
		
		selected.setPosition(positionX - 13, positionY - 13);

		label.setString(text);
		label.setPosition(positionX + 10, positionY - 15);
	}

	// Retorna o estado
	bool getActive() {
		return isActive;
	}

	void setActive(bool isActive) {
		this->isActive = isActive;
	}

	// Retorna o Título do Label
	std::string getLabel() {
		return label.getString();
	}

	// Verifica o clique
	void checkClick(sf::RenderWindow* window)
	{
		if (!(sf::Mouse::getPosition().x - window->getPosition().x < box.getPosition().x
			||
			sf::Mouse::getPosition().x - window->getPosition().x > box.getPosition().x + box.getSize().x
			||
			sf::Mouse::getPosition().y - (window->getPosition().y + 31) < box.getPosition().y
			||
			sf::Mouse::getPosition().y - (window->getPosition().y + 31) > box.getPosition().y + box.getSize().y))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timer.getElapsedTime().asSeconds() > 0.5) {
				isActive = !isActive;
				timer.restart();
			}
		}
	}

	void draw(sf::RenderWindow* window)
	{
		window->draw(box);
		if (isActive)
			window->draw(selected);
		window->draw(label);
	}
};

#endif