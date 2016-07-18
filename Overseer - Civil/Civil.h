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
	// ----- Métodos -----
	// Construtor Padrão
	Civil();

	// Esse método recebe valores do Objeto de Fronteira (Interface Gráfica) e,
	// a partir deles, gera um Relatório que é enviado para uma Atendente.
	void enviarRelatorio(bool isRealTime, Ocorrencia* ocorrencia);
};

#endif

