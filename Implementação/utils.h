/**\file utils.h
 * \brief Ficheiro com fun��es �teis para a interface com o utilizador.
 *
 * PROJECTO: Projecto 2 - Gest�o do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: utils.h \n
 * DESCRI��O: Ficheiro com fun��es �teis para a interface com o utilizador. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - V�tor Am�lio Maia Martins Moreira
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <climits>
#include <algorithm>
#include <cstdlib>
#include "Exceptions.h"

using std::string;
using std::stringstream;
using std::vector;
using std::cin;
using std::cout;
using std::setw;
using std::flush;
using std::endl;
using std::max;
using std::getline;
using std::istream;


//Ficheiro de base de dados do programa
const string FILE_SAVE_DB = "AeroportoDB.txt";
const string FILE_SAVE_DB_TIPOS_AVIAO = "TipoAviaoDB.txt";

//Delimitador usado ao guardar a base de dados
const char SAVE_DELIM = '|';

//Atributos gerais das classes
#define CLASS_AEROPORTO_ATTR_SIZE	8
#define CLASS_COMPANHIA_ATTR_SIZE	7
#define CLASS_AVIAO_ATTR_SIZE		10
#define CLASS_TRIPULANTE_ATTR_SIZE	13
#define CLASS_VOO_ATTR_SIZE			15
#define CLASS_FROTA_ATTR_SIZE		1
#define CLASS_PORTAE_ATTR_SIZE		6
#define CLASS_PASSAGEIRO_ATTR_SIZE	11
#define CLASS_TIPO_AVIAO_ATTR_SIZE	16



/**
 * \brief Limpa as flags do cin e fica � espera de um input para prosseguir.
 * \details Serve para parar o programa e esperar que o utilizador fa�a algum input para prosseguir.
 */
void getch();


///getline que faz o sync para n�o ler lixo do buffer.
void getlineCin(string &output);


/**
 * \brief Mostra a "message" ao utilizador e espera por um input de um n�mero entre min (default � 0) e size-1 (default � INT_MAX).
 * \details Enquanto n�o for introduzido um input v�lido vai pedindo ao utilizador para introduzir novamente os dados.
 */
int get_int_cin(const char* message, int size = INT_MAX, int min = 0);

/**
 * \brief Mostra a "message" ao utilizador e espera por um input de um n�mero entre min (default � 0) e size-1 (default � UINT_MAX).
 * \details Enquanto n�o for introduzido um input v�lido vai pedindo ao utilizador para introduzir novamente os dados.
 */
template <class Tipo>
Tipo get_uint_cin(const char* message, Tipo size = UINT_MAX, Tipo min = 0, bool menu = false, const char* error_message = "N�mero fora do intervalo!") {

	if( (size == min) && min == 0)
		throw ExNoInterval();

	Tipo numero;
	do {
		cout << message << flush;

		/*
		 * Enquanto cin devolver um apontador NULL (e como tal no teste do if dar true (por estar negado)),
		 * devido ao facto de estar a ler dados que n�o s�o n�meros, (ex: caracteres...)
		 * informa ao utilizador que tem que introduzir um n� e pede para introduzir os dados novamente.
		 */
		if (!(cin >> numero)) {

			//Limpa as flags do cin
			cin.clear();

			//Extrai e ignora todos os caracteres que estavam no buffer de cin, visto que ao tentar-se introduzir
			//caracteres num int (por ex), o cin entra em estado de erro e n�o remove os caracteres que leu do buffer
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Introduza um n�mero!" << endl << endl;
		} else

			//Testa se os n�meros introduzidos est�o dentro do intervalo pedido
			if (menu)
				if (numero >= min && numero <= size)
					break; //Se estiverem sai-se do loop
				else
					cout << error_message << endl << endl; //Sen�o informasse o utilizador e pede-se novamente o n�
			else
				if (numero >= min && numero < size)
					break; //Se estiverem sai-se do loop
				else
					cout << error_message << endl << endl; //Sen�o informasse o utilizador e pede-se novamente o n�

	} while (true);

	if (menu)
		if(numero == 0)
			throw ExOutOfRange("");
		else
			return (numero - 1);
	else
		return numero;
}

///Pergunta message ao utilizador e retorna Sim/N�o.
bool get_yes_no(const char* message,
				const char* message_erro = "Introduziu uma op��o incorrecta!\nIntroduza S para continuar ou N para parar: ");

///Converte uma string para mai�sculas.
string to_upper(string str);


///Converte uma string para min�sculas.
string to_lower(string str);


///Fun��o que separa uma string em substrings sempre que encontrar o caracter delimitador ("delim").
vector <string> split(string in, char delim);

///Fun��o de convers�o de objecto para string usando o operador <<.
template <class T>
string to_string(T obj) {
	stringstream ss;
	ss << obj;
	return ss.str();
}


/**
 * \brief M�todo que imprime uma tabela com os dados de um vector de colunas (vector de strings).
 *
 * @param title Titulo da tabela.
 * @param columns Vector de colunas.
 * @param colNames Vector com o nome das colunas.
 * @param reverse Caso seja true, inverte-se a ordem dos dados na coluna (mostra a tabela invetida - linhas 0 1 2 3 passam a 3 2 1 0).
 * @param hide_index Caso seja true, n�o imprime a numera��o das linhas.
 * @return Um booleano caso tenha sido feito algum output de dados.
 */
bool printMenu(string & title, const vector< vector <string> > & columns, const vector <string> & colNames, bool menu = false, bool reverse = false, bool hide_index = false, bool hide_colnames = false);

#endif
