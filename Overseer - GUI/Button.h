#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <iostream>
#include <SFML\Graphics.hpp>

#define MousePosX sf::Mouse::getPosition().x-window->getPosition().x
#define MousePosY sf::Mouse::getPosition().y-(window->getPosition().y+31)

class Button
{
private:
	// ----- Atributos ------
	sf::RectangleShape buttonBox;
	sf::Text buttonText;
	sf::Font font;
	sf::Clock timer;

public:
	// ----- Métodos ------
	// Construtor Padrão
	Button() 
	{
		buttonBox.setOutlineThickness(1);
		buttonBox.setOutlineColor(sf::Color(0, 0, 0, 50));
		buttonBox.setFillColor(sf::Color(216, 220, 221));
		buttonBox.setSize(sf::Vector2f(50, 50));

		font.loadFromFile("res/roboto.ttf");

		buttonText.setFont(font);
		buttonText.setString("Button");
		buttonText.setColor(sf::Color::Black);
		buttonText.setCharacterSize(24);

		timer.restart();
	}

	// Construtor Personalizado
	void create(float positionX, float positionY, int width, int height, std::string text)
	{
		buttonBox.setOutlineThickness(1);
		buttonBox.setOutlineColor(sf::Color(0, 0, 0, 50));
		buttonBox.setFillColor(sf::Color(216, 220, 221));
		buttonBox.setSize(sf::Vector2f(width, height));

		font.loadFromFile("res/roboto.ttf");

		buttonText.setFont(font);
		buttonText.setString(text);
		buttonText.setColor(sf::Color::Black);
		buttonText.setCharacterSize(24);

		buttonBox.setPosition(positionX - (width / 2), positionY - (height / 2));
		buttonText.setPosition(buttonBox.getPosition().x + (width / 2) - (buttonText.getLocalBounds().width / 2),
								buttonBox.getPosition().y + (height / 2) - (buttonText.getLocalBounds().height / 2) - 5);
	}

	// Position The Box
	void setPosition(float positionX, float positionY)
	{
		buttonBox.setPosition(positionX - (buttonBox.getLocalBounds().width / 2), positionY - (buttonBox.getLocalBounds().height / 2));
		buttonText.setPosition(buttonBox.getPosition().x + (buttonBox.getLocalBounds().width / 2) - (buttonText.getLocalBounds().width / 2),
							buttonBox.getPosition().y + (buttonBox.getLocalBounds().height / 2) - (buttonText.getLocalBounds().height / 2) - 5);
	}

	// Update Button
	bool checkClick(sf::RenderWindow* window)
	{
		if (!(MousePosX < buttonBox.getPosition().x
			||
			MousePosX > buttonBox.getPosition().x + buttonBox.getSize().x
			||
			MousePosY < buttonBox.getPosition().y
			||
			MousePosY > buttonBox.getPosition().y + buttonBox.getSize().y))
		{
			buttonBox.setFillColor(sf::Color(189, 195, 199));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timer.getElapsedTime().asSeconds() > 0.5) {
				buttonBox.setFillColor(sf::Color(149, 165, 166));
				timer.restart();
				return true;
			}
		}
		else
			buttonBox.setFillColor(sf::Color(216, 220, 221));

		return false;
	}

	// Renderiza o botão
	void draw(sf::RenderWindow* window)
	{
		window->draw(buttonBox);
		window->draw(buttonText);
	}
};

#endif