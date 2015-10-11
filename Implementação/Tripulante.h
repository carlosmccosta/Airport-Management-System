/**\file Tripulante.h
 * \brief Classe que contém a informação associada a cada Tripulante Aéreo.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Tripulante.h \n
 * DESCRIÇÃO: Classe que contém a informação associada a cada Tripulante Aéreo. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#ifndef TRIPULANTE_H_
#define TRIPULANTE_H_

#include "Pessoa.h"
#include "DataHora.h"

//Foward declarations de classes necessárias (pointers)
class Companhia;
class Voo;

#include <string>

using std::string;


/**
 * \brief Classe que armazena informação acerca de um tripulante de uma dada companhia aérea.
 * \details Subclasse de Pessoa.
 */
class Tripulante : public Pessoa {
private:
	unsigned _numero;				///<Ex: 230
	string _categoria;				///<Ex: Cte
	unsigned _salario_hora;			///<Ex: 120
	unsigned _numero_horas_trabalho;

	string _tipoContrato;
	DataHora _expiracaoContrato;
	Companhia *_companhia;			///<Companhia a que pertence o tripulante
	Voo *_voo_actual;				///<Voo a que o tripulante está associado num dado momento (NULL, se não tem voo atribuido)

public:
	Tripulante(): _numero(0), _salario_hora(0), _companhia(NULL), _voo_actual(NULL) {}
	//(numero, categoria, nome, salario hora)
	//<230, Cte, Pinto da Costa, 120>
	Tripulante(unsigned numero, string categoria, string nome, unsigned salario_hora):
		Pessoa(), _numero(numero), _categoria(categoria), _salario_hora(salario_hora) { setNome(nome); }
	Tripulante(string nome, string morada, string nacionalidade, unsigned contacto, unsigned BI, unsigned idade,
			unsigned numero, string categoria, unsigned salario_hora, unsigned numero_horas_trabalho, string tipoContrato, DataHora expiracaoContrato,
			Companhia *companhia, Voo *voo_actual) :
				Pessoa(nome, morada, nacionalidade, contacto, BI, idade),
				_numero(numero), _categoria(categoria), _salario_hora(salario_hora), _numero_horas_trabalho(numero_horas_trabalho),
				_tipoContrato(tipoContrato), _expiracaoContrato(expiracaoContrato),
				_companhia(companhia), _voo_actual(voo_actual) {}
	virtual ~Tripulante() {}

	unsigned getNumero() const { return _numero; }
	string getCategoria() const { return _categoria; }
	unsigned getSalarioHora() const { return _salario_hora; }
	unsigned getNumeroHorasTrabalho() const { return _numero_horas_trabalho; }
	string getTipoContrato() const { return _tipoContrato; }
	DataHora getExpiracaoContrato() const { return _expiracaoContrato; }
	Companhia* getCompanhia() const { return _companhia; }
	Voo* getVooActual() const { return _voo_actual; }

	void setNumero(unsigned numero) { _numero = numero; }
	void setCategoria(string categoria) { _categoria = categoria; }
	void setSalarioHora(unsigned salario_hora) { _salario_hora = salario_hora; }
	void setNumeroHorasTrabalho(unsigned numero_horas_trabalho) { _numero_horas_trabalho = numero_horas_trabalho; }
	void setTipoContrato(string tipoContrato) { _tipoContrato = tipoContrato; }
	void setExpiracaoContrato(DataHora expericaoContrato) { _expiracaoContrato = expericaoContrato; }
	void setCompanhia(Companhia *companhia) { _companhia = companhia; }
	void setVooActual(Voo *voo_actual) { _voo_actual = voo_actual; }

	virtual void imprimeInfo() const {}


	///Operador que verifica se dois tripulantes são equivalentes, comparando o seu número.
	bool operator==(const Tripulante &tripulante) const;
	///Operador que verifica se dois tripulantes são equivalentes, comparando o seu número  (overloading para tratar de apontadores para tripulantes).
	bool operator==(const Tripulante* &tripulante) const;

	/**
	 * \brief Operador que verifica se o nome de um Tripulante é "menor" do que outro.
	 * \details Se os nomes forem iguais compara o número desses Tripulantes.
	 */
	bool operator<(const Tripulante &tripulante) const;
};

#endif
