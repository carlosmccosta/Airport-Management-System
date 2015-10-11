/**\file Aeroporto.h
 * \brief Classe que contém a informação associada ao Aeroporto.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Aeroporto.h \n
 * DESCRIÇÃO: Classe que contém a informação associada ao Aeroporto. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#ifndef AEROPORTO_H_
#define AEROPORTO_H_

#include "Aviao.h"
#include "TipoAviao.h"
#include "Companhia.h"
#include "Tripulante.h"
#include "Voo.h"
#include "PortaEmbarque.h"
#include "Exceptions.h"
#include "utils.h"
#include "BST.h"

// remover no fim as que não são necessárias

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <limits>
#include <time.h>
#include <algorithm>
#include <utility>
#include <functional>
//#include <hash_set>

#ifdef __GNUC__			// se compilar com GCC
#include <hash_set>
using namespace __gnu_cxx;
#else					// se for visual studio
#include <hash_set>
#define _DEFINE_DEPRECATED_HASH_CLASSES 0
using namespace std;
using namespace stdext;
#endif

using std::ifstream;
using std::ofstream;
using std::endl;
using std::cout;
using std::cin;
using std::setw;
using std::getline;
using std::string;
using std::vector;
using std::sort;
using std::find_if;
using std::bind2nd;
using std::stringstream;
using std::equal_to;

extern PortaEmbarquePtr porta_embarque_null;

#ifdef __GNUC__				// se compilar com GCC

//Tabela de dispersão dos voos
struct hash_voo_operators {
	bool operator() (const Voo *voo1, const Voo *voo2) const { return (voo1->getNumeroVoo() == voo2->getNumeroVoo()); }
	size_t operator() (const Voo *voo) const { return voo->getNumeroVoo(); }
};

typedef hash_set<Voo*, hash_voo_operators, hash_voo_operators> HASH_SET_VOOS;

#else						// se for visual studio

class hash_voo_operators
{

public:
   static const size_t bucket_size = 4;
   static const size_t min_buckets = 8;

   size_t operator()(const Voo* key) const
   {
	   return (key->getNumeroVoo());
   }
   bool operator()(const Voo* key1, const Voo* key2) const
   {
	   return (key1->getNumeroVoo() == key2->getNumeroVoo());
   }
};

typedef hash_set<Voo*, hash_voo_operators> HASH_SET_VOOS;

#endif



///Classe que armazena informação acerca de um aeroporto.
class Aeroporto {
private:
	string _nome;
	string _localizacao;
	string _pais;
	unsigned _taxa_portas_embarque;

	vector <Companhia*> _companhias;
	//vector <PortaEmbarque*> _portas_embarque;
	vector <Passageiro*> _passageiros_aeroporto;

	//BST das portas de embarque
	BST<PortaEmbarquePtr> _portas_embarque_bst;

	HASH_SET_VOOS _hash_set_voos;

public:
	Aeroporto(): _nome((string)"Aerporto do Porto"), _localizacao((string)"Porto"), _pais((string)"Portugal"), _taxa_portas_embarque(0),
	_companhias(), _passageiros_aeroporto(), _portas_embarque_bst(porta_embarque_null) {}
	Aeroporto(string nome, string localizacao, string pais, unsigned taxa_portas_embarque)
		: _nome(nome), _localizacao(localizacao), _pais(pais), _taxa_portas_embarque(taxa_portas_embarque),
		  _companhias(), _portas_embarque_bst(porta_embarque_null) {}
	virtual ~Aeroporto();

	string getNome() const { return _nome; }
	string getLocalizacao() const { return _localizacao; }
	string getPais() const { return _pais ; }
	unsigned getTaxaPortasEmbarque() const { return _taxa_portas_embarque; }


	vector <Companhia*> getCompanhias() const { return _companhias; }
	//Variante do get do vector usada em iteradores constantes
	const vector <Companhia*>& getConstRefCompanhias() { return _companhias; }
	//Variante do get do vector que permite alterá-lo através da referência que é dada
	vector <Companhia*>& getRefCompanhias() { return _companhias; }

	HASH_SET_VOOS getHashSetVoos() const { return _hash_set_voos; }
	//Variante do get do vector usada em iteradores constantes
	const HASH_SET_VOOS& getConstRefHashSetVoos() { return _hash_set_voos; }
	//Variante do get do vector que permite alterá-lo através da referência que é dada
	HASH_SET_VOOS& getRefHashSetVoos() { return _hash_set_voos; }


/*
	const vector <PortaEmbarque*> getPortasEmbarque() const { return _portas_embarque; }
	const vector <PortaEmbarque*>& getConstRefPortasEmbarque() const { return _portas_embarque; }
	vector <PortaEmbarque*>& getRefPortasEmbarque() { return _portas_embarque; }
*/
	vector <Passageiro*> getPassageirosAeroporto() const { return _passageiros_aeroporto; }
	const vector <Passageiro*>& getConstRefPassageirosAeroporto() const { return _passageiros_aeroporto; }
	vector <Passageiro*>& getRefPassageirosAeroporto() { return _passageiros_aeroporto; }

	BST <PortaEmbarquePtr> getPortasEmbarqueBST() const { return _portas_embarque_bst; }
	const BST <PortaEmbarquePtr>& getConstRefPortasEmbarqueBST() const { return _portas_embarque_bst; }
	BST <PortaEmbarquePtr>& getRefPortasEmbarqueBST() { return _portas_embarque_bst; }

	void setNome(string nome) { _nome = nome; }
	void setLocalizacao(string localizacao) { _localizacao = localizacao; }
	void setPais(string pais) { _pais = pais; }
	void setTaxaPortasEmbarque(unsigned taxa_portas_embarque) { _taxa_portas_embarque = taxa_portas_embarque; }

	void setCompanhias(vector <Companhia*> companhias) { _companhias = companhias; }
	//void setPortasEmbarque(vector <PortaEmbarque*> portas_embarque) { _portas_embarque = portas_embarque; }
	void setPassageirosAeroporto(vector <Passageiro*> passageiros_aeroporto) { _passageiros_aeroporto = passageiros_aeroporto; }


	void addVooHashSetVoos(Voo *voo) { _hash_set_voos.insert(voo); }
	HASH_SET_VOOS::iterator findVooHashSetVoos(Voo *voo) { return _hash_set_voos.find(voo); }
	void delVooHashSetVoos(Voo *voo) { _hash_set_voos.erase(voo); }
};

#endif
