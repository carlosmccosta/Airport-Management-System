/**\file TipoAviaoDB.h
 * \brief Classe que contém uma base de dados de tipos de aviões.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: TipoAviaoDB.h \n
 * DESCRIÇÃO: Classe que contém uma base de dados de tipos de aviões. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */


#ifndef TIPOAVIAODB_H_
#define TIPOAVIAODB_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "TipoAviao.h"
#include "DataHora.h"
#include "Exceptions.h"
#include "Comandos.h"
#include "utils.h"
#include "PortaEmbarque.h"

using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::flush;
using std::cout;
using std::cin;
using std::find_if;
using std::sort;
//using std::bind2nd;
//using std::equal_to;

///Compara se o Tipo de um tipo de avião é menor do que outro.
bool cmpTipoAviaoTipo(const TipoAviao *ta1, const TipoAviao *ta2);
///Compara se a descrição de um tipo de avião é menor do que outro.
bool cmpTipoAviaoDescricao(const TipoAviao *ta1, const TipoAviao *ta2);
///Compara se a categoria de um tipo de avião é menor do que outro.
bool cmpTipoAviaoCategoria(const TipoAviao *ta1, const TipoAviao *ta2);


///Classe que contém uma base de dados de tipos de aviões. \n
class TipoAviaoDB {
private:
	vector <TipoAviao*> _tipos_aviao;

public:
	virtual ~TipoAviaoDB();

	string getNomeTipoAviaoCin(const char* mensagem);

	vector <TipoAviao*> getTiposAviao() const { return _tipos_aviao; }
	//Variante dos gets para os vectores, usadas em iteradores constantes
	const vector <TipoAviao*>& getConstRefTiposAviao() const { return _tipos_aviao; }
	//Variante do get do vector que permite alterá-lo através da referência que é dada
	vector <TipoAviao*>& getRefTiposAviao() { return _tipos_aviao; }

	///Adiciona um tipo de aviao à base de dados com os dados introduzidos pelo utilizador.
	void addTipoAviao();

	/**
	 * \brief Adiciona um tipo de avião à base de dados verificando se o nome desse tipo já existe.
	 * @param tipo_aviao Apontador para um tipo de avião, que já existe numa base de dados.
	 * @return True se a adição foi feita com sucesso. Caso contrário é lançada uma excepção.
	 */
	void addTipoAviao(TipoAviao *tipo_aviao);


	///Lista todos os Tipos de avião da base de dados de TipoAviaoDB.
	void listTipoAviao(bool final_pause = true);

	/**
	 * \brief Selecciona um tipo de aviao de uma base de dados, de uma lista de Tipos de aviões.
	 * @return O índice desse tipo de avião no vector de apontadores para tipos de avião.
	 */
	size_t selTipoAviao();

	/**
	 * \brief Selecciona um tipo de aviao de uma base de dados, de uma lista de Tipos de aviões.
	 * @return O apontador para o avião que foi selecionado.
	 */
	TipoAviao* selTipoAviaoPtr();

	///Método que mostra ao utilizador os atributos dum tipo de avião.
	void infoTipoAviao();

	/**
	 * \brief Método que pede fornece ao utilizador a possibilidade de editar TipoAviao que já estão criados.
	 * \details Começa por pedir ao utilziador que atributos do tipo de avião existente pretende modificar e depois pede os novos dados.
	 */
	void editTipoAviao();

	///Elimina um tipo de aviao da base de dados TipoAviaoDB perguntando ao utilizador o índice.
	void delTipoAviao();

	///Elimina o tipo de aviao da base de dados que está no índice fornecido.
	void delTipoAviao(size_t index);

	///Carrega a base de dados de aviões a partir do nome de ficheiro predefinido
	void loaddb_tipos_aviao();

	///Carrega a base de dados de aviões a partir do nome de ficheiro fornecido.
	void loaddb_tipos_aviao(string filename);

	///Guarda a base de dados para o ficheiro de de texto com o nome predefinido.
	void savedb_tipos_aviao();

	///Guarda a base de dados para o ficheiro de de texto com o nome fornecido.
	void savedb_tipos_aviao(string filename);
};


#endif
