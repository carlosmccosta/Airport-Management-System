/**\file GestaoAeroporto.h
 * \brief Ficheiro que contém os métodos CRUD (manutenção de dados), de cada classe.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: GestaoAeroporto.h \n
 * DESCRIÇÃO: Ficheiro que contém os métodos CRUD (manutenção de dados), de cada classe. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */


#ifndef GESTAOAEROPORTO_H_
#define GESTAOAEROPORTO_H_

#include "Aeroporto.h"
#include "DataHora.h"
#include "Aviao.h"
#include "TipoAviao.h"
#include "Companhia.h"
#include "Tripulante.h"
#include "Piloto.h"
#include "Hospedeiro.h"
#include "Voo.h"
#include "PortaEmbarque.h"
#include "Exceptions.h"
#include "utils.h"

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

using std::ifstream;
using std::ofstream;
using std::stringstream;
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
using std::equal_to;


extern TipoAviaoDB tipo_aviao_DB;

extern Aeroporto aeroporto;

//############################### Métodos CRUD (create, read, update, delete) para as classes #####################################

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Apontadores usados entre chamadas a funções  CRUD <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
extern PortaEmbarque* porta_embarque_actual;
extern Passageiro* passageiro_actual;
extern Companhia* companhia_actual;
extern Aviao *aviao_actual;
extern TipoAviao *tipo_aviao_actual;
extern Tripulante *tripulante_actual;
extern Voo *voo_actual;

namespace CRUD {

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Aviao <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

///Adiciona um Avião a uma companhia com os dados introduzidos pelo utilizador.
void addAviao(Companhia *companhia);
///Adiciona um apontador de Avião a uma companhia.
void addAviao(Companhia *companhia, Aviao *aviao);

///Função usada para a ordenação do vector de aviões segundo a Matricula.
bool cmpAviaoMatricula(const Aviao *av1, const Aviao *av2);
///Função usada para a ordenação do vector de aviões segundo o nome.
bool cmpAviaoNome(const Aviao *av1, const Aviao *av2);
///Função usada para a ordenação do vector de aviões segundo a DataProximaRevisao.
bool cmpAviaoProximaRevisao(const Aviao *av1, const Aviao *av2);

/**
 * \brief Mostra todas os Aviões de uma Companhia numa tabela,
 * 		  pedindo ao utilizador o parâmetro que quer usar para fazer a ordenação da tabela.
 * @param final_pause boolenao que caso seja true faz com que o método pare no fim da função e espere por input do utilizador para continuar
 */
void listAviao(Companhia *companhia, bool final_pause = true);

/**
 * \brief Selecciona um Avião de uma Companhia, de uma lista de aviões.
 * @param companhia Companhia que contem os planos de voo a mostrar.
 * @return Returna o indice do vector, (que está dentro de uma companhia), onde está o apontador para um determinado avião.
 */
size_t selAviao(Companhia *companhia);

/**
 * \brief Selecciona um Avião de uma Companhia, de uma lista de aviões.
 * @return Returna o apontador para o avião selecionado pelo utilizador.
 */
Aviao* selAviaoPtr(Companhia *companhia);

///Método que mostra ao utilizador os atributos dum avião.
void infoAviao(Companhia *companhia);

///Método que permite ao utilizador editar os atributos de um avião.
void editAviao(Aeroporto *aeroporto, Companhia *companhia);

/**
 * \brief Método que elimina um dado avião caso não esteja associado a um voo.
 * \details Caso seja eliminado, o apontador para este avião no vector de apontadores de aviões da companhia respectiva é eliminado também.
 */
void delAviao(Companhia *companhia);

/**
 * \brief Método que elimina o avião que stá no indice do vector de apontadores para aviões da companhia, caso não esteja associado a um voo.
 * \details Caso seja eliminado, o apontador para este avião no vector de apontadores de aviões da companhia respectiva é eliminado também.
 */
void delAviao(Companhia *companhia, size_t indice);

/**
 * \brief Método que remove do vector de *Aviao de uma companhia o apontador aviao_ptr. Não apaga o aviao, só o apontador.
 * @param aviao_ptr Apontador do aviao que vai ser revomido do vector
 */
void delAviaoPtr(Companhia *companhia, Aviao *aviao_ptr);

 ///Método que remove da frota o tipo de avião, se não estiver a ser utilizado.
bool delTipoAviaoAviao(Companhia* companhia, Aviao* aviao);


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Tripulante <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * \brief Adiciona um tripulante a uma companhia com os dados introduzidos pelo utilizador.
 * \details Verifica se o BI e o número do tripulante são únicos na companhia selecionada.
 */
void addTripulante(Companhia *companhia);

///Adiciona um tripulante a uma companhia, verificando se já exitem nessa companhia um tripulante com o mesmo número.
void addTripulante(Companhia *companhia, Tripulante *tripulante);

///Compara se o nome de um tripulante é menor do que outro.
bool cmpTripulanteNome(const Tripulante *tripulante_1, const Tripulante *tripulante_2);
///Compara se o número de um tripulante é menor do que outro.
bool cmpTripulanteNumero(const Tripulante *tripulante_1, const Tripulante *tripulante_2);
///Compara se a categoria de um tripulante é menor do que outra.
bool cmpTripulanteCategoria(const Tripulante *tripulante_1, const Tripulante *tripulante_2);
///Compara se o salário/hora de um tripulante é menor do que outro.
bool cmpTripulanteSalarioHora(const Tripulante *tripulante_1, const Tripulante *tripulante_2);
///Compara se o número de horas de trabalho de um tripulante é menor do que outro.
bool cmpTripulanteNumeroHorasTrabalho(const Tripulante *tripulante_1, const Tripulante *tripulante_2);
///Compara se o tipo de contrato de um tripulante é menor do que outro.
bool cmpTripulanteTipoContrato(const Tripulante *tripulante_1, const Tripulante *tripulante_2);
///Compara se o data de expiração do contrato de um tripulante é menor do que outra.
bool cmpTripulanteExpiracaoContrato(const Tripulante *tripulante_1, const Tripulante *tripulante_2);


/**
 * \brief Mostra todos os tripulantes de uma companhia, segundo o critério de ordenação que o utilizador selecionou.
 * @param companhia Companhia que contem os planos de voo a mostrar.
 * @param final_pause boolenao que caso seja true faz com que o método pare no fim da função e espere por input do utilizador para continuar
 */
void listTripulante(Companhia *companhia, bool final_pause = true);

/**
 * \brief Selecciona um Tripulante de uma Companhia, de uma lista de tripulantes.
 * @return Returna o indice do vector, (que está dentro de uma companhia), onde está o apontador para um determinado tripulante.
 */
size_t selTripulante(Companhia *companhia);

/**
 * \brief Selecciona um Tripulante de uma Companhia, de uma lista de tripulantes.
 * @return Returna o apontador para o tripulante selecionado pelo utilizador.
 */
Tripulante* selTripulantePtr(Companhia *companhia);


///Método que mostra ao utilizador os atributos dum tripulante.
void infoTripulante(Companhia *companhia);


///Método que permite ao utilizador editar os atributos de um Tripulante.
void editTripulante(Aeroporto *aeroporto, Companhia *companhia);

/**
 * \brief Elimina um Tripulante de uma Companhia.
 * \details Caso esse tripulante ainda esteja associado a um voo, a eliminação não é possível.
 * 			Se esse tripulante estiver livre, é eliminado, e o vector de tripulantes é actualizado,
 * 			tirando-se o apontador que apontava para o tripulante que acabou de ser elimindo.
 */
void delTripulante(Companhia *companhia);

/**
 * \brief Elimina um Tripulante de uma Companhia perguntando ao utilizador o índice.
 * \details Caso esse tripulante ainda esteja associado a um voo, a eliminação não é possível.
 * 			Se esse tripulante estiver livre, é eliminado, e o vector de tripulantes é actualizado,
 * 			tirando-se o apontador que apontava para o tripulante que acabou de ser elimindo.
 */
void delTripulante(Companhia *companhia, size_t indice);

/**
 * \brief Método que remove do vector de *Tripulante de uma companhia o apontador tripulante_ptr. Não apaga o tripulante, só o apontador.
 * \details Usado para a transferência de tripulantes entre companhias.
 * @param tripulante_ptr Apontador do aviao que vai ser revomido do vector
 */
void delTripulantePtr(Companhia *companhia, Tripulante *tripulante_ptr);



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PlanoVoo <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

///Adiciona um Plano de Voo a uma companhia com os dados introduzidos pelo utilizador.
void addPlanoVoo(Aeroporto *aeroporto, Companhia *companhia);
///Adiciona um Plano de Voo a uma companhia.
bool addPlanoVoo(Companhia *companhia, Voo* voo);

///Compara se o número de um voo é menor do que outro.
bool cmpVooNumeroVoo(const Voo *voo1, const Voo *voo2);
///Compara se a origem de um voo é menor do que outra.
bool cmpVooOrigem(const Voo *voo1, const Voo *voo2);
///Compara se o destino de um voo é menor do que outro.
bool cmpVooDestino(const Voo *voo1, const Voo *voo2);
///Compara se a data de saida de um voo é menor do que outra.
bool cmpVooDataSaida(const Voo *voo1, const Voo *voo2);
///Compara se a data de chegada de um voo é menor do que outra.
bool cmpVooDataChegada(const Voo *voo1, const Voo *voo2);
///Compara se o atraso de um voo é menor do que outro.
bool cmpVooAtraso(const Voo *voo1, const Voo *voo2);
///Verifica se o primeiro voo foi cancelado.
bool cmpVooCancelado(const Voo *voo1, const Voo *voo2);

/**
 * \brief Lista todas os Planos de voo de uma Companhia, ordenados segundo o critério que o utilizador seleccionou.
 * @param companhia Companhia que contem os planos de voo a mostrar.
 * @param final_pause boolenao que caso seja true faz com que o método pare no fim da função e espere por input do utilizador para continuar
 */
void listPlanoVoo(Companhia *companhia, bool final_pause = true);

/**
 * \brief Selecciona um plano de voo de uma Companhia, de uma lista de planos de voo.
 * @return Returna o indice do vector, (que está dentro de uma companhia), onde está o apontador para um determinado voo.
 */
size_t selPlanoVoo(Companhia* companhia);

/**
 * \brief Selecciona um plano de voo de uma Companhia, de uma lista de planos de voo (retorna o apontador).
 * @param companhia Companhia que contem os planos de voo a mostrar.
 * @return Returna o apontador para o voo selecionado pelo utilizador.
 */
Voo* selPlanoVooPtr(Companhia* companhia);


///Método que mostra ao utilizador os atributos dum plano de voo.
void infoPlanoVoo(Companhia *companhia, Voo *voo = NULL);


///Método que permite ao utilizador editar os atributos de um Voo.
void editPlanoVoo(Aeroporto *aeroporto, Companhia *companhia);

/**
 * \brief Elimina um Plano de Voo de uma Companhia perguntando ao utilizador o índice.
 * \details Ao eliminar um plano de voos, a porta de embarque, o avião e os tripulantesa a que estava associado são "libertados",
 * 			podendo agora ser associados a outros voos.
 * 			Os passageiros são eliminados, e o vector de voos da companhia á actualizado.
 */
void delPlanoVoo(Aeroporto *aeroporto, Companhia* companhia);

/**
 * \brief Elimina um Plano de Voo de uma Companhia que está situada no índice fornecido (no vector de voos, dentro da companhia).
 * \details Ao eliminar um plano de voos, a porta de embarque, o avião e os tripulantesa a que estava associado são "libertados",
 * 			podendo agora ser associados a outros voos.
 * 			Os passageiros são eliminados, e o vector de voos da companhia á actualizado.
 */
void delPlanoVoo(Aeroporto *aeroporto, Companhia* companhia, size_t indice);

/**
 * \brief Método que remove do vector de *Voo de uma companhia o apontador voo_ptr. Não apaga o voo, só o apontador.
 * \details Usado para a sincronização de vetores de apontadores.
 * @param voo_ptr Apontador do voo que vai ser revomido do vector.
 */
void delPlanoVooPtr(Aeroporto *aeroporto, Companhia *companhia, Voo *voo_ptr);



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Aeroporto <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Adiciona um aeroporto com os dados forneceidos pelo utilizador.
void addAeroporto(Aeroporto *aeroporto);

///Altera um aeroporto com os dados introduzidos pelo utilizador.
void editAeroporto(Aeroporto *aeroporto);

///Imprime as informações acerca do aeroporto.
void infoAeroporto(Aeroporto *aeroporto);



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Companhia <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

///Adiciona uma companhia a um aeroporto com os dados introduzidos pelo utilizador
void addCompanhia(Aeroporto *aeroporto);
///Adiciona uma companhia a um aeroporto.
void addCompanhia(Aeroporto *aeroporto, Companhia *companhia);

///Função usada para a ordenação do vector de companhias segundo a Sigla.
bool cmpCompanhiaSigla(const Companhia *c1, const Companhia *c2);
///Função usada para a ordenação do vector de companhias segundo o Nome.
bool cmpCompanhiaNome(const Companhia *c1, const Companhia *c2);
///Função usada para a ordenação do vector de companhia segundo a taxa de utilização dos blacões de check-in.
bool cmpCompanhiaTaxa(const Companhia *c1, const Companhia *c2);

/**
 * \brief Lista todas as companhias de um aeroporto
 * @param companhia
 * @param final_pause boolenao que caso seja true faz com que o método pare no fim da função e espere por input do utilizador para continuar
 */
void listCompanhia(Aeroporto *aeroporto, bool final_pause = false);

/**
 * \brief Selecciona uma companhia de um aeroporto, de uma lista de Companhias.
 * @param aeroporto Aeroporto de onde vai ser selecionada a companhia.
 * @return Returna o indice do vector, (que está dentro de uma companhia), onde está o apontador para um determinado voo.
 */
size_t selCompanhia(Aeroporto *aeroporto);

/**
 * \brief Selecciona uma companhia de um aeroporto, de uma lista de Companhias (retorna apontador)
 * @param aeroporto Aeroporto de onde vai ser selecionada a companhia.
 * @return Returna o apontador para o Companhia selecionado pelo utilizador.
 */
Companhia* selCompanhiaPtr(Aeroporto *aeroporto);


///Método que mostra ao utilizador os atributos dum plano de uma companhia.
void infoCompanhia(Companhia *companhia);


///Método que permite ao utilizador editar os atributos de uma Companhia.
void editCompanhia(Aeroporto *aeroporto, Companhia *companhia = NULL);

/**
 * \brief Elimina uma companhia de um aeroporto selecionada pelo utilizador.
 * \details Ao eliminar uma companhia são eliminados todos os seus passageiros, voos, tripulantes e aviões.
 * 			São sincronizados os vectores de companhias, tipos de avião, passageiros e portas de embarque.
 * @param aeroporto Aeroporto de onde vai ser elimindada a companhia.
 */
void delCompanhia(Aeroporto *aeroporto);

/**
 * \brief Elimina um Plano de Voo de uma Companhia que está situada no índice fornecido (no vector de voos, dentro da companhia).
 * \details Ao eliminar uma companhia são eliminados todos os seus passageiros, voos, tripulantes e aviões.
 * 			São sincronizados os vectores de companhias, tipos de avião, passageiros e portas de embarque.
 * @param aeroporto Aeroporto de onde vai ser eliminada a Companhia.
 * @param indice Indice da companhia a ser elimindada.
 */
void delCompanhia(Aeroporto *aeroporto, size_t indice);

/**
 * \brief Método que remove do vector de *Companhia o apontador companhia_ptr. Não apaga a companhia, só o apontador.
 * \details Usado para a sincronização de vetores de apontadores.
 * @param companhia_ptr Apontador da companhia que vai ser revomida do vector.
 */
void delCompanhiaPtr(Aeroporto *aeroporto, Companhia *companhia_ptr);



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Passageiro <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

///Adiciona um passageiro a um aeroporto com os dados introduzidos pelo utilizador
void addPassageiro(Aeroporto* aeroporto);
///Adiciona um passageiro a um aeroporto (classe Passageiro)
void addPassageiro(Aeroporto* aeroporto, Passageiro *passageiro);

///Função usada para a ordenação do vector de Passageiros segundo o Nome.
bool cmpPassageiroNome(const Passageiro *p1, const Passageiro *p2);
///Função usada para a ordenação do vector de Passageiros segundo o BI.
bool cmpPassageiroBI(const Passageiro *p1, const Passageiro *p2);
///Função usada para a ordenação do vector de Passageiros segundo o Numero de voo.
bool cmpPassageiroNumero(const Passageiro *p1, const Passageiro *p2);

///Lista todas os passageiros de um aeroporto
void listPassageiro(Aeroporto *aeroporto, bool final_pause = true);
///Selecciona um passageiro de um aeroporto, de uma lista de passageiros
size_t selPassageiro(Aeroporto* aeroporto);
///Selecciona um passageiro de um aeroporto, de uma lista de passageiros (retorna apontador)
Passageiro* selPassageiroPtr(Aeroporto* aeroporto);
///Método que mostra ao utilizador os atributos dum Passageiro.
void infoPassageiro(Aeroporto *aeroporto, Passageiro *passageiro = NULL);
///Método que permite ao utilizador editar os atributos de um Passageiro.
void editPassageiro(Aeroporto * aeroporto);
///Elimina um passageiro de um aeroporto perguntando ao utilizador o índice.
void delPassageiro(Aeroporto *aeroporto);
///Elimina um passageiro de um aeroporto
void delPassageiro(Aeroporto *aeroporto, size_t indice);
///Eliminda o apontador de um passageiro no vector de passageiros no aeroporto fornecido.
void delPassageiroPtr(Aeroporto* aeroporto, Passageiro* passageiro);


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CheckIn <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//************  Usadas no menu dentro das companhias
///Função que cria a fila do check-in
void initCheckIn(Voo *voo);
///Função que simula o check-in dos passageiros.
void checkIn(Aeroporto *aeroporto, Voo *voo);
///Função que permite o check-in do próximo passageiro que está na fila_check_in para o voo dado.
void checkInNextPassageiro(Aeroporto *aeroporto, Voo *voo);

///Função que imprime a lista dos passageiros que estão na fila de embarque do voo (usada no meno dos voos)
void printPriorityQueue(Voo *voo);
///Função que simula a chamada dos passageiros para o embarque
void chamadaEmbarqueVoo(Aeroporto *aeroporto, Voo *voo);

//*********** Usadas no menu dentro das portas de embarque
///Função que imprime a lista dos passageiros que estão na fila de embarque do voo (usada no menu das portas de embarque)
void printPassageirosPortaEmbarque(Aeroporto *aeroporto);
///Função que imprime a lista dos passageiros que estão na fila de embarque do voo selecionado pelo utilizador
///a partir da lista de voos que estão associado à porta de embarque em questão (usada no menu das portas de embarque)
void chamadaEmbarqueVooPortaEmbarque(Aeroporto *aeroporto);


///Função que termina o check-in de um voo e coloca-o na tabela de dispersão
void fecharVoo(Aeroporto *aeroporto, Voo *voo);


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Tabela de dispersão <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

///Função que lista todos os voos que estão na hash_set_voos
void listHashSetVoos(Aeroporto *aeroporto);
/**
 * Função que lista os voos que estão na hash_set_voos por um dado critério e que cujas datas de partida
 * estão entre o limite inferior e superior dado pelo utilizador
 */
void listHashSetVoosEntreDatasCriterio(Aeroporto *aeroporto);
///Função que dado o id de um avião mostra as informações a ele asssociadas
void searchHashSetVoos(Aeroporto *aeroporto);
///Função que adiciona um voo à tabela dos voos fechados (fechando o voo escolhido)
void addVooHashSetVoos(Aeroporto *aeroporto);
///Função que elimina um voo da tabela de voos fechados
void delVooHashSetVoos(Aeroporto *aeroporto);


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Taxas <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

///Função que mostra a soma das taxas de utilização dos balcões de check-in das companhia num determinado intervalo de tempo (entre datas).
void listTaxasBalcoesEntreDatas(Aeroporto *aeroporto);
///Função que mostra a soma das taxas de utilização dos balcões de check-in das companhias para um dado voo que ocorreu entre as datas dadas pelo utilizador.
void listTaxasBalcoesVooEntreDatas(Aeroporto *aeroporto);
/**
 * \brief Função que mostra a soma das taxas de utilização dos balcões de check-in das companhias para os voos
 * 		  que estão dentro das datas limite fornecidas pelo utilizador (mostra os voos com as respectivas taxas, bem como a taxa total).
 */
void listTaxasBalcoesVoosEntreDatas(Aeroporto *aeroporto);


///Função que mostra a soma das taxas de utilização das portas de embarque entre as datas limite fornecidas pelo utilizador
void listTaxasPortasEmbarqueEntreDatas(Aeroporto *aeroporto);
///Função que mostra a soma das taxas de utilização da porta de embarque selecionada pelo utilizador.
void listTaxasPortasEmbarqueVooEntreDatas(Aeroporto *aeroporto);
///Função que mostra a soma das taxas de utilização das portas de embarque para os voos
///que estão dentro das datas limite fornecidas pelo utilizador (mostra os voos com as respectivas taxas, bem como a taxa total).
void listTaxasPortasEmbarqueVoosEntreDatas(Aeroporto *aeroporto);

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Porta de embarque <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

///Adiciona uma porta de embarque a um aeroporto com os dados introduzidos pelo utilizador
void addPortaEmbarque(Aeroporto* aeroporto);
///Adiciona uma porta de embarque a um aeroporto (classe PortaEmbarque)
void addPortaEmbarque(Aeroporto* aeroporto, PortaEmbarque* porta);

///Função usada para a ordenação do vector de portas de embarque segundo o numero.
bool cmpPortaEmbarqueNumero(const PortaEmbarque *obj1, const PortaEmbarque *obj2);
///Função usada para a ordenação do vector de portas de embarque segundo a localizacao.
bool cmpPortaEmbarqueLocalizacao(const PortaEmbarque *obj1, const PortaEmbarque *obj2);
///Função usada para a ordenação do vector de portas de embarque segundo a capacidade.
bool cmpPortaEmbarqueCapacidadePass(const PortaEmbarque *obj1, const PortaEmbarque *obj2);
///Função usada para a ordenação do vector de portas de embarque segundo a categoria.
bool cmpPortaEmbarqueCategoriaAvioes(const PortaEmbarque *obj1, const PortaEmbarque *obj2);


///Lista todas as portas de embarque de um aeroporto
size_t listPortaEmbarque(Aeroporto *aeroporto, bool final_pause = true, bool no_order = false);
///Selecciona uma porta de embarque de um aeroporto, de uma lista de portas de embarque
size_t selPortaEmbarque(Aeroporto* aeroporto);
///Selecciona uma porta de embarque de um aeroporto, de uma lista de portas de embarque (retorna apontador)
PortaEmbarque* selPortaEmbarquePtr(Aeroporto* aeroporto);

///Selecciona uma porta de embarque de um aeroporto, de uma lista de portas de embarque
PortaEmbarque* selPortaEmbarque(Aeroporto *aeroporto, size_t index);

///Método que mostra ao utilizador os atributos duma porta de embarque.
void infoPortaEmbarque(Aeroporto *aeroporto);
///Método que permite ao utilizador editar os atributos de uma porta de embarque
void editPortaEmbarque(Aeroporto *aeroporto);

///Método que actualiza a disponibilidade de uma porta de embarque e retorna-a
PortaEmbarque* updatePortaEmbarqueDisp(Aeroporto *aeroporto, unsigned capacidade_pass, unsigned categoria);

///Elimina uma porta de embarque de um aeroporto perguntando ao utilizador o índice
void delPortaEmbarque(Aeroporto *aeroporto);
///Elimina uma porta de embarque de um aeroporto
void delPortaEmbarque(Aeroporto *aeroporto, size_t indice);
///Elimina a porta de embarque passada como apontador do vector em aeroporto
void delPortaEmbarquePtr(Aeroporto *aeroporto, PortaEmbarque *porta_ptr);
///Função que elimina do vector de voos associados à porta de embarque o voo dado (só apontador para o voo)
void delVooPtrPortaEmbarque(PortaEmbarque *porta_embarque, Voo *voo_a_remover);



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Interface para Tripulante de um voo <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

///Adiciona um tripulante a uma companhia com os dados introduzidos pelo utilizador
void addTripulanteVoo(Companhia* companhia);
///Adiciona um tripulante a uma companhia (classe Tripulante)
void addTripulanteVoo(Voo* voo, Tripulante *tripulante);
///Lista todas os tripulantes de uma companhia
void listTripulanteVoo(Voo* voo, bool final_pause = true);
///Selecciona um tripulante de uma companhia, de uma lista de passageiros
size_t selTripulanteVoo(Voo *voo);
///Selecciona um tripulante de uma companhia, de uma lista de passageiros (retorna apontador)
Tripulante* selTripulanteVooPtr(Voo *voo);
///Elimina um tripulante de uma companhia perguntando ao utilizador o índice
void delTripulanteVoo(Voo* voo);
///Elimina um tripulante de uma companhia
void delTripulanteVoo(Voo* voo, size_t indice);



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Gestão das bases de dados <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void loaddb();
void loaddb(string filename);
void savedb();
void savedb(string filename);

template <class T>
int calcVectorIndex(const vector<T> &vec, T elem)
{
	typename vector<T>::const_iterator it = find(vec.begin(), vec.end(), elem);

	if(it==vec.end())
		return -1;
	else
		return (it-vec.begin());
}

template <class T>
T getVectorElem(vector<T> &vec, int index)
{
	if( (index==-1) || ((size_t)index>=vec.size()) )
		return NULL;
	else
		return vec[index];
}

template <class T>
int calcBSTIndex(BST<T> &bst, T elem)
{
	size_t i = 0;
	BSTItrIn<T> it(bst);
	while (!it.isAtEnd())
	{
		if(it.retrieve() == elem)
			return i;

		it.advance();
		++i;
	}

	return -1;
}

template <class T>
T getBSTElem(BST<T> &bst, size_t index)
{
	BSTItrIn<T> it( bst );
	size_t i = 0;
	while (!it.isAtEnd() && i<index)
	{
		it.advance();
		++i;
	}

	if( it.isAtEnd())
		return porta_embarque_null;
	else
		return it.retrieve();
}

template <class T>
unsigned calcBSTSize(const BST<T> &bst)
{
	size_t i = 0;
	BSTItrIn<T> it(bst);
	while (!it.isAtEnd())
	{
		it.advance();
		++i;
	}

	return i;
}

} //Fim do namespace

#endif
