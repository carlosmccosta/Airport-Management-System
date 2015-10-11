/**\file Aviao.h
 * \brief Classe que contém a informação associada a um avião.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Aviao.h \n
 * DESCRIÇÃO: Classe que contém a informação associada a cada avião. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#ifndef AVIAO_H_
#define AVIAO_H_

#include <string>

//Foward declarations de classes necessárias (pointers)
class Companhia;
class Voo;

#include "TipoAviao.h"
#include "DataHora.h"

using std::string;

///Classe que armazena informação acerca de um avião de uma dada companhia.
class Aviao
{
private:
	string _matricula;				///<Ex: CSTNA
	string _nome;					///<Ex: Camões
	unsigned _peso_max_bagagem;		///<Peso máximo da bagagem por passageiro. Ex: 50

	TipoAviao *_tipoAviao;
	Companhia *_companhia;			///<Companhia a que pertence o avião
	Voo *_voo_actual;				///<Voo a que o avião está atribuído
	DataHora _dataConstrucao;
	DataHora _primeiroVoo;
	DataHora _ultimaRevisao;
	DataHora _proximaRevisao;

public:
	Aviao(): _peso_max_bagagem(0), _tipoAviao(NULL), _companhia(NULL), _voo_actual(NULL) {}
	//(matricula, nome, peso máximo)
	//<CSTNA, Camões, 50>
	Aviao(string matricula, string nome, unsigned pesoMaxBagagem) :
		_matricula(matricula), _nome(nome), _peso_max_bagagem(pesoMaxBagagem) {}
	Aviao(string matricula, string nome, unsigned pesoMaxBagagem,
			TipoAviao *tipoAviao, Companhia *companhia, Voo *voo_actual,
			DataHora dataConstrucao, DataHora primeiroVoo, DataHora ultimaRevisao, DataHora proximaRevisao) :
				_matricula(matricula), _nome(nome), _peso_max_bagagem(pesoMaxBagagem),
				_tipoAviao(tipoAviao), _companhia(companhia), _voo_actual(voo_actual),
				_dataConstrucao(dataConstrucao), _primeiroVoo(primeiroVoo),
				_ultimaRevisao(ultimaRevisao), _proximaRevisao(proximaRevisao) {}
	virtual ~Aviao() {}

	string getMatricula() const { return _matricula; }
	string getNome() const { return _nome; }
	unsigned getPesoMaxBagagem() const { return _peso_max_bagagem; }
	TipoAviao* getTipoAviao() { return _tipoAviao; }
	Companhia *getCompanhia() const { return _companhia; }
	Voo *getVooActual() const { return _voo_actual; }
	DataHora getDataConstrucao() const { return _dataConstrucao; }
	DataHora getPrimeiroVoo() const { return _primeiroVoo; }
	DataHora getUltimaRevisao() const { return _ultimaRevisao; }
	DataHora getProximaRevisao() const { return _proximaRevisao; }

	void setMatricula(string matricula) { _matricula = matricula; }
	void setNome(string nome) { _nome = nome; }
	void setPesoMaxBagagem(unsigned pesoMaxBagagem) { _peso_max_bagagem = pesoMaxBagagem; }
	void setTipoAviao(TipoAviao* tipoAviao) { _tipoAviao = tipoAviao; }
	void setCompanhia(Companhia *companhia) { _companhia = companhia; }
	void setVooActual(Voo *voo_actual) { _voo_actual = voo_actual; }
	void setDataConstrucao(DataHora dataConstrucao) { _dataConstrucao = dataConstrucao; }
	void setPrimeiroVoo(DataHora primeiroVoo) { _primeiroVoo = primeiroVoo; }
	void setUltimaRevisao(DataHora ultimaRevisao) { _ultimaRevisao = ultimaRevisao; }
	void setProximaRevisao(DataHora proximaRevisao) { _proximaRevisao = proximaRevisao; }


	///Operador que permite comparar se dois aviões são equivalentes, comparando a sua matrícula.
	bool operator==(const Aviao &aviao) const;

	///Operador que verifica se a matricula de um avião é menor do que outra.
	bool operator<(const Aviao &aviao) const;
};

#endif
