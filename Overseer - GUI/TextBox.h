#ifndef _TEXTBOX_H_
#define _TEXTBOX_H_

#include <iostream>
#include <SFML/Graphics.hpp>

class TextBox
{
private:
	// ----- Atributos -----
	sf::RectangleShape textBox;
	sf::Text text;
	std::string content;
	sf::Font font;
	bool isFocused;
	bool isWritable;
	bool isHidden;
	int charLimit;

public:
	// ----- Métodos -----
	// Construtor Padrão
	TextBox()
	{
		textBox.setOutlineThickness(2);
		textBox.setOutlineColor(sf::Color::Black);
		textBox.setFillColor(sf::Color(255, 255, 255, 200));
		textBox.setSize(sf::Vector2f(200, 25));

		font.loadFromFile("res/roboto.ttf");

		text.setFont(font);
		text.setColor(sf::Color::Black);
		text.setCharacterSize(16);

		this->isFocused = false;
		this->charLimit = 100;
		this->isWritable = isWritable;
		this->isHidden = false;
		this->content = "";
	}

	void create(float positionX, float positionY, int width, int charLimit, bool isWritable, bool isHidden = false)
	{
		textBox.setOutlineThickness(1);
		textBox.setOutlineColor(sf::Color(0, 0, 0, 50));
		textBox.setFillColor(sf::Color(255, 255, 255, 200));
		textBox.setSize(sf::Vector2f(width, 25));

		font.loadFromFile("res/roboto.ttf");

		text.setFont(font);
		text.setColor(sf::Color::Black);
		text.setCharacterSize(16);

		textBox.setPosition(positionX - (width / 2), positionY - 12);
		text.setPosition(textBox.getPosition().x + 2, textBox.getPosition().y + 2);

		this->isFocused = false;
		this->charLimit = charLimit;
		this->isHidden = isHidden;
		this->isWritable = isWritable;
		this->content = "";
	}

	void create(float positionX, float positionY, int width, std::string text, sf::Text::Style style = sf::Text::Regular)
	{
		textBox.setOutlineThickness(0);
		textBox.setFillColor(sf::Color(sf::Color::Transparent));
		textBox.setSize(sf::Vector2f(width, 25));

		font.loadFromFile("res/roboto.ttf");

		this->text.setFont(font);
		this->text.setColor(sf::Color::Black);
		this->text.setCharacterSize(16);
		this->text.setStyle(style);

		textBox.setPosition(positionX - (width / 2), positionY - 12);
		this->text.setPosition(textBox.getPosition().x + 2, textBox.getPosition().y + 2);

		this->isFocused = false;
		this->charLimit = 9999;
		this->isHidden = isHidden;
		this->isWritable = isWritable;
		this->content = "";

		setText(text);
	}

	void setPosition(float positionX, float positionY)
	{
		textBox.setPosition(positionX - (textBox.getSize().x / 2), positionY - 12);
		text.setPosition(textBox.getPosition().x + 2, textBox.getPosition().y + 2);
	}

	std::string getText() {
		return content;
	}

	void setText(std::string text) {
		this->text.setString(text);
		content = text;
	}

	bool getWritable() {
		return isWritable;
	}

	void updateFont(sf::Font font){
		text.setFont(font);
	}

	void checkTextBox(sf::RenderWindow* window) 
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isWritable)
		{
			textBox.setOutlineColor(sf::Color(0, 0, 0, 50));

			isFocused = (!(sf::Mouse::getPosition().x - window->getPosition().x < textBox.getPosition().x
				||
				sf::Mouse::getPosition().x - window->getPosition().x > textBox.getPosition().x + textBox.getSize().x
				||
				sf::Mouse::getPosition().y - (window->getPosition().y + 31) < textBox.getPosition().y
				||
				sf::Mouse::getPosition().y - (window->getPosition().y + 31) > textBox.getPosition().y + textBox.getSize().y));
		}

		if (isFocused)
			textBox.setOutlineColor(sf::Color(0, 0, 0, 255));

		if (!isWritable) {
			textBox.setOutlineThickness(0);
			textBox.setFillColor(sf::Color::Transparent);
		}
	}

	void textEntered(sf::Event* textEvent)
	{
		if (isFocused && isWritable)
		{
			if (textEvent->type == sf::Event::TextEntered)
			{
				if (textEvent->text.unicode != 8 && text.getString().getSize() < charLimit) {
					content += (char)textEvent->text.unicode;
					if (!isHidden)
						text.setString(content);
					else
						text.setString(text.getString() + '*');
				}
				else if (textEvent->text.unicode == 8 && text.getString().getSize() > 0) {
					text.setString(text.getString().substring(0, text.getString().getSize() - 1));
					content = content.substr(0, content.length() - 1);
				}
			}
		}
	}

	void draw(sf::RenderWindow* window)
	{
		window->draw(textBox);
		window->draw(text);
	}
};

#endif