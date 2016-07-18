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

public:		// Métodos
	DataManager() {}	// Construtor Padrão

	// Método de Escrita
	void salvar(string file, string data, bool end = false)
	{
		// Primeiramente, abre-se o arquivo. O comando exige dois parâmetros: o nome e o modo de leitura.
		// Vamos colocar o nome de "dataFiles.txt" e utilizaremos o "app" (concatenação)
		escrita.open(file.c_str(), ofstream::app);	// Obs.: Se o arquivo não existir, ele é criado.

		// Dentro desse arquivo, utilizamos o operando "<<" para escrevermos o "string dado" no seu interior, 
		// de forma semelhante ao cout e o cin...
		escrita << data << ";";
		if (end)
			escrita << "&";

		// Fechamos o arquivo para que o dado escrito seja salvo.
		escrita.close();
	}

	// Método que irá ler, separa cada Pessoa e armazenar no vector "info"
	void ler(string file)
	{
		// Primeiramente, limpamos o Vector para que não haja dados repetidos
		info.clear();

		// Criamos as strings temporárias, uma para cada dado e outra para a linha inteira
		string tempFrase = "", tempLinha = "";

		// Vector para ler a separação linhas
		vector<string> aux;
		int k = 0;

		// Abriremos o arquivo, leremos seu conteúdo e o armazenaremos na variável "tempLinha"
		// Não é necessário nenhum modo especial pois a leitura não modifica os dados.
		leitura.open(file.c_str());

		// Esse o comando de leitura de uma linha inteira
		getline(leitura, tempLinha);

		// É imprescindível fechar-se o arquivo!
		leitura.close();

		// Agora que já temos a linha inteira armazenada em uma String, iremos "destrinchá-la", colocando cada caracter antes
		// de um ponto-e-vírgula (;) na string "tempFrase". Quando tivermos um dado completo, colocaremos ela em um aux[n]
		// e continuamos a verificação até encontrarmos o "&". Encontrado esse caracter, teremos um aux inteiro montado
		// e passamos essa lista para dentro do vector "info"
		for (int i = 0; i < tempLinha.length(); i++)
		{
			if (tempLinha[i] != ';' && tempLinha[i] != '&')
				tempFrase += tempLinha[i];						// Adicionaremos esse caracter na frase

			else if (tempLinha[i] == ';') {
				aux.push_back(tempFrase);	// Colocamos aquela frase no vector
				tempFrase = "";				// Reiniciamos a variável para a próxima frase
			}
			else if (tempLinha[i] == '&') {
				info.push_back(aux);						// Passamos o aux para o vector
				tempFrase = "";								// Resetamos a "tempFrase"
				k = 0;										// Resetamos o "k"
			}
		}

		// No final desse for, já teremos garantia que todo o arquivo ".txt" foi destrinchado e cada uma das suas informações
		// foram armazenadas no vector. O vector nada mais é do que um "vetor infinito", falando-se a grosso modo.
	}

	// Esse método retorna uma pessoa do vector na posição indicada como parâmetro
	string getData(string file, int linha, int posicao)
	{
		// Chamamos o método "ler()" para atualizarmos o vector
		ler(file);

		// Primeiro, verificamos se a posição é inválida
		if (linha < 0 || posicao < 0 || linha > info.size() || posicao > info[linha].size())
			return "";
		else // Se a posição for válida...
			return info[linha][posicao];	// Retornamos a frase daquela determinada posição

	}

	// Retorna a quantidade de "Linhas" armazenadas
	int getQuantidade(string file)
	{
		ler(file);	// Atualizamos o "vector"

		return info.size();	// Retornamos o seu tamanho
	}
};

#endif

