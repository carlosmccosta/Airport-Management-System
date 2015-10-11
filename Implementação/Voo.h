/**\file Voo.h
 * \brief Classe que contém a informação associada a cada plano de voos de uma companhia aérea.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Voo.h \n
 * DESCRIÇÃO: Classe que contém a informação associada a cada plano de voo de uma companhia aérea. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#ifndef VOO_H_
#define VOO_H_

#include <string>
#include <queue>
#include <cstdlib>
#include <algorithm>

#include "Passageiro.h"
#include "Tripulante.h"
#include "DataHora.h"
#include "PortaEmbarque.h"
#include "Aviao.h"

//Foward declaration da classe avião para evitar mutual includes
class Companhia;

using std::string;
using std::queue;
using std::priority_queue;
using std::random_shuffle;


 ///Classe que armazena informação acerca de um voo de uma dada companhia.
class Voo
{
private:
	unsigned _numero_voo;				///<Ex: 301
	string _origem;						///<Ex: OPO
	string _destino;					///<Ex: ORY
	DataHora _datahora_saida;			///<Ex: 2010/09/03 10:00
	DataHora _datahora_chegada;			///<Ex: 2010/09/03 12:00
	unsigned _numero_passageiros;		///<Ex: 125

	PortaEmbarque *_porta_embarque;
	Aviao *_aviao_ptr;
	Companhia *_companhia;
	unsigned _atraso;
	bool _cancelado;
	bool _fechado;

	vector <Passageiro*> _passageiros_voo;
	queue <Passageiro*> _fila_check_in;
	priority_queue <Passageiro*> _passageiros_voo_pq;
	vector <Tripulante*> _tripulantes_voo;


public:
	///Construtor que inicializa os elementos com valores inválidos.
	Voo(): _numero_voo(0), _numero_passageiros(0),
		_porta_embarque(NULL), _aviao_ptr(NULL), _companhia(NULL), _atraso(0), _cancelado(false), _fechado(false), _passageiros_voo(), _passageiros_voo_pq(), _tripulantes_voo() {}
	//(número voo, companhia, origem, destino, avião, data/hora saida, data/hora chegada, numero passageiros).
	//Ex: <301, TAP, OPO, ORY, CSTNA, 2010/09/03 10:00, 2010/09/03 12:00, 125>
	Voo(unsigned numero_voo, string origem, string destino,
			DataHora datahora_saida, DataHora datahora_chegada, unsigned numero_passageiros,
			PortaEmbarque *porta_embarque = NULL, Aviao *aviao_ptr = NULL, Companhia *companhia = NULL,
			unsigned atraso = 0, bool cancelado = false, bool fechado = false,
			const vector <Passageiro*> &passageiros_voo = vector <Passageiro*>(0),
			const queue <Passageiro*> &fila_check_in = queue <Passageiro*>(),
			const priority_queue <Passageiro*> &passageiros_voo_pq = priority_queue <Passageiro*>(),
			const vector <Tripulante*> &tripulantes_voo = vector <Tripulante*>(0)):
				_numero_voo(numero_voo), _origem(origem), _destino(destino),
				_datahora_saida(datahora_saida), _datahora_chegada(datahora_chegada), _numero_passageiros(numero_passageiros),
				_porta_embarque(porta_embarque), _aviao_ptr(aviao_ptr), _companhia(companhia),
				_atraso(atraso), _cancelado(cancelado), _fechado(fechado), _passageiros_voo(passageiros_voo), _fila_check_in(fila_check_in),
				_passageiros_voo_pq(passageiros_voo_pq), _tripulantes_voo(tripulantes_voo) {}
	virtual ~Voo() {}

	unsigned getNumeroVoo() const { return _numero_voo; }
	Companhia* getCompanhia() const { return _companhia; }
	string getOrigem() const { return _origem; }
	string getDestino() const { return _destino; }
    DataHora getDatahoraSaida() const { return _datahora_saida; }
	DataHora getDatahoraChegada() const { return _datahora_chegada; }
	unsigned getNumeroPassageiros() const { return _numero_passageiros; }
	PortaEmbarque* getPortaEmbarque() const { return _porta_embarque; }
	Aviao* getAviao() const { return _aviao_ptr; }
	unsigned getAtraso() const { return _atraso; }
	bool getCancelado() const { return _cancelado; }
	bool getFechado() const { return _fechado; }


	vector <Passageiro*> getPassageirosVoo() const { return _passageiros_voo; }
	//Variante do get do vector usada em iteradores constantes
	const vector <Passageiro*>& getConstRefPassageirosVoo() const { return _passageiros_voo; }
	//Variante do get do vector que permite alterá-lo através da referência que é dada
	vector <Passageiro*>& getRefPassageirosVoo() { return _passageiros_voo; }

	queue <Passageiro*> getFilaCheckIn() const { return _fila_check_in; }
	//Variante do get da queue usada em iteradores constantes
	const queue <Passageiro*>& getConstRefFilaCheckIn() const { return _fila_check_in; }
	//Variante do get da queue que permite alterá-lo através da referência que é dada
	queue <Passageiro*>& getRefFilaCheckIn() { return _fila_check_in; }

	priority_queue <Passageiro*> getPassageirosVooPQ() const { return _passageiros_voo_pq; }
	//Variante do get da priority_queue usada em iteradores constantes
	const priority_queue <Passageiro*>& getConstRefPassageirosVooPQ() const { return _passageiros_voo_pq; }
	//Variante do get da priority_queue que permite alterá-lo através da referência que é dada
	priority_queue <Passageiro*>& getRefPassageirosVooPQ() { return _passageiros_voo_pq; }

	vector <Tripulante*> getTripulantesVoo() const { return _tripulantes_voo; }
	//Variante do get do vector usada em iteradores constantes
	const vector <Tripulante*>& getConstRefTripulantesVoo() const { return _tripulantes_voo; }
	//Variante do get do vector que permite alterá-lo através da referência que é dada
	vector <Tripulante*>& getRefTripulantesVoo() { return _tripulantes_voo; }


	void setNumero_voo(unsigned numero_voo) { _numero_voo = numero_voo; }
	void setCompanhia(Companhia *companhia) { _companhia = companhia; }
	void setOrigem(string origem) { _origem = origem; }
	void setDestino(string destino) { _destino = destino; }
	void setDatahoraSaida(DataHora datahora_saida) { _datahora_saida = datahora_saida; }
	void setDatahoraChegada(DataHora datahora_chegada) { _datahora_chegada = datahora_chegada; }
	void setNumeroPassageiros(unsigned numero_passageiros) { _numero_passageiros = numero_passageiros; }
	void setPortaEmbarque(PortaEmbarque *porta_embarque) { _porta_embarque = porta_embarque; }
	void setAviao(Aviao *aviao_ptr) { _aviao_ptr = aviao_ptr; }
	void setAtraso(unsigned atraso) { _atraso = atraso; }
	void setCanselado(bool canselado) { _cancelado = canselado; }
	void setFechado(bool fechado) { _fechado = fechado; }
	void setPassageirosVoo(priority_queue <Passageiro*> passageiros_voo) { _passageiros_voo_pq = passageiros_voo; }
	void setTripulantesVoo(vector <Tripulante*> tripulantes_voo) { _tripulantes_voo = tripulantes_voo; }

	///Adiciona um passageiro ao vector de passageiros do voo.
	void addPassageiro(Passageiro* passageiro) { _passageiros_voo.push_back(passageiro); }
	///Adiciona um passageiro à fila de prioridade do voo, que vai ser usada a quando do embarque.
	void addPassageiroPQ(Passageiro *passageiro) { _passageiros_voo_pq.push(passageiro); }
	///Simula a chegada dos passageiros a uma fila de check-in, criando a queue fila_check_in
	void criaFilaCheckIn();

	///Operador que permite comparar se dois voos são equivalentes, comparando o número do voo.
	bool operator==(const Voo &voo) const;
	///Operador que permite comparar se a hora de partida do voo é menor do que a hora de partida de outro voo.
	bool operator<(const Voo &voo) const;
};

#endif
