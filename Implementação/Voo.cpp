/**\file Voo.cpp
 * \brief Ficheiro com a implementa��o da classe Voo.
 *
 * PROJECTO: Projecto 2 - Gest�o do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Voo.cpp \n
 * DESCRI��O: Ficheiro com a implementa��o da classe Voo. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - V�tor Am�lio Maia Martins Moreira
 */

#include "Voo.h"


void Voo::criaFilaCheckIn() {
	//Simula��o da chegada aleat�ria dos passageiros
	vector <Passageiro*> passageiros_temp = _passageiros_voo;
	random_shuffle(passageiros_temp.begin(), passageiros_temp.end());
	size_t tamanho_inicial_vec = passageiros_temp.size();

	for(size_t i(0); i < tamanho_inicial_vec; ++i) {
		_fila_check_in.push(passageiros_temp.back());
		passageiros_temp.pop_back();
	}
}


bool Voo::operator==(const Voo &voo) const {
	if ((_numero_voo == voo._numero_voo))
		return true;
	else
		return false;
}

bool Voo::operator<(const Voo &voo) const {
	if (_datahora_saida < voo._datahora_saida)
		return true;
	else
		return false;
}
