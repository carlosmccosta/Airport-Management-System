/**\file Aeroporto.cpp
 * \brief Ficheiro com a implementação da classe Aeroporto.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Aeroporto.cpp \n
 * DESCRIÇÃO: Ficheiro com a implementação da classe Aeroporto. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#include "Aeroporto.h"

Aeroporto::~Aeroporto()
{
	for(vector<Companhia* >::iterator it = _companhias.begin() ; it!=_companhias.end() ; ++it)
		delete (*it);

	BSTItrIn<PortaEmbarquePtr> it2(_portas_embarque_bst);

	while (!it2.isAtEnd())
	{
		delete it2.retrieve()();
		it2.advance();
	}

	for(vector<Passageiro* >::iterator it = _passageiros_aeroporto.begin() ; it!=_passageiros_aeroporto.end() ; ++it)
		delete (*it);
}

