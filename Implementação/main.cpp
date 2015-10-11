/**\file main.cpp
 * \brief Inicialização do programa criando menus e load/save da base de dados.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: main.cpp \n
 * DESCRIÇÃO: Inicialização do programa criando menus e load/save da base de dados. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#include <iostream>
#include "GestaoAeroporto.h"
#include "Aeroporto.h"
#include "Companhia.h"
#include "TipoAviaoDB.h"
#include "Comandos.h"
#include "Menu.h"

using namespace CRUD;

PortaEmbarque porta_embarque_null_("NULL","NULL",0,0,-1);
PortaEmbarquePtr porta_embarque_null(&porta_embarque_null_);	// tem que ser criada antes do aeroporto porque é usada lá

Aeroporto aeroporto;
TipoAviaoDB tipo_aviao_DB;

PortaEmbarque* porta_embarque_actual(NULL);
Passageiro* passageiro_actual(NULL);
Companhia* companhia_actual(NULL);
Aviao *aviao_actual(NULL);
TipoAviao *tipo_aviao_actual(NULL);
Tripulante *tripulante_actual(NULL);
Voo *voo_actual(NULL);

void opNewCompanhia()							{ addCompanhia(&aeroporto); }
void opNewTipoAviao()							{ tipo_aviao_DB.addTipoAviao(); }
void opNewAviao()								{ addAviao(companhia_actual); }
void opNewPlanoVoo()							{ addPlanoVoo(&aeroporto, companhia_actual); }
void opNewTripulante()							{ addTripulante(companhia_actual); }
void opNewTripulanteVoo()						{ addTripulanteVoo(companhia_actual); }
void opNewPassageiro()							{ addPassageiro(&aeroporto); }
void opNewPortaEmbarque()						{ addPortaEmbarque(&aeroporto); }

void opInfoAeroporto()							{ infoAeroporto(&aeroporto); }
void opInfoCompanhia()							{ infoCompanhia(companhia_actual); }
void opInfoTipoAviao()							{ tipo_aviao_DB.infoTipoAviao(); }
void opInfoAviao()								{ infoAviao(companhia_actual); }
void opInfoPlanoVoo()							{ infoPlanoVoo(companhia_actual, voo_actual); }
void opInfoTripulante()							{ infoTripulante(companhia_actual); }
void opInfoPassageiro()							{ infoPassageiro(&aeroporto); }
void opInfoPortaEmbarque()						{ infoPortaEmbarque(&aeroporto); }

void opEditAeroporto()							{ editAeroporto(&aeroporto); }
void opEditCompanhia()							{ editCompanhia(&aeroporto); }
void opEditCompanhiaActual()					{ editCompanhia(&aeroporto, companhia_actual); }
void opEditTipoAviao()							{ tipo_aviao_DB.editTipoAviao(); }
void opEditAviao()								{ editAviao(&aeroporto, companhia_actual); }
void opEditPlanoVoo()							{ editPlanoVoo(&aeroporto, companhia_actual); }
void opEditTripulante()							{ editTripulante(&aeroporto, companhia_actual); }
void opEditPassageiro()							{ editPassageiro(&aeroporto); }
void opEditPortaEmbarque()						{ editPortaEmbarque(&aeroporto); }

void opDelCompanhia()							{ delCompanhia(&aeroporto); }
void opDelTipoAviao()							{ tipo_aviao_DB.delTipoAviao(); }
void opDelAviao()								{ delAviao(companhia_actual); }
void opDelPlanoVoo()							{ delPlanoVoo(&aeroporto, companhia_actual); }
void opDelTripulante()							{ delTripulante(companhia_actual); }
void opDelTripulanteVoo()						{ delTripulanteVoo(voo_actual); }
void opDelPassageiro()							{ delPassageiro(&aeroporto); }
void opDelPortaEmbarque()						{ delPortaEmbarque(&aeroporto); }

void opSelCompanhia()							{ selCompanhia(&aeroporto); }
void opSelCompanhiaPlanoVoo()					{ selPlanoVooPtr(companhia_actual); }


void opInitCheckIn()							{ initCheckIn(voo_actual); }
void opCheckIn()								{ checkIn(&aeroporto, voo_actual); }
void opChamadaEmbarqueVoo()						{ chamadaEmbarqueVoo(&aeroporto, voo_actual); }
void opPrintFilaPrioridadeEmbarque()			{ printPriorityQueue(voo_actual); }
void opChamadaEmbarqueVooPortaEmbarque()		{ chamadaEmbarqueVooPortaEmbarque(&aeroporto); }
void opPrintPassageirosPortaEmbarque()			{ printPassageirosPortaEmbarque(&aeroporto); }

void opFecharVoo()								{ fecharVoo(&aeroporto, voo_actual); }

void opListHashSetVoos()						{ listHashSetVoos(&aeroporto); }
void opListHashSetVoosEntreDatasCriterio()		{ listHashSetVoosEntreDatasCriterio(&aeroporto); }
void opSearchHashSetVoos()						{ searchHashSetVoos(&aeroporto); }
void opAddVooHashSetVoos()						{ addVooHashSetVoos(&aeroporto); }
void opDelVooHashSetVoos()						{ delVooHashSetVoos(&aeroporto); }

void opListTaxasBalcoesEntreDatas()				{ listTaxasBalcoesEntreDatas(&aeroporto); }
void opListTaxasBalcoesVooEntreDatas()			{ listTaxasBalcoesVooEntreDatas(&aeroporto); }
void opListTaxasBalcoesVoosEntreDatas()			{ listTaxasBalcoesVoosEntreDatas(&aeroporto); }
void opListTaxasPortasEmbarqueEntreDatas() 		{ listTaxasPortasEmbarqueEntreDatas(&aeroporto); }
void opListTaxasPortasEmbarqueVooEntreDatas()	{ listTaxasPortasEmbarqueVooEntreDatas(&aeroporto); }
void opListTaxasPortasEmbarqueVoosEntreDatas()	{ listTaxasPortasEmbarqueVoosEntreDatas(&aeroporto); }



int main()
{
	try
	{
		tipo_aviao_DB.loaddb_tipos_aviao();
		loaddb();

		cout << "Base de Dados lida com sucesso!" << endl;
	}
	catch(Exceptions & e)
	{
		cout << "Erro ao carregar Base de Dados!\n" << e.what() << endl;
		getch();
	}

	//Inicialização dos vectores com os comandos que existem em cada classe
	Comandos::initAllOp();

	//Inicialização do vector com as descrições das necessidades especiais
	Passageiro::init_necessidades_especiais_info();

	//Inicialização do vector com as descrições das categorias de avião
	PortaEmbarque::init_categorias_avioes_info();

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Gestão de companhias  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Menu menuTiposAvioes("Gestao de tipos de aviões", "Retroceder");
	menuTiposAvioes.addFunction("Listar Tipos de Aviões", opInfoTipoAviao);
	menuTiposAvioes.addFunction("Adicionar Tipo de Avião", opNewTipoAviao);
	menuTiposAvioes.addFunction("Editar Tipo de Avião", opEditTipoAviao);
	menuTiposAvioes.addFunction("Remover Tipo de Avião", opDelTipoAviao);

	//*********************  Aviões ************************
	Menu menuAvioes("Gestao de aviões", "Retroceder");
	menuAvioes.addFunction("Listar aviões", opInfoAviao);
	menuAvioes.addFunction("Adicionar avião", opNewAviao);
	menuAvioes.addFunction("Editar avião", opEditAviao);
	menuAvioes.addFunction("Remover avião", opDelAviao);

	//*********************  Tripulantes ************************
	Menu menuTripulantes("Gestao de Tripulantes", "Retroceder");
	menuTripulantes.addFunction("Listar tripulantes", opInfoTripulante);
	menuTripulantes.addFunction("Adicionar tripulante", opNewTripulante);
	menuTripulantes.addFunction("Editar tripulante", opEditTripulante);
	menuTripulantes.addFunction("Remover tripulante", opDelTripulante);

	//*********************  Plano de Voo ************************
	Menu menuPlanoVoo("Gestão do voo", "Retroceder");
	menuPlanoVoo.addFunction("Inicialização do check-in do voo", opInitCheckIn);
	menuPlanoVoo.addFunction("Check-in dos passageiros", opCheckIn);
	menuPlanoVoo.addFunction("Lista dos passageiros a embarcar num voo", opPrintFilaPrioridadeEmbarque);
	menuPlanoVoo.addFunction("Chamada dos passageiros a embarcar num voo", opChamadaEmbarqueVoo);
	menuPlanoVoo.addFunction("Informações sobre o voo", opInfoPlanoVoo);
	menuPlanoVoo.addFunction("Fechar voo", opFecharVoo);

	//*********************  Plano de voos ************************
	Menu menuVoos("Gestao de Planos de Voo", "Retroceder");
	menuVoos.addSubMenu("Selecionar plano de voo", menuPlanoVoo, opSelCompanhiaPlanoVoo);
	menuVoos.addFunction("Adicionar plano de Voo", opNewPlanoVoo);
	menuVoos.addFunction("Adicionar tripulantes ao voo", opNewTripulanteVoo);
	menuVoos.addFunction("Remover tripulantes ao voo", opDelTripulanteVoo);
	menuVoos.addFunction("Editar plano de voo", opEditPlanoVoo);
	menuVoos.addFunction("Remover plano de voo", opDelPlanoVoo);

	//*********************  Companhias ************************
	Menu menuCompanhia("Gestão da companhia aérea", "Retroceder");
	menuCompanhia.addSubMenu("Gestao de aviões", menuAvioes);
	menuCompanhia.addSubMenu("Gestao de tipos de aviões", menuTiposAvioes);
	menuCompanhia.addSubMenu("Gestao de tripulantes", menuTripulantes);
	menuCompanhia.addSubMenu("Gestão de planos de Voo", menuVoos);
	menuCompanhia.addFunction("Editar esta companhia Aérea", opEditCompanhiaActual);
	menuCompanhia.addFunction("Informações sobre a companhia", opInfoCompanhia);

	//*********************  Companhia ************************
	Menu menuCompanhias("Gestao de companhias aéreas", "Retroceder");
	menuCompanhias.addSubMenu("Listar companhias aéreas", menuCompanhia, opSelCompanhia);
	menuCompanhias.addFunction("Adicionar companhia aérea", opNewCompanhia);
	menuCompanhias.addFunction("Editar companhia aérea", opEditCompanhia);
	menuCompanhias.addFunction("Remover companhia aérea", opDelCompanhia);


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Gestão de portas de embarque  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Menu menuPortasEmbarque("Gestao de Portas de Embarque", "Retroceder");
	menuPortasEmbarque.addFunction("Listar informações das portas de embarque", opInfoPortaEmbarque);
	menuPortasEmbarque.addFunction("Lista dos passageiros a embarcar num voo", opPrintFilaPrioridadeEmbarque);
	menuPortasEmbarque.addFunction("Chamada dos passageiros a embarcar num voo", opChamadaEmbarqueVoo);
	menuPortasEmbarque.addFunction("Adicionar porta de embarque", opNewPortaEmbarque);
	menuPortasEmbarque.addFunction("Editar porta de embarque", opEditPortaEmbarque);
	menuPortasEmbarque.addFunction("Remover porta de embarque", opDelPortaEmbarque);


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Gestão de passageiros  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Menu menuPassageiros("Gestão de passageiros", "Retroceder");
	menuPassageiros.addFunction("Listar passageiros", opInfoPassageiro);
	menuPassageiros.addFunction("Adicionar passageiro", opNewPassageiro);
	menuPassageiros.addFunction("Editar pssageiro", opEditPassageiro);
	menuPassageiros.addFunction("Remover passageiro", opDelPassageiro);


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Gestão dos voos fechados  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Menu menuVoosFechados("Gestão dos voos fechados do aeroporto", "Sair");
	menuVoosFechados.addFunction("Listagem de todos os voos fechados", opListHashSetVoos);
	menuVoosFechados.addFunction("Listagem de todos os voos fechados entre datas por critério", opListHashSetVoosEntreDatasCriterio);
	menuVoosFechados.addFunction("Pesquisar voo fechado", opSearchHashSetVoos);
	menuVoosFechados.addFunction("Inserir voo aos voos fechados", opAddVooHashSetVoos);
	menuVoosFechados.addFunction("Eliminar voo da tabela de voos fechado", opDelVooHashSetVoos);


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Gestão das taxas  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Menu menuTaxas("Visualização das taxas dos balcões e portas de embarque", "Sair");
	menuTaxas.addFunction("Cálculo da taxas de utilização dos balcões entre datas", opListTaxasBalcoesEntreDatas);
	menuTaxas.addFunction("Cálculo da taxas de utilização dos balcões para um dado voo", opListTaxasBalcoesVooEntreDatas);
	menuTaxas.addFunction("Listagem das taxas de utilização dos balcões por voo entre datas", opListTaxasBalcoesVoosEntreDatas);
	menuTaxas.addFunction("Cálculo da taxas de utilização das portas de embarque ente datas", opListTaxasPortasEmbarqueEntreDatas);
	menuTaxas.addFunction("Cálculo da taxas de utilização das portas de embarque para um dado voo", opListTaxasPortasEmbarqueVooEntreDatas);
	menuTaxas.addFunction("Listagem das taxas de utilização das portas de embarque por voo entre datas", opListTaxasPortasEmbarqueVoosEntreDatas);


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Menu  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Menu menuPrincipal("Gestão do embarque dos passageiros num aeroporto (check-in/embarque)", "Sair");
	menuPrincipal.addSubMenu("Gestao de companhias aéreas", menuCompanhias);
	menuPrincipal.addSubMenu("Gestão de portas de embarque", menuPortasEmbarque);
	menuPrincipal.addSubMenu("Gestão de passageiros", menuPassageiros);
	menuPrincipal.addSubMenu("Gestao dos voos fechados do aeroporto", menuVoosFechados);
	menuPrincipal.addSubMenu("Visualização das taxas dos balcões e portas de embarque", menuTaxas);
	menuPrincipal.addFunction("Informações acerca do aeroporto", opInfoAeroporto);
	menuPrincipal.addFunction("Editar Informações acerca do aeroporto", opEditAeroporto);

	menuPrincipal.go();

	try
	{
		savedb();
		tipo_aviao_DB.savedb_tipos_aviao();

		cout << "Base de Dados guardada com sucesso!" << endl;
	}
	catch(Exceptions & e)
	{
		cout << "Erro ao guardar Base de Dados!\n" << e.what() << endl;
		getch();
	}

	return 0;
}
