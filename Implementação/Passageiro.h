/**\file Passageiro.h
 * \brief Classe que contém informação associada a um passageiro de um voo.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Passageiro.h \n
 * DESCRIÇÃO: Classe que contém informação associada a um passageiro de um voo. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

#include <string>
#include <vector>

#include "Pessoa.h"
#include "utils.h"

//Foward declaration da classe Voo para evitar mutual includes
class Voo;

using std::string;
using std::vector;


/**
 * \brief Classe que contém informação associada a um passageiro de um determinado voo.
 * \details Subclasse de Pessoa.
 */
class Passageiro : public Pessoa {
public:
	enum necessidades_especiais_t { CADEIRA_RODAS, IDOSO, CRIANCA_DESACOMPANHADA, SEM_NECESSIDADES_ESPECIAIS };

private:
	static vector <string> _necessidades_especiais_info;

	unsigned _necessidades_especiais;
	unsigned _peso_bagagem;
	unsigned _numero_lugar_aviao;

	///Voo associado ao passageiro.
	Voo *_voo;

public:
	///Construtor vazio que inicaliza um Passageiro, com valores inválidos de forma a sinalizar que têm que ser definidos mais tarde.
	Passageiro() : Pessoa(), _necessidades_especiais(), _peso_bagagem(0), _numero_lugar_aviao(0), _voo(NULL) {}
	Passageiro(string nome, string morada, string nacionalidade, unsigned contacto, unsigned BI, unsigned idade,
			unsigned necessidades_especiais, unsigned peso_bagagem, unsigned numero_lugar_aviao, Voo *voo = NULL) :
		Pessoa(nome, morada, nacionalidade, contacto, BI, idade),
		_necessidades_especiais(necessidades_especiais), _peso_bagagem(peso_bagagem), _numero_lugar_aviao(numero_lugar_aviao), _voo(voo) {}

	unsigned getNecessidades_especiais() const { return _necessidades_especiais; }
	unsigned getPesoBagagem() const { return _peso_bagagem; }
	unsigned getNumeroLugarAviao() const { return _numero_lugar_aviao; }
	Voo* getVoo() const { return _voo; }

	void setNecessidades_especiais(unsigned necessidades_especiais) { _necessidades_especiais = necessidades_especiais; }
	void setPesoBagagem(unsigned peso_bagagem) { _peso_bagagem = peso_bagagem; }
	void setNumeroLugarAviao(unsigned numero_lugar_aviao) { _numero_lugar_aviao = numero_lugar_aviao; }
	void setVoo(Voo *voo) { _voo = voo; }

	///Operador que verifica se dois passageiros são equivalentes, verificando se têm o mesmo voo e mesmo número de lugar no avião.
	bool operator==(const Passageiro &passageiro);

	/**
	 * \brief Operador que verifica se o número do lugar do avião de um Passageiro é menor do que outro Passageiro.
	 * \details Os passageiros devem ser do mesmo voo. Se não forem retorna false.
	 */
	bool operator<(const Passageiro &passageiro) const;

	static void init_necessidades_especiais_info();
	static vector <string> &getRefNecessidadesEspeciaisInfo() { return _necessidades_especiais_info; }
	static string getInfoEnumNecessidadesEspeciais(unsigned nc_t){
		if(nc_t >= _necessidades_especiais_info.size())
			throw ExOutOfRange();
		else
			return _necessidades_especiais_info[(size_t)nc_t];
	}
	static void listNecessidadesEspeciaisInfo();
};

#endif
