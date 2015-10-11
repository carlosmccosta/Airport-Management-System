/**\file Pessoa.cpp
 * \brief Ficheiro com a implementação da classe Pessoa.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Pessoa.cpp \n
 * DESCRIÇÃO: Ficheiro com a implementação da classe Pessoa. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#include "Pessoa.h"


bool Pessoa::operator==(const Pessoa &pessoa) {
	if (_BI == pessoa._BI)
		return true;
	else
		return false;
}


bool Pessoa::operator<(const Pessoa &pessoa) {
	if (_nome < pessoa._nome)
		return true;
	else if (_nome > pessoa._nome)
		return false;
	else if (_BI < pessoa._BI)
		return true;
	else
		return false;
}
