/**\file main.cpp
 * \brief Inicializa��o do programa criando menus e load/save da base de dados.
 *
 * PROJECTO: Projecto 2 - Gest�o do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: main.cpp \n
 * DESCRI��O: Inicializa��o do programa criando menus e load/save da base de dados. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - V�tor Am�lio Maia Martins Moreira
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
PortaEmbarquePtr porta_embarque_null(&porta_embarque_null_);	// tem que ser criada antes do aeroporto porque � usada l�

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

	//Inicializa��o dos vectores com os comandos que existem em cada classe
	Comandos::initAllOp();

	//Inicializa��o do vector com as descri��es das necessidades especiais
	Passageiro::init_necessidades_especiais_info();

	//Inicializa��o do vector com as descri��es das categorias de avi�o
	PortaEmbarque::init_categorias_avioes_info();

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Gest�o de companhias  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Menu menuTiposAvioes("Gestao de tipos de avi�es", "Retroceder");
	menuTiposAvioes.addFunction("Listar Tipos de Avi�es", opInfoTipoAviao);
	menuTiposAvioes.addFunction("Adicionar Tipo de Avi�o", opNewTipoAviao);
	menuTiposAvioes.addFunction("Editar Tipo de Avi�o", opEditTipoAviao);
	menuTiposAvioes.addFunction("Remover Tipo de Avi�o", opDelTipoAviao);

	//*********************  Avi�es ************************
	Menu menuAvioes("Gestao de avi�es", "Retroceder");
	menuAvioes.addFunction("Listar avi�es", opInfoAviao);
	menuAvioes.addFunction("Adicionar avi�o", opNewAviao);
	menuAvioes.addFunction("Editar avi�o", opEditAviao);
	menuAvioes.addFunction("Remover avi�o", opDelAviao);

	//*********************  Tripulantes ************************
	Menu menuTripulantes("Gestao de Tripulantes", "Retroceder");
	menuTripulantes.addFunction("Listar tripulantes", opInfoTripulante);
	menuTripulantes.addFunction("Adicionar tripulante", opNewTripulante);
	menuTripulantes.addFunction("Editar tripulante", opEditTripulante);
	menuTripulantes.addFunction("Remover tripulante", opDelTripulante);

	//*********************  Plano de Voo ************************
	Menu menuPlanoVoo("Gest�o do voo", "Retroceder");
	menuPlanoVoo.addFunction("Inicializa��o do check-in do voo", opInitCheckIn);
	menuPlanoVoo.addFunction("Check-in dos passageiros", opCheckIn);
	menuPlanoVoo.addFunction("Lista dos passageiros a embarcar num voo", opPrintFilaPrioridadeEmbarque);
	menuPlanoVoo.addFunction("Chamada dos passageiros a embarcar num voo", opChamadaEmbarqueVoo);
	menuPlanoVoo.addFunction("Informa��es sobre o voo", opInfoPlanoVoo);
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
	Menu menuCompanhia("Gest�o da companhia a�rea", "Retroceder");
	menuCompanhia.addSubMenu("Gestao de avi�es", menuAvioes);
	menuCompanhia.addSubMenu("Gestao de tipos de avi�es", menuTiposAvioes);
	menuCompanhia.addSubMenu("Gestao de tripulantes", menuTripulantes);
	menuCompanhia.addSubMenu("Gest�o de planos de Voo", menuVoos);
	menuCompanhia.addFunction("Editar esta companhia A�rea", opEditCompanhiaActual);
	menuCompanhia.addFunction("Informa��es sobre a companhia", opInfoCompanhia);

	//*********************  Companhia ************************
	Menu menuCompanhias("Gestao de companhias a�reas", "Retroceder");
	menuCompanhias.addSubMenu("Listar companhias a�reas", menuCompanhia, opSelCompanhia);
	menuCompanhias.addFunction("Adicionar companhia a�rea", opNewCompanhia);
	menuCompanhias.addFunction("Editar companhia a�rea", opEditCompanhia);
	menuCompanhias.addFunction("Remover companhia a�rea", opDelCompanhia);


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Gest�o de portas de embarque  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Menu menuPortasEmbarque("Gestao de Portas de Embarque", "Retroceder");
	menuPortasEmbarque.addFunction("Listar informa��es das portas de embarque", opInfoPortaEmbarque);
	menuPortasEmbarque.addFunction("Lista dos passageiros a embarcar num voo", opPrintFilaPrioridadeEmbarque);
	menuPortasEmbarque.addFunction("Chamada dos passageiros a embarcar num voo", opChamadaEmbarqueVoo);
	menuPortasEmbarque.addFunction("Adicionar porta de embarque", opNewPortaEmbarque);
	menuPortasEmbarque.addFunction("Editar porta de embarque", opEditPortaEmbarque);
	menuPortasEmbarque.addFunction("Remover porta de embarque", opDelPortaEmbarque);


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Gest�o de passageiros  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Menu menuPassageiros("Gest�o de passageiros", "Retroceder");
	menuPassageiros.addFunction("Listar passageiros", opInfoPassageiro);
	menuPassageiros.addFunction("Adicionar passageiro", opNewPassageiro);
	menuPassageiros.addFunction("Editar pssageiro", opEditPassageiro);
	menuPassageiros.addFunction("Remover passageiro", opDelPassageiro);


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Gest�o dos voos fechados  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Menu menuVoosFechados("Gest�o dos voos fechados do aeroporto", "Sair");
	menuVoosFechados.addFunction("Listagem de todos os voos fechados", opListHashSetVoos);
	menuVoosFechados.addFunction("Listagem de todos os voos fechados entre datas por crit�rio", opListHashSetVoosEntreDatasCriterio);
	menuVoosFechados.addFunction("Pesquisar voo fechado", opSearchHashSetVoos);
	menuVoosFechados.addFunction("Inserir voo aos voos fechados", opAddVooHashSetVoos);
	menuVoosFechados.addFunction("Eliminar voo da tabela de voos fechado", opDelVooHashSetVoos);


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Gest�o das taxas  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Menu menuTaxas("Visualiza��o das taxas dos balc�es e portas de embarque", "Sair");
	menuTaxas.addFunction("C�lculo da taxas de utiliza��o dos balc�es entre datas", opListTaxasBalcoesEntreDatas);
	menuTaxas.addFunction("C�lculo da taxas de utiliza��o dos balc�es para um dado voo", opListTaxasBalcoesVooEntreDatas);
	menuTaxas.addFunction("Listagem das taxas de utiliza��o dos balc�es por voo entre datas", opListTaxasBalcoesVoosEntreDatas);
	menuTaxas.addFunction("C�lculo da taxas de utiliza��o das portas de embarque ente datas", opListTaxasPortasEmbarqueEntreDatas);
	menuTaxas.addFunction("C�lculo da taxas de utiliza��o das portas de embarque para um dado voo", opListTaxasPortasEmbarqueVooEntreDatas);
	menuTaxas.addFunction("Listagem das taxas de utiliza��o das portas de embarque por voo entre datas", opListTaxasPortasEmbarqueVoosEntreDatas);


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Menu  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Menu menuPrincipal("Gest�o do embarque dos passageiros num aeroporto (check-in/embarque)", "Sair");
	menuPrincipal.addSubMenu("Gestao de companhias a�reas", menuCompanhias);
	menuPrincipal.addSubMenu("Gest�o de portas de embarque", menuPortasEmbarque);
	menuPrincipal.addSubMenu("Gest�o de passageiros", menuPassageiros);
	menuPrincipal.addSubMenu("Gestao dos voos fechados do aeroporto", menuVoosFechados);
	menuPrincipal.addSubMenu("Visualiza��o das taxas dos balc�es e portas de embarque", menuTaxas);
	menuPrincipal.addFunction("Informa��es acerca do aeroporto", opInfoAeroporto);
	menuPrincipal.addFunction("Editar Informa��es acerca do aeroporto", opEditAeroporto);

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
