/**\file Comandos.h
 * \brief Classe que armazena os comandos poss�veis para cada classe.
 *
 * PROJECTO: Projecto 2 - Gest�o do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Comandos.h \n
 * DESCRI��O: Classe que armazena os comandos poss�veis para cada classe. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - V�tor Am�lio Maia Martins Moreira
 */

#ifndef COMANDOS_H_
#define COMANDOS_H_

#include <vector>
#include <string>

using std::string;
using std::vector;

///Classe que armazena os comandos poss�veis para cada classe.
class Comandos {
public:
	///Vectores com as listas de par�metros que podem ser alterados em cada classe.
	static vector <string> _tipo_aviao_op_list;
	static vector <string> _aviao_op_list;
	static vector <string> _tripulante_op_list;
	static vector <string> _passageiro_op_list;
	static vector <string> _voo_op_list;
	static vector <string> _portas_embarque_op_list;
	static vector <string> _companhia_op_list;
	static vector <string> _aeroporto_op_list;

	//Fun��es que introduzem os dados nos vectores de comandos
	static void initTipoAviaoOp();
	static void initAviaoOp();
	static void initTripulanteOp();
	static void initPassageiroOp();
	static void initVooOp();
	static void initPortaEmbarqueOp();
	static void initCompanhiaOp();
	static void initAeroportoOp();

	///Inicializa��o de todos os vectores de comandos de dados.
	static void initAllOp();

};

#endif
