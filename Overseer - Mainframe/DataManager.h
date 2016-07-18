#ifndef _DATAMANAGER_H_
#define _DATAMANAGER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class DataManager {
private:	// Atributos
	ofstream escrita;					// Objeto utilizado para escrever no arquivo "txt"
	ifstream leitura;					// Objeto utilizado para leitura no arquivo "txt"
	vector<vector<string>> info;		// Objeto que utilizaremos para separar os textos do arquivo

public:		// M�todos
	DataManager() {}	// Construtor Padr�o

	// M�todo de Escrita
	void salvar(string file, string data, bool end = false)
	{
		// Primeiramente, abre-se o arquivo. O comando exige dois par�metros: o nome e o modo de leitura.
		// Vamos colocar o nome de "dataFiles.txt" e utilizaremos o "app" (concatena��o)
		escrita.open(file.c_str(), ofstream::app);	// Obs.: Se o arquivo n�o existir, ele � criado.

		// Dentro desse arquivo, utilizamos o operando "<<" para escrevermos o "string dado" no seu interior, 
		// de forma semelhante ao cout e o cin...
		escrita << data << ";";
		if (end)
			escrita << "&";

		// Fechamos o arquivo para que o dado escrito seja salvo.
		escrita.close();
	}

	// M�todo que ir� ler, separa cada Pessoa e armazenar no vector "info"
	void ler(string file)
	{
		// Primeiramente, limpamos o Vector para que n�o haja dados repetidos
		info.clear();

		// Criamos as strings tempor�rias, uma para cada dado e outra para a linha inteira
		string tempFrase = "", tempLinha = "";

		// Vector para ler a separa��o linhas
		vector<string> aux;
		int k = 0;

		// Abriremos o arquivo, leremos seu conte�do e o armazenaremos na vari�vel "tempLinha"
		// N�o � necess�rio nenhum modo especial pois a leitura n�o modifica os dados.
		leitura.open(file.c_str());

		// Esse o comando de leitura de uma linha inteira
		getline(leitura, tempLinha);

		// � imprescind�vel fechar-se o arquivo!
		leitura.close();

		// Agora que j� temos a linha inteira armazenada em uma String, iremos "destrinch�-la", colocando cada caracter antes
		// de um ponto-e-v�rgula (;) na string "tempFrase". Quando tivermos um dado completo, colocaremos ela em um aux[n]
		// e continuamos a verifica��o at� encontrarmos o "&". Encontrado esse caracter, teremos um aux inteiro montado
		// e passamos essa lista para dentro do vector "info"
		for (int i = 0; i < tempLinha.length(); i++)
		{
			if (tempLinha[i] != ';' && tempLinha[i] != '&')
				tempFrase += tempLinha[i];						// Adicionaremos esse caracter na frase

			else if (tempLinha[i] == ';') {
				aux.push_back(tempFrase);	// Colocamos aquela frase no vector
				tempFrase = "";				// Reiniciamos a vari�vel para a pr�xima frase
			}
			else if (tempLinha[i] == '&') {
				info.push_back(aux);						// Passamos o aux para o vector
				tempFrase = "";								// Resetamos a "tempFrase"
				k = 0;										// Resetamos o "k"
			}
		}

		// No final desse for, j� teremos garantia que todo o arquivo ".txt" foi destrinchado e cada uma das suas informa��es
		// foram armazenadas no vector. O vector nada mais � do que um "vetor infinito", falando-se a grosso modo.
	}

	// Esse m�todo retorna uma pessoa do vector na posi��o indicada como par�metro
	string getData(string file, int linha, int posicao)
	{
		// Chamamos o m�todo "ler()" para atualizarmos o vector
		ler(file);

		// Primeiro, verificamos se a posi��o � inv�lida
		if (linha < 0 || posicao < 0 || linha > info.size() || posicao > info[linha].size())
			return "";
		else // Se a posi��o for v�lida...
			return info[linha][posicao];	// Retornamos a frase daquela determinada posi��o

	}

	// Retorna a quantidade de "Linhas" armazenadas
	int getQuantidade(string file)
	{
		ler(file);	// Atualizamos o "vector"

		return info.size();	// Retornamos o seu tamanho
	}
};

#endif

