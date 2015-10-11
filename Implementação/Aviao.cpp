/**\file Aviao.cpp
 * \brief Ficheiro com a implementação da classe Aviao.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Aviao.cpp \n
 * DESCRIÇÃO: Ficheiro com a implementação da classe Aviao. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#include "Aviao.h"


bool Aviao::operator==(const Aviao &aviao) const {
	if (_matricula == aviao._matricula)
		return true;
	else
		return false;
}

bool Aviao::operator<(const Aviao &aviao) const {
	if (_matricula < aviao._matricula)
		return true;
	else
		return false;
}
