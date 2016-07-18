#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextBox.h"
#include "CheckBox.h"

class Display
{
private:
	// ----- Atributos -----
	Button buttonList[10]; int buttonCounter;
	TextBox textBoxList[10]; int textBoxCounter;
	CheckBox checkBoxList[10]; int checkBoxCounter;
	sf::Font font;

public:
	// ----- Métodos -----
	// Construtor Padrão
	Display() 
	{
		font.loadFromFile("res/roboto.ttf");

		buttonCounter = textBoxCounter = checkBoxCounter = 0;
	}

	// Adiciona um Button
	void addButton(float positionX, float positionY, int width, int height, std::string text) {
		buttonList[buttonCounter].create(positionX, positionY, width, height, text);
		buttonCounter++;
	}

	// Adiciona um TextBox
	void addTextBox(float positionX, float positionY, int width, int charLimit, bool isWritable, bool isHidden = false) {
		textBoxList[textBoxCounter].create(positionX, positionY, width, charLimit, isWritable, isHidden);
		textBoxCounter++;
	}

	void addTextBox(float positionX, float positionY, int width, std::string text, sf::Text::Style style = sf::Text::Regular) {
		textBoxList[textBoxCounter].create(positionX, positionY, width, text);
		textBoxCounter++;
	}

	// Adiciona um CheckBox
	void addCheckBox(float positionX, float positionY, std::string label) {
		checkBoxList[checkBoxCounter].create(positionX, positionY, label);
		checkBoxCounter++;
	}

	// Retorna se um botão está apertado ou não
	bool checkButton(int index, sf::RenderWindow* window) {
		return buttonList[index].checkClick(window);
	}

	// TextEntered dos TextBoxes Writables
	void textBoxWriting(sf::Event* e) {
		for (int i = 0; i < textBoxCounter; i++)
			if (textBoxList[i].getWritable() == true)
				textBoxList[i].textEntered(e);
	}

	// Verifica se um CheckBox está ativo
	bool checkBox(int index) {
		return checkBoxList[index].getActive();
	}

	// Retorna o texto de um dos TextBoxes
	std::string getText(int index) {
		return textBoxList[index].getText();
	}

	// Modifica o Texto de um dos TextBoxes
	void setText(int index, std::string text) {
		textBoxList[index].setText(text);
	}

	// Modifica o estado dos CheckBoxes
	void setCheckBox(int index, bool isActive) {
		checkBoxList[index].setActive(isActive);
	}

	// Retorna o Label dos CheckBoxes
	std::string getLabel(int checkBox) {
		return checkBoxList[checkBox].getLabel();
	}

	// Renderiza o Display
	void draw(sf::RenderWindow* window) {
		for (int i = 0; i < buttonCounter; i++) {
			buttonList[i].checkClick(window);
			buttonList[i].draw(window);
		}

		for (int i = 0; i < textBoxCounter; i++) {
			textBoxList[i].checkTextBox(window);
			textBoxList[i].draw(window);
		}

		for (int i = 0; i < checkBoxCounter; i++) {
			checkBoxList[i].checkClick(window);
			checkBoxList[i].draw(window);
		}
	}
};

#endif