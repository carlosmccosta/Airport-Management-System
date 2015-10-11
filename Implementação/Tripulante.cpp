/**\file Tripulante.cpp
 * \brief Ficheiro com a implemantação da classe Tripulante.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Tripulante.cpp \n
 * DESCRIÇÃO: Ficheiro com a implemantação da classe Tripulante. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#include "Tripulante.h"


bool Tripulante::operator==(const Tripulante &tripulante) const {
	if ((_numero == tripulante._numero))
		return true;
	else
		return false;
}


bool Tripulante::operator<(const Tripulante &tripulante) const {
	if (this->getNome() < tripulante.getNome())
		return true;
	else if (this->getNome() > tripulante.getNome())
		return false;
	else if (_numero < tripulante._numero)
		return true;
	else
		return false;
}
