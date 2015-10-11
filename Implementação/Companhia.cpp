/**\file Companhia.cpp
 * \brief Ficheiro com a implementação da classe Companhia.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Companhia.cpp \n
 * DESCRIÇÃO: Ficheiro com a implementação da classe Companhia. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costaz
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#include "Companhia.h"

extern TipoAviaoDB tipoaviaoDB;

Companhia::~Companhia()
{
	if(_can_delete_values)
	{
		for(vector<Aviao*>::iterator it = _avioes.begin() ; it!=_avioes.end() ; ++it)
			delete (*it);
		for(vector<Tripulante*>::iterator it = _tripulacao.begin() ; it!=_tripulacao.end() ; ++it)
			delete (*it);
		for(vector<Voo*>::iterator it = _voos.begin() ; it!=_voos.end() ; ++it)
			delete (*it);
	}
}

bool Companhia::operator==(const Companhia &companhia) const {
	if ((_sigla == companhia._sigla) && (_nome == companhia._nome))
		return true;
	else
		return false;
}


bool Companhia::operator<(const Companhia &companhia) const {
	if (_nome < companhia._nome)
		return true;
	else if (_nome > companhia._nome)
		return false;
	else if (_sigla < companhia._sigla)
		return true;
	else
		return false;
}


string Companhia::getMatriculaAviaoCin(const char* mensagem) {
	//Verifica-se se a matrícula do avião já existe.
	string matricula;
	bool matricula_repetida;
	do {
		matricula_repetida = false;
		cout << mensagem << flush;
		getlineCin(matricula);

		for (vector<Aviao*>::const_iterator it = _avioes.begin(); it != _avioes.end(); ++it)
			if (matricula == (*it)->getMatricula()) {
				matricula_repetida = true;
				cout << "A matrícula já existe!" << endl << endl;
				break;
			}
	} while(matricula_repetida);

	return matricula;
}


unsigned Companhia::getBICin(const char* mensagem) {
	//Verifica-se se BI já existe
	unsigned BI;
	bool BI_repetido;
	do {
		BI_repetido = false;
		BI = get_uint_cin<unsigned>(mensagem);

		for (vector<Tripulante*>::const_iterator it = _tripulacao.begin(); it != _tripulacao.end(); ++it)
			if (BI == (*it)->getBI()) {
				BI_repetido = true;
				cout << "O BI introduzido já existe!" << endl << endl;
				break;
			}
	} while(BI_repetido);

	return BI;
}


unsigned Companhia::getNumeroTripulanteCin(const char* mensagem) {
//Verifica-se se número para o tripulante que se recebeu já existe
unsigned numero_tripulante;
bool numero_tripulante_repetido;
do {
	numero_tripulante_repetido = false;
	numero_tripulante = get_int_cin(mensagem);

	for (vector<Tripulante*>::const_iterator it = _tripulacao.begin(); it != _tripulacao.end(); ++it)
		if (numero_tripulante == (*it)->getNumero()) {
			numero_tripulante_repetido = true;
			cout << "O número para o Tripulante que introduziu já existe!" << endl << endl;
			break;
		}
} while(numero_tripulante_repetido);

return numero_tripulante;
}


unsigned Companhia::getNumeroVooCin(const char *mensagem) {
	//Verifica-se se número para o tripulante que se recebeu já existe
	unsigned numero_voo;
	bool numero_voo_repetido;
	do {
		numero_voo_repetido = false;
		numero_voo = get_int_cin(mensagem);

		for (vector<Voo*>::const_iterator it = _voos.begin(); it != _voos.end(); ++it)
			if (numero_voo == (*it)->getNumeroVoo()) {
				numero_voo_repetido = true;
				cout << "O número de Voo que introduziu já existe!" << endl << endl;
				break;
			}
	} while(numero_voo_repetido);

	return numero_voo;
}


