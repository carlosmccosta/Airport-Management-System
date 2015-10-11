/**\file Piloto.h
 * \brief Classe que contém a informação associada a cada plano de voos de uma companhia aérea.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Piloto.h \n
 * DESCRIÇÃO: Classe que contém a informação associada a cada plano de voo de uma companhia aérea. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#ifndef PILOTO_H_
#define PILOTO_H_

#include "Tripulante.h"
#include "Companhia.h"
#include "Voo.h"
#include "Comandos.h"
#include "DataHora.h"
#include "utils.h"

///Classe que contém a informação associada a cada plano de voo de uma companhia aérea. \n
class Piloto : public Tripulante {
public:
	Piloto(): Tripulante() {}
	//(numero, categoria, nome, salario hora)
	//<230, Cte, Pinto da Costa, 120>
	Piloto(unsigned numero, string categoria, string nome, unsigned salario_hora):
		Tripulante(numero, categoria, nome, salario_hora) {}
	Piloto(string nome, string morada, string nacionalidade, unsigned contacto, unsigned BI, unsigned idade,
			unsigned numero, string categoria, unsigned salario_hora, unsigned numero_horas_trabalho, string tipoContrato, DataHora expiracaoContrato,
			Companhia *companhia, Voo *voo_actual) :
				Tripulante(nome, morada, nacionalidade, contacto, BI, idade,
						numero, categoria, salario_hora, numero_horas_trabalho, tipoContrato, expiracaoContrato,
						companhia, voo_actual) {}
	virtual ~Piloto() {}

	virtual void imprimeInfo();
};

#endif
