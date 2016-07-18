#ifndef _OCORRENCIA_H_
#define _OCORRENCIA_H_

#include <iostream>
#include <string>

class Ocorrencia
{
private:
	// ----- Atributos -----
	std::string titulo;
	std::string descricao;
	enum Categoria { furto, assalto, invasao, 
					 agressao, agressaoGrave, homicidio };

public:
	// ---- M�todos -----
	// Construtor Padr�o
	Ocorrencia();

	std::string getDescription();
};

#endif