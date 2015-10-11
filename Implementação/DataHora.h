/**\file DataHora.h
 * \brief Classe que contém informação associada a uma data e hora.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: DataHora.h \n
 * DESCRIÇÃO: Classe que contém informação associada a uma data e hora. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#ifndef DATA_HORA_H_
#define DATA_HORA_H_


#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>

#include "utils.h"
#include "Exceptions.h"
#include "Atraso.h"

using std::string;
using std::vector;
using std::ostream;
using std::istream;


///Classe que contém informação acerca de uma data e hora (ex: 2010/09/03 12:00).
class DataHora {
private:
	int _ano;
	int _mes;
	int _dia;
	int _hora;
	int _min;

public:
	///Construtor vazio, que inicializa os dados da classe com valores de erro, denotando que necessitam de ser actualizados.
	DataHora() : _ano(-1), _mes(-1), _dia(-1), _hora(-1), _min(-1) {}
	DataHora(int ano, int mes, int dia, int hora, int min): _ano(ano), _mes(mes), _dia(dia), _hora(hora), _min(min)	{}
	///Construtor de uma DataHora, que recebe uma string no formato AAAA/MM/DD HH:mm e extrai os dados para os membros respectivos da classe DataHora.
	DataHora(string data_hora) { *this = Parser_DataHora(data_hora); }
	virtual ~DataHora() {}

	int getAno() const { return _ano; }
	int getMes() const { return _mes; }
	int getDia() const { return _dia; }
	int getHora() const { return _hora; }
	int getMin() const { return _min; }

	void setAno(unsigned ano) { _ano = ano; }
	void setMes(unsigned mes) { _mes = mes; }
	void setDia(unsigned dia) { _dia = dia; }
	void setHora(unsigned hora) { _hora = hora; }
	void setMin(unsigned min) { _min = min; }

	/**
	 * \brief Parser que a partir de uma string no formato AAAA/MM/DD HH:mm, retira os dados necessários para inicializar um objecto do tipo DataHora.
	 *
	 * @param data_hora string que deve estar no formato AAAA/MM/DD HH:mm
	 * @return DataHora inicializada com as dados que estavam contidos na string.
	 */
	DataHora Parser_DataHora(string data_hora);

	/**
	 * \brief Método que pede ao utilizador para introduzir uma data no formato <AAAA/MM/DD HH:mm>.
	 * \details Enquanto não for introduzido uma data no formato pedido continua a pedir ao utilizador para introduzir a data.
	 * 			O objecto que chamou o método fica igual aos dados que o utilizador introduziu.
	 * @param mensagem Mensagem a ser mostrado ao utilizador antes de pedir o input.
	 */
	void getDataHoraCin(const char* mensagem);

	///Método que adiciona um atraso a uma DataHora de um voo.
	void addAtraso(Atraso &atraso) {
		_hora += atraso.getHora();
		_min += atraso.getMin();
		_dia += atraso.getDia();
	}

	///Operador que permite comparar se duas datas são equivalentes.
	bool operator==(const DataHora &data_hora) const;

	/**
	 * \brief Operador que compara se uma hora é menor do que outra.
	 * \details Faz uma verfificação a todos os membros de uma DataHora pela ordem do formato AAAA/MM/DD HH:mm.
	 */
	bool operator<(const DataHora &data_hora) const;
};

///Operador que imprime um objecto do tipo DataHora no formato AAAA/MM/DD HH:mm
ostream& operator<<(ostream &os,const DataHora &obj);

///Operador que permite a leitura de dados para um objecto do tipo DataHora
istream& operator>>(istream &is, DataHora &obj);

#endif
