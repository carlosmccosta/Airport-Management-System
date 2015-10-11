/**\file PortaEmbarque.h
 * \brief Classe que contém informação de uma dada porta de embarque de um aeroporto.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: PortaEmbarque.h \n
 * DESCRIÇÃO: Classe que contém informação de uma dada porta de embarque de um aeroporto. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */


#ifndef PORTAEMBARQUE_H_
#define PORTAEMBARQUE_H_

#include <string>
#include <vector>
#include <utility>
#include "utils.h"

//Para resolver o problema de dependência mútua
class Voo;

using std::string;
using std::pair;
using std::vector;

///Classe que contém informação de uma dada porta de embarque de um aeroporto.
class PortaEmbarque {
public:
	enum categorias_avioes_t { MEDIO_CURSO, LONGO_CURSO };

private:
	static vector <string> _categorias_avioes_info;

	string _numero;				///<Ex: P01
	string _localizacao;		///<Ex: Norte
	unsigned _capacidade_pass;	///<Ex: 250
	unsigned _vagas_pass;		///<Ex: 5 lugares vazios
	unsigned _categoria_avioes;	///<Ex: Médio Curso

	///Vector de apontadores para os voos que estão a usar esta porta de embarque.
	vector <Voo*> _vec_voos_porta_embarque;

public:
	PortaEmbarque(): _capacidade_pass(0), _vagas_pass(0),  _vec_voos_porta_embarque() {}
	PortaEmbarque(string numero, string localizacao, unsigned capacidade_pass, unsigned vagas_pass, unsigned categoria_avioes, vector <Voo*> vec_voos_porta_embarque = vector <Voo*> ()):
		_numero(numero), _localizacao(localizacao), _capacidade_pass(capacidade_pass), _vagas_pass(vagas_pass), _categoria_avioes(categoria_avioes),
		_vec_voos_porta_embarque(vec_voos_porta_embarque) {}
	virtual ~PortaEmbarque() {}

	string getNumero() const { return _numero; }
	string getLocalizacao() const { return _localizacao; }
	unsigned getCapacidadePass() const { return _capacidade_pass; }
	unsigned getVagasPass() const { return _vagas_pass; }
	unsigned getCategoriaAvioes() const { return _categoria_avioes; }


	vector <Voo*> getVoosPortaEmbarque() const { return _vec_voos_porta_embarque; }
	//Variante do get do vector usada em iteradores constantes
	const vector <Voo*>& getConstRefVoosPortaEmbarque() const { return _vec_voos_porta_embarque; }
	//Variante do get do vector que permite alterá-lo através da referência que é dada
	vector <Voo*>& getRefVoosPortaEmbarque() { return _vec_voos_porta_embarque; }


	void setNumero(string numero) { _numero = numero; }
	void setLocalizacao(string localizacao) { _localizacao = localizacao; }
	void setCapacidadePass(unsigned capacidade_pass) { _capacidade_pass = capacidade_pass; }
	void setVagasPass(unsigned vagas_pass) { _vagas_pass = vagas_pass; }
	void setCategoriaAvioes(unsigned categoria_avioes) { _categoria_avioes = categoria_avioes; }
	void setVoosPortaEmbarque(vector <Voo*> vec_voos_porta_embarque) { _vec_voos_porta_embarque = vec_voos_porta_embarque; }

	///Operador que permite verificar se duas portas de embarque são equivalentes, comparando o seu número e a sua localização.
	bool operator==(const PortaEmbarque &porta_embarque) const;

	///Operador que verifica se o número de uma porta de embarque é menor do que outra.
	bool operator<(const PortaEmbarque &porta_embarque) const;

	static void init_categorias_avioes_info();
	static vector <string> &getRefCategoriasAvioesInfo() { return _categorias_avioes_info; }
	static string getInfoEnumCategoriasAvioes(unsigned nc_t){
		if(nc_t >= _categorias_avioes_info.size())
			throw ExOutOfRange();
		else
			return _categorias_avioes_info[(size_t)nc_t];
	}
	static void listCategoriasAvioesInfo();
};

///Classe que contém apontador para a classe PortaEmbarque (usada na BST).
class PortaEmbarquePtr{
private:
	PortaEmbarque* porta;
public:
	PortaEmbarquePtr(PortaEmbarque* p): porta(p) {}
	virtual ~PortaEmbarquePtr() {}

	string getNumero() const { return porta->getNumero(); }
	string getLocalizacao() const { return porta->getLocalizacao(); }
	unsigned getCapacidadePass() const { return porta->getCapacidadePass(); }
	unsigned getVagasPass() const { return porta->getVagasPass(); }
	unsigned getCategoriaAvioes() const { return porta->getCategoriaAvioes(); }

	///Operador que retorna o apontador para a PortaEmbarque.
	PortaEmbarque* operator()()
	{
		return porta;
	};

	///Operador que permite verificar se duas portas de embarque são equivalentes, comparando o seu número e a sua localização.
	bool operator==(const PortaEmbarquePtr &porta_embarque) const;

	///Operador que verifica se o número de uma porta de embarque é menor do que outra.
	bool operator<(const PortaEmbarquePtr &porta_embarque) const;
};

#endif
