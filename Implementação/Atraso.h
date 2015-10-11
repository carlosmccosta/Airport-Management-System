/**\file Atraso.h
 * \brief Classe que contém informação acerca de um atraso de um voo.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Atraso.h \n
 * DESCRIÇÃO: Classe que contém informação acerca de um atraso de um voo na sua hora de partida / chegada (dia:hora:min ou hora:min) \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#ifndef HORAMIN_H_
#define HORAMIN_H_

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

#include "utils.h"
#include "Exceptions.h"

using std::string;
using std::ostream;
using std::istream;
using std::vector;


///Classe que contém informação acerca de um atraso de um voo na sua hora de partida / chegada (dia:hora:min ou hora:min).
class Atraso {
private:
	int _hora;
	int _min;
	int _dia;


public:
	///Construtor vazio, que inicializa os dados da classe com valores de erro, denotando que necessitam de ser actualizados.
	Atraso() : _hora(-1), _min(-1), _dia(-1) {}
	Atraso(int hora, int min, int dia = 0): _hora(hora), _min(min), _dia(dia)  {}
	///Construtor de um atraso, que recebe uma string no formato DD:HH:mm ou HH:mm e extrai os dados para os membros respectivos da classe Atraso.
	Atraso(string atraso) { *this = Parser_Atraso(atraso); }
	~Atraso() {}

	int getHora() const { return _hora; }
	int getMin() const { return _min; }
	int getDia() const { return _dia; }

	void setHora(int hora) { _hora = hora; }
	void setMin(int min) { _min = min; }
	void setDia(int dia) { _dia = dia; }

	/** \brief Verificação da compatibilidade de uma string com a classe Atraso.
	 *
	 *  Método que permite analisar se o formato de de uma string é compatível com a classe de Atraso de um voo.
	 *  @param atraso String que deve estar no formato DD:HH:mm ou HH:mm
	 *  @return Atraso no formato DD:HH:mm ou 00:HH:mm
	 */
	Atraso Parser_Atraso(string atraso);

	/**
	 * \brief Método que pede ao utilizador para introduzir um atraso no formato <DD:HH:mm> ou <HH:mm>.
	 * \details Enquanto não for introduzido um Atraso no formato pedido continua a pedir ao utilizador para introduzir um Atraso.
	 * 			O objecto que chamou o método fica igual aos dados que o utilizador introduziu.
	 * @param mensagem Mensagem a ser mostrado ao utilizador antes de pedir o input.
	 */
	void getAtrasoCin(const char* mensagem);

	///Operador que permite comparar se dois atrasos são equivalentes.
	bool operator==(const Atraso &atraso) const;

	/**
	 * \brief Operador que compara se um atraso é menor do que outro.
	 * \details Faz uma verfificação a todos os membros de um atraso pela ordem do formato DD:HH:mm.
	 */
	bool operator<(const Atraso &atraso) const;
};

///Operador que imprime um objecto do tipo Atraso no formato AAAA/MM/DD HH:mm
ostream& operator<<(ostream &os,const Atraso &obj);

///Operador que permite a leitura de dados para um objecto do tipo Atraso
istream& operator>>(istream &is, Atraso &obj);

#endif
