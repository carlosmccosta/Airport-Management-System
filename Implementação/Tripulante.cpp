/**\file Tripulante.cpp
 * \brief Ficheiro com a implemanta��o da classe Tripulante.
 *
 * PROJECTO: Projecto 2 - Gest�o do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Tripulante.cpp \n
 * DESCRI��O: Ficheiro com a implemanta��o da classe Tripulante. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - V�tor Am�lio Maia Martins Moreira
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
