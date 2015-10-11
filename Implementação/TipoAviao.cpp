/**\file TipoAviao.cpp
 * \brief Ficheiro com a implementação da classe TipoAviao.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: TipoAviao.cpp \n
 * DESCRIÇÃO: Ficheiro com a implementação da classe TipoAviao. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#include "TipoAviao.h"


bool TipoAviao::operator==(const TipoAviao &tipo_aviao) const {
	if (_nome_tipo == tipo_aviao._nome_tipo)
		return true;
	else
		return false;
}


bool TipoAviao::operator<(const TipoAviao &tipo_aviao) const {
	if (_nome_tipo < tipo_aviao._nome_tipo)
		return true;
	else
		return false;
}
