/**\file Comandos.cpp
 * \brief Ficheiro com a implementa��o da classe Comandos.
 *
 * PROJECTO: Projecto 2 - Gest�o do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Comandos.cpp \n
 * DESCRI��O: Ficheiro com a implementa��o da classe Comandos. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - V�tor Am�lio Maia Martins Moreira
 */

#include "Comandos.h"

//Inicializa��o dos membros est�ticos
vector <string> Comandos::_tipo_aviao_op_list(0);
vector <string> Comandos::_aviao_op_list(0);
vector <string> Comandos::_tripulante_op_list(0);
vector <string> Comandos::_passageiro_op_list(0);
vector <string> Comandos::_voo_op_list(0);
vector <string> Comandos::_portas_embarque_op_list(0);
vector <string> Comandos::_companhia_op_list(0);
vector <string> Comandos::_aeroporto_op_list(0);

void Comandos::initTipoAviaoOp() {
	_tipo_aviao_op_list.clear();
	_tipo_aviao_op_list.push_back("Tipo");
	_tipo_aviao_op_list.push_back("Descri��o");
	_tipo_aviao_op_list.push_back("Categoria");
	_tipo_aviao_op_list.push_back("Fabricante");
	_tipo_aviao_op_list.push_back("Data lan�amento");
	_tipo_aviao_op_list.push_back("Pre�o (euros)");
	_tipo_aviao_op_list.push_back("N� de passageiros m�ximo");
	_tipo_aviao_op_list.push_back("Autonomia (km)");
	_tipo_aviao_op_list.push_back("Velocidade m�xima (km/h)");
	_tipo_aviao_op_list.push_back("N�mero de motores");
	_tipo_aviao_op_list.push_back("Peso vazio (kg)");
	_tipo_aviao_op_list.push_back("Peso m�ximo (kg)");
	_tipo_aviao_op_list.push_back("Comprimento (m)");
	_tipo_aviao_op_list.push_back("Envergadura (m)");
	_tipo_aviao_op_list.push_back("Altura (m)");
	_tipo_aviao_op_list.push_back("Altitude m�xima (m)");
}


void Comandos::initAviaoOp() {
	_aviao_op_list.clear();
	_aviao_op_list.push_back("Matricula");
	_aviao_op_list.push_back("Nome");
	_aviao_op_list.push_back("Peso m�ximo");
	_aviao_op_list.push_back("Tipo de avi�o");
	_aviao_op_list.push_back("Companhia");
	_aviao_op_list.push_back("Voo actual");
	_aviao_op_list.push_back("Data constru��o");
	_aviao_op_list.push_back("Primeiro voo");
	_aviao_op_list.push_back("�ltima revis�o");
	_aviao_op_list.push_back("Pr�xima revis�o");
}


void Comandos::initTripulanteOp() {
	_tripulante_op_list.clear();
	_tripulante_op_list.push_back("Nome");
	_tripulante_op_list.push_back("Morada");
	_tripulante_op_list.push_back("Nacionalidade");
	_tripulante_op_list.push_back("Contacto");
	_tripulante_op_list.push_back("BI");
	_tripulante_op_list.push_back("Idade");
	_tripulante_op_list.push_back("N�mero");
	_tripulante_op_list.push_back("Categoria");
	_tripulante_op_list.push_back("Sal�rio/hora");
	_tripulante_op_list.push_back("N�mero de Horas");
	_tripulante_op_list.push_back("Tipo de contrato");
	_tripulante_op_list.push_back("Data de expira��o do contrato");
	_tripulante_op_list.push_back("Companhia");
	_tripulante_op_list.push_back("Voo associado");
}

void Comandos::initPassageiroOp() {
	_passageiro_op_list.clear();
	_passageiro_op_list.push_back("Nome");
	_passageiro_op_list.push_back("Morada");
	_passageiro_op_list.push_back("Nacionalidade");
	_passageiro_op_list.push_back("Contacto");
	_passageiro_op_list.push_back("BI");
	_passageiro_op_list.push_back("Idade");
	_passageiro_op_list.push_back("Necessidades especiais");
	_passageiro_op_list.push_back("Peso da bagagem");
	_passageiro_op_list.push_back("N�mero do lugar no avi�o");
}


void Comandos::initVooOp() {
	_voo_op_list.clear();
	_voo_op_list.push_back("N�mero do voo");
	_voo_op_list.push_back("Origem");
	_voo_op_list.push_back("Destino");
	_voo_op_list.push_back("Data e hora da sa�da");
	_voo_op_list.push_back("Data e hora da chegada");
	_voo_op_list.push_back("N�mero de passageiros");
	_voo_op_list.push_back("Porta de embarque");
	_voo_op_list.push_back("Avi�o");
	_voo_op_list.push_back("Companhia");
	_voo_op_list.push_back("Atraso");
	_voo_op_list.push_back("Cancelado");
}

void Comandos::initPortaEmbarqueOp() {
	_portas_embarque_op_list.clear();
	_portas_embarque_op_list.push_back("N�mero da Porta");
	_portas_embarque_op_list.push_back("Localiza��o");
	_portas_embarque_op_list.push_back("Capacidade");
	_portas_embarque_op_list.push_back("Categoria");
}

void Comandos::initCompanhiaOp() {
	_companhia_op_list.clear();
	_companhia_op_list.push_back("Sigla");
	_companhia_op_list.push_back("Nome");
	_companhia_op_list.push_back("Taxa de utiliza��o dos balc�es de check-in");
}

void Comandos::initAeroportoOp() {
	_aeroporto_op_list.clear();
	_aeroporto_op_list.push_back("Nome");
	_aeroporto_op_list.push_back("Localiza��o");
	_aeroporto_op_list.push_back("Pa�s");
	_aeroporto_op_list.push_back("Taxa de utiliza��o das portas de embarque");
}

void Comandos::initAllOp() {
	Comandos::initTipoAviaoOp();
	Comandos::initAviaoOp();
	Comandos::initTripulanteOp();
	Comandos::initPassageiroOp();
	Comandos::initVooOp();
	Comandos::initPortaEmbarqueOp();
	Comandos::initCompanhiaOp();
	Comandos::initAeroportoOp();
}

