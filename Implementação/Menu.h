/**\file Menu.h
 * \brief Classe de gestão de menus.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Menu.h \n
 * DESCRIÇÃO: Classe de gestão de menus. \n
 * 			  (Baseada na estrutura do código de jcard@fe.up.pt, mas com implementação diferente). \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - DOCENTES DA FEUP
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#ifndef MENU_H_
#define MENU_H_

#include <string>
#include <vector>
#include <iostream>

#include "Exceptions.h"
#include "utils.h"

using std::string;
using std::vector;

#define DEFAULT_EXIT_MESSAGE "Voltar ao menu anterior"


///Classe que gera e processa menus.
class Menu {
private:
	/**
	 * \brief Classe abstrata privada nested de Menu.
	 *
	 * Tem uma string descritiva do que é o submenu.
	 * As subclasses devem implementar o método abstrato execute().
	 */
	class MenuEntry {
	public:
		MenuEntry() : _nome(), _function(NULL) {}
		MenuEntry(string nome, void (*function)()): _nome(nome), _function(function) {}
		virtual ~MenuEntry() {}

		string _nome; 				///< Nome do Menu.
		void (*_function)();		///< Apontador para um função.
		virtual void execute() = 0; ///< Executa as operações associadas a esse submenu (entrar noutro menu ou executar uma função).
	};


	/**
	 * \brief Subclasse de MenuEntry, que representa um submenu que executa uma função quando é escolhido.
	 */
	class FunctionEntry: public MenuEntry {
	public:
		FunctionEntry(): MenuEntry() {}
		FunctionEntry(string nome, void (*function)()): MenuEntry(nome, function) {}
		///Executa a função dada pelo apontador (*_function)() da superclasse.
		void execute() { (*_function)(); }
	};


	/**
	 * Subclasse de MenuEntry, que representa um submenu que aponta para outro menu.
	 */
	class SubMenuEntry: public MenuEntry {
	public:
		SubMenuEntry(): _submenu(NULL) {}
		SubMenuEntry(string nome, Menu *submenu, void (*menu_function)() = NULL): MenuEntry(nome, menu_function), _submenu(submenu) {}
		Menu *_submenu;	///< Apontador para outro Menu.
		void execute();	///< Entra no submenu e executa a função associada a essa entrada caso exista.
	};


	string _nome; 						///< Nome do Menu.
	string _mensagem_saida; 			///< Texto mostrado para a opção de saída do Menu.
	vector <MenuEntry*> _vec_sub_menus;	///< Vector com os submenus.


public:
	Menu() : _nome(), _mensagem_saida(), _vec_sub_menus() {}
	Menu(string nome, string mensagem_saida = DEFAULT_EXIT_MESSAGE) : _nome(nome), _mensagem_saida(mensagem_saida), _vec_sub_menus() {}
	virtual ~Menu();

	string getNome() const { return _nome; }
	string getMensagemSaida() const { return _mensagem_saida; }
	const vector <MenuEntry*> getVecSubMenus() const { return _vec_sub_menus; }
	vector <MenuEntry*>& getRefVecSubMenus() { return _vec_sub_menus; }
	const vector <MenuEntry*>& getConstRefVecSubMenus() const { return _vec_sub_menus; }

	void setNome(string nome) { _nome = nome; }
	void setMensagemSaida(string mensagem_saida) { _mensagem_saida = mensagem_saida; }
	void setVecSubMenus(vector <MenuEntry*> vec_sub_menus) { _vec_sub_menus = vec_sub_menus; }

	/**
	 * \brief Adiciona um submenu a este Menu.
	 *
	 * @param nome Nome a dar ao submenu.
	 * @param menu Apontador para o submenu.
	 * @param menu_function Apontador para uma função a ser executada pela nas subclasses pela função execute().
	 */
	void addSubMenu(const string &nome, Menu &menu, void (*menu_function)() = NULL);

	/**
	 * \brief Adiciona uma entrada a este menu que executa uma determinada função.
	 *
	 * @param nome Nome a dar à função no menu.
	 * @param function Apontador para a função a executar.
	 */
	void addFunction(const string &nome, void (*function)());

	///Motra os submenus deste menu e pede ao utilizador para introduzir o número do comando que quer executar.
	void go();

	///Limpa o ecrã da consola, metendo 100 linhas vazias após o último output.
	static void clear();
};

#endif
