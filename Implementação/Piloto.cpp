/**\file Piloto.cpp
 * \brief Ficheiro com a implementa��o da classe Piloto.
 *
 * PROJECTO: Projecto 2 - Gest�o do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Piloto.cpp \n
 * DESCRI��O: Ficheiro com a implementa��o da classe Piloto. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - V�tor Am�lio Maia Martins Moreira
 */

#include "Piloto.h"

void Piloto::imprimeInfo()
{
	string str_title = "Informa��es sobre o piloto";

		vector <string> colNames;					// nomes de colunas n�o s�o usados, logo v�o strings vazias
		colNames.push_back(string(""));
		colNames.push_back(string(""));

		vector < vector<string> > col;
		vector <string> dados;

		//Nomes dos atributos
		col.push_back(Comandos::_tripulante_op_list);

		//dados referentes � superclasse Pessoa
		dados.push_back( getNome() );
		dados.push_back( getMorada() );
		dados.push_back( getNacionalidade() );
		dados.push_back( to_string<unsigned>(getContacto()) );
		dados.push_back( to_string<unsigned>(getBI()) );
		dados.push_back( to_string<unsigned>(getIdade()) );

		//Dados referentes � subclasse tripulante
		dados.push_back( to_string<unsigned>(getNumero()) );
		dados.push_back( getCategoria() );
		dados.push_back( to_string<unsigned>(getSalarioHora()) );
		dados.push_back( to_string<unsigned>(getNumeroHorasTrabalho()) );
		dados.push_back( getTipoContrato() );
		dados.push_back( to_string<DataHora>(getExpiracaoContrato()) );
		dados.push_back( getCompanhia()->getNome() );

		if (getVooActual() == NULL)
			dados.push_back((string)"N/A");
		else
			dados.push_back( to_string<unsigned>(getVooActual()->getNumeroVoo()) );


		//Dados relativos aos atributos
		col.push_back(dados);

		printMenu(str_title, col, colNames, false, false, true, true);
}

