/**\file PortaEmbarque.cpp
 * \brief Ficheiro com a implementação da classe PortaEmbarque.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: PortaEmbarque.cpp \n
 * DESCRIÇÃO: Ficheiro com a implementação da classe PortaEmbarque. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#include "PortaEmbarque.h"


bool PortaEmbarque::operator==(const PortaEmbarque &porta_embarque) const {
	if ((_numero == porta_embarque._numero) && (_localizacao == porta_embarque._localizacao))
		return true;
	else
		return false;
}

bool PortaEmbarque::operator<(const PortaEmbarque &porta_embarque) const {
	if (_numero < porta_embarque._numero)
		return true;
	else
		return false;
}

bool PortaEmbarquePtr::operator==(const PortaEmbarquePtr &porta_embarque) const{
	if ((porta->getNumero() == porta_embarque.getNumero()) && (porta->getLocalizacao() == porta_embarque.getLocalizacao()))
		return true;
	else
		return false;
}

bool PortaEmbarquePtr::operator<(const PortaEmbarquePtr &porta_embarque) const{
	if (porta->getVagasPass() < porta_embarque.getVagasPass())
		return false;
	else if (porta->getVagasPass() > porta_embarque.getVagasPass())
		return true;
	else if (porta->getCategoriaAvioes() < porta_embarque.getCategoriaAvioes())
		return false;
	else if (porta->getCategoriaAvioes() > porta_embarque.getCategoriaAvioes())
		return true;
	else if (porta->getNumero() < porta_embarque.getNumero())
		return true;
	else if (porta->getNumero() > porta_embarque.getNumero())
		return false;
	else
		return false;


/*
	if (porta->getVagasPass() < porta_embarque.getVagasPass())
	{
		return false;
	}
	else if (porta->getVagasPass() == porta_embarque.getVagasPass())
	{
		if (porta->getCategoriaAvioes() < porta_embarque.getCategoriaAvioes())
		{
			return false;
		}
		else if (porta->getCategoriaAvioes() == porta_embarque.getCategoriaAvioes())
		{
			if (porta->getCapacidadePass() < porta_embarque.getCapacidadePass())
			{
				return false;
			}
			else if (porta->getCapacidadePass() == porta_embarque.getCapacidadePass())
			{
				if (porta->getNumero() < porta_embarque.getNumero())
				{
					return false;
				}
				else
					return true;
			}
			else
				return true;
		}
		else
			return true;
	}
	else
		return true;*/
}

//Inicialização do vector que contem a informação associada a cada tipo da enumeração necessidades_especiais_t
vector <string> PortaEmbarque::_categorias_avioes_info;

void PortaEmbarque::init_categorias_avioes_info() {
	_categorias_avioes_info.clear();
	_categorias_avioes_info.push_back("Médio Curso");
	_categorias_avioes_info.push_back("Longo Curso");
}

void PortaEmbarque::listCategoriasAvioesInfo() {
	vector < vector <string> > info;
	info.push_back(_categorias_avioes_info);
	string title = (string)"Possiveis categorias de aviões";
	vector <string> colnames;
	colnames.push_back("");
	printMenu(title, info, colnames, false, false, false, true);
	cout << endl;
}
