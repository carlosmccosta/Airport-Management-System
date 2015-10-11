/**\file Companhia.h
 * \brief Classe que cont�m informa��o associada a uma Companhia.
 *
 * PROJECTO: Projecto 2 - Gest�o do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Companhia.cpp \n
 * DESCRI��O: Classe que cont�m informa��o associada a uma Companhia A�rea. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - V�tor Am�lio Maia Martins Moreira
 */

#ifndef COMPANHIA_H_
#define COMPANHIA_H_

#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <utility>
#include <functional>
#include <sstream>

#include "Aviao.h"
#include "Tripulante.h"
#include "DataHora.h"
#include "Voo.h"
#include "TipoAviao.h"
#include "Exceptions.h"
#include "utils.h"
#include "Comandos.h"
#include "TipoAviaoDB.h"

using std::vector;
using std::string;
using std::endl;
using std::find_if;
using std::bind2nd;
using std::equal_to;
using std::find;
using std::stringstream;
using std::flush;
using std::pow;


extern TipoAviaoDB tipoaviaoDB;

///Classe que armazena informa��o acerca de uma Companhia de um dado Aeroporto.
class Companhia {
private:
	string _sigla;						///<Ex: TAP
	string _nome;						///<Ex: TAP Portugal
	unsigned _taxa_balcoes;

	vector <Aviao*> _avioes;
	vector <Tripulante*> _tripulacao;
	vector <Voo*> _voos;
	//� um vector de apontadores porque o mesmo tipo de avi�o pode estar associado a avi�es de companhias diferentes (evita duplica��o de dados)
	vector <TipoAviao*> _frota;

	bool _can_delete_values;

public:
	Companhia(): _taxa_balcoes(0), _avioes(), _tripulacao(), _voos(), _frota(), _can_delete_values(false) {}
	Companhia(string sigla, string nome, unsigned taxa_balcoes): _sigla(sigla), _nome(nome), _taxa_balcoes(taxa_balcoes),
			_avioes(), _tripulacao(), _voos(), _frota(), _can_delete_values(true) {}
	virtual ~Companhia();

	string getSigla() const { return _sigla; }
	string getNome() const { return _nome; }
	unsigned getTaxaBalcoes() const { return _taxa_balcoes; }

	vector <Aviao*> getAvioes() const { return _avioes; }
	//Variante dos gets para os vectores, usadas em iteradores constantes
	const vector <Aviao*>& getConstRefAvioes() const { return _avioes; }
	//Variante do get do vector que permite alter�-lo atrav�s da refer�ncia que � dada
	vector <Aviao*>& getRefAvioes() { return _avioes; }

	vector <Tripulante*> getTripulacao() const { return _tripulacao; }
	const vector <Tripulante*>& getConstRefTripulacao() const { return _tripulacao; }
	vector <Tripulante*>& getRefTripulacao() { return _tripulacao; }

	vector <Voo*> getVoos() const { return _voos; }
	const vector <Voo*>& getConstRefVoos() const { return _voos; }
	vector <Voo*>& getRefVoos() { return _voos; }

	vector <TipoAviao*> getFrota() const { return _frota; }
	const vector <TipoAviao*>& getConstRefFrota() const { return _frota; }
	vector <TipoAviao*>& getRefFrota() { return _frota; }

	void setSigla(string sigla) { _sigla = sigla; }
	void setNome(string nome) { _nome = nome; }
	void setTaxaBalcoes(unsigned taxa_balcoes) { _taxa_balcoes = taxa_balcoes; }

	void setAvioes(vector <Aviao*> avioes) { _avioes = avioes; }
	void setTripulacao(vector <Tripulante*> tripulacao) { _tripulacao = tripulacao; }
	void setVoos(vector <Voo*> voos) { _voos = voos; }
	void setFrota(vector <TipoAviao*> frota) { _frota = frota; }

	///Operador que permite comparar se duas Companhias t�m a mesma sigla e nome.
	bool operator==(const Companhia &companhia) const;

	///Operador que permite verificar se o nome de uma companhia � "menor" que o de outra. Se forem iguais compara a sigla.
	bool operator<(const Companhia &companhia) const;



	/**
	 * \brief Fun��o que pede ao utilizador uma nova matr�cula para um avi�o, verificando se ela j� est� atribu�da.
	 * \details Caso esteja, continua a pedir para introduzir uma nova matr�cula.
	 * @param mensagem Mesagem a ser mostrada ao utilizador antes de pedir a matr�cula.
	 * @return Uma matricula, que � unica naquela companhia.
	 */
	string getMatriculaAviaoCin(const char* mensagem);

	/**
	 * \brief Fun��o que pede ao utilizador um BI.
	 * @param mensagem Mesagem a ser mostrada ao utilizador antes de pedir o BI.
	 * @return Um BI que � �nico naquela companhia.
	 */
	unsigned getBICin(const char* mensagem);

	/**
	 * \brief Fun��o que pede ao utilizador um n�mero (ID) para um tripulante.
	 * @param mensagem Mensagem a ser mostrada ao utilizador antes de pedir o n�mero.
	 * @return Um ID para um tripulante que � �nico na companhia.
	 */
	unsigned getNumeroTripulanteCin(const char* mensagem);

	/**
	 * \brief Fun��o que pede ao utilizador um n�mero de voo e verifica se esse n�mero (ID), � �nico na companhia em quest�o.
	 * @param mensagem Mensagem a ser mostrada ao utilizador antes de se pedir o n�mero.
	 * @return O n�mero de um voo �nico na companhia.
	 */
	unsigned getNumeroVooCin(const char *mensagem);

};

#endif
