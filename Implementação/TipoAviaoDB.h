/**\file TipoAviaoDB.h
 * \brief Classe que cont�m uma base de dados de tipos de avi�es.
 *
 * PROJECTO: Projecto 2 - Gest�o do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: TipoAviaoDB.h \n
 * DESCRI��O: Classe que cont�m uma base de dados de tipos de avi�es. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - V�tor Am�lio Maia Martins Moreira
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

///Compara se o Tipo de um tipo de avi�o � menor do que outro.
bool cmpTipoAviaoTipo(const TipoAviao *ta1, const TipoAviao *ta2);
///Compara se a descri��o de um tipo de avi�o � menor do que outro.
bool cmpTipoAviaoDescricao(const TipoAviao *ta1, const TipoAviao *ta2);
///Compara se a categoria de um tipo de avi�o � menor do que outro.
bool cmpTipoAviaoCategoria(const TipoAviao *ta1, const TipoAviao *ta2);


///Classe que cont�m uma base de dados de tipos de avi�es. \n
class TipoAviaoDB {
private:
	vector <TipoAviao*> _tipos_aviao;

public:
	virtual ~TipoAviaoDB();

	string getNomeTipoAviaoCin(const char* mensagem);

	vector <TipoAviao*> getTiposAviao() const { return _tipos_aviao; }
	//Variante dos gets para os vectores, usadas em iteradores constantes
	const vector <TipoAviao*>& getConstRefTiposAviao() const { return _tipos_aviao; }
	//Variante do get do vector que permite alter�-lo atrav�s da refer�ncia que � dada
	vector <TipoAviao*>& getRefTiposAviao() { return _tipos_aviao; }

	///Adiciona um tipo de aviao � base de dados com os dados introduzidos pelo utilizador.
	void addTipoAviao();

	/**
	 * \brief Adiciona um tipo de avi�o � base de dados verificando se o nome desse tipo j� existe.
	 * @param tipo_aviao Apontador para um tipo de avi�o, que j� existe numa base de dados.
	 * @return True se a adi��o foi feita com sucesso. Caso contr�rio � lan�ada uma excep��o.
	 */
	void addTipoAviao(TipoAviao *tipo_aviao);


	///Lista todos os Tipos de avi�o da base de dados de TipoAviaoDB.
	void listTipoAviao(bool final_pause = true);

	/**
	 * \brief Selecciona um tipo de aviao de uma base de dados, de uma lista de Tipos de avi�es.
	 * @return O �ndice desse tipo de avi�o no vector de apontadores para tipos de avi�o.
	 */
	size_t selTipoAviao();

	/**
	 * \brief Selecciona um tipo de aviao de uma base de dados, de uma lista de Tipos de avi�es.
	 * @return O apontador para o avi�o que foi selecionado.
	 */
	TipoAviao* selTipoAviaoPtr();

	///M�todo que mostra ao utilizador os atributos dum tipo de avi�o.
	void infoTipoAviao();

	/**
	 * \brief M�todo que pede fornece ao utilizador a possibilidade de editar TipoAviao que j� est�o criados.
	 * \details Come�a por pedir ao utilziador que atributos do tipo de avi�o existente pretende modificar e depois pede os novos dados.
	 */
	void editTipoAviao();

	///Elimina um tipo de aviao da base de dados TipoAviaoDB perguntando ao utilizador o �ndice.
	void delTipoAviao();

	///Elimina o tipo de aviao da base de dados que est� no �ndice fornecido.
	void delTipoAviao(size_t index);

	///Carrega a base de dados de avi�es a partir do nome de ficheiro predefinido
	void loaddb_tipos_aviao();

	///Carrega a base de dados de avi�es a partir do nome de ficheiro fornecido.
	void loaddb_tipos_aviao(string filename);

	///Guarda a base de dados para o ficheiro de de texto com o nome predefinido.
	void savedb_tipos_aviao();

	///Guarda a base de dados para o ficheiro de de texto com o nome fornecido.
	void savedb_tipos_aviao(string filename);
};


#endif
