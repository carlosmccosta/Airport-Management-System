/**\file Menu.cpp
 * \brief Ficheiro com a implemneta��o da classe Menu.
 *
 * PROJECTO: Projecto 2 - Gest�o do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Menu.cpp \n
 * DESCRI��O: Ficheiro com a implemneta��o da classe Menu \n
 * 			  (Baseada na estrutura do c�digo de jcard@fe.up.pt, mas com implementa��o diferente). \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - DOCENTES DA FEUP
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - V�tor Am�lio Maia Martins Moreira
 */

#include "Menu.h"


Menu::~Menu() {
	for (size_t i(0); i < _vec_sub_menus.size(); ++i)
		delete _vec_sub_menus[i];
}

void Menu::addSubMenu(const string &nome, Menu &menu, void (*menu_function)()) {
	SubMenuEntry *submenu = new SubMenuEntry(nome, &menu, menu_function);
	_vec_sub_menus.push_back(submenu);
}


void Menu::addFunction(const string &nome, void (*ptr2function)()) {
	FunctionEntry *newfunction = new FunctionEntry(nome, ptr2function);
	_vec_sub_menus.push_back(newfunction);
}


void Menu::clear() {
	for (int i = 0; i < 100; ++i)
		cout << endl;
}

void Menu::go() {
	while (true) {
		clear();
		cout << "\n\t***** " << _nome << " *****\n" << endl; //Nome do Menu
		cout << "\t0 - " << _mensagem_saida << endl; 		 //Op��o para retornar para o menu anterior

		for (size_t i = 0; i < _vec_sub_menus.size(); ++i) {
			//Mostra as op��es que se pode selecionar neste Menu.
			cout << '\t' << i + 1 << " - " << _vec_sub_menus[i]->_nome << endl;
		}
		cout << endl;

		//Pede-se ao utilizador para escolher uma das op��es listadas em cima.
		int opcao = get_int_cin("Op��o: ", (_vec_sub_menus.size() + 1), 0);

		if (opcao == 0)
			return; //Returna para o Menu anterior.
		else {
			try {
				/*
				 * Tenta abrir um submenu ou executar uma fun��o
				 * [opcao - 1] porque a primeria das op��es � para retroceder, e essa n�o est� no vector de _sub_menus
				 */
				_vec_sub_menus[opcao - 1]->execute();
			} catch (exception & e) {
				//Mostra o erro que encontrou.
				cout << e.what() << endl;
				getch();
			} catch (...) {
				//Faz o catch de todos os outros erros.
				cout << endl << endl << "Ocorreu um erro desconhecido...\nRegressando ao menu anterior..." << endl << endl;
				getch();
			}
		}
	}
}


void Menu::SubMenuEntry::execute() {
	//Se houver uma fun��o a executar, executa-a (visto que a fun��o � opcional nesta classe)
	if (_function != NULL)
		(*_function)();

	//Mostra o submenu
	 _submenu->go();
}
