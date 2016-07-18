#ifndef _CIVIL_H_
#define _CIVIL_H_

#include <iostream>
#include <string>
#include "Ocorrencia.h"
#include <SFML\Graphics.hpp>

class Civil
{
private:
	// ----- Atributos -----
	int cpf;
	std::string nome;
	std::string email;
	sf::Vector2i coordenadas;

public:
	// ----- M�todos -----
	// Construtor Padr�o
	Civil();

	// Esse m�todo recebe valores do Objeto de Fronteira (Interface Gr�fica) e,
	// a partir deles, gera um Relat�rio que � enviado para uma Atendente.
	void enviarRelatorio(bool isRealTime, Ocorrencia* ocorrencia);
};

#endif

