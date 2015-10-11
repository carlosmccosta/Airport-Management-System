/**\file Passageiro.cpp
 * \brief Ficheiro com a implementa��o da classe Passageiro.
 *
 * PROJECTO: Projecto 2 - Gest�o do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Passageiro.cpp \n
 * DESCRI��O: Ficheiro com a implementa��o da classe Passageiro. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - V�tor Am�lio Maia Martins Moreira
 */

#include "Passageiro.h"


bool Passageiro::operator==(const Passageiro &passageiro) {
	if ( this->getBI() == passageiro.getBI() )
		return true;
	else
		return false;
}


bool Passageiro::operator<(const Passageiro &passageiro) const {
	return (this->getBI() < passageiro.getBI());
}


//Inicializa��o do vector que contem a informa��o associada a cada tipo da enumera��o necessidades_especiais_t
vector <string> Passageiro::_necessidades_especiais_info;

void Passageiro::init_necessidades_especiais_info() {
	_necessidades_especiais_info.clear();
	_necessidades_especiais_info.push_back("Passageiro com cadeira de rodas");
	_necessidades_especiais_info.push_back("Passageiro idoso");
	_necessidades_especiais_info.push_back("Passageiro de menor idade desacompanhado");
	_necessidades_especiais_info.push_back("Passageiro sem necessidades especiais");
}

void Passageiro::listNecessidadesEspeciaisInfo() {
	vector < vector <string> > info;
	info.push_back(_necessidades_especiais_info);
	string title = (string)"Possiveis necessidades especiais";
	vector <string> colnames;
	colnames.push_back("");
	printMenu(title, info, colnames, false, false, false, true);
	cout << endl;
}
