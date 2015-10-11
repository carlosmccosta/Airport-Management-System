/**\file GestaoAeroporto.cpp
 * \brief Ficheiro que contém os métodos CRUD (manutenção de dados), de cada classe.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: GestaoAeroporto.cpp \n
 * DESCRIÇÃO: Ficheiro que contém os métodos CRUD (manutenção de dados), de cada classe. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */


#include "GestaoAeroporto.h"

//############################### Métodos CRUD (create, read, update, delete) para as classes #####################################


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Aviao <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void CRUD::addAviao(Companhia *companhia) {
	cout << endl << endl;
	string matricula;						//Ex: CSTNA
	string nome;							//Ex: Camões
	unsigned peso_max_bagagem;				//Peso máximo da bagagem por passageiro. Ex: 50
	unsigned capacidade_max_passageiros;
	TipoAviao *tipoAviao(NULL);
	Voo *voo_actual(NULL);
	DataHora dataConstrucao;
	DataHora primeiroVoo;
	DataHora ultimaRevisao;
	DataHora proximaRevisao;

	matricula = companhia_actual->getMatriculaAviaoCin("Introduza a matrícula do avião: ");

	cout << "Introduza o nome: " << flush;
	getlineCin(nome);

	peso_max_bagagem = get_uint_cin<unsigned>("Introduza o peso máximo da bagagem em kg: ");
	capacidade_max_passageiros = get_uint_cin<unsigned>("Introduza o número máximo de passageiros que o avião suporta: ");

	cout << "Selecione o tipo de avião: " << flush;
	tipoAviao = tipo_aviao_DB.selTipoAviaoPtr();

	cout << endl;

	bool adic_voo = get_yes_no("Pretende adicionar um voo a este avião?\n(S/N): ");
	if (adic_voo) {
		cout << "Selecione o voo associado a este avião: " << endl;
		voo_actual = selPlanoVooPtr(companhia);
	}

	cout << endl;

	dataConstrucao.getDataHoraCin("Introduza a data de construção do avião\n no formato <AAAA/MM/DD HH:mm>: ");
	primeiroVoo.getDataHoraCin("Introduza a data do primeiro voo do avião\n no formato <AAAA/MM/DD HH:mm>: ");
	ultimaRevisao.getDataHoraCin("Introduza a data da última revisão do avião\n no formato <AAAA/MM/DD HH:mm>: ");
	proximaRevisao.getDataHoraCin("Introduza a data da próxima revisão do avião\n no formato <AAAA/MM/DD HH:mm>: ");

	Aviao* aviao = new Aviao(matricula, nome, peso_max_bagagem, tipoAviao, companhia_actual, voo_actual, dataConstrucao, primeiroVoo, ultimaRevisao, proximaRevisao);

	addAviao(companhia, aviao);
	cout << endl << endl <<"Adicionado com sucesso!" << endl << endl << endl;
	getch();
}


void CRUD::addAviao(Companhia *companhia, Aviao *aviao) {
	vector <Aviao*> &vec_avioes = companhia->getRefAvioes();
	vector <Aviao*>::const_iterator it_aviao;

	for (it_aviao = vec_avioes.begin(); it_aviao != vec_avioes.end(); ++it_aviao)
		if ((*aviao) == *(*it_aviao))
			throw ExElementAlreadyExists <Aviao> (*aviao);

	aviao->getTipoAviao()->getRefAvioesAssociados().push_back(aviao);

	vector<TipoAviao*>::iterator it = find( companhia->getRefFrota().begin(), companhia->getRefFrota().end(), aviao->getTipoAviao() );
	if( it==companhia->getRefFrota().end() )
		companhia->getRefFrota().push_back(aviao->getTipoAviao());

	vec_avioes.push_back(aviao);
}



bool CRUD::cmpAviaoMatricula(const Aviao *av1, const Aviao *av2) {
	return (av1->getMatricula() < av2->getMatricula());
}

bool CRUD::cmpAviaoNome(const Aviao *av1, const Aviao *av2) {
	return (av1->getNome() < av2->getNome());
}

bool CRUD::cmpAviaoProximaRevisao(const Aviao *av1, const Aviao *av2) {
	return (av1->getProximaRevisao() < av2->getProximaRevisao());
}


void CRUD::listAviao(Companhia *companhia, bool final_pause) {
	cout << endl << endl;
	vector <Aviao*> &vec_avioes = companhia->getRefAvioes();

	if (vec_avioes.size() == 0) {
		throw ExEmptyVector("Não existem aviões na companhia!");
	}

	//Selecção do método de ordenação
	string str_title_ordenacao = "Método de ordenação";

	vector <string> colNames_ordenacao;
	colNames_ordenacao.push_back(string("Critério de ordenação"));

	vector < vector<string> > col_ordenacao;
	vector <string> parametros_ordenacao;
	parametros_ordenacao.push_back((string)"Matrícula");
	parametros_ordenacao.push_back((string)"Nome");
	parametros_ordenacao.push_back((string)"Data próxima revisão");
	col_ordenacao.push_back(parametros_ordenacao);


	cout << endl;
	printMenu(str_title_ordenacao, col_ordenacao, colNames_ordenacao);

	cout << endl << endl;
	size_t metodo = get_uint_cin("Selecione o critério de ordenação que quer usar: ", parametros_ordenacao.size());
	cout << endl;

	//Listagem ordenada dos aviões
	string str_title = "Lista de avioes";
	vector < vector<string> > col;

	vector <string> colNames;

	col.push_back(vector<string> ());
	col.push_back(vector<string> ());
	col.push_back(vector<string> ());


	//Ordenação do vector de acordo com o parâmetro fornecido
	switch (metodo) {
		case 0: {
			sort(vec_avioes.begin(), vec_avioes.end(), cmpAviaoMatricula);
			colNames.push_back((string)"Matrícula");
			colNames.push_back((string)"Nome");
			colNames.push_back((string)"Data próxima revisão");
			size_t i = 0;
			for (vector <Aviao*>::const_iterator it_aviao = vec_avioes.begin(); it_aviao != vec_avioes.end(); ++it_aviao) {
				col[i++].push_back((*it_aviao)->getMatricula());
				col[i++].push_back((*it_aviao)->getNome());
				col[i].push_back(to_string((*it_aviao)->getProximaRevisao()));
				i = 0;
			}
			break;
		}

		case 1: {
			sort(vec_avioes.begin(), vec_avioes.end(), cmpAviaoNome);
			colNames.push_back((string)"Nome");
			colNames.push_back((string)"Matrícula");
			colNames.push_back((string)"Data próxima revisão");
			size_t i = 0;
			for (vector <Aviao*>::const_iterator it_aviao = vec_avioes.begin(); it_aviao != vec_avioes.end(); ++it_aviao) {
				col[i++].push_back((*it_aviao)->getNome());
				col[i++].push_back((*it_aviao)->getMatricula());
				col[i].push_back(to_string((*it_aviao)->getProximaRevisao()));
				i = 0;
			}
			break;
		}

		case 2: {
			sort(vec_avioes.begin(), vec_avioes.end(), cmpAviaoProximaRevisao);
			colNames.push_back((string)"Data próxima revisão");
			colNames.push_back((string)"Matrícula");
			colNames.push_back((string)"Nome");
			size_t i = 0;
			for (vector <Aviao*>::const_iterator it_aviao = vec_avioes.begin(); it_aviao != vec_avioes.end(); ++it_aviao) {
				col[i++].push_back(to_string((*it_aviao)->getProximaRevisao()));
				col[i++].push_back((*it_aviao)->getMatricula());
				col[i].push_back((*it_aviao)->getNome());
				i = 0;
			}
			break;
		}
	}

	printMenu(str_title, col, colNames, true);

	if (final_pause)
		getch();
}


size_t CRUD::selAviao(Companhia *companhia) {
	listAviao(companhia);
	cout << endl << endl;
	size_t indice = get_uint_cin<size_t>("\nIntroduza o índice do avião para mais informações (0 para retroceder): ", companhia->getConstRefAvioes().size(),0,true);
	aviao_actual = companhia->getConstRefAvioes()[indice];
	return indice;
}


Aviao* CRUD::selAviaoPtr(Companhia *companhia) {
	return companhia->getConstRefAvioes()[ selAviao(companhia) ];
}


void CRUD::infoAviao(Companhia *companhia) {
	cout << endl << endl;
	size_t indice = selAviao(companhia);

	Aviao *aviao = companhia->getConstRefAvioes()[indice];

	string str_title = "Informações sobre o avião";

	vector <string> colNames;					// nomes de colunas não são usados, logo vão strings vazias
	colNames.push_back(string(""));
	colNames.push_back(string(""));

	vector < vector<string> > col;
	vector <string> dados;

	//Nomes dos atributos
	col.push_back(Comandos::_aviao_op_list);

	dados.push_back( aviao->getMatricula() );
	dados.push_back( aviao->getNome() );
	dados.push_back( to_string<unsigned>(aviao->getPesoMaxBagagem()) );
	dados.push_back( aviao->getTipoAviao()->getNomeTipo() );
	dados.push_back( aviao->getCompanhia()->getNome() );

	if (aviao->getVooActual() == NULL)
		dados.push_back( (string)"N/A" );
	else
		dados.push_back( to_string<unsigned>(aviao->getVooActual()->getNumeroVoo()) );
	dados.push_back( to_string<DataHora>(aviao->getDataConstrucao()) );
	dados.push_back( to_string<DataHora>(aviao->getPrimeiroVoo()) );
	dados.push_back( to_string<DataHora>(aviao->getUltimaRevisao()) );
	dados.push_back( to_string<DataHora>(aviao->getProximaRevisao()) );


	//Dados relativos aos atributos
	col.push_back(dados);

	printMenu(str_title, col, colNames, false, false, true, true);

	getch();
}


void CRUD::editAviao(Aeroporto *aeroporto, Companhia *companhia) {
	bool continuar;
	do {
		//Selecção do avião
		Aviao* aviao = selAviaoPtr(companhia);

		//Escolha do atributo a editar
		string titulo("Atributos dos aviões: ");
		string col_name("Atributos");
		vector <string> nome_coluna;
		nome_coluna.push_back(col_name);

		vector < vector <string> > colunas;
		colunas.push_back(Comandos::_aviao_op_list);

		cout << endl << endl;
		printMenu(titulo, colunas, nome_coluna);

		cout << endl;
		size_t indice_atributo = get_uint_cin("Escolha o atributo que quer editar: ", Comandos::_aviao_op_list.size());
		cout << endl;

		string str_temp;
		unsigned uns_temp;

		//Edição do atributo escolhido
		switch (indice_atributo) {
			case 0: {
				str_temp = companhia->getMatriculaAviaoCin("Introduza a nova matrícula do avião: ");
				aviao->setMatricula(str_temp);
				break;
			}

			case 1: {
				cout << "Introduza o novo nome do avião: ";
				getlineCin(str_temp);
				aviao->setNome(str_temp);
				break;
			}

			case 2: {
				uns_temp = get_uint_cin<unsigned>("Introduza o novo peso máximo da bagagem para este avião: ");
				aviao->setPesoMaxBagagem(uns_temp);
				break;
			}

			case 3: {
				cout << "Introduza o novo tipo de avião:\n" << endl;
				TipoAviao* novo_tipo_aviao = tipo_aviao_DB.selTipoAviaoPtr();
				aviao->setTipoAviao(novo_tipo_aviao);

				if( delTipoAviaoAviao(companhia, aviao) )
					companhia->getRefFrota().push_back(aviao->getTipoAviao());

				break;
			}

			case 4: {
				bool introduzir_novamente;
				do {
					cout << "Introduza a nova companhia para este avião:\n" << endl;
					Companhia* nova_companhia = selCompanhiaPtr(aeroporto);
					try {
						//Se não lançar excepção, significa que o elemento ainda não existe no vector <Aviao*> de nova_companhia, logo é adicionado lá
						addAviao(nova_companhia, aviao);
						aviao->setCompanhia(nova_companhia);
						delAviaoPtr(companhia, aviao);
						introduzir_novamente = false;
					} catch (exception &e) {
						cout << e.what() << endl;
						introduzir_novamente = get_yes_no("Deseja selecionar outra companhia para este avião?\n(S/N): ");
					}
				} while (introduzir_novamente);
				break;
			}

			case 5: {
				bool introduzir_novamente;
				do {
					cout << "Introduza o voo que quer associar a este avião:\n" << endl;
					Voo* novo_voo = selPlanoVooPtr(companhia);
					if (novo_voo->getAviao() != NULL) {
						aviao->setVooActual(novo_voo);
						novo_voo->setAviao(aviao);
						introduzir_novamente = false;
					} else {
						cout << "O voo que tentou associar a este avião já está associado a um outro avião!" << endl << endl;
						introduzir_novamente = get_yes_no("Deseja introduzir outro voo para este avião?\n(S/N): ");
						cout << endl;
					}
				} while (introduzir_novamente);
				break;
			}

			case 6: {
				DataHora nova_data_construcao;
				nova_data_construcao.getDataHoraCin("Introduza a nova data / hora da construção do avião, no formato AAAA/MM/DD HH:mm: ");
				aviao->setDataConstrucao(nova_data_construcao);
				break;
			}

			case 7: {
				DataHora nova_data_primeiro_voo;
				nova_data_primeiro_voo.getDataHoraCin("Introduza a nova data / hora do primeiro voo deste avião, no formato AAAA/MM/DD HH:mm: ");
				aviao->setPrimeiroVoo(nova_data_primeiro_voo);
				break;
			}

			case 8: {
				DataHora nova_ultima_revisao;
				nova_ultima_revisao.getDataHoraCin("Introduza a nova data / hora da última revisão deste avião, no formato AAAA/MM/DD HH:mm: ");
				aviao->setUltimaRevisao(nova_ultima_revisao);
				break;
			}

			case 9: {
				DataHora nova_data_proxima_revisao;
				nova_data_proxima_revisao.getDataHoraCin("Introduza a nova data / hora da próxima revisão deste avião, no formato AAAA/MM/DD HH:mm: ");
				aviao->setUltimaRevisao(nova_data_proxima_revisao);
				break;
			}
		}

		//Pergunta ao utilizador se quer continuar a editar o avião
		continuar = get_yes_no("\n\nDeseja continuar a editar este avião (S/N): ");

	} while (continuar);
}


void CRUD::delAviao(Companhia *companhia) {
	try {
		size_t indice = selAviao(companhia);
		delAviao(companhia, indice);
		cout << "Removido com sucesso!" << endl;
	} catch (exception & e) {
		cout << e.what() << endl;
	}

	getch();
}


void CRUD::delAviao(Companhia *companhia, size_t indice) {
	if ((indice < 0) && (indice >= companhia->getRefAvioes().size()))
		throw ExOutOfRange();

	vector<Aviao*>::iterator it_aviao = companhia->getRefAvioes().begin() + indice;

	//Caso o avião não esteja associado a um voo, o avião é eliminado
	if ((*it_aviao)->getVooActual() == NULL) {

		vector<Aviao*>::iterator it = find( (*it_aviao)->getTipoAviao()->getRefAvioesAssociados().begin(), (*it_aviao)->getTipoAviao()->getRefAvioesAssociados().end(), (*it_aviao) );
		if( it!=(*it_aviao)->getTipoAviao()->getRefAvioesAssociados().end() )
			(*it_aviao)->getTipoAviao()->getRefAvioesAssociados().erase(it);

		delTipoAviaoAviao(companhia, (*it_aviao));

		delete *(it_aviao);
		companhia->getRefAvioes().erase(it_aviao);
	}
	else
		//Caso contrário é lançada uma excepção dizendo que esse elemento está a ser usado e não pode ser eliminado
		throw ExElementInUse <Voo>(*((*it_aviao)->getVooActual()));
}


void CRUD::delAviaoPtr(Companhia *companhia, Aviao *aviao_ptr) {
	vector<Aviao*> &vec_avioes = companhia->getRefAvioes();
	vector<Aviao*>::iterator it_aviao = vec_avioes.begin();

	//Se encontrar o apontador para o avião que vai ser removido desta companhia (foi associado a outra companhia), é removido do vector
	for (it_aviao = vec_avioes.begin(); it_aviao != vec_avioes.end(); ++it_aviao) {
		if (*(*it_aviao) == *aviao_ptr) {
			vec_avioes.erase(it_aviao);
			return;
		}
	}

	//Caso contrário é lançada uma excepção dizendo que esse elemento não existe
	throw ExElementDoesntExists <Aviao> (*aviao_ptr);
}

bool CRUD::delTipoAviaoAviao(Companhia* companhia, Aviao* aviao)
{
	vector<TipoAviao*>::iterator it = find( companhia->getRefFrota().begin(), companhia->getRefFrota().end(), aviao->getTipoAviao() );
	if( it!=companhia->getRefFrota().end() )
	{
		if( aviao->getTipoAviao()->getRefAvioesAssociados().size() > 0 )
		{
			unsigned i=0;

			for(size_t in = 0 ; in< aviao->getTipoAviao()->getRefAvioesAssociados().size() ; ++in)
			{
				if( (*aviao->getTipoAviao()->getRefAvioesAssociados()[in]->getCompanhia()) ==  (*companhia) )
					++i;
				if(i>=2)
					return false;
			}
		}

		companhia->getRefFrota().erase( it );

		return true;
	}
	return false;
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Tripulante <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void CRUD::addTripulante(Companhia *companhia) {
	cout << endl << endl;
	//Dados para a classe Pessoa
	string nome;
	string morada;
	string nacionalidade;
	unsigned contacto;
	unsigned BI;
	unsigned idade;

	//Dados do tripulante
	unsigned numero;
	string categoria;
	unsigned salario_hora;
	unsigned numero_horas_trabalho;
	string tipoContrato;
	DataHora expiracaoContrato;
	Voo *voo_actual(NULL);

	unsigned opcao = get_uint_cin<unsigned>("Pretende adicionar um Piloto (0) ou Hospedeira (1): ", 2, 0);

	cout << "Introduza o nome do tripulante: ";
	getlineCin(nome);

	cout << "Introduza a morada do tripulante: ";
	getlineCin(morada);

	cout << "Introduza a nacionalidade do tripulante: ";
	getlineCin(nacionalidade);

	contacto = get_uint_cin<unsigned>("Introduza o contacto do tripulante: ");
	BI = companhia->getBICin("Introduza o BI do tripulante: ");
	idade = get_uint_cin<unsigned>("Introduza a idade do tripulante: ");

	numero = companhia->getNumeroTripulanteCin("Introduza o número do tripulante (ID): ");

	cout << "Introduza a categoria do tripulante:\nEx: Piloto, Co-piloto, Hospedeira, Mecanico...\nCategoria: " << endl;
	getlineCin(categoria);

	salario_hora = get_uint_cin<unsigned>("Introduza o salário/hora do tripulante: ");

	numero_horas_trabalho = get_uint_cin<unsigned>("Introduza o número de horas de trabalho do tripulante: ");

	cout << "Introduza o tipo de contracto para este tripulante: ";
	getlineCin(tipoContrato);

	expiracaoContrato.getDataHoraCin("Introduza a data da expriação do contrato para este tripulante: ");

	bool sel_voo = get_yes_no("Pretende associar este tripulante a um voo?\n(S/N): ");
	if (sel_voo)
		voo_actual = selPlanoVooPtr(companhia);

	Tripulante* novo_tripulante;
	if(opcao == 0)
		novo_tripulante = new Piloto(nome, morada, nacionalidade, contacto, BI, idade, numero, categoria, salario_hora, numero_horas_trabalho, tipoContrato, expiracaoContrato, companhia, voo_actual);
	else
		novo_tripulante = new Hospedeiro(nome, morada, nacionalidade, contacto, BI, idade, numero, categoria, salario_hora, numero_horas_trabalho, tipoContrato, expiracaoContrato, companhia, voo_actual);

	companhia->getRefTripulacao().push_back(novo_tripulante);
	cout << "Adicionado com sucesso!" << endl;

	getch();
}


void CRUD::addTripulante(Companhia *companhia, Tripulante *tripulante) {
	vector <Tripulante*> &vec_tripulantes = companhia->getRefTripulacao();
	vector <Tripulante*>::const_iterator it_tripulante;

	for (it_tripulante = vec_tripulantes.begin(); it_tripulante != vec_tripulantes.end(); ++it_tripulante)
		if (*tripulante == *(*it_tripulante))
			throw ExElementAlreadyExists<Tripulante> (*tripulante);

	vec_tripulantes.push_back(tripulante);
}


bool CRUD::cmpTripulanteNome(const Tripulante *tripulante_1, const Tripulante *tripulante_2) {
	return (tripulante_1->getNome() < tripulante_2->getNome());
}

bool CRUD::cmpTripulanteNumero(const Tripulante *tripulante_1, const Tripulante *tripulante_2) {
	return (tripulante_1->getNumero() < tripulante_2->getNumero());
}

bool CRUD::cmpTripulanteCategoria(const Tripulante *tripulante_1, const Tripulante *tripulante_2) {
	return (tripulante_1->getCategoria() < tripulante_2->getCategoria());
}

bool CRUD::cmpTripulanteSalarioHora(const Tripulante *tripulante_1, const Tripulante *tripulante_2) {
	return (tripulante_1->getSalarioHora() < tripulante_2->getSalarioHora());
}

bool CRUD::cmpTripulanteNumeroHorasTrabalho(const Tripulante *tripulante_1, const Tripulante *tripulante_2) {
	return (tripulante_1->getNumeroHorasTrabalho() < tripulante_2->getNumeroHorasTrabalho());
}

bool CRUD::cmpTripulanteTipoContrato(const Tripulante *tripulante_1, const Tripulante *tripulante_2) {
	return (tripulante_1->getTipoContrato() < tripulante_2->getTipoContrato());
}

bool CRUD::cmpTripulanteExpiracaoContrato(const Tripulante *tripulante_1, const Tripulante *tripulante_2) {
	return (tripulante_1->getExpiracaoContrato() < tripulante_2->getExpiracaoContrato());
}


void CRUD::listTripulante(Companhia *companhia, bool final_pause) {
	cout << endl << endl;
	vector <Tripulante*> &vec_tripulacao = companhia->getRefTripulacao();

	if (vec_tripulacao.size() == 0) {
		throw ExEmptyVector("Não existem tripulantes na companhia!");
	}

	//Selecção do método de ordenação
	string str_title_ordenacao = "Método de ordenação";

	vector <string> colNames_ordenacao;
	colNames_ordenacao.push_back((string)"Critério de ordenação");

	vector < vector<string> > col_ordenacao;
	vector <string> parametros_ordenacao;
	parametros_ordenacao.push_back((string)"Nome");
	parametros_ordenacao.push_back((string)"Número (ID)");
	parametros_ordenacao.push_back((string)"Categoria");
	parametros_ordenacao.push_back((string)"Salário / hora");
	parametros_ordenacao.push_back((string)"Número de horas de trabalho");
	parametros_ordenacao.push_back((string)"Tipo de contrato");
	parametros_ordenacao.push_back((string)"Data de expiração do contrato");


	printMenu(str_title_ordenacao, col_ordenacao, colNames_ordenacao);

	vector <string> colNames;
	colNames.push_back((string)"Nome");


	cout << endl;

	size_t metodo = get_uint_cin("Selecione o critério de ordenação que quer usar: ", parametros_ordenacao.size());

	//Listagem ordenada para os tripulantes
	string str_title = "Lista de tripulantes";
	vector < vector<string> > col;

	col.push_back(vector<string> ());
	col.push_back(vector<string> ());

	cout << endl;

	//Ordenação do vector de acordo com o parâmetro fornecido
	switch (metodo) {
		case 0: {
			sort(vec_tripulacao.begin(), vec_tripulacao.end(), cmpTripulanteNome);
			colNames.push_back((string)"Número (ID)");
			size_t i0 = 0;
			for (vector<Tripulante*>::const_iterator it_tripulante0 = vec_tripulacao.begin(); it_tripulante0 != vec_tripulacao.end(); ++it_tripulante0) {
				col[i0++].push_back((*it_tripulante0)->getNome());
				col[i0].push_back(to_string((*it_tripulante0)->getNumero()));
				i0 = 0;
			}
			break;
		}


		case 1: {
			sort(vec_tripulacao.begin(), vec_tripulacao.end(), cmpTripulanteNumero);
			colNames.push_back((string)"Número (ID)");
			size_t i1 = 0;
			for (vector<Tripulante*>::const_iterator it_tripulante1 = vec_tripulacao.begin(); it_tripulante1 != vec_tripulacao.end(); ++it_tripulante1) {
				col[i1++].push_back((*it_tripulante1)->getNome());
				col[i1].push_back(to_string((*it_tripulante1)->getNumero()));
				i1 = 0;
			}

			break;
		}

		case 2: {
			sort(vec_tripulacao.begin(), vec_tripulacao.end(), cmpTripulanteCategoria);
			colNames.push_back((string)"Categoria");
			size_t i2 = 0;
			for (vector<Tripulante*>::const_iterator it_tripulante2 = vec_tripulacao.begin(); it_tripulante2 != vec_tripulacao.end(); ++it_tripulante2) {
				col[i2++].push_back((*it_tripulante2)->getNome());
				col[i2++].push_back((*it_tripulante2)->getCategoria());
				i2 = 0;
			}

			break;
		}

		case 3: {
			sort(vec_tripulacao.begin(), vec_tripulacao.end(), cmpTripulanteSalarioHora);
			colNames.push_back((string)"Salário / hora");
			size_t i3 = 0;
			for (vector<Tripulante*>::const_iterator it_tripulante3 = vec_tripulacao.begin(); it_tripulante3 != vec_tripulacao.end(); ++it_tripulante3) {
				col[i3++].push_back((*it_tripulante3)->getNome());
				col[i3].push_back(to_string((*it_tripulante3)->getSalarioHora()));
				i3 = 0;
			}
			break;
		}

		case 4: {
			sort(vec_tripulacao.begin(), vec_tripulacao.end(), cmpTripulanteNumeroHorasTrabalho);
			colNames.push_back((string)"Número de horas de trabalho");
			size_t i4 = 0;
			for (vector<Tripulante*>::const_iterator it_tripulante4 = vec_tripulacao.begin(); it_tripulante4 != vec_tripulacao.end(); ++it_tripulante4) {
				col[i4++].push_back((*it_tripulante4)->getNome());
				col[i4].push_back(to_string((*it_tripulante4)->getNumeroHorasTrabalho()));
				i4 = 0;
			}
			break;
		}

		case 5: {
			sort(vec_tripulacao.begin(), vec_tripulacao.end(), cmpTripulanteTipoContrato);
			colNames.push_back((string)"Tipo de contrato");
			size_t i5 = 0;
			for (vector<Tripulante*>::const_iterator it_tripulante5 = vec_tripulacao.begin(); it_tripulante5 != vec_tripulacao.end(); ++it_tripulante5) {
				col[i5++].push_back((*it_tripulante5)->getNome());
				col[i5].push_back((*it_tripulante5)->getTipoContrato());
				i5 = 0;
			}

			break;
		}

		case 6: {
			sort(vec_tripulacao.begin(), vec_tripulacao.end(), cmpTripulanteExpiracaoContrato);
			colNames.push_back((string)"Data de expiração do contrato");
			size_t i6 = 0;
			for (vector<Tripulante*>::const_iterator it_tripulante6 = vec_tripulacao.begin(); it_tripulante6 != vec_tripulacao.end(); ++it_tripulante6) {
				col[i6++].push_back((*it_tripulante6)->getNome());
				stringstream str_temp;
				str_temp << (*it_tripulante6)->getExpiracaoContrato();
				col[i6].push_back(str_temp.str());
				i6 = 0;
			}

			break;
		}
	}


	col_ordenacao.push_back(parametros_ordenacao);
	printMenu(str_title, col, colNames, true);

	if (final_pause)
		getch();
}


size_t CRUD::selTripulante(Companhia *companhia) {
	listTripulante(companhia);
	cout << endl << endl;
	size_t indice = get_uint_cin<size_t>("\nIntroduza o índice do tripulante para mais informações (0 para retroceder): ", companhia->getConstRefTripulacao().size(), 0, true);
	tripulante_actual = companhia->getConstRefTripulacao()[indice];
	return indice;
}


Tripulante* CRUD::selTripulantePtr(Companhia *companhia) {
	return companhia->getConstRefTripulacao()[ selTripulante(companhia) ];
}


void CRUD::infoTripulante(Companhia *companhia) {
	size_t indice = selTripulante(companhia);

	Tripulante *tripulante = companhia->getConstRefTripulacao()[indice];

	//Uso do polimorfismo para imprimir mensagens diferentes.
	tripulante->imprimeInfo();
	getch();

}


void CRUD::editTripulante(Aeroporto *aeroporto, Companhia *companhia) {
	bool continuar;
	do {
		cout << endl << endl;
		//Selecção do tripulante
		Tripulante* tripulante = selTripulantePtr(companhia);

		//Escolha do atributo a editar
		string titulo("Atributos dos tripulantes: ");
		string col_name("Atributos");
		vector <string> nome_coluna;
		nome_coluna.push_back(col_name);

		vector < vector <string> > colunas;
		colunas.push_back(Comandos::_tripulante_op_list);

		cout << endl << endl;
		printMenu(titulo, colunas, nome_coluna);

		cout << endl << endl;
		size_t indice_atributo = get_uint_cin("Escolha o atributo que quer editar: ", Comandos::_tripulante_op_list.size());
		cout << endl << endl;

		string str_temp;
		unsigned uns_temp;

		//Edição do atributo escolhido
		switch (indice_atributo) {
			case 0: {
				cout << "Introduza o novo nome para o tripulante: ";
				getlineCin(str_temp);
				tripulante->setNome(str_temp);
				break;
			}

			case 1: {
				cout << "Introduza a nova morada para o tripulante: ";
				getlineCin(str_temp);
				tripulante->setMorada(str_temp);
				break;
			}

			case 2: {
				cout << "Introduza a nova nacionalidade para o tripulante: ";
				getlineCin(str_temp);
				tripulante->setNacionalidade(str_temp);
				break;
			}

			case 3: {
				uns_temp = get_uint_cin<unsigned>("Introduza o novo número de contacto para o tripulante: ");
				tripulante->setContacto(uns_temp);
				break;
			}

			case 4: {
				uns_temp = get_uint_cin<unsigned>("Introduza o novo BI para o tripulante: ");
				tripulante->setBI(uns_temp);
				break;
			}

			case 5: {
				uns_temp = get_uint_cin<unsigned>("Introduza a nova idade para o tripulante: ");
				tripulante->setIdade(uns_temp);
				break;
			}

			case 6: {
				uns_temp = companhia->getNumeroTripulanteCin("Introduza o novo número, (ID), para o tripulante: ");
				tripulante->setNumero(uns_temp);
				break;
			}

			case 7: {
				cout << "Introduza a nova categoria do tripulante:\nEx: Piloto, Co-piloto, Hospedeira, Mecanico...\nCategoria: " << endl;
				getlineCin(str_temp);
				tripulante->setCategoria(str_temp);
				break;
			}

			case 8: {
				uns_temp = get_uint_cin<unsigned>("Introduza o novo salário/hora para o tripulante: ");
				tripulante->setSalarioHora(uns_temp);
				break;
			}

			case 9: {
				uns_temp = get_uint_cin<unsigned>("Introduza o novo número de horas de trabalho do tripulante: ");
				tripulante->setNumeroHorasTrabalho(uns_temp);
				break;
			}

			case 10: {
				cout << "Introduza o novo tipo de contrato para o tripulante: " << endl;
				getlineCin(str_temp);
				tripulante->setTipoContrato(str_temp);
				break;
			}

			case 11: {
				DataHora nova_data_expiracao_contrato;
				nova_data_expiracao_contrato.getDataHoraCin("Introduza a nova data/hora da expiração do contrato do tripulante\n, no formato AAAA/MM/DD HH:mm: ");
				tripulante->setExpiracaoContrato(nova_data_expiracao_contrato);
				break;
			}

			case 12: {
				cout << "Introduza a nova companhia para este tripulante:\n" << endl;
				Companhia* nova_companhia = selCompanhiaPtr(aeroporto);
				try {
					//Se não lançar excepção, significa que o elemento ainda não existe no vector <Tripulante*> da nova_companhia, logo é adicionado lá
					addTripulante(nova_companhia, tripulante);
					tripulante->setCompanhia(nova_companhia);
					delTripulantePtr(companhia, tripulante);
				} catch (exception &e) {
					cout << e.what() << endl;
				}
				break;
			}

			case 13: {
				cout << "Introduza o voo que quer associar a este tripulante:\n" << endl;
				Voo* novo_voo = selPlanoVooPtr(companhia);
				if (tripulante->getVooActual() != NULL) {
					tripulante->setVooActual(novo_voo);
					novo_voo->getRefTripulantesVoo().push_back(tripulante);
				} else {
					cout << "O tripulante ainda está associado a outro voo!" << endl;
					cout << "Só pode mudar o voo de um tripulante se ele não estiver associado a nenhum voo no momento da edição!" << endl << endl;
					cout << endl;
				}
				break;
			}
		}

		//Pergunta ao utilizador se quer continuar a editar o avião
		continuar = get_yes_no("\n\nDeseja continuar a editar este tripulante (S/N): ");

	} while (continuar);
}


void CRUD::delTripulante(Companhia *companhia) {
	try {
		size_t indice = selTripulante(companhia);
		delTripulante(companhia, indice);

		cout << endl << endl;
		cout << "Removido com sucesso!" << endl;
	} catch (exception & e) {
		cout << e.what() << endl;
	}

	getch();
}


void CRUD::delTripulante(Companhia *companhia, size_t indice) {
	vector <Tripulante*> &vec_tripulacao = companhia->getRefTripulacao();
	if ((indice < 0) && (indice >= vec_tripulacao.size()))
		throw ExOutOfRange();

	vector <Tripulante*>::iterator it_tripulante = vec_tripulacao.begin();
	const Voo* voo_actual_tripulante = vec_tripulacao[indice]->getVooActual();

	if (voo_actual_tripulante == NULL) {
		delete *(it_tripulante + indice);
		vec_tripulacao.erase(it_tripulante + indice);
	}
	else {
		throw ExElementInUse <Voo> (*voo_actual_tripulante);
	}
}


void CRUD::delTripulantePtr(Companhia *companhia, Tripulante *tripulante_ptr) {
	vector <Tripulante*> &vec_tripulacao = companhia->getRefTripulacao();
	vector <Tripulante*>::iterator it_tripulante = vec_tripulacao.begin();

	//Se encontrar o apontador para o tripulante que vai ser removido desta companhia (foi associado a outra companhia), é removido do vector
	for ( ; it_tripulante != vec_tripulacao.end(); ++it_tripulante) {
		if (*it_tripulante == tripulante_ptr) {
			vec_tripulacao.erase(it_tripulante);
			return;
		}
	}

	//Caso contrário é lançada uma excepção dizendo que esse elemento não existe
	throw ExElementDoesntExists <Tripulante> (*tripulante_ptr);
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Plano voo <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void CRUD::addPlanoVoo(Aeroporto *aeroporto, Companhia *companhia) {
	cout << endl << endl;
	unsigned numero_voo;
	string origem;
	string destino;
	string matricula_aviao;
	DataHora datahora_saida;
	DataHora datahora_chegada;
	unsigned numero_passageiros;
	PortaEmbarque *porta_embarque;
	Aviao *aviao_ptr;

	numero_voo = companhia->getNumeroVooCin("Introduza o número de voo: ");

	cout << "Introduza a origem do voo:" << endl;
	getlineCin(origem);

	cout << "Introduza o destino do voo:" << endl;
	getlineCin(destino);

	datahora_saida.getDataHoraCin("Introduza a data/hroa de saída do voo no formato AAAA/MM/DD HH:mm: ");
	datahora_chegada.getDataHoraCin("Introduz a data/hora de chegada do voo no formato AAAA/MM/DD HH:mm: ");

	numero_passageiros = get_uint_cin<unsigned>("Introduza o número de passageiros do voo: ");

	aviao_ptr = selAviaoPtr(companhia);

	porta_embarque = updatePortaEmbarqueDisp(aeroporto, numero_passageiros, aviao_ptr->getTipoAviao()->getCategoria());



	Voo* novo_voo = new Voo(numero_voo, origem, destino, datahora_saida, datahora_chegada, numero_passageiros,
			porta_embarque, aviao_ptr, companhia_actual, 0, false);

	porta_embarque->getRefVoosPortaEmbarque().push_back( novo_voo );

	companhia->getRefVoos().push_back(novo_voo);
	cout << endl << endl;
	cout << "Adicionado com sucesso!" << endl;

	getch();
}


bool CRUD::addPlanoVoo(Companhia *companhia, Voo* voo) {
	vector <Voo*> &vec_voos = companhia->getRefVoos();
	vector <Voo*>::const_iterator it_voos;

	for (it_voos = vec_voos.begin(); it_voos != vec_voos.end(); ++it_voos)
		if ((*voo) == *(*it_voos))
			throw ExElementAlreadyExists<Voo> (*voo);

	vec_voos.push_back(voo);
	return true;
}


bool CRUD::cmpVooNumeroVoo(const Voo *voo1, const Voo *voo2) {
	return (voo1->getNumeroVoo() < voo2->getNumeroVoo());
}

bool CRUD::cmpVooOrigem(const Voo *voo1, const Voo *voo2) {
	return (voo1->getOrigem() < voo2->getOrigem());
}

bool CRUD::cmpVooDestino(const Voo *voo1, const Voo *voo2) {
	return (voo1->getDestino() < voo2->getDestino());
}

bool CRUD::cmpVooDataSaida(const Voo *voo1, const Voo *voo2) {
	return (voo1->getDatahoraSaida() < voo2->getDatahoraSaida());
}

bool CRUD::cmpVooDataChegada(const Voo *voo1, const Voo *voo2) {
	return (voo1->getDatahoraChegada() < voo2->getDatahoraChegada());
}

bool CRUD::cmpVooAtraso(const Voo *voo1, const Voo *voo2) {
	return (voo1->getAtraso() < voo2->getAtraso());
}

bool CRUD::cmpVooCancelado(const Voo *voo1, const Voo *voo2) {
	return voo1->getCancelado();
}


void CRUD::listPlanoVoo(Companhia *companhia, bool final_pause) {
	cout << endl << endl;
	vector <Voo*> &vec_planos_voo = companhia->getRefVoos();

	if (vec_planos_voo.size() == 0) {
		throw ExEmptyVector("Não existem voos na companhia!");
	}

	//Selecção do método de ordenação
	string str_title_ordenacao = "Método de ordenação";

	vector <string> colNames_ordenacao;
	colNames_ordenacao.push_back((string)"Critério de ordenação");

	vector < vector<string> > col_ordenacao;
	vector <string> parametros_ordenacao;
	parametros_ordenacao.push_back((string)"Número voo");
	parametros_ordenacao.push_back((string)"Origem do voo");
	parametros_ordenacao.push_back((string)"Destino do voo");
	parametros_ordenacao.push_back((string)"Data/hora saída do voo");
	parametros_ordenacao.push_back((string)"Data/hora cheagada do voo");
	parametros_ordenacao.push_back((string)"Atraso do voo");
	parametros_ordenacao.push_back((string)"Cancelado");
	col_ordenacao.push_back(parametros_ordenacao);

	printMenu(str_title_ordenacao, col_ordenacao, colNames_ordenacao);

	vector <string> colNames;

	cout << endl << endl;

	size_t metodo = get_uint_cin<unsigned>("Selecione o critério de ordenação que quer usar: ", parametros_ordenacao.size());

	//Listagem ordenada para os tripulantes
	string str_title = "Lista de planos de voo";
	vector < vector<string> > col;

	col.push_back(vector<string> ());
	col.push_back(vector<string> ());
	col.push_back(vector<string> ());

	cout << endl;

	//Ordenação do vector de acordo com o parâmetro fornecido
	switch (metodo) {
		case 0: {
			sort(vec_planos_voo.begin(), vec_planos_voo.end(), cmpVooNumeroVoo);
			colNames.push_back((string)"Número voo");
			colNames.push_back((string)"Origem do voo");
			colNames.push_back((string)"Destino do voo");
			size_t i0 = 0;
			for (vector<Voo*>::const_iterator it_voo0 = vec_planos_voo.begin(); it_voo0 != vec_planos_voo.end(); ++it_voo0) {
				col[i0++].push_back(to_string((*it_voo0)->getNumeroVoo()));
				col[i0++].push_back((*it_voo0)->getOrigem());
				col[i0].push_back((*it_voo0)->getDestino());
				i0 = 0;
			}
			break;
		}

		case 1: {
			sort(vec_planos_voo.begin(), vec_planos_voo.end(), cmpVooOrigem);
			colNames.push_back((string)"Origem do voo");
			colNames.push_back((string)"Número voo");
			colNames.push_back((string)"Destino do voo");
			size_t i1 = 0;
			for (vector<Voo*>::const_iterator it_voo1 = vec_planos_voo.begin(); it_voo1 != vec_planos_voo.end(); ++it_voo1) {
				col[i1++].push_back((*it_voo1)->getOrigem());
				col[i1++].push_back(to_string((*it_voo1)->getNumeroVoo()));
				col[i1].push_back((*it_voo1)->getDestino());
				i1 = 0;
			}
			break;
		}

		case 2: {
			sort(vec_planos_voo.begin(), vec_planos_voo.end(), cmpVooDestino);
			colNames.push_back((string)"Destino do voo");
			colNames.push_back((string)"Número voo");
			colNames.push_back((string)"Origem do voo");
			size_t i2 = 0;
			for (vector<Voo*>::const_iterator it_voo2 = vec_planos_voo.begin(); it_voo2 != vec_planos_voo.end(); ++it_voo2) {
				col[i2++].push_back((*it_voo2)->getDestino());
				col[i2++].push_back(to_string((*it_voo2)->getNumeroVoo()));
				col[i2].push_back((*it_voo2)->getOrigem());
				i2 = 0;
			}
			break;
		}

		case 3: {
			sort(vec_planos_voo.begin(), vec_planos_voo.end(), cmpVooDataSaida);
			colNames.push_back((string)"Data/hora saída do voo");
			colNames.push_back((string)"Número voo");
			colNames.push_back((string)"Destino do voo");
			size_t i3 = 0;
			for (vector<Voo*>::const_iterator it_voo3 = vec_planos_voo.begin(); it_voo3 != vec_planos_voo.end(); ++it_voo3) {
				col[i3++].push_back(to_string((*it_voo3)->getDatahoraSaida()));
				col[i3++].push_back(to_string((*it_voo3)->getNumeroVoo()));
				col[i3].push_back((*it_voo3)->getDestino());
				i3 = 0;
			}
			break;
		}

		case 4: {
			sort(vec_planos_voo.begin(), vec_planos_voo.end(), cmpVooDataChegada);
			colNames.push_back((string)"Data/hora cheagada do voo");
			colNames.push_back((string)"Número voo");
			colNames.push_back((string)"Destino do voo");
			size_t i4 = 0;
			for (vector<Voo*>::const_iterator it_voo4 = vec_planos_voo.begin(); it_voo4 != vec_planos_voo.end(); ++it_voo4) {
				col[i4++].push_back(to_string((*it_voo4)->getDatahoraChegada()));
				col[i4++].push_back(to_string((*it_voo4)->getNumeroVoo()));
				col[i4].push_back((*it_voo4)->getDestino());
				i4 = 0;
			}
			break;
		}

		case 5: {
			sort(vec_planos_voo.begin(), vec_planos_voo.end(), cmpVooAtraso);
			colNames.push_back((string)"Atraso do voo");
			colNames.push_back((string)"Número voo");
			colNames.push_back((string)"Destino do voo");
			size_t i5 = 0;
			for (vector<Voo*>::const_iterator it_voo5 = vec_planos_voo.begin(); it_voo5 != vec_planos_voo.end(); ++it_voo5) {
				col[i5++].push_back(to_string((*it_voo5)->getAtraso()));
				col[i5++].push_back(to_string((*it_voo5)->getNumeroVoo()));
				col[i5].push_back((*it_voo5)->getDestino());
				i5 = 0;
			}
			break;
		}

		case 6: {
			sort(vec_planos_voo.begin(), vec_planos_voo.end(), cmpVooCancelado);
			colNames.push_back((string)"Cancelado");
			colNames.push_back((string)"Número voo");
			colNames.push_back((string)"Destino do voo");
			size_t i6 = 0;
			for (vector<Voo*>::const_iterator it_voo6 = vec_planos_voo.begin(); it_voo6 != vec_planos_voo.end(); ++it_voo6) {
				if ((*it_voo6)->getCancelado())
					col[i6++].push_back((string)"Cancelado");
				else
					col[i6++].push_back((string)"Não cancelado");
				col[i6++].push_back(to_string((*it_voo6)->getNumeroVoo()));
				col[i6].push_back((*it_voo6)->getDestino());
				i6 = 0;
			}
			break;
		}
	}

	cout << endl << endl;
	printMenu(str_title, col, colNames, true);

	if (final_pause)
		getch();
}


size_t CRUD::selPlanoVoo(Companhia* companhia) {
	listPlanoVoo(companhia);
	size_t indice = get_uint_cin<size_t>("\nIntroduza o índice (0 para retroceder):", companhia->getConstRefVoos().size(), 0, true);
	voo_actual = (companhia->getConstRefVoos()[indice]);
	return indice;
}


Voo* CRUD::selPlanoVooPtr(Companhia* companhia) {
	return companhia->getConstRefVoos()[ selPlanoVoo(companhia) ];
}


void CRUD::infoPlanoVoo(Companhia *companhia, Voo *voo) {
	cout << endl << endl;
	if (voo == NULL)
		voo = selPlanoVooPtr(companhia);

	string str_title = "Informações sobre o plano de voos";

	vector <string> colNames;					// nomes de colunas não são usados, logo vão strings vazias
	colNames.push_back(string(""));
	colNames.push_back(string(""));

	vector < vector<string> > col;
	vector <string> dados;

	//Nomes dos atributos
	col.push_back(Comandos::_voo_op_list);

	dados.push_back( to_string<unsigned>(voo->getNumeroVoo()) );
	dados.push_back( voo->getOrigem() );
	dados.push_back( voo->getDestino() );
	dados.push_back( to_string<DataHora>(voo->getDatahoraSaida()) );
	dados.push_back( to_string<DataHora>(voo->getDatahoraChegada()) );
	dados.push_back( to_string<unsigned>(voo->getNumeroPassageiros()) );
	dados.push_back( voo->getPortaEmbarque()->getNumero() );
	dados.push_back( voo->getAviao()->getNome() );
	dados.push_back( voo->getCompanhia()->getNome() );
	dados.push_back( to_string<unsigned>(voo->getAtraso()) );

	string cancelado;
	if (voo->getCancelado())
		cancelado = "Cancelado";
	else
		cancelado = "Não cancelado";

	dados.push_back( cancelado );

	//Dados relativos aos atributos
	col.push_back(dados);

	printMenu(str_title, col, colNames, false, false, true, true);

	getch();

}


void CRUD::editPlanoVoo(Aeroporto *aeroporto, Companhia *companhia) {
	bool continuar;
	do {
		cout << endl << endl;
		//Selecção do voo
		Voo* voo = selPlanoVooPtr(companhia);

		//Escolha do atributo a editar
		string titulo("Atributos dos planos de voo: ");
		string col_name("Atributos");
		vector <string> nome_coluna;
		nome_coluna.push_back(col_name);

		vector < vector <string> > colunas;
		colunas.push_back(Comandos::_voo_op_list);

		cout << endl << endl;
		printMenu(titulo, colunas, nome_coluna);

		cout << endl << endl;
		size_t indice_atributo = get_uint_cin("Escolha o atributo que quer editar: ", Comandos::_voo_op_list.size());
		cout << endl << endl;

		string str_temp;
		unsigned uns_temp;

		//Edição do atributo escolhido
		switch (indice_atributo) {
			case 0: {
				uns_temp = companhia->getNumeroVooCin("Introduza o novo número para o voo: ");
				voo->setNumero_voo(uns_temp);
				break;
			}

			case 1: {
				cout << "Introduza a nova origem do voo: ";
				getlineCin(str_temp);
				voo->setOrigem(str_temp);
				break;
			}

			case 2: {
				cout << "Introduza o novo destino do voo: ";
				getlineCin(str_temp);
				voo->setDestino(str_temp);
				break;
			}

			case 3: {
				DataHora data_temp;
				data_temp.getDataHoraCin("Introduza a nova data/hora de saída do voo no formato AAAA/MM/DD HH:mm: ");
				str_temp = to_string(data_temp);
				voo->setDatahoraSaida(data_temp);
				break;
			}

			case 4: {
				DataHora data_temp;
				data_temp.getDataHoraCin("Introduza a nova data/hora de chegada do voo no formato AAAA/MM/DD HH:mm: ");
				str_temp = to_string(data_temp);
				voo->setDatahoraChegada(data_temp);
				break;
			}

			case 5: {
				unsigned numero_passsageiros_voo = voo->getNumeroPassageiros();
				unsigned capacidade_aviao = voo->getAviao()->getTipoAviao()->getMaximoPassageiros();
				stringstream error_message;
				error_message << "O novo número de passageiros do voo tem que ser maior do que o número actual (" << numero_passsageiros_voo;
				error_message << ") e menor do que a capacidade do avião do voo (" << capacidade_aviao << "): ";
				uns_temp = get_uint_cin<unsigned>("Introduza o novo número de passageiros para o voo: ", capacidade_aviao + 1, numero_passsageiros_voo, false, error_message.str().c_str());
				voo->setNumeroPassageiros(uns_temp);

				//Se o número de passageiros do voo foi alterado é verificada a validade da porta de embarque actual
				//Caso a porta de embarque não tenha vagas suficientes, é atribuida outra porta de embarque ao voo
				unsigned vagas_necessarias = uns_temp - numero_passsageiros_voo;
				if ((uns_temp != numero_passsageiros_voo) && (vagas_necessarias > voo->getPortaEmbarque()->getVagasPass())) {
					PortaEmbarque *porta_embarque_actual = voo->getPortaEmbarque();
					porta_embarque_actual->setVagasPass(porta_embarque_actual->getVagasPass() + vagas_necessarias);
					aeroporto->getRefPortasEmbarqueBST().insert(porta_embarque_actual);

					PortaEmbarque *nova_porta_embarque = updatePortaEmbarqueDisp(aeroporto, voo->getNumeroPassageiros(), voo->getAviao()->getTipoAviao()->getCategoria());
					voo->setPortaEmbarque(nova_porta_embarque);
				}
				break;
			}

			case 6: {
				bool continuar = true;
				do {
					cout << "Selecione a nova porta de embarque para este voo: " << endl;
					PortaEmbarquePtr porta_embarque_actual(voo->getPortaEmbarque());
					//Remoção da porta da BST
					aeroporto->getRefPortasEmbarqueBST().remove(porta_embarque_actual);
					//Actualização das vagas da porta removida
					porta_embarque_actual()->setVagasPass(porta_embarque_actual()->getVagasPass() + voo->getNumeroPassageiros());
					//Reinserção da porta com as vagas actualizadas
					aeroporto->getRefPortasEmbarqueBST().insert(porta_embarque_actual);

					//Selecção da nova porta de embarque
					PortaEmbarque *porta_embarque_nova = selPortaEmbarquePtr(aeroporto);

					//Caso a nova porta tenha vagas suficientes, associa-se o voo a essa porta
					if (voo->getNumeroPassageiros() <= porta_embarque_nova->getVagasPass()) {
						//Remove-se a porta
						aeroporto->getRefPortasEmbarqueBST().remove(porta_embarque_nova);
						//Actualiza-se o nº de vagas
						porta_embarque_nova->setVagasPass(porta_embarque_nova->getVagasPass() - voo->getNumeroPassageiros());
						//Reinserção da porta com as vagas actualizadas
						aeroporto->getRefPortasEmbarqueBST().insert(porta_embarque_nova);

						//Associação da porta ao voo
						voo->setPortaEmbarque(porta_embarque_nova);

						cout << "\nPorta de embarque associada com sucesso ao voo!\n" << endl;
					}
					else {
						//Reassociaão automática do voo a uma porta de embarque disponível
						porta_embarque_nova = updatePortaEmbarqueDisp(aeroporto, voo->getNumeroPassageiros(), voo->getAviao()->getTipoAviao()->getCategoria());
						voo->setPortaEmbarque(porta_embarque_nova);

						continuar = get_yes_no("Deseja selecionar novamente uma nova porta para este voo? (S/N): ", "Introduza S ou N: ");

						cout << "\nA porta selecionada não tem vagas suficientes para acomodar este voo!\n" << endl;
					}
				} while (continuar);

				break;
			}

			case 7: {
				cout << "Selecione o novo avião para este voo: " << endl;
				Aviao *aviao = selAviaoPtr(companhia);
				voo->setAviao(aviao);
				break;
			}

			case 8: {
				uns_temp = get_uint_cin<unsigned>("Introduza o novo atraso para o avião: ");
				voo->setAtraso(uns_temp);
				break;
			}

			case 9: {
				bool cancelado = get_yes_no("Introduza S para cancelar este voo e N para não cancelar:\n(S/N): ");
				voo->setCanselado(cancelado);
				break;
			}
		}

		//Pergunta ao utilizador se quer continuar a editar o avião
		continuar = get_yes_no("\n\nDeseja continuar a editar este voo (S/N): ");

	} while (continuar);
}


void CRUD::delPlanoVoo(Aeroporto *aeroporto, Companhia *companhia) {
	try {
		size_t indice = selPlanoVoo(companhia);
		delPlanoVoo(aeroporto, companhia, indice);
		cout << endl << endl;
		cout << "Removido com sucesso!" << endl;
	} catch (exception & e) {
		cout << e.what() << endl;
	}

	getch();
}

void CRUD::delPlanoVoo(Aeroporto *aeroporto, Companhia* companhia, size_t indice) {
	if ((indice < 0) && (indice >= companhia->getRefVoos().size()))
		throw ExOutOfRange();

	Voo *voo = companhia->getRefVoos()[indice];

	//Remoção do voo da porta de embarque que a ele está associada
	delVooPtrPortaEmbarque(voo->getPortaEmbarque(), voo);

	//Eliminação do objecto
	vector<Voo*>::iterator it_voo = companhia->getRefVoos().begin();

	if( !voo->getFechado() )
		(*(it_voo + indice))->getPortaEmbarque()->setVagasPass((*(it_voo + indice))->getPortaEmbarque()->getVagasPass() + (*(it_voo + indice))->getNumeroPassageiros());

	//Actualização do avião
	voo->getAviao()->setVooActual(NULL);

	//Actualização dos tripulantes
	vector <Tripulante*> vec_tripulantes_voo = voo->getRefTripulantesVoo();

	for (size_t i = 0; i < vec_tripulantes_voo.size(); ++i) {
		vec_tripulantes_voo[i]->setVooActual(NULL);
	}

	//Actualização dos passageiros
	vector <Passageiro*> &vec_passageiros_voo = voo->getRefPassageirosVoo();
	Passageiro *passageiro(NULL);

	for (size_t i = 0; i < vec_passageiros_voo.size(); ++i) {
		passageiro = vec_passageiros_voo[i];
		delPassageiroPtr(aeroporto, passageiro);
		delete passageiro;
		}

	//delete (*(it_voo + indice));
	Voo* vv = *(it_voo + indice);

	//Actualização do vector de voos da companhia e da hash_table, caso seja necessário
	delPlanoVooPtr(aeroporto, companhia, voo);

	delete vv;
}


void CRUD::delPlanoVooPtr(Aeroporto *aeroporto, Companhia *companhia, Voo *voo_ptr) {
	vector <Voo*> &vec_voos = companhia->getRefVoos();
	vector <Voo*>::iterator it_voo = vec_voos.begin();

	//Se encontrar o apontador para o voo que vai ser removido desta companhia, é removido do vector
	for ( ; it_voo != vec_voos.end(); ++it_voo) {
		if (*it_voo == voo_ptr) {
			vec_voos.erase(it_voo);

			//Actualização da hash_table dos voos vazios
			aeroporto->delVooHashSetVoos(voo_ptr);

			return;
		}
	}

	//Caso contrário é lançada uma excepção dizendo que esse elemento não existe
	throw ExElementDoesntExists <Voo> (*voo_ptr);
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Aeroporto <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void CRUD::addAeroporto(Aeroporto *aeroporto) {
	cout << endl << endl;
	string nome;
	string localizacao;
	string pais;
	unsigned taxa_portas_embarque;

	cout << "Introduza o nome para o aeroporto: ";
	getlineCin(nome);

	cout << "Introduza a localização do aeroporto: ";
	getlineCin(localizacao);

	cout << "Introduza o país do aeroporto: ";
	getlineCin(pais);

	taxa_portas_embarque = get_uint_cin<unsigned>("Introduza a taxa de utilização das portas de embarque para este aeroporto: ");

	aeroporto->setNome(nome);
	aeroporto->setLocalizacao(localizacao);
	aeroporto->setPais(pais);
	aeroporto->setTaxaPortasEmbarque(taxa_portas_embarque);
}


void CRUD::editAeroporto(Aeroporto *aeroporto) {
	bool continuar;
	do {
		cout << endl << endl;
		//Escolha do atributo a editar
		string titulo("Atributos do aeroporto: ");
		string col_name("Atributos");
		vector <string> nome_coluna;
		nome_coluna.push_back(col_name);

		vector < vector <string> > colunas;
		colunas.push_back(Comandos::_aeroporto_op_list);

		cout << endl << endl;
		printMenu(titulo, colunas, nome_coluna);

		cout << endl << endl;
		size_t indice_atributo = get_uint_cin("Escolha o atributo que quer editar: ", Comandos::_aeroporto_op_list.size());
		cout << endl << endl;

		string str_temp;

		//Edição do atributo escolhido
		switch (indice_atributo) {
			case 0: {
				cout << "Introduza o novo nome para o aeroporto: ";
				getlineCin(str_temp);
				aeroporto->setNome(str_temp);
				break;
			}

			case 1: {
				cout << "Introduza a nova localização para o aeroporto: ";
				getlineCin(str_temp);
				aeroporto->setLocalizacao(str_temp);
				break;
			}

			case 2: {
				cout << "Introduza o novo país para o aeroporto: ";
				getlineCin(str_temp);
				aeroporto->setPais(str_temp);
				break;
			}

			case 3: {
				unsigned taxa_portas_embarque = get_uint_cin<unsigned>("Introduza a nova taxa de utilização das portas de embarque para este aeroporto: ");
				aeroporto->setTaxaPortasEmbarque(taxa_portas_embarque);
			}

		}

		//Pergunta ao utilizador se quer continuar a editar o avião
		continuar = get_yes_no("\n\nDeseja continuar a editar este aeroporto (S/N): ");

	} while (continuar);
}


void CRUD::infoAeroporto(Aeroporto *aeroporto) {
	string str_title = "Informações sobre o aeroporto";

	vector <string> colNames;					// nomes de colunas não são usados, logo vão strings vazias
	colNames.push_back(string(""));
	colNames.push_back(string(""));

	vector < vector<string> > col;
	vector <string> dados;

	//Nomes dos atributos
	col.push_back(Comandos::_aeroporto_op_list);

	//dados referentes à superclasse Pessoa
	dados.push_back( aeroporto->getNome() );
	dados.push_back( aeroporto->getLocalizacao() );
	dados.push_back( aeroporto->getPais() );
	dados.push_back( to_string(aeroporto->getTaxaPortasEmbarque()) );

	//Dados relativos aos atributos
	col.push_back(dados);

	cout << endl << endl;
	printMenu(str_title, col, colNames, false, false, true, true);

	getch();
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Companhia <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void CRUD::addCompanhia(Aeroporto *aeroporto) {
	bool continuar;
	do {
		cout << endl << endl;
		string sigla;		//Ex: TAP
		string nome;		//Ex: TAP Portugal
		unsigned taxa_balcoes;

		cout << "Introduza a sigla: " << flush;

		getlineCin(sigla);

		cout << "Introduza o nome: " << flush;
		getlineCin(nome);

		taxa_balcoes = get_uint_cin<unsigned>("Introduza taxa de utilização dos balcões de check-in desta companhia: ");

		cout << endl;

		Companhia* nova_companhia = new Companhia(sigla, nome, taxa_balcoes);

		try {
			addCompanhia(aeroporto, nova_companhia);
			cout << "Adicionado com sucesso!" << endl << endl;
			continuar = false;
			getch();
		} catch (exception &e) {
			delete nova_companhia;
			cout << e.what() << endl;
			continuar = get_yes_no("Deseja adicionar novamente uma companhia?\n(S/N): ");
		}

	} while (continuar);
}


void CRUD::addCompanhia(Aeroporto *aeroporto, Companhia *companhia) {
	vector <Companhia*> &vec_companhias = aeroporto->getRefCompanhias();
	vector <Companhia*>::const_iterator it_companhia;

	for (it_companhia = vec_companhias.begin(); it_companhia != vec_companhias.end(); ++it_companhia)
		if ((*companhia) == *(*it_companhia))
			throw ExElementAlreadyExists <Companhia> (*companhia);

	vec_companhias.push_back(companhia);
}


bool CRUD::cmpCompanhiaSigla(const Companhia *c1, const Companhia *c2) {
	return (c1->getSigla() < c2->getSigla());
}

bool CRUD::cmpCompanhiaNome(const Companhia *c1, const Companhia *c2) {
	return (c1->getNome() < c2->getNome());
}

bool CRUD::cmpCompanhiaTaxa(const Companhia *c1, const Companhia *c2) {
	return (c1->getTaxaBalcoes() < c2->getTaxaBalcoes());
}


void CRUD::listCompanhia(Aeroporto *aeroporto, bool final_pause) {
	cout << endl << endl;
	vector <Companhia*> &vec_companhias = aeroporto->getRefCompanhias();

	if (vec_companhias.size() == 0) {
		throw ExEmptyVector("Não existem companhias no aeroporto!");
	}

	//Selecção do método de ordenação
	string str_title_ordenacao = "Método de ordenação";

	vector <string> colNames_ordenacao;
	colNames_ordenacao.push_back(string("Critério de ordenação"));

	vector < vector<string> > col_ordenacao;
	vector <string> parametros_ordenacao;
	parametros_ordenacao.push_back((string)"Sigla");
	parametros_ordenacao.push_back((string)"Nome");
	parametros_ordenacao.push_back((string)"Taxa de utilização dos balcões de check-in");
	col_ordenacao.push_back(parametros_ordenacao);


	cout << endl << endl;
	printMenu(str_title_ordenacao, col_ordenacao, colNames_ordenacao);
	cout << endl << endl;

	size_t metodo = get_uint_cin("Selecione o critério de ordenação que quer usar: ", parametros_ordenacao.size());

	//Listagem ordenada das companhias
	string str_title = "Lista de companhias";
	vector < vector<string> > col;
	vector <string> colNames;


	col.push_back(vector<string> ());
	col.push_back(vector<string> ());
	col.push_back(vector<string> ());

	//Ordenação do vector de acordo com o parâmetro fornecido
	switch (metodo) {
		case 0: {
			sort(vec_companhias.begin(), vec_companhias.end(), cmpCompanhiaSigla);
			colNames.push_back((string)"Sigla");
			colNames.push_back((string)"Nome");
			colNames.push_back((string)"Taxa de utilização dos balcões de check-in");

			size_t i = 0;
			for (vector <Companhia*>::const_iterator it = vec_companhias.begin(); it != vec_companhias.end(); ++it) {
				col[i++].push_back((*it)->getSigla());
				col[i++].push_back((*it)->getNome());
				col[i].push_back(to_string((*it)->getTaxaBalcoes()));
				i = 0;
			}

			break;
		}

		case 1: {
			sort(vec_companhias.begin(), vec_companhias.end(), cmpCompanhiaNome);
			colNames.push_back((string)"Nome");
			colNames.push_back((string)"Sigla");
			colNames.push_back((string)"Taxa de utilização dos balcões de check-in");

			size_t i1 = 0;
			for (vector <Companhia*>::const_iterator it1 = vec_companhias.begin(); it1 != vec_companhias.end(); ++it1) {
				col[i1++].push_back((*it1)->getNome());
				col[i1++].push_back((*it1)->getSigla());
				col[i1].push_back(to_string((*it1)->getTaxaBalcoes()));

				i1 = 0;
			}

			break;
		}

		case 2: {
			sort(vec_companhias.begin(), vec_companhias.end(), cmpCompanhiaTaxa);
			colNames.push_back((string)"Taxa de utilização dos balcões de check-in");
			colNames.push_back((string)"Nome");
			colNames.push_back((string)"Sigla");

			size_t i1 = 0;
			for (vector <Companhia*>::const_iterator it1 = vec_companhias.begin(); it1 != vec_companhias.end(); ++it1) {
				col[i1++].push_back(to_string((*it1)->getTaxaBalcoes()));
				col[i1++].push_back((*it1)->getNome());
				col[i1].push_back((*it1)->getSigla());

				i1 = 0;
			}

			break;
		}
	}

	cout << endl << endl;
	printMenu(str_title, col, colNames, true);
	cout << endl << endl;


	if (final_pause)
		getch();
}


size_t CRUD::selCompanhia(Aeroporto* aeroporto) {
	listCompanhia(aeroporto);
	cout << endl;
	size_t indice = get_uint_cin<size_t>("\nIntroduza o índice da companhia (0 para retroceder): ", aeroporto->getConstRefCompanhias().size(), 0, true);
	companhia_actual = aeroporto->getConstRefCompanhias()[indice];
	return indice;
}



Companhia* CRUD::selCompanhiaPtr(Aeroporto *aeroporto) {
	return aeroporto->getConstRefCompanhias()[ selCompanhia(aeroporto) ];
}


void CRUD::infoCompanhia(Companhia *companhia) {
	cout << endl << endl;
	cout << endl;
	string str_title = "Informações sobre a companhia";

	vector <string> colNames;					// nomes de colunas não são usados, logo vão strings vazias
	colNames.push_back(string(""));
	colNames.push_back(string(""));


	vector < vector<string> > col;
	vector <string> dados;

	//Nomes dos atributos
	col.push_back(Comandos::_companhia_op_list);

	dados.push_back( companhia->getSigla() );
	dados.push_back( companhia->getNome() );
	dados.push_back( to_string(companhia->getTaxaBalcoes()) );



	//Dados relativos aos atributos
	col.push_back(dados);

	printMenu(str_title, col, colNames, false, false, true, true);

	getch();
}


void CRUD::editCompanhia(Aeroporto *aeroporto, Companhia *companhia) {
	bool continuar;
	do {
		cout << endl << endl;
		//Selecção da companhia
		if (companhia == NULL)
			companhia = selCompanhiaPtr(aeroporto);

		//Escolha do atributo a editar
		string titulo("Atributos das companhias: ");
		string col_name("Atributos");
		vector <string> nome_coluna;
		nome_coluna.push_back(col_name);

		vector < vector <string> > colunas;
		colunas.push_back(Comandos::_companhia_op_list);


		cout << endl << endl;
		printMenu(titulo, colunas, nome_coluna);


		cout << endl << endl;
		int indice_atributo = get_int_cin("Escolha o atributo que quer editar: ", Comandos::_companhia_op_list.size());
		cout << endl << endl;

		string str_temp;

		//Edição do atributo escolhido
		switch (indice_atributo) {
			case 0: {
				cout << "Introduza a nova sigla da companhia: ";
				getlineCin(str_temp);
				companhia->setSigla(str_temp);
				break;
			}

			case 1: {
				cout << "Introduza o novo nome da companhia: ";
				getlineCin(str_temp);
				companhia->setNome(str_temp);
				break;
			}

			case 2: {
				unsigned taxa_balcoes = get_uint_cin<unsigned>("Introduza a nova taxa de utilização para os balcões desta companhia: ");
				companhia->setTaxaBalcoes(taxa_balcoes);
			}
		}

		//Pergunta ao utilizador se quer continuar a editar a companhia
		continuar = get_yes_no("\n\nDeseja continuar a editar esta companhia (S/N): ");

	} while (continuar);
}


void CRUD::delCompanhia(Aeroporto *aeroporto) {
	try {
		int indice = selCompanhia(aeroporto);
		delCompanhia(aeroporto, indice);
		cout << endl << endl;
		cout << "Removido com sucesso!" << endl;
	} catch (exception & e) {
		cout << e.what() << endl;
	}

	getch();
}


void CRUD::delCompanhia(Aeroporto *aeroporto, size_t indice) {
	if ((indice < 0) && (indice >= (int)aeroporto->getRefCompanhias().size()))
		throw ExOutOfRange();

	vector<Companhia*>::iterator it_companhia = aeroporto->getRefCompanhias().begin() + indice;

	for (vector<Voo*>::iterator it_voo = companhia_actual->getRefVoos().begin(); it_voo != companhia_actual->getRefVoos().end(); ++it_voo) {
		delVooPtrPortaEmbarque((*it_voo)->getPortaEmbarque(), (*it_voo));

		for (vector<Passageiro*>::iterator it_passageiro = (*it_voo)->getRefPassageirosVoo().begin(); it_passageiro != (*it_voo)->getRefPassageirosVoo().end(); ++it_passageiro) {
			delPassageiroPtr(aeroporto, (*it_passageiro));
			delete *(it_passageiro);
			(*it_voo)->getRefPassageirosVoo().erase(it_passageiro);
		}
	}

	delete *(it_companhia);
	aeroporto->getRefCompanhias().erase(it_companhia);
}


void CRUD::delCompanhiaPtr(Aeroporto *aeroporto, Companhia *companhia_ptr) {
	vector<Companhia*> &vec_companhias = aeroporto->getRefCompanhias();
	vector<Companhia*>::iterator it_companhia = vec_companhias.begin();

	//Se encontrar o apontador para a companhia que vai ser removido deste aeroporto (foi associado a outro aeroporto), é removido do vector
	for (it_companhia = vec_companhias.begin(); it_companhia != vec_companhias.end(); ++it_companhia) {
		if (*it_companhia == companhia_ptr) {
			vec_companhias.erase(it_companhia);
			return;
		}
	}

	//Caso contrário é lançada uma excepção dizendo que esse elemento não existe
	throw ExElementDoesntExists <Companhia> (*companhia_ptr);
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Passageiro <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


void CRUD::addPassageiro(Aeroporto* aeroporto)
{
	cout << endl << endl;
	string nome;
	string morada;
	string nacionalidade;
	unsigned contacto;
	unsigned BI;
	unsigned idade;

	unsigned necessidades_especiais;
	unsigned peso_bagagem(0);
	unsigned numero_lugar_aviao(0);
	Voo *voo_actual(NULL);

	cout << "Introduza o nome:" << endl;
	getlineCin(nome);

	cout << "Introduza a morada:" << endl;
	getlineCin(morada);

	cout << "Introduza a nacionalidade:" << endl;
	getlineCin(nacionalidade);

	cout << "Introduza o contacto:" << endl;
	cin >> contacto;

	cout << "Introduza o BI:" << endl;
	cin >> BI;

	cout << "Introduza a idade:" << endl;
	cin >> idade;

	cout << "Necessidades epeciais a associar ao passageiro:\n" << endl;
	Passageiro::listNecessidadesEspeciaisInfo();
	necessidades_especiais = get_uint_cin <unsigned>("Caso possua necessidades especiais selecione uma da lista em cima:\n", Passageiro::getRefNecessidadesEspeciaisInfo().size(), 0, false);


	cout << "Seleccione um voo de uma companhia:" << endl;
	bool continuar = true;
	do {
		voo_actual = selPlanoVooPtr( selCompanhiaPtr(aeroporto) );
		if (voo_actual->getFechado()) {
			cout << "\nO voo selecionado já está fechado, selecione um novo voo.\n" << endl;
			continuar = true;
		}
		else
			continuar = false;

	} while (continuar);


	Passageiro* p = new Passageiro(
			nome,
			morada,
			nacionalidade,
			contacto,
			BI,
			idade,
			necessidades_especiais,
			peso_bagagem,
			numero_lugar_aviao,
			voo_actual);

	try
	{
		if(voo_actual->getConstRefPassageirosVoo().size() >= voo_actual->getNumeroPassageiros())
			throw ExOutOfRange("Capacidade do voo foi excedida!");

		addPassageiro(aeroporto, p);

		voo_actual->addPassageiro(p);
		cout << endl << endl;

		cout << "Adicionado com sucesso!" << endl;
	}
	catch(Exceptions & e)
	{
		delete p;
		cout << e.what() << endl;
	}

	getch();
}

void CRUD::addPassageiro(Aeroporto* aeroporto, Passageiro *passageiro) {
	vector<Passageiro*>::const_iterator it;

	for (it = aeroporto->getRefPassageirosAeroporto().begin(); it != aeroporto->getRefPassageirosAeroporto().end(); ++it)
		if ((*passageiro) == *(*it))
			throw ExElementAlreadyExists<Passageiro> (*passageiro);

	aeroporto->getRefPassageirosAeroporto().push_back(passageiro);
}



bool CRUD::cmpPassageiroNome(const Passageiro *p1, const Passageiro *p2) {
	return (p1->getNome() < p2->getNome());
}

bool CRUD::cmpPassageiroBI(const Passageiro *p1, const Passageiro *p2) {
	return (p1->getBI() < p2->getBI());
}

bool CRUD::cmpPassageiroNumero(const Passageiro *p1, const Passageiro *p2) {
	return (p1->getNumeroLugarAviao() < p2->getNumeroLugarAviao());
}

void CRUD::listPassageiro(Aeroporto *aeroporto, bool final_pause) {
	cout << endl << endl;
	vector<Passageiro*> &passageiros_aeroporto = aeroporto->getRefPassageirosAeroporto();

	if (passageiros_aeroporto.size() == 0) {
		throw ExEmptyVector("Não existem passageiros no aeroporto!");
	}

	//Selecção do método de ordenação
	string str_title_ordenacao = "Método de ordenação";

	vector <string> colNames_ordenacao;
	colNames_ordenacao.push_back(string("Critério de ordenação"));

	vector < vector<string> > col_ordenacao;
	vector <string> parametros_ordenacao;
	parametros_ordenacao.push_back((string)"Nome");
	parametros_ordenacao.push_back((string)"BI");
	parametros_ordenacao.push_back((string)"Número Lugar Avião");
	col_ordenacao.push_back(parametros_ordenacao);

	printMenu(str_title_ordenacao, col_ordenacao, colNames_ordenacao);

	vector <string> colNames;

	cout << endl << endl;

	size_t metodo = get_uint_cin("Selecione o critério de ordenação que quer usar: ", parametros_ordenacao.size());

	cout << endl << endl;

	//Listagem ordenada das companhias
	string str_title = "Lista de passageiros";
	vector < vector<string> > col;

	col.push_back(vector<string> ());
	col.push_back(vector<string> ());
	col.push_back(vector<string> ());

	//Ordenação do vector de acordo com o parâmetro fornecido
	switch (metodo) {
		case 0: {
			sort(passageiros_aeroporto.begin(), passageiros_aeroporto.end(), cmpPassageiroNome);
			colNames.push_back((string)"Nome");
			colNames.push_back((string)"BI");
			colNames.push_back((string)"Número Lugar Avião");

			size_t i = 0;
			for (vector <Passageiro*>::const_iterator it = passageiros_aeroporto.begin(); it != passageiros_aeroporto.end(); ++it) {
				col[i++].push_back((*it)->getNome());
				col[i++].push_back( to_string<unsigned>((*it)->getBI()) );
				col[i].push_back( to_string<unsigned>((*it)->getNumeroLugarAviao()) );
				i = 0;
			}

			break;
		}

		case 1: {
			sort(passageiros_aeroporto.begin(), passageiros_aeroporto.end(), cmpPassageiroBI);
			colNames.push_back((string)"BI");
			colNames.push_back((string)"Nome");
			colNames.push_back((string)"Número Lugar Avião");

			size_t i = 0;
			for (vector <Passageiro*>::const_iterator it = passageiros_aeroporto.begin(); it != passageiros_aeroporto.end(); ++it) {
				col[i++].push_back( to_string<unsigned>((*it)->getBI()) );
				col[i++].push_back((*it)->getNome());
				col[i].push_back( to_string<unsigned>((*it)->getNumeroLugarAviao()) );
				i = 0;
			}

			break;
		}
	col.push_back(vector<string> ());

		case 2: {
			sort(passageiros_aeroporto.begin(), passageiros_aeroporto.end(), cmpPassageiroNumero);
			colNames.push_back((string)"Número Lugar Avião");
			colNames.push_back((string)"Nome");
			colNames.push_back((string)"BI");

			size_t i = 0;
			for (vector <Passageiro*>::const_iterator it = passageiros_aeroporto.begin(); it != passageiros_aeroporto.end(); ++it) {
				col[i++].push_back( to_string<unsigned>((*it)->getNumeroLugarAviao()) );
				col[i++].push_back((*it)->getNome());
				col[i].push_back( to_string<unsigned>((*it)->getBI()) );
				i = 0;
			}

			break;
		}
	}


	cout << endl << endl;
	printMenu(str_title, col, colNames, true);

	if (final_pause)
		getch();
}

size_t CRUD::selPassageiro(Aeroporto* aeroporto)
{
	listPassageiro(aeroporto);
	cout << endl << endl;
	size_t indice = get_uint_cin<size_t>("\nIntroduza o índice:",aeroporto->getConstRefPassageirosAeroporto().size(), 0, true);
	passageiro_actual = aeroporto->getRefPassageirosAeroporto()[indice];
	return indice;
}

Passageiro* CRUD::selPassageiroPtr(Aeroporto* aeroporto) {
	return aeroporto->getConstRefPassageirosAeroporto()[ selPassageiro(aeroporto) ];
}


void CRUD::infoPassageiro(Aeroporto *aeroporto, Passageiro *passageiro) {
	cout << endl << endl;


	if (passageiro == NULL) {
		size_t indice = selPassageiro(aeroporto);
		passageiro = aeroporto->getRefPassageirosAeroporto()[indice];
	}

	string str_title = "Informações sobre o passageiro";

	vector <string> colNames;					// nomes de colunas não são usados, logo vão strings vazias
	colNames.push_back(string(""));
	colNames.push_back(string(""));

	vector < vector<string> > col;
	vector <string> dados;

	//Nomes dos atributos
	col.push_back(Comandos::_passageiro_op_list);

	//dados referentes à superclasse Pessoa
	dados.push_back( passageiro->getNome() );
	dados.push_back( passageiro->getMorada() );
	dados.push_back( passageiro->getNacionalidade() );
	dados.push_back( to_string<unsigned>(passageiro->getContacto()) );
	dados.push_back( to_string<unsigned>(passageiro->getBI()) );
	dados.push_back( to_string<unsigned>(passageiro->getIdade()) );

	//Dados referentes à subclasse Passageiro
	dados.push_back( Passageiro::getInfoEnumNecessidadesEspeciais( passageiro->getNecessidades_especiais() ) );
	dados.push_back( to_string<unsigned>(passageiro->getPesoBagagem()) );
	dados.push_back( to_string<unsigned>(passageiro->getNumeroLugarAviao()) );
	dados.push_back( to_string<unsigned>(passageiro->getVoo()->getNumeroVoo()) );

	//Dados relativos aos atributos
	col.push_back(dados);

	printMenu(str_title, col, colNames, false, false, true, true);

	getch();
}


void CRUD::editPassageiro(Aeroporto * aeroporto) {
	bool continuar;
	do {
		cout << endl << endl;
		//Selecção do Passageiro
		Passageiro* passageiro = selPassageiroPtr(aeroporto);

		//Escolha do atributo a editar
		string titulo("Atributos dos passageiros: ");
		string col_name("Atributos");
		vector <string> nome_coluna;
		nome_coluna.push_back(col_name);

		vector < vector <string> > colunas;
		colunas.push_back(Comandos::_passageiro_op_list);

		cout << endl << endl;
		printMenu(titulo, colunas, nome_coluna);

		cout << endl << endl;
		size_t indice_atributo = get_uint_cin("Escolha o atributo que quer editar: ", Comandos::_passageiro_op_list.size());
		cout << endl << endl;

		string str_temp;
		unsigned uns_temp;

		//Edição do atributo escolhido
		switch (indice_atributo) {
			case 0: {
				cout << "Introduza o novo nome para o passageiro: ";
				getlineCin(str_temp);
				passageiro->setNome(str_temp);
				break;
			}

			case 1: {
				cout << "Introduza a nova morada para o passageiro: ";
				getlineCin(str_temp);
				passageiro->setMorada(str_temp);
				break;
			}

			case 2: {
				cout << "Introduza a nova nacionalidade para o passageiro: ";
				getlineCin(str_temp);
				passageiro->setNacionalidade(str_temp);
				break;
			}

			case 3: {
				uns_temp = get_uint_cin<unsigned>("Introduza o novo número de contacto para o passageiro: ");
				passageiro->setContacto(uns_temp);
				break;
			}

			case 4: {
				uns_temp = get_uint_cin<unsigned>("Introduza o novo BI para o passageiro: ");
				passageiro->setBI(uns_temp);
				break;
			}

			case 5: {
				uns_temp = get_uint_cin<unsigned>("Introduza a nova idade para o passageiro: ");
				passageiro->setIdade(uns_temp);
				break;
			}

			case 6: {
				cout << "Necessidades epeciais a associar ao passageiro:\n" << endl;
				Passageiro::listNecessidadesEspeciaisInfo();
				unsigned necessidades_especiais = get_uint_cin <size_t>("Caso possua necessidades especiais selecione uma da lista em cima:\n", Passageiro::getRefNecessidadesEspeciaisInfo().size(), 0, false);
				passageiro->setNecessidades_especiais(necessidades_especiais);
				break;
			}

			case 7: {
				uns_temp = get_uint_cin<unsigned>("Introduza o peso da bagagem deste pasageiro: ");
				passageiro->setPesoBagagem(uns_temp);
				break;
			}

			case 8: {
				uns_temp = get_uint_cin<unsigned>("Introduza o número do lugar no avião deste pasageiro: ");
				passageiro->setNumeroLugarAviao(uns_temp);
				break;
			}
		}

		//Pergunta ao utilizador se quer continuar a editar o passageiro
		continuar = get_yes_no("\n\nDeseja continuar a editar este passageiro (S/N): ");

	} while (continuar);
}


void CRUD::delPassageiro(Aeroporto *aeroporto)
{
	try {
		size_t indice = selPassageiro(aeroporto);

		delPassageiro(aeroporto, indice);

		cout << endl << endl;

		cout << "Removido com sucesso!" << endl;
	} catch (exception & e) {
		cout << e.what() << endl;
	}

	getch();
}


void CRUD::delPassageiro(Aeroporto *aeroporto, size_t indice) {
	vector<Passageiro*> &vec_passageiros = aeroporto->getRefPassageirosAeroporto();
	if( (indice < 0) && (indice >= vec_passageiros.size()) )
		throw ExOutOfRange();

	vector<Passageiro*>::iterator it = vec_passageiros.begin();

	delete *(it + indice);
	vec_passageiros.erase(it + indice);
}

void CRUD::delPassageiroPtr(Aeroporto* aeroporto, Passageiro* passageiro) {
	vector <Passageiro*> &vec_passageiros = aeroporto->getRefPassageirosAeroporto();
	vector <Passageiro*>::iterator it_passageiro = vec_passageiros.begin();

	for ( ; it_passageiro != vec_passageiros.end(); ++it_passageiro) {
		if (*(*it_passageiro) == *passageiro) {
			vec_passageiros.erase(it_passageiro);
			return;}
	}
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Check-in <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void CRUD::initCheckIn(Voo *voo) {
	if(!voo->getFechado())
		voo->criaFilaCheckIn();
}


void CRUD::checkIn(Aeroporto *aeroporto, Voo *voo) {
	//Caso a fila de check-in não esteja inicializada, inicializa-se
	if (voo->getConstRefFilaCheckIn().empty() && voo->getConstRefPassageirosVooPQ().empty())
		initCheckIn(voo);

	if (voo->getFechado()) {
		cout << "O voo encontra-se fechado!\nNão é possivel fazer mais check-ins!\n" << endl;
		getch();
		return;
	}

	bool continuar = true;
	while(continuar) {
		if (voo->getFilaCheckIn().empty()) {
			cout << "Não existem mais passageiros para fazer check-in!\n\n" << endl;
			getch();
			break;
		}
		else {
			checkInNextPassageiro(aeroporto, voo);
			continuar = get_yes_no("Deseja continuar a fazer o check-in do próximo passageiro? (S/N): ", "Introduza S para continuar e N para parar de fazer o check-in deste voo.");
		}
	}
}

void CRUD::checkInNextPassageiro(Aeroporto *aeroporto, Voo *voo) {
	if (voo->getFechado()) {
		cout << "O voo encontra-se fechado!\nNão é possivel fazer mais check-ins!\n" << endl;
		getch();
		return;
	}

	Passageiro *next_passageiro = voo->getRefFilaCheckIn().front();
	voo->getRefFilaCheckIn().pop();

	infoPassageiro(aeroporto, next_passageiro);
	cout << "\n" << endl;
	unsigned peso_max_bagagem = voo->getAviao()->getPesoMaxBagagem();
	unsigned capacidade_passageiros_aviao = voo->getAviao()->getTipoAviao()->getMaximoPassageiros();

	stringstream error_message_bagagem;
	error_message_bagagem << "O limite máximo do peso da bagagem para este avião é de " << peso_max_bagagem << "kg.";
	stringstream error_message_numero_lugar;
	error_message_numero_lugar << "O limite máximo do número do lugar no avião é " << capacidade_passageiros_aviao << ".";

	unsigned necessidades_especiais;
	cout << "Necessidades epeciais a associar ao passageiro:\n" << endl;
	Passageiro::listNecessidadesEspeciaisInfo();
	necessidades_especiais = get_uint_cin <unsigned>("Caso possua necessidades especiais selecione uma da lista em cima:\n", Passageiro::getRefNecessidadesEspeciaisInfo().size(), 0, false);

	unsigned peso_bagagem = get_uint_cin<unsigned>("Introduza o peso da bagagem para este passageiro: ", peso_max_bagagem, 0, false, error_message_bagagem.str().c_str());
	next_passageiro->setPesoBagagem(peso_bagagem);

	unsigned numero_lugar_aviao = get_uint_cin<unsigned>("Introduza o número do lugar no avião para este passageiro ", capacidade_passageiros_aviao, 0, false, error_message_numero_lugar.str().c_str());
	next_passageiro->setNumeroLugarAviao(numero_lugar_aviao);

	voo->getRefPassageirosVooPQ().push(next_passageiro);
}


void CRUD::printPriorityQueue(Voo *voo) {
	if (voo->getPassageirosVooPQ().empty()) {
		cout << "Não existem passageiros para embarcar!\n" << endl;
		getch();
		return;
	}

	if (voo->getFechado()) {
		cout << "O voo encontra-se fechado!\nNão é possivel mostrar os passageiros que se encontram à espera para embarcar!\n" << endl;
		getch();
		return;
	}

	priority_queue <Passageiro*> passageiros_voo_pq_backup = voo->getPassageirosVooPQ();

	string title("Lista de passageiros a embarcar");
	vector < vector <string> > colunas;
	vector <string> nomes_passageiros;
	vector <string> colnames;

	colnames.push_back("Nome dos passageiros");

	while(!passageiros_voo_pq_backup.empty()) {
		nomes_passageiros.push_back(passageiros_voo_pq_backup.top()->getNome());
		passageiros_voo_pq_backup.pop();
	}

	colunas.push_back(nomes_passageiros);

	printMenu(title, colunas, colnames);
	cout << "\n\n" << endl;
	getch();
}


void CRUD::chamadaEmbarqueVoo(Aeroporto *aeroporto, Voo *voo) {
	if (voo->getPassageirosVooPQ().empty()) {
		cout << "Não existem passageiros para embarcar!\n" << endl;
		getch();
		return;
	}

	if (voo->getFechado()) {
		cout << "O voo encontra-se fechado!\nNão é possivel mostrar os passageiros que se encontram à espera para embarcar!\n" << endl;
		getch();
		return;
	}

	vector <Passageiro*> backup_passageiros_nao_presentes;
	priority_queue <Passageiro*> passageiros_voo_pq = voo->getRefPassageirosVooPQ();
	Passageiro *passageiro_actual;
	bool presente = true;
	bool continuar = true;

	cout << "Chamada dos pessageiros por ordem de prioridade.\n Introduza S se o passageiro entrou ou N se não está presente.";
	cout << "\n\nNota:\nIntroduza S para comtinuar a fazer o embarque ou N para sair (entre as chamadas dos passageiros).\n" << endl;

	getch();

	while(continuar && !passageiros_voo_pq.empty()) {
		passageiro_actual = passageiros_voo_pq.top();
		passageiros_voo_pq.pop();

		cout << passageiro_actual->getNome() << "\t";
		presente = get_yes_no("Presente? (S/N): ", "Introduza S ou N conforme o passageiro tenha ou não embarcado: ");

		if (!presente)
			backup_passageiros_nao_presentes.push_back(passageiro_actual);

		continuar = get_yes_no("\nContinuar o embarque? (S/N): ", "Introduza S ou N conforme queira continuar o embarque dos passageiros: ");
	}

	if (backup_passageiros_nao_presentes.empty() && passageiros_voo_pq.empty()) {
		cout << "\n\nNão existem mais passageiros para chamar!\nVoo fechado!" << endl;
		fecharVoo(aeroporto, voo);
		getch();
	}
	else {
		for (size_t i(0); i < backup_passageiros_nao_presentes.size(); ++i)
			passageiros_voo_pq.push(backup_passageiros_nao_presentes[i]);

		cout << "Ainda há passageiros que não embarcaram!";
		bool fechar = get_yes_no("Pretende fechar o voo? (S/N): ", "Introduza S ou N consoante queira ou não fechar o voo actual: ");

		if (fechar) {
			fecharVoo(aeroporto, voo);
			cout << "\nVoo fechado!\n" << endl;
			getch();
		}
	}
}


void CRUD::printPassageirosPortaEmbarque(Aeroporto *aeroporto) {
	cout << "Selecione a porta de embarque da qual pretende listar os passageiros a embarcar:\n" << endl;
	PortaEmbarque *porta_embarque = selPortaEmbarquePtr(aeroporto);

	Companhia companhia_temp;
	companhia_temp.setVoos(porta_embarque->getVoosPortaEmbarque());

	cout << "Selecione o voo para o qual quer listar os passageiros que estão nesta sala de embarque:\n" << endl;
	Voo *voo_selecionado = selPlanoVooPtr(&companhia_temp);

	printPriorityQueue(voo_selecionado);
}


void CRUD::chamadaEmbarqueVooPortaEmbarque(Aeroporto *aeroporto) {
	cout << "Selecione a porta de embarque da qual pretende fazer a chamada dos passageiros a embarcar:\n" << endl;
	PortaEmbarque *porta_embarque = selPortaEmbarquePtr(aeroporto);

	Companhia companhia_temp;
	companhia_temp.setVoos(porta_embarque->getVoosPortaEmbarque());

	cout << "Selecione o voo para o qual quer fazer a chamada dos passageiros que estão nesta sala de embarque:\n" << endl;
	Voo *voo_selecionado = selPlanoVooPtr(&companhia_temp);

	chamadaEmbarqueVoo(aeroporto, voo_selecionado);
}


void CRUD::fecharVoo(Aeroporto *aeroporto, Voo *voo) {
	aeroporto->addVooHashSetVoos(voo);
	voo->setFechado(true);
	voo->getPortaEmbarque()->setVagasPass(voo->getPortaEmbarque()->getVagasPass() + voo->getNumeroPassageiros());
}



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Tabela de dispersão <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void CRUD::listHashSetVoos(Aeroporto *aeroporto) {
	if (aeroporto->getConstRefHashSetVoos().empty()) {
		cout << "Não existem voos fechados!\n" << endl;
		getch();
		return;
	}

	string title("Voos fechados do aeroporto");

	vector < vector <string> > colunas;
	colunas.push_back(vector <string> ());
	colunas.push_back(vector <string> ());
	colunas.push_back(vector <string> ());
	colunas.push_back(vector <string> ());


	vector <string> colnames;
	colnames.push_back("Id do avião");
	colnames.push_back("Destino");
	colnames.push_back("Origem");
	colnames.push_back("Data saída do voo");

	HASH_SET_VOOS::const_iterator it_hash_set_voos = aeroporto->getConstRefHashSetVoos().begin();
	HASH_SET_VOOS::const_iterator it_hash_set_voos_end = aeroporto->getConstRefHashSetVoos().end();

	while(it_hash_set_voos != it_hash_set_voos_end) {
		colunas[0].push_back(to_string((*it_hash_set_voos)->getNumeroVoo()));
		colunas[1].push_back((*it_hash_set_voos)->getDestino());
		colunas[2].push_back((*it_hash_set_voos)->getOrigem());
		colunas[3].push_back(to_string((*it_hash_set_voos)->getDatahoraSaida()));

		++it_hash_set_voos;
	}

	printMenu(title, colunas, colnames, false, false, true, false);
	getch();
}


void CRUD::listHashSetVoosEntreDatasCriterio(Aeroporto *aeroporto) {
	vector <Voo*> vec_voos;

	DataHora data_inicio, data_fim;
	data_inicio.getDataHoraCin("Introduza a menor data de partida do voo que quer usar na pesquisa:\n(AAAA/MM/DD HH:mm): ");
	data_fim.getDataHoraCin("Introduza a maior data de partida do voo que quer usar na pesquisa:\n(AAAA/MM/DD HH:mm): ");

	HASH_SET_VOOS::const_iterator it_hash_set_voos = aeroporto->getConstRefHashSetVoos().begin();
	HASH_SET_VOOS::const_iterator it_hash_set_voos_end = aeroporto->getConstRefHashSetVoos().end();

	//Construção do vector de Voo* a partir dos voos fechados que têm uma data de partida compatível com os limites introduzidos pelo utilizador
	while (it_hash_set_voos != it_hash_set_voos_end) {
		if ((data_inicio < (*it_hash_set_voos)->getDatahoraSaida()) && ((*it_hash_set_voos)->getDatahoraSaida() < data_fim))
			vec_voos.push_back(*it_hash_set_voos);

		++it_hash_set_voos;
	}

	if (vec_voos.empty()) {
		cout << "\nNenhum voo está compreendido entre as datas que introduziu!\n" << endl;
		getch();
		return;
	}

	Companhia companhia_temp;		//Companhia temporária usada para não alterar a interface dos algoritmos usados na parte 1 do projecto
	companhia_temp.setVoos(vec_voos);

	cout << "\nListagem dos voos fechados deste aeroporto:\nSelecione um índice para ver mais informações acerca do voo\n" << endl;

	infoPlanoVoo(&companhia_temp);
}


void CRUD::searchHashSetVoos(Aeroporto *aeroporto) {
	unsigned numero_voo = get_uint_cin <unsigned>("Introduza o número do voo do qual pretende ver as informações: ");

	Voo voo;
	voo.setNumero_voo(numero_voo);

	HASH_SET_VOOS::const_iterator it_hash_set_voo = aeroporto->getConstRefHashSetVoos().find(&voo);
	HASH_SET_VOOS::const_iterator it_hash_set_voo_end = aeroporto->getConstRefHashSetVoos().end();

	if(it_hash_set_voo == it_hash_set_voo_end) {
		cout << "O voo com o id especificado não existe!\n" << endl;
		getch();
	}
	else {
		string title("Informações sobre o plano de voo");
		vector <vector <string> > colunas;
		vector <string> colnames;

		colnames.push_back("");
		colnames.push_back("");

		colunas.push_back(Comandos::_voo_op_list);
		colunas.push_back(vector <string> ());

		colunas[1].push_back( to_string<unsigned>((*it_hash_set_voo)->getNumeroVoo()) );
		colunas[1].push_back( (*it_hash_set_voo)->getOrigem() );
		colunas[1].push_back( (*it_hash_set_voo)->getDestino() );
		colunas[1].push_back( to_string<DataHora>((*it_hash_set_voo)->getDatahoraSaida()) );
		colunas[1].push_back( to_string<DataHora>((*it_hash_set_voo)->getDatahoraChegada()) );
		colunas[1].push_back( to_string<unsigned>((*it_hash_set_voo)->getNumeroPassageiros()) );
		colunas[1].push_back( (*it_hash_set_voo)->getPortaEmbarque()->getNumero() );
		colunas[1].push_back( (*it_hash_set_voo)->getAviao()->getNome() );
		colunas[1].push_back( (*it_hash_set_voo)->getCompanhia()->getNome() );
		colunas[1].push_back( to_string<unsigned>((*it_hash_set_voo)->getAtraso()) );

		string cancelado;
		if ((*it_hash_set_voo)->getCancelado())
			cancelado = "Cancelado";
		else
			cancelado = "Não cancelado";

		colunas[1].push_back( cancelado );

		printMenu(title, colunas, colnames, false, false, true, true);

		getch();
	}
}


void CRUD::addVooHashSetVoos(Aeroporto *aeroporto) {
	Companhia *companhia_voo = selCompanhiaPtr(aeroporto);
	Voo *voo = selPlanoVooPtr(companhia_voo);
	fecharVoo(aeroporto, voo);
}


void CRUD::delVooHashSetVoos(Aeroporto *aeroporto) {
	vector <Voo*> vec_voos;

	HASH_SET_VOOS::iterator it_hash_set = aeroporto->getRefHashSetVoos().begin();
	HASH_SET_VOOS::iterator it_hash_set_end = aeroporto->getRefHashSetVoos().end();
	while(it_hash_set != it_hash_set_end)
	{
		vec_voos.push_back(*it_hash_set);

		it_hash_set++;
	}

	Companhia companhia_temp;
	companhia_temp.setVoos(vec_voos);

	cout << "\nSelecione o voo que quer eliminar desta tabela de voos fechados:\n" << endl;

	size_t indice_voo_a_eliminar = selPlanoVoo(&companhia_temp);
	Voo *voo_a_eliminar = vec_voos[indice_voo_a_eliminar];

	//Eliminação do voo e actualização das variáveis a ele ligadas (esta função também elimina o voo da hash_table)
	delPlanoVoo(aeroporto, voo_a_eliminar->getCompanhia(), indice_voo_a_eliminar);
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Taxas <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//************************* taxas - balcões  ****************************
void CRUD::listTaxasBalcoesEntreDatas(Aeroporto *aeroporto) {
	unsigned taxa_total(0);

	DataHora data_inicio, data_fim;
	data_inicio.getDataHoraCin("Introduza o limite inferior (data) a usar na pesquisa:\n(AAAA/MM/DD HH:mm): ");
	data_fim.getDataHoraCin("Introduza o limite superior (data) a usar na pesquisa:\n(AAAA/MM/DD HH:mm): ");

	HASH_SET_VOOS::const_iterator it_hash_set_voos = aeroporto->getConstRefHashSetVoos().begin();
	HASH_SET_VOOS::const_iterator it_hash_set_voos_end = aeroporto->getConstRefHashSetVoos().end();

	while (it_hash_set_voos != it_hash_set_voos_end) {
		if ((data_inicio < (*it_hash_set_voos)->getDatahoraSaida()) && ((*it_hash_set_voos)->getDatahoraSaida() < data_fim))
			taxa_total += ((*it_hash_set_voos)->getCompanhia()->getTaxaBalcoes() * (*it_hash_set_voos)->getNumeroPassageiros()); //<<<<<<<<<<<< cálculo da taxa

		++it_hash_set_voos;
	}

	cout << "A taxa de utilização dos balcões de check-in entre " << data_inicio << " e " << data_fim << " é de " << taxa_total << " euros.\n" << endl;
	getch();
}


void CRUD::listTaxasBalcoesVooEntreDatas(Aeroporto *aeroporto) {
	DataHora data_inicio, data_fim;
	data_inicio.getDataHoraCin("Introduza o limite inferior (data de saída do voo) a usar na pesquisa:\n(AAAA/MM/DD HH:mm): ");
	data_fim.getDataHoraCin("Introduza o limite superior (data de saída do voo) a usar na pesquisa:\n(AAAA/MM/DD HH:mm): ");

	HASH_SET_VOOS::const_iterator it_hash_set_voos = aeroporto->getConstRefHashSetVoos().begin();
	HASH_SET_VOOS::const_iterator it_hash_set_voos_end = aeroporto->getConstRefHashSetVoos().end();

	vector <Voo*> vec_voos;

	//Construção do vector de Voo* a partir dos voos fechados que têm uma data de partida compatível com os limites introduzidos pelo utilizador
	while(it_hash_set_voos != it_hash_set_voos_end) {
		if ((data_inicio < (*it_hash_set_voos)->getDatahoraSaida()) && ((*it_hash_set_voos)->getDatahoraSaida() < data_fim))
			vec_voos.push_back(*it_hash_set_voos);

		++it_hash_set_voos;
	}


	if (vec_voos.empty()) {
		cout << "\nNenhum voo está compreendido entre as datas que introduziu!\n" << endl;
		getch();
		return;
	}


	Companhia companhia_temp;
	companhia_temp.setVoos(vec_voos);

	cout << "\nSelecione o voo do qual pretende ver a taxa:\n\n" << endl;
	Voo *voo_selecionado = selPlanoVooPtr(&companhia_temp);

	unsigned taxa_voo = voo_selecionado->getCompanhia()->getTaxaBalcoes() * voo_selecionado->getNumeroPassageiros(); //<<<<<<<<<<<< cálculo da taxa

	cout << "A taxa de utilização dos balcões de check-in para o voo selecionado é de " << taxa_voo << " euros.\n" << endl;
	getch();
}


void CRUD::listTaxasBalcoesVoosEntreDatas(Aeroporto *aeroporto) {
	DataHora data_inicio, data_fim;
	data_inicio.getDataHoraCin("Introduza o limite inferior (data de saída dos voos) a usar na pesquisa:\n(AAAA/MM/DD HH:mm): ");
	data_fim.getDataHoraCin("Introduza o limite superior (data de saída dos voos) a usar na pesquisa:\n(AAAA/MM/DD HH:mm): ");

	HASH_SET_VOOS::const_iterator it_hash_set_voos = aeroporto->getConstRefHashSetVoos().begin();
	HASH_SET_VOOS::const_iterator it_hash_set_voos_end = aeroporto->getConstRefHashSetVoos().end();

	vector <Voo*> vec_voos;

	//Construção do vector de Voo* a partir dos voos fechados que têm uma data de partida compatível com os limites introduzidos pelo utilizador
	while(it_hash_set_voos != it_hash_set_voos_end) {
		if ((data_inicio < (*it_hash_set_voos)->getDatahoraSaida()) && ((*it_hash_set_voos)->getDatahoraSaida() < data_fim))
			vec_voos.push_back(*it_hash_set_voos);

		++it_hash_set_voos;
	}


	if (vec_voos.empty()) {
		cout << "\nNenhum voo está compreendido entre as datas que introduziu!\n" << endl;
		getch();
		return;
	}


	string title("Listagem dos voos e respectivas taxas de utilização dos balcões de check-in");

	vector < vector <string> > colunas;
	colunas.push_back(vector <string> ());
	colunas.push_back(vector <string> ());
	colunas.push_back(vector <string> ());
	colunas.push_back(vector <string> ());

	vector <string> colnames;
	colnames.push_back("Origem");
	colnames.push_back("Destino");
	colnames.push_back("Data de saida");
	colnames.push_back("Taxa de utilização");

	unsigned taxa_utilizacao_voo;
	for (size_t i(0); i < vec_voos.size(); ++i) {
		taxa_utilizacao_voo = vec_voos[i]->getCompanhia()->getTaxaBalcoes() * vec_voos[i]->getNumeroPassageiros(); //<<<<<<<<<<<< cálculo da taxa

		colunas[0].push_back(vec_voos[i]->getOrigem());
		colunas[1].push_back(vec_voos[i]->getDestino());
		colunas[2].push_back(to_string(vec_voos[i]->getDatahoraSaida()));
		colunas[3].push_back(to_string(taxa_utilizacao_voo));
	}

	printMenu(title, colunas, colnames, false, false, false, false);
	getch();
}


//*************************  taxas - portas de embarque  ****************************

void CRUD::listTaxasPortasEmbarqueEntreDatas(Aeroporto *aeroporto) {
	unsigned taxa_total(0);

	DataHora data_inicio, data_fim;
	data_inicio.getDataHoraCin("Introduza o limite inferior (data) a usar na pesquisa:\n(AAAA/MM/DD HH:mm): ");
	data_fim.getDataHoraCin("Introduza o limite superior (data) a usar na pesquisa:\n(AAAA/MM/DD HH:mm): ");

	HASH_SET_VOOS::const_iterator it_hash_set_voos = aeroporto->getConstRefHashSetVoos().begin();
	HASH_SET_VOOS::const_iterator it_hash_set_voos_end = aeroporto->getConstRefHashSetVoos().end();

	while (it_hash_set_voos != it_hash_set_voos_end) {
		if ((data_inicio < (*it_hash_set_voos)->getDatahoraSaida()) && ((*it_hash_set_voos)->getDatahoraSaida() < data_fim))
			taxa_total += (aeroporto->getTaxaPortasEmbarque() * (*it_hash_set_voos)->getNumeroPassageiros()); //<<<<<<<<<<<< cálculo da taxa

		++it_hash_set_voos;
	}

	cout << "A taxa de utilização das portas de embarque entre " << data_inicio << " e " << data_fim << " é de " << taxa_total << " euros.\n" << endl;
	getch();
}


void CRUD::listTaxasPortasEmbarqueVooEntreDatas(Aeroporto *aeroporto) {
	DataHora data_inicio, data_fim;
	data_inicio.getDataHoraCin("Introduza o limite inferior (data de saída do voo) a usar na pesquisa:\n(AAAA/MM/DD HH:mm): ");
	data_fim.getDataHoraCin("Introduza o limite superior (data de saída do voo) a usar na pesquisa:\n(AAAA/MM/DD HH:mm): ");

	HASH_SET_VOOS::const_iterator it_hash_set_voos = aeroporto->getConstRefHashSetVoos().begin();
	HASH_SET_VOOS::const_iterator it_hash_set_voos_end = aeroporto->getConstRefHashSetVoos().end();

	vector <Voo*> vec_voos;

	//Construção do vector de Voo* a partir dos voos fechados que têm uma data de partida compatível com os limites introduzidos pelo utilizador
	while(it_hash_set_voos != it_hash_set_voos_end) {
		if ((data_inicio < (*it_hash_set_voos)->getDatahoraSaida()) && ((*it_hash_set_voos)->getDatahoraSaida() < data_fim))
			vec_voos.push_back(*it_hash_set_voos);

		++it_hash_set_voos;
	}


	if (vec_voos.empty()) {
		cout << "\nNenhum voo está compreendido entre as datas que introduziu!\n" << endl;
		getch();
		return;
	}


	Companhia companhia_temp;
	companhia_temp.setVoos(vec_voos);

	cout << "\nSelecione o voo do qual pretende ver a taxa:\n\n" << endl;
	Voo *voo_selecionado = selPlanoVooPtr(&companhia_temp);

	unsigned taxa_voo = aeroporto->getTaxaPortasEmbarque() * voo_selecionado->getNumeroPassageiros(); //<<<<<<<<<<<< cálculo da taxa

	cout << "A taxa de utilização da porta de embarque para o voo selecionado é de " << taxa_voo << " euros.\n" << endl;
	getch();
}


void CRUD::listTaxasPortasEmbarqueVoosEntreDatas(Aeroporto *aeroporto) {
	DataHora data_inicio, data_fim;
	data_inicio.getDataHoraCin("Introduza o limite inferior (data de saída dos voos) a usar na pesquisa:\n(AAAA/MM/DD HH:mm): ");
	data_fim.getDataHoraCin("Introduza o limite superior (data de saída dos voos) a usar na pesquisa:\n(AAAA/MM/DD HH:mm): ");

	HASH_SET_VOOS::const_iterator it_hash_set_voos = aeroporto->getConstRefHashSetVoos().begin();
	HASH_SET_VOOS::const_iterator it_hash_set_voos_end = aeroporto->getConstRefHashSetVoos().end();

	vector <Voo*> vec_voos;

	//Construção do vector de Voo* a partir dos voos fechados que têm uma data de partida compatível com os limites introduzidos pelo utilizador
	while(it_hash_set_voos != it_hash_set_voos_end) {
		if ((data_inicio < (*it_hash_set_voos)->getDatahoraSaida()) && ((*it_hash_set_voos)->getDatahoraSaida() < data_fim))
			vec_voos.push_back(*it_hash_set_voos);

		++it_hash_set_voos;
	}


	if (vec_voos.empty()) {
		cout << "\nNenhum voo está compreendido entre as datas que introduziu!\n" << endl;
		getch();
		return;
	}


	string title("Listagem dos voos e respectivas taxas de utilização das portas de embarque");

	vector < vector <string> > colunas;
	colunas.push_back(vector <string> ());
	colunas.push_back(vector <string> ());
	colunas.push_back(vector <string> ());
	colunas.push_back(vector <string> ());

	vector <string> colnames;
	colnames.push_back("Origem");
	colnames.push_back("Destino");
	colnames.push_back("Data de saida");
	colnames.push_back("Taxa de utilização");

	unsigned taxa_utilizacao_voo;
	for (size_t i(0); i < vec_voos.size(); ++i) {
		taxa_utilizacao_voo = aeroporto->getTaxaPortasEmbarque() * vec_voos[i]->getNumeroPassageiros(); //<<<<<<<<<<<< cálculo da taxa

		colunas[0].push_back(vec_voos[i]->getOrigem());
		colunas[1].push_back(vec_voos[i]->getDestino());
		colunas[2].push_back(to_string(vec_voos[i]->getDatahoraSaida()));
		colunas[3].push_back(to_string(taxa_utilizacao_voo));
	}

	printMenu(title, colunas, colnames, false, false, false, false);
	getch();
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Porta embarque <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void CRUD::addPortaEmbarque(Aeroporto *aeroporto) {
	cout << endl << endl;
	string numero;				//Ex: P01
	string localizacao;			//Ex: Norte
	unsigned capacidade_pass;		//Ex: 250
	unsigned categoria_avioes;	//Ex: Médio Curso
	Voo *voo_actual(NULL);

	cout << "Introduza o número da porta: " << flush;
	getlineCin(numero);

	cout << "Introduza a localização: " << flush;
	getlineCin(localizacao);

	capacidade_pass = get_uint_cin<unsigned>("Introduza a capacidade máxima de passageiros: ");


	cout << "Categorias de Aviões a associar à Porta de Embarque:\n" << endl;
	PortaEmbarque::listCategoriasAvioesInfo();
	categoria_avioes = get_uint_cin <unsigned>("Introduza a categoria dos aviões:\n", PortaEmbarque::getRefCategoriasAvioesInfo().size(), 0, false);


	cout << endl;

	bool adic_voo = get_yes_no("Pretende adicionar um voo a este avião?\n(S/N): ");
	if (adic_voo) {
		cout << "Selecione o voo associado a este avião: " << endl;
		voo_actual = selPlanoVooPtr(companhia_actual);
	}

	cout << endl;

	PortaEmbarque* porta = new PortaEmbarque(numero, localizacao, capacidade_pass, capacidade_pass, categoria_avioes);

	try
	{
		addPortaEmbarque(aeroporto, porta);

	} catch (ExElementAlreadyExists<PortaEmbarque> &e) {
		delete porta;
		cout << e.what() << endl;
	}

	cout << endl << endl <<"Adicionado com sucesso!" << endl << endl << endl;
	getch();
}


void CRUD::addPortaEmbarque(Aeroporto *aeroporto, PortaEmbarque* porta) {
	BST <PortaEmbarquePtr>& bst_portas = aeroporto->getRefPortasEmbarqueBST();

	PortaEmbarquePtr portaPtr( porta );

	if ( !(bst_portas.find(portaPtr) == porta_embarque_null) )
		throw ExElementAlreadyExists <PortaEmbarque> (*porta);

	bst_portas.insert(portaPtr);
}



bool CRUD::cmpPortaEmbarqueNumero(const PortaEmbarque *obj1, const PortaEmbarque *obj2) {
	return (obj1->getNumero() < obj2->getNumero());
}

bool CRUD::cmpPortaEmbarqueLocalizacao(const PortaEmbarque *obj1, const PortaEmbarque *obj2) {
	return (obj1->getLocalizacao() < obj2->getLocalizacao());
}

bool CRUD::cmpPortaEmbarqueCapacidadePass(const PortaEmbarque *obj1, const PortaEmbarque *obj2) {
	return (obj1->getCapacidadePass() < obj2->getCapacidadePass());
}

bool CRUD::cmpPortaEmbarqueCategoriaAvioes(const PortaEmbarque *obj1, const PortaEmbarque *obj2) {
	return (obj1->getCategoriaAvioes() < obj2->getCategoriaAvioes());
}


size_t CRUD::listPortaEmbarque(Aeroporto *aeroporto, bool final_pause, bool no_order) {
	cout << endl << endl;
	BST <PortaEmbarquePtr>& bst_portas = aeroporto->getRefPortasEmbarqueBST();

	if (bst_portas.isEmpty()) {
		throw ExEmptyVector("Não existem portas de embarque no aeroporto!");
	}

	//Selecção do método de ordenação
	string str_title_ordenacao = "Método de ordenação";

	vector <string> colNames_ordenacao;
	colNames_ordenacao.push_back(string("Critério de ordenação"));

	vector < vector<string> > col_ordenacao;
	vector <string> parametros_ordenacao;
	parametros_ordenacao.push_back((string)"Número");
	parametros_ordenacao.push_back((string)"Localização");
	parametros_ordenacao.push_back((string)"Capacidade");
	parametros_ordenacao.push_back((string)"Categoria");
	parametros_ordenacao.push_back((string)"Vagas");
	col_ordenacao.push_back(parametros_ordenacao);

	if(!no_order)
		printMenu(str_title_ordenacao, col_ordenacao, colNames_ordenacao);

	vector <string> colNames;

	cout << endl;

	size_t metodo = 0;

	if(!no_order)
		metodo = get_uint_cin("Selecione o critério de ordenação que quer usar: ", parametros_ordenacao.size());

	cout << endl;

	//Listagem ordenada das portas de embarque
	string str_title = "Lista de portas de embarque";
	vector < vector<string> > col;

	col.push_back(vector<string> ());
	col.push_back(vector<string> ());
	col.push_back(vector<string> ());
	col.push_back(vector<string> ());
	col.push_back(vector<string> ());

	size_t size = 0;



	vector<PortaEmbarque* > vec_portas;
	BSTItrIn<PortaEmbarquePtr> it(bst_portas);
	while (!it.isAtEnd())
	{
		vec_portas.push_back( it.retrieve()() );

		it.advance();

		++size;
	}

	//Ordenação do vector de acordo com o parâmetro fornecido
	switch (metodo) {
		case 0: {
			if(!no_order)
				sort(vec_portas.begin(), vec_portas.end(), cmpPortaEmbarqueNumero);
			colNames.push_back((string)"Número");
			colNames.push_back((string)"Localização");
			colNames.push_back((string)"Capacidade");
			colNames.push_back((string)"Vagas");
			colNames.push_back((string)"Categoria");

			size_t i = 0;
			for (vector <PortaEmbarque*>::const_iterator it_porta = vec_portas.begin(); it_porta != vec_portas.end(); ++it_porta) {
				col[i++].push_back((*it_porta)->getNumero());
				col[i++].push_back((*it_porta)->getLocalizacao());
				col[i++].push_back( to_string( (*it_porta)->getCapacidadePass() ) );
				col[i++].push_back( to_string( (*it_porta)->getVagasPass() ) );
				col[i].push_back( PortaEmbarque::getInfoEnumCategoriasAvioes((*it_porta)->getCategoriaAvioes()) );
				i = 0;
			}

			break;
		}

		case 1: {
			sort(vec_portas.begin(), vec_portas.end(), cmpPortaEmbarqueLocalizacao);
			colNames.push_back((string)"Localização");
			colNames.push_back((string)"Número");
			colNames.push_back((string)"Capacidade");
			colNames.push_back((string)"Vagas");
			colNames.push_back((string)"Categoria");

			size_t i = 0;
			for (vector <PortaEmbarque*>::const_iterator it_porta = vec_portas.begin(); it_porta != vec_portas.end(); ++it_porta) {
				col[i++].push_back((*it_porta)->getLocalizacao());
				col[i++].push_back((*it_porta)->getNumero());
				col[i++].push_back( to_string( (*it_porta)->getCapacidadePass() ) );
				col[i++].push_back( to_string( (*it_porta)->getVagasPass() ) );
				col[i].push_back( PortaEmbarque::getInfoEnumCategoriasAvioes((*it_porta)->getCategoriaAvioes()) );
				i = 0;
			}

			break;
		}

		case 2: {
			sort(vec_portas.begin(), vec_portas.end(), cmpPortaEmbarqueCapacidadePass);
			colNames.push_back((string)"Capacidade");
			colNames.push_back((string)"Vagas");
			colNames.push_back((string)"Número");
			colNames.push_back((string)"Localização");
			colNames.push_back((string)"Categoria");

			size_t i = 0;
			for (vector <PortaEmbarque*>::const_iterator it_porta = vec_portas.begin(); it_porta != vec_portas.end(); ++it_porta) {
				col[i++].push_back( to_string( (*it_porta)->getCapacidadePass() ) );
				col[i++].push_back( to_string( (*it_porta)->getVagasPass() ) );
				col[i++].push_back((*it_porta)->getNumero());
				col[i++].push_back((*it_porta)->getLocalizacao());
				col[i].push_back( PortaEmbarque::getInfoEnumCategoriasAvioes((*it_porta)->getCategoriaAvioes()) );
				i = 0;
			}
			break;
		}

		case 3: {
			sort(vec_portas.begin(), vec_portas.end(), cmpPortaEmbarqueCategoriaAvioes);
			colNames.push_back((string)"Categoria");
			colNames.push_back((string)"Número");
			colNames.push_back((string)"Localização");
			colNames.push_back((string)"Capacidade");
			colNames.push_back((string)"Vagas");

			size_t i = 0;
			for (vector <PortaEmbarque*>::const_iterator it_porta = vec_portas.begin(); it_porta != vec_portas.end(); ++it_porta) {
				col[i++].push_back( PortaEmbarque::getInfoEnumCategoriasAvioes((*it_porta)->getCategoriaAvioes()) );
				col[i++].push_back((*it_porta)->getNumero());
				col[i++].push_back((*it_porta)->getLocalizacao());
				col[i++].push_back( to_string( (*it_porta)->getCapacidadePass() ) );
				col[i].push_back( to_string( (*it_porta)->getVagasPass() ) );
				i = 0;
			}
			break;
		}

		case 4: {
			sort(vec_portas.begin(), vec_portas.end(), cmpPortaEmbarqueCategoriaAvioes);
			colNames.push_back((string)"Vagas");
			colNames.push_back((string)"Categoria");
			colNames.push_back((string)"Número");
			colNames.push_back((string)"Localização");
			colNames.push_back((string)"Capacidade");

			size_t i = 0;
			for (vector <PortaEmbarque*>::const_iterator it_porta = vec_portas.begin(); it_porta != vec_portas.end(); ++it_porta) {
				col[i++].push_back( to_string( (*it_porta)->getVagasPass() ) );
				col[i++].push_back( PortaEmbarque::getInfoEnumCategoriasAvioes((*it_porta)->getCategoriaAvioes()) );
				col[i++].push_back((*it_porta)->getNumero());
				col[i++].push_back((*it_porta)->getLocalizacao());
				col[i].push_back( to_string( (*it_porta)->getCapacidadePass() ) );
				i = 0;
			}
			break;
		}
	}




	printMenu(str_title, col, colNames, true);

	if (final_pause)
		getch();

	return size;
}


size_t CRUD::selPortaEmbarque(Aeroporto *aeroporto) {
	size_t size = listPortaEmbarque(aeroporto,true,true);
	cout << endl;
	size_t indice = get_uint_cin<size_t>("\nIntroduza o índice da porta de embarque (ou 0 para retroceder): ", size, 0, true);
	porta_embarque_actual = selPortaEmbarque(aeroporto, indice);
	return indice;
}


PortaEmbarque* CRUD::selPortaEmbarquePtr(Aeroporto *aeroporto) {
	return selPortaEmbarque( aeroporto, selPortaEmbarque(aeroporto) );
}

PortaEmbarque* CRUD::selPortaEmbarque(Aeroporto *aeroporto, size_t index) {

	BSTItrIn<PortaEmbarquePtr> it( aeroporto->getConstRefPortasEmbarqueBST() );
	size_t i = 0;
	while (!it.isAtEnd() && i<index)
	{
		it.advance();
		++i;
	}

	return it.retrieve()();
}

void CRUD::infoPortaEmbarque(Aeroporto *aeroporto) {
	cout << endl << endl;

	PortaEmbarque *porta_embarque = selPortaEmbarquePtr(aeroporto);

	string str_title = "Informações sobre a porta de embarque";

	vector <string> colNames;					// nomes de colunas não são usados, logo vão strings vazias
	colNames.push_back(string(""));
	colNames.push_back(string(""));

	vector < vector<string> > col;
	vector <string> dados;

	//Nomes dos atributos
	col.push_back(Comandos::_portas_embarque_op_list);

	dados.push_back( porta_embarque->getNumero() );
	dados.push_back( porta_embarque->getLocalizacao() );
	dados.push_back( to_string<unsigned>(porta_embarque->getCapacidadePass()) );
	dados.push_back( PortaEmbarque::getInfoEnumCategoriasAvioes( porta_embarque->getCategoriaAvioes() ) );

	//Dados relativos aos atributos
	col.push_back(dados);

	printMenu(str_title, col, colNames, false, false, true, true);

	Companhia companhia_temp;
	companhia_temp.setVoos(porta_embarque->getRefVoosPortaEmbarque());

	cout << "\nSelecione o voo sobre o qual pretende ver informações:\n" << endl;
	infoPlanoVoo(&companhia_temp);

	getch();
}


void CRUD::editPortaEmbarque(Aeroporto *aeroporto) {

	PortaEmbarque* porta = selPortaEmbarquePtr(aeroporto);

	bool continuar;
	do {
		cout << endl << endl;
		//Selecção da porta de embarque

		//Escolha do atributo a editar
		string titulo("Atributos das portas de embarque: ");
		string col_name("Atributos");
		vector <string> nome_coluna;
		nome_coluna.push_back(col_name);

		vector < vector <string> > colunas;
		colunas.push_back(Comandos::_portas_embarque_op_list);


		printMenu(titulo, colunas, nome_coluna);


		cout << endl << endl;
		size_t indice_atributo = get_uint_cin("Escolha o atributo que quer editar: ", Comandos::_portas_embarque_op_list.size());
		cout << endl << endl;

		string str_temp;
		unsigned uns_temp;

		aeroporto->getRefPortasEmbarqueBST().remove(porta);	// remove da BST para voltar a introduzir

		//Edição do atributo escolhido
		switch (indice_atributo) {
			case 0: {
				cout << "Introduza o novo número da porta de embarque: ";
				getlineCin(str_temp);
				porta->setNumero(str_temp);
				break;
			}

			case 1: {
				cout << "Introduza a nova localização da porta de embarque: ";
				getlineCin(str_temp);
				porta->setLocalizacao(str_temp);
				break;
			}

			case 2: {
				uns_temp = get_uint_cin<unsigned>("Introduza a nova capacidade da porta de embarque: ");
				porta->setCapacidadePass(uns_temp);
				break;
			}

			case 3: {
				cout << "Categorias de Aviões a associar à Porta de Embarque:\n" << endl;
				PortaEmbarque::listCategoriasAvioesInfo();
				unsigned uns_temp = get_uint_cin <unsigned>("Introduza a nova categoria da porta de embarque:\n", PortaEmbarque::getRefCategoriasAvioesInfo().size(), 0, false);
				porta->setCategoriaAvioes(uns_temp);
				break;
			}
		}

		//Pergunta ao utilizador se quer continuar a editar a porta de embarque
		continuar = get_yes_no("\n\nDeseja continuar a editar esta porta de embarque (S/N): ");

	} while (continuar);

	aeroporto->getRefPortasEmbarqueBST().insert(porta);	// actualiza (e mantém o endereço)
}



PortaEmbarque* CRUD::updatePortaEmbarqueDisp(Aeroporto *aeroporto, unsigned capacidade_pass, unsigned categoria) {

	BST<PortaEmbarquePtr>& portas = aeroporto->getRefPortasEmbarqueBST();

	if( portas.isEmpty() )
	{
		throw ExEmptyVector("Não existem portas de embarque no aeroporto!");
	}
	else
	{
		BSTItrIn<PortaEmbarquePtr> it_bast_in(portas);

		while (it_bast_in.retrieve()()->getCategoriaAvioes() != categoria) {

			it_bast_in.advance();

			if (it_bast_in.isAtEnd()) {
				throw ExElementDoesntExists<PortaEmbarque*>(it_bast_in.retrieve()(), "Não existe portas de embarque para esta categoria de aviões com vagas suficientes.");
			}
		}

		PortaEmbarquePtr porta_embarque = it_bast_in.retrieve();

		unsigned vagas = porta_embarque()->getVagasPass();

		if(vagas < capacidade_pass)
			throw ExPortasFull();

		portas.remove(porta_embarque);

		porta_embarque()->setVagasPass( porta_embarque()->getVagasPass() - capacidade_pass );

		portas.insert(porta_embarque);

		return porta_embarque();
	}
}

void CRUD::delPortaEmbarque(Aeroporto *aeroporto) {
	try {
		size_t indice = selPortaEmbarque(aeroporto);
		delPortaEmbarque(aeroporto, indice);
		cout << endl << endl;
		cout << "Removido com sucesso!" << endl;
	} catch (exception & e) {
		cout << endl << endl;
		cout << e.what() << endl;
		cout << endl << endl;
	}

	getch();
}


void CRUD::delPortaEmbarque(Aeroporto *aeroporto, size_t indice) {

	BSTItrIn<PortaEmbarquePtr> it( aeroporto->getConstRefPortasEmbarqueBST() );
	size_t i = 0;
	while (!it.isAtEnd() && i<indice)
	{
		it.advance();
		++i;
	}

	if ( it.isAtEnd() )
		throw ExOutOfRange();

	//Caso a porta de embarque não esteja associado a um voo, a porta de embarque é eliminada
	if ( it.retrieve()()->getVoosPortaEmbarque().empty()) {
		PortaEmbarque* del = it.retrieve()();
		aeroporto->getRefPortasEmbarqueBST().remove( it.retrieve()() );
		delete del;
	}
	else
		//Caso contrário é lançada uma excepção dizendo que esse elemento está a ser usado e não pode ser eliminado
		throw ExElementInUse <vector <Voo*> >(it.retrieve()()->getVoosPortaEmbarque());
}


void CRUD::delPortaEmbarquePtr(Aeroporto *aeroporto, PortaEmbarque *porta_ptr) {

	//Caso a porta de embarque não esteja associado a um voo, a porta de embarque é eliminada
	if (porta_ptr->getVoosPortaEmbarque().empty()) {
		//Caso contrário é lançada uma excepção dizendo que esse elemento está a ser usado e não pode ser eliminado
		throw ExElementInUse <vector <Voo*> >(porta_ptr->getVoosPortaEmbarque());
	}

	aeroporto->getRefPortasEmbarqueBST().remove( porta_ptr );
	delete &porta_ptr;

	//Caso contrário é lançada uma excepção dizendo que esse elemento não existe
	throw ExElementDoesntExists <PortaEmbarque> (*porta_ptr);
}


void CRUD::delVooPtrPortaEmbarque(PortaEmbarque *porta_embarque, Voo *voo_a_remover) {
	vector <Voo*>::iterator it_remover = find((*porta_embarque).getRefVoosPortaEmbarque().begin(), (*porta_embarque).getRefVoosPortaEmbarque().end(), voo_a_remover);

	if (it_remover != (*porta_embarque).getRefVoosPortaEmbarque().end())
		(*porta_embarque).getRefVoosPortaEmbarque().erase(it_remover);
}


///////////////////////////

void CRUD::addTripulanteVoo(Companhia* companhia)
{
	cout << endl << endl;
	Voo* voo = selPlanoVooPtr(companhia);

	bool continuar = true;
	do {
		Tripulante* tripulante = selTripulantePtr(companhia);

		try{
			addTripulanteVoo(voo, tripulante);

		} catch (ExElementAlreadyExists<Tripulante> &e) {
			delete tripulante;
			cout << e.what() << endl;
		}

		//Pergunta ao utilizador se quer continuar a editar o avião
		continuar = get_yes_no("\n\nDeseja continuar a adicionar tripulantes a este voo (S/N): ");

	} while (continuar);
}

void CRUD::addTripulanteVoo(Voo* voo, Tripulante *tripulante)
{
	vector<Tripulante* >::const_iterator it;

	for (it = voo->getRefTripulantesVoo().begin(); it != voo->getRefTripulantesVoo().end(); ++it)
		if ((*tripulante) == *(*it))
			throw ExElementAlreadyExists<Tripulante> (*tripulante);

	voo->getRefTripulantesVoo().push_back(tripulante);
}

void CRUD::listTripulanteVoo(Voo* voo, bool final_pause) {
	cout << endl << endl;
	vector <Tripulante*> &vec_tripulacao = voo->getRefTripulantesVoo();

	if (vec_tripulacao.size() == 0) {
		throw ExEmptyVector("Não existem tripulantes no voo!");
	}

	//Selecção do método de ordenação
	string str_title_ordenacao = "Método de ordenação";

	vector <string> colNames_ordenacao;
	colNames_ordenacao.push_back((string)"Critério de ordenação");

	vector < vector<string> > col_ordenacao;
	vector <string> parametros_ordenacao;
	parametros_ordenacao.push_back((string)"Nome");
	parametros_ordenacao.push_back((string)"Número (ID)");
	parametros_ordenacao.push_back((string)"Categoria");
	parametros_ordenacao.push_back((string)"Salário / hora");
	parametros_ordenacao.push_back((string)"Número de horas de trabalho");
	parametros_ordenacao.push_back((string)"Tipo de contrato");
	parametros_ordenacao.push_back((string)"Data de expiração do contrato");
	col_ordenacao.push_back(parametros_ordenacao);

	printMenu(str_title_ordenacao, col_ordenacao, colNames_ordenacao);

	vector <string> colNames;
	colNames.push_back((string)"Nome");


	cout << endl << endl;
	size_t metodo = get_uint_cin("Selecione o critério de ordenação que quer usar: ", parametros_ordenacao.size());
	cout << endl << endl;

	//Listagem ordenada para os tripulantes
	string str_title = "Lista de tripulantes";
	vector < vector<string> > col;

	col.push_back(vector<string> ());
	col.push_back(vector<string> ());

	cout << endl;

	//Ordenação do vector de acordo com o parâmetro fornecido
	switch (metodo) {
		case 0: {
			sort(vec_tripulacao.begin(), vec_tripulacao.end(), cmpTripulanteNome);
			colNames.push_back((string)"Número (ID)");
			size_t i0 = 0;
			for (vector<Tripulante*>::const_iterator it_tripulante0 = vec_tripulacao.begin(); it_tripulante0 != vec_tripulacao.end(); ++it_tripulante0) {
				col[i0++].push_back((*it_tripulante0)->getNome());
				col[i0].push_back(to_string((*it_tripulante0)->getNumero()));
				i0 = 0;
			}
			break;
		}


		case 1: {
			sort(vec_tripulacao.begin(), vec_tripulacao.end(), cmpTripulanteNumero);
			colNames.push_back((string)"Número (ID)");
			size_t i1 = 0;
			for (vector<Tripulante*>::const_iterator it_tripulante1 = vec_tripulacao.begin(); it_tripulante1 != vec_tripulacao.end(); ++it_tripulante1) {
				col[i1++].push_back((*it_tripulante1)->getNome());
				col[i1].push_back(to_string((*it_tripulante1)->getNumero()));
				i1 = 0;
			}

			break;
		}

		case 2: {
			sort(vec_tripulacao.begin(), vec_tripulacao.end(), cmpTripulanteCategoria);
			colNames.push_back((string)"Categoria");
			size_t i2 = 0;
			for (vector<Tripulante*>::const_iterator it_tripulante2 = vec_tripulacao.begin(); it_tripulante2 != vec_tripulacao.end(); ++it_tripulante2) {
				col[i2++].push_back((*it_tripulante2)->getNome());
				col[i2++].push_back((*it_tripulante2)->getCategoria());
				i2 = 0;
			}

			break;
		}

		case 3: {
			sort(vec_tripulacao.begin(), vec_tripulacao.end(), cmpTripulanteSalarioHora);
			colNames.push_back((string)"Salário / hora");
			size_t i3 = 0;
			for (vector<Tripulante*>::const_iterator it_tripulante3 = vec_tripulacao.begin(); it_tripulante3 != vec_tripulacao.end(); ++it_tripulante3) {
				col[i3++].push_back((*it_tripulante3)->getNome());
				col[i3].push_back(to_string((*it_tripulante3)->getSalarioHora()));
				i3 = 0;
			}
			break;
		}

		case 4: {
			sort(vec_tripulacao.begin(), vec_tripulacao.end(), cmpTripulanteNumeroHorasTrabalho);
			colNames.push_back((string)"Número de horas de trabalho");
			size_t i4 = 0;
			for (vector<Tripulante*>::const_iterator it_tripulante4 = vec_tripulacao.begin(); it_tripulante4 != vec_tripulacao.end(); ++it_tripulante4) {
				col[i4++].push_back((*it_tripulante4)->getNome());
				col[i4].push_back(to_string((*it_tripulante4)->getNumeroHorasTrabalho()));
				i4 = 0;
			}
			break;
		}

		case 5: {
			sort(vec_tripulacao.begin(), vec_tripulacao.end(), cmpTripulanteTipoContrato);
			colNames.push_back((string)"Tipo de contrato");
			size_t i5 = 0;
			for (vector<Tripulante*>::const_iterator it_tripulante5 = vec_tripulacao.begin(); it_tripulante5 != vec_tripulacao.end(); ++it_tripulante5) {
				col[i5++].push_back((*it_tripulante5)->getNome());
				col[i5].push_back((*it_tripulante5)->getTipoContrato());
				i5 = 0;
			}

			break;
		}

		case 6: {
			sort(vec_tripulacao.begin(), vec_tripulacao.end(), cmpTripulanteExpiracaoContrato);
			colNames.push_back((string)"Data de expiração do contrato");
			size_t i6 = 0;
			for (vector<Tripulante*>::const_iterator it_tripulante6 = vec_tripulacao.begin(); it_tripulante6 != vec_tripulacao.end(); ++it_tripulante6) {
				col[i6++].push_back((*it_tripulante6)->getNome());
				stringstream str_temp;
				str_temp << (*it_tripulante6)->getExpiracaoContrato();
				col[i6].push_back(str_temp.str());
				i6 = 0;
			}

			break;
		}
	}



	printMenu(str_title, col, colNames, true);

	if (final_pause)
		getch();
}

size_t CRUD::selTripulanteVoo(Voo* voo)
{
	listTripulanteVoo(voo);
	cout << endl << endl;
	size_t indice = get_uint_cin<size_t>("\nintroduza o índice:",voo->getRefTripulantesVoo().size(), 0, true);
	return indice;
}

Tripulante* CRUD::selTripulanteVooPtr(Voo* voo)
{
	return voo->getRefTripulantesVoo()[ selTripulanteVoo(voo) ];
}

void CRUD::delTripulanteVoo(Voo* voo)
{
	try {
		size_t indice = selTripulanteVoo(voo);

		delTripulanteVoo(voo, indice);

		cout << endl << endl;
		cout << "Removido com sucesso!" << endl;
	} catch (exception & e) {
		cout << e.what() << endl;
	}

	getch();
}

void CRUD::delTripulanteVoo(Voo* voo, size_t indice)
{
	if( (indice <0) && (indice>=voo->getRefTripulantesVoo().size()) )
		throw ExOutOfRange();

	vector<Tripulante* >::iterator it = voo->getRefTripulantesVoo().begin();

	delete *(it + indice);
	voo->getRefTripulantesVoo().erase(it + indice);
}



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Loads e saves <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


/// Carrega os dados do ficheiro por defeito.
void CRUD::loaddb()
{
	loaddb(FILE_SAVE_DB);
}

/// Carrega os dados do ficheiro fornecido como parametro.
void CRUD::loaddb(string filename)
{
	ifstream file;
	file.open(filename.c_str());

	if (file.is_open())
    {
		string linha;
		vector<string> str;

		getline(file,linha);
		str = split(linha,SAVE_DELIM);				// carrega dados guardados

		if( str.size() != CLASS_AEROPORTO_ATTR_SIZE)
			throw ExCorruptedFile();

		//unsigned a = 0;

		// ***************************** aeroporto

		aeroporto.setNome(str[0]);
		aeroporto.setLocalizacao(str[1]);
		aeroporto.setPais(str[2]);
		aeroporto.setTaxaPortasEmbarque( atoi(str[3].c_str()) );

		size_t n_com = atoi(str[4].c_str());
		size_t n_pem = atoi(str[5].c_str());
		size_t n_pas = atoi(str[6].c_str());
		size_t n_hash = atoi(str[7].c_str());

		// ***************************** companhias
		for(size_t i=0 ; i<n_com ; ++i)
		{
			//unsigned b = 0;

			getline(file,linha);
			str = split(linha,SAVE_DELIM);

			if( str.size() != CLASS_COMPANHIA_ATTR_SIZE)
				throw ExCorruptedFile();

			Companhia* com = new Companhia(str[0],
				str[1],
				atoi(str[2].c_str()));

			addCompanhia(&aeroporto, com);

			size_t n_av = atoi(str[3].c_str());
			size_t n_tr = atoi(str[4].c_str());
			size_t n_voo = atoi(str[5].c_str());
			size_t n_fro = atoi(str[6].c_str());

			// ***************************** aviões de companhias
			for(size_t j=0 ; j<n_av ; ++j)
			{
				//unsigned c = 0;

				getline(file,linha);
				str = split(linha,SAVE_DELIM);

				if( str.size() != CLASS_AVIAO_ATTR_SIZE)
					throw ExCorruptedFile();

				Aviao* avi = new Aviao(str[0],
					str[1],
					atoi(str[2].c_str()),
					getVectorElem( tipo_aviao_DB.getRefTiposAviao(), atoi(str[3].c_str()) ),
					0,
					0,
					DataHora( str[6] ),
					DataHora( str[7] ),
					DataHora( str[8] ),
					DataHora( str[9] ) );

				addAviao(com, avi);
			}

			// ***************************** tripulantes da companhia
			for(size_t j=0 ; j<n_tr ; ++j)
			{
				//unsigned c = 0;

				getline(file,linha);
				str = split(linha,SAVE_DELIM);

				if( str.size() != CLASS_TRIPULANTE_ATTR_SIZE)
					throw ExCorruptedFile();

				Tripulante* tr = new Tripulante(
					str[0],
					str[1],
					str[2],
					atoi(str[3].c_str()),
					atoi(str[4].c_str()),
					atoi(str[5].c_str()),
					atoi(str[6].c_str()),
					str[7],
					atoi(str[8].c_str()),
					atoi(str[9].c_str()),
					str[10],
					DataHora( str[11] ),
					0,
					0 );

				addTripulante(com, tr);
			}

			// ***************************** voos da companhia
			for(size_t j=0 ; j<n_voo ; ++j)
			{
				//unsigned c = 0;

				getline(file,linha);
				str = split(linha,SAVE_DELIM);

				if( str.size() != CLASS_VOO_ATTR_SIZE)
					throw ExCorruptedFile();

				Voo* voo = new Voo(
					atoi(str[0].c_str()),
					str[1],
					str[2],
					DataHora( str[3] ),
					DataHora( str[4] ),
					atoi( str[5].c_str() ),
					0,
					0,
					0,
					atoi( str[9].c_str() ),
					( atoi( str[10].c_str() ) > 0 ? true : false ) );

				addPlanoVoo(com, voo);

				// ***************************** passageiros e tripulantes (le em branco)
				size_t n_pass_v = atoi(str[11].c_str());
				size_t n_pass_q = atoi(str[12].c_str());
				size_t n_pass_pq = atoi(str[13].c_str());
				size_t n_trip_v = atoi(str[14].c_str());

				if(n_pass_v>0 )
				{
					getline(file,linha);
				}

				if(n_pass_q>0 )
				{
					getline(file,linha);
				}

				if(n_pass_pq>0 )
				{
					getline(file,linha);
				}

				if(n_trip_v>0 )
				{
					getline(file,linha);
				}
			}

			// ***************************** tipos de aviao
			if(n_fro>0 )
			{
				//unsigned c = 0;

				getline(file,linha);
				str = split(linha,SAVE_DELIM);

				//if( str.size() != CLASS_FROTA_ATTR_SIZE)
				//	throw ExCorruptedFile();

				for(size_t k=0 ; k<str.size() ; ++k)
				{
					com->getRefFrota()[k] = getVectorElem( tipo_aviao_DB.getRefTiposAviao(), atoi(str[k].c_str()) );
				}
			}
		}

		// ***************************** portas de embarque
		for(size_t i=0 ; i<n_pem ; ++i)
		{
			//unsigned b = 0;

			getline(file,linha);
			str = split(linha,SAVE_DELIM);

			if( str.size() != CLASS_PORTAE_ATTR_SIZE)
				throw ExCorruptedFile();

			PortaEmbarque* pem = new PortaEmbarque(str[0],
				str[1],
				atoi(str[2].c_str()),
				atoi(str[3].c_str()),
				atoi(str[4].c_str()));

			// ****************** vector voos nas portas de embarque
			if( atoi(str[5].c_str()) > 0 )
				getline(file,linha);

			addPortaEmbarque(&aeroporto, pem);
		}

		// ***************************** passageiros do aeroporto
		for(size_t j=0 ; j<n_pas ; ++j)
		{
			//unsigned c = 0;

			getline(file,linha);
			str = split(linha,SAVE_DELIM);

			if( str.size() != CLASS_PASSAGEIRO_ATTR_SIZE)
				throw ExCorruptedFile();

			Passageiro* pas = new Passageiro(
				str[0],
				str[1],
				str[2],
				atoi(str[3].c_str()),
				atoi(str[4].c_str()),
				atoi(str[5].c_str()),
				atoi(str[6].c_str()),
				atoi(str[7].c_str()),
				atoi(str[8].c_str()),
				0 );

			addPassageiro(&aeroporto, pas);
		}

		// ********************** hash set aponta voos
		if(n_hash>0 )
		{
			getline(file,linha);
		}

		// set dos apontadores
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		file.seekg(0, std::ios::beg);

		getline(file,linha);
		str = split(linha,SAVE_DELIM);				// carrega dados guardados

		if( str.size() != CLASS_AEROPORTO_ATTR_SIZE)
			throw ExCorruptedFile();

		for(size_t i=0 ; i<n_com ; ++i)
		{
			getline(file,linha);
			str = split(linha,SAVE_DELIM);

			if( str.size() != CLASS_COMPANHIA_ATTR_SIZE)
				throw ExCorruptedFile();

			size_t n_av = atoi(str[3].c_str());
			size_t n_tr = atoi(str[4].c_str());
			size_t n_voo = atoi(str[5].c_str());
			size_t n_fro = atoi(str[6].c_str());

			Companhia* com = aeroporto.getRefCompanhias()[i];

			for(size_t j=0 ; j<n_av ; ++j)
			{
				getline(file,linha);
				str = split(linha,SAVE_DELIM);

				if( str.size() != CLASS_AVIAO_ATTR_SIZE)
					throw ExCorruptedFile();

				Aviao* av = com->getAvioes()[j];

				//av->setTipoAviao( getVectorElem( tipo_aviao_DB.getRefTiposAviao(), atoi(str[3].c_str()) ) );
				av->setCompanhia( getVectorElem( aeroporto.getRefCompanhias(), atoi(str[4].c_str()) ) );
				av->setVooActual( getVectorElem( com->getRefVoos(), atoi(str[5].c_str()) ) );

			}

			for(size_t j=0 ; j<n_tr ; ++j)
			{
				getline(file,linha);
				str = split(linha,SAVE_DELIM);

				if( str.size() != CLASS_TRIPULANTE_ATTR_SIZE)
					throw ExCorruptedFile();

				Tripulante* tr = com->getTripulacao()[j];

				tr->setCompanhia( getVectorElem( aeroporto.getRefCompanhias(), atoi(str[12].c_str()) ) );
				//tr->setVooActual( getVectorElem( com->getRefVoos(), atoi(str[13].c_str()) ) );
			}

			for(size_t j=0 ; j<n_voo ; ++j)
			{
				getline(file,linha);
				str = split(linha,SAVE_DELIM);

				if( str.size() != CLASS_VOO_ATTR_SIZE)
					throw ExCorruptedFile();

				Voo* voo = com->getRefVoos()[j];

				voo->setPortaEmbarque( getBSTElem( aeroporto.getRefPortasEmbarqueBST(), atoi(str[6].c_str()) )() );
				voo->setAviao( getVectorElem( com->getRefAvioes(), atoi(str[7].c_str()) ) );
				voo->setCompanhia( getVectorElem( aeroporto.getRefCompanhias(), atoi(str[8].c_str()) ) );

				// ***************************** passageiros e tripulantes (actualiza apontadores)
				size_t n_pass_v = atoi(str[11].c_str());
				size_t n_pass_q = atoi(str[12].c_str());
				size_t n_pass_pq = atoi(str[13].c_str());
				size_t n_trip_v = atoi(str[14].c_str());

				if(n_pass_v>0 )
				{
					getline(file,linha);
					str = split(linha,SAVE_DELIM);

					for(size_t j=0 ; j<str.size() ; ++j)
					{
						voo->getRefPassageirosVoo().push_back(
							getVectorElem( aeroporto.getRefPassageirosAeroporto() ,atoi(str[j].c_str()))  );

						getVectorElem( aeroporto.getRefPassageirosAeroporto() ,atoi(str[j].c_str()))->setVoo( voo );
					}
				}

				if(n_pass_q>0 )
				{
					getline(file,linha);
					str = split(linha,SAVE_DELIM);

					for(size_t j=0 ; j<str.size() ; ++j)
					{
						voo->getRefFilaCheckIn().push(
							getVectorElem( aeroporto.getRefPassageirosAeroporto() ,atoi(str[j].c_str())) );
					}
				}

				if(n_pass_pq>0 )
				{
					getline(file,linha);
					str = split(linha,SAVE_DELIM);

					for(size_t j=0 ; j<str.size() ; ++j)
					{
						voo->getRefPassageirosVooPQ().push(
							getVectorElem( aeroporto.getRefPassageirosAeroporto() ,atoi(str[j].c_str())) );
					}
				}

				if(n_trip_v>0 )
				{
					getline(file,linha);
					str = split(linha,SAVE_DELIM);

					for(size_t j=0 ; j<str.size() ; ++j)
					{
						voo->getRefTripulantesVoo().push_back(
							getVectorElem( com->getRefTripulacao() ,atoi(str[j].c_str())) );
					}
				}
			}

			if( n_fro>0)
			{
				getline(file,linha);
			}
		}

		for(size_t j=0 ; j<n_pem ; ++j)
		{
			getline(file,linha);
			str = split(linha,SAVE_DELIM);

			// ****************** vector voos nas portas de embarque

			if( atoi(str[5].c_str()) > 0 )
			{
				getline(file,linha);
				str = split(linha,SAVE_DELIM);

				for(size_t k=0 ; k<str.size() ; k+=2)
				{
					Companhia *comp = getVectorElem( aeroporto.getRefCompanhias() ,atoi(str[k].c_str()));

					getBSTElem( aeroporto.getRefPortasEmbarqueBST(), j)()->getRefVoosPortaEmbarque().push_back(
						getVectorElem( comp->getRefVoos() ,atoi(str[k+1].c_str()))
						);
				}
			}
		}

		for(size_t j=0 ; j<n_pas ; ++j)
		{
			getline(file,linha);
			str = split(linha,SAVE_DELIM);

			if( str.size() != CLASS_PASSAGEIRO_ATTR_SIZE)
				throw ExCorruptedFile();

			Companhia* com = aeroporto.getCompanhias()[ atoi(str[10].c_str()) ];
			Passageiro* pas = aeroporto.getPassageirosAeroporto()[j];

			pas->setVoo( getVectorElem( com->getRefVoos(), atoi(str[9].c_str()) ) );
		}

		// ***************************** hashset dos voos fechados
		if(n_hash>0 )
		{
			getline(file,linha);
			str = split(linha,SAVE_DELIM);

			for(size_t j=0 ; j<str.size() ; j+=2)
			{
				Companhia *comp = getVectorElem( aeroporto.getRefCompanhias() ,atoi(str[j].c_str()));

				aeroporto.getRefHashSetVoos().insert(
					getVectorElem( comp->getRefVoos() ,atoi(str[j+1].c_str()))
					);
			}
		}

	}

	file.close();

}

/// Grava os dados no ficheiro por defeito.
void CRUD::savedb()
{
	savedb(FILE_SAVE_DB);
}

/// Grava os dados no ficheiro fornecido como parametro.
void CRUD::savedb(string filename)
{
	ofstream file;
    file.open(filename.c_str());

	if (file.is_open())
    {
		// ***************************** aeroporto

		file << aeroporto.getNome() << SAVE_DELIM;
		file << aeroporto.getLocalizacao() << SAVE_DELIM;
		file << aeroporto.getPais() << SAVE_DELIM;
		file << aeroporto.getTaxaPortasEmbarque() << SAVE_DELIM;
		file << aeroporto.getConstRefCompanhias().size() << SAVE_DELIM;
		file << calcBSTSize( aeroporto.getConstRefPortasEmbarqueBST() ) << SAVE_DELIM;
		file << aeroporto.getConstRefPassageirosAeroporto().size() << SAVE_DELIM;
		file << aeroporto.getConstRefHashSetVoos().size() << endl;

		// ***************************** companhia

		for(vector<Companhia* >::const_iterator it=aeroporto.getRefCompanhias().begin() ; it!=aeroporto.getRefCompanhias().end() ; ++it)
		{
			file << (*it)->getSigla() << SAVE_DELIM;
			file << (*it)->getNome() << SAVE_DELIM;
			file << (*it)->getTaxaBalcoes() << SAVE_DELIM;
			file << (*it)->getConstRefAvioes().size() << SAVE_DELIM;
			file << (*it)->getConstRefTripulacao().size() << SAVE_DELIM;
			file << (*it)->getConstRefVoos().size() << SAVE_DELIM;
			file << (*it)->getConstRefFrota().size() << endl;

			// ***************************** avioes da companhia

			for(vector<Aviao* >::const_iterator it2=(*it)->getConstRefAvioes().begin() ; it2!=(*it)->getConstRefAvioes().end() ; ++it2)
			{
				file << (*it2)->getMatricula() << SAVE_DELIM;
				file << (*it2)->getNome() << SAVE_DELIM;
				file << (*it2)->getPesoMaxBagagem() << SAVE_DELIM;

				file << calcVectorIndex( tipo_aviao_DB.getRefTiposAviao(), (*it2)->getTipoAviao() ) << SAVE_DELIM;	//ptr
				file << calcVectorIndex( aeroporto.getRefCompanhias(), (*it2)->getCompanhia() ) << SAVE_DELIM;	//ptr
				file << calcVectorIndex( (*it)->getRefVoos(), (*it2)->getVooActual() ) << SAVE_DELIM;	//ptr
				file << (*it2)->getDataConstrucao() << SAVE_DELIM;
				file << (*it2)->getPrimeiroVoo() << SAVE_DELIM;
				file << (*it2)->getUltimaRevisao() << SAVE_DELIM;
				file << (*it2)->getProximaRevisao() << endl;
			}

			// ***************************** tripulantes da companhia

			for(vector<Tripulante* >::const_iterator it2=(*it)->getConstRefTripulacao().begin() ; it2!=(*it)->getConstRefTripulacao().end() ; ++it2)
			{
				file << (*it2)->getNome() << SAVE_DELIM;
				file << (*it2)->getMorada() << SAVE_DELIM;
				file << (*it2)->getNacionalidade() << SAVE_DELIM;
				file << (*it2)->getContacto() << SAVE_DELIM;
				file << (*it2)->getBI() << SAVE_DELIM;
				file << (*it2)->getIdade() << SAVE_DELIM;

				file << (*it2)->getNumero() << SAVE_DELIM;
				file << (*it2)->getCategoria() << SAVE_DELIM;
				file << (*it2)->getSalarioHora() << SAVE_DELIM;
				file << (*it2)->getNumeroHorasTrabalho() << SAVE_DELIM;

				file << (*it2)->getTipoContrato() << SAVE_DELIM;
				file << (*it2)->getExpiracaoContrato() << SAVE_DELIM;
				file << calcVectorIndex( aeroporto.getRefCompanhias(), (*it2)->getCompanhia() ) << endl;	//ptr
				//file << calcVectorIndex( (*it)->getRefVoos(), (*it2)->getVooActual() ) << endl;	//ptr
			}

			// ***************************** voos

			for(vector<Voo* >::const_iterator it2=(*it)->getConstRefVoos().begin() ; it2!=(*it)->getConstRefVoos().end() ; ++it2)
			{
				file << (*it2)->getNumeroVoo() << SAVE_DELIM;
				file << (*it2)->getOrigem() << SAVE_DELIM;
				file << (*it2)->getDestino() << SAVE_DELIM;
				file << (*it2)->getDatahoraSaida() << SAVE_DELIM;
				file << (*it2)->getDatahoraChegada() << SAVE_DELIM;
				file << (*it2)->getNumeroPassageiros() << SAVE_DELIM;

				PortaEmbarquePtr ppp((*it2)->getPortaEmbarque());

				file << calcBSTIndex( aeroporto.getRefPortasEmbarqueBST(), ppp ) << SAVE_DELIM;	//ptr
				file << calcVectorIndex( (*it)->getRefAvioes(), (*it2)->getAviao() ) << SAVE_DELIM;	//ptr
				file << calcVectorIndex( aeroporto.getRefCompanhias(), (*it2)->getCompanhia() ) << SAVE_DELIM;	//ptr
				file << (*it2)->getAtraso() << SAVE_DELIM;
				file << ( (*it2)->getCancelado() ? 1 : 0 ) << SAVE_DELIM;
				file << (*it2)->getConstRefPassageirosVoo().size() << SAVE_DELIM;
				file << (*it2)->getConstRefFilaCheckIn().size() << SAVE_DELIM;
				file << (*it2)->getConstRefPassageirosVooPQ().size() << SAVE_DELIM;
				file << (*it2)->getConstRefTripulantesVoo().size() << endl;

				// *****************************  passageiros de voo
				size_t cnt = 0;
				for(vector<Passageiro* >::const_iterator it3=(*it2)->getConstRefPassageirosVoo().begin() ; it3!=(*it2)->getConstRefPassageirosVoo().end() ; ++it3)
				{
					++cnt;
					file << calcVectorIndex( aeroporto.getConstRefPassageirosAeroporto(), (*it3) );

					if( ((*it2)->getPassageirosVoo().size() == 1) || ((*it2)->getPassageirosVoo().size() == cnt) )
						file << endl;
					else
						file << SAVE_DELIM;
				}

				// ***************************** passageiros de voo q
				queue <Passageiro*> _fila_check_in = (*it2)->getConstRefFilaCheckIn();

				while( _fila_check_in.size() > 0 )
				{
					file << calcVectorIndex( aeroporto.getConstRefPassageirosAeroporto(), _fila_check_in.front() );

					_fila_check_in.pop();

					if( _fila_check_in.size() == 0 )
						file << endl;
					else
						file << SAVE_DELIM;
				};

				// ***************************** passageiros do voo pq
				priority_queue <Passageiro*> _passageiros_voo_pq = (*it2)->getConstRefPassageirosVooPQ();

				while( _passageiros_voo_pq.size() > 0 )
				{
					file << calcVectorIndex( aeroporto.getConstRefPassageirosAeroporto(), _passageiros_voo_pq.top() );

					_passageiros_voo_pq.pop();

					if( _passageiros_voo_pq.size() == 0 )
						file << endl;
					else
						file << SAVE_DELIM;
				};

				// ***************************** tripulantes do voo
				cnt = 0;
				for(vector<Tripulante* >::const_iterator it3=(*it2)->getConstRefTripulantesVoo().begin() ; it3!=(*it2)->getConstRefTripulantesVoo().end() ; ++it3)
				{
					++cnt;
					file << calcVectorIndex( (*it)->getConstRefTripulacao(), (*it3) );

					if( ((*it2)->getTripulantesVoo().size() == 1) || ((*it2)->getTripulantesVoo().size() == cnt) )
						file << endl;
					else
						file << SAVE_DELIM;
				}
			}

			// ***************************** tipos de avião
			size_t cnt = 0;
			for(vector<TipoAviao* >::const_iterator it2=(*it)->getConstRefFrota().begin() ; it2!=(*it)->getConstRefFrota().end() ; ++it2)
			{
				++cnt;
				file << calcVectorIndex( tipo_aviao_DB.getRefTiposAviao(), (*it2) );

				if( ((*it)->getConstRefFrota().size() == 1) || ((*it)->getConstRefFrota().size() == cnt) )
					file << endl;
				else
					file << SAVE_DELIM;
			}
		}

		// ***************************** portas de embarque
		BSTItrIn<PortaEmbarquePtr> it( aeroporto.getConstRefPortasEmbarqueBST() );
		while (!it.isAtEnd())
		{
			file << it.retrieve()()->getNumero() << SAVE_DELIM;
			file << it.retrieve()()->getLocalizacao() << SAVE_DELIM;
			file << it.retrieve()()->getCapacidadePass() << SAVE_DELIM;
			file << it.retrieve()()->getVagasPass() << SAVE_DELIM;
			file << it.retrieve()()->getCategoriaAvioes() << SAVE_DELIM;
			file << it.retrieve()()->getConstRefVoosPortaEmbarque().size() << endl;

			// ****************** vector voos nas portas de embarque
			size_t cnt = 0;
			for(vector<Voo* >::const_iterator it2=it.retrieve()()->getConstRefVoosPortaEmbarque().begin() ;
				it2!=it.retrieve()()->getConstRefVoosPortaEmbarque().end() ; ++it2)
			{
				++cnt;
				file << calcVectorIndex<Companhia*>( aeroporto.getConstRefCompanhias(), (*it2)->getCompanhia() ) << SAVE_DELIM;
				file << calcVectorIndex<Voo*>( (*it2)->getCompanhia()->getConstRefVoos(), (*it2) );

				if( (it.retrieve()()->getConstRefVoosPortaEmbarque().size() == 1) || (it.retrieve()()->getConstRefVoosPortaEmbarque().size() == cnt) )
					file << endl;
				else
					file << SAVE_DELIM;
			}

			it.advance();
		}

		// ***************************** passageiros do aeroporto
		for(vector<Passageiro* >::const_iterator it=aeroporto.getConstRefPassageirosAeroporto().begin() ; it!=aeroporto.getConstRefPassageirosAeroporto().end() ; ++it)
		{
			//if( (*it)->getVoo() != NULL )
			//{
				file << (*it)->getNome() << SAVE_DELIM;
				file << (*it)->getMorada() << SAVE_DELIM;
				file << (*it)->getNacionalidade() << SAVE_DELIM;
				file << (*it)->getContacto() << SAVE_DELIM;
				file << (*it)->getBI() << SAVE_DELIM;
				file << (*it)->getIdade() << SAVE_DELIM;

				file << (*it)->getNecessidades_especiais() << SAVE_DELIM;
				file << (*it)->getPesoBagagem() << SAVE_DELIM;
				file << (*it)->getNumeroLugarAviao() << SAVE_DELIM;

				file << calcVectorIndex( (*it)->getVoo()->getCompanhia()->getRefVoos(), (*it)->getVoo() ) << SAVE_DELIM;	//ptr
				file << calcVectorIndex( aeroporto.getRefCompanhias(), (*it)->getVoo()->getCompanhia() ) << endl;	//ptr
			//}
		}

		// ***************************** hashset dos voos fechados
		size_t cnt = 0;
		for(HASH_SET_VOOS::const_iterator it = aeroporto.getConstRefHashSetVoos().begin() ;
			it != aeroporto.getConstRefHashSetVoos().end() ;
			++it)
		{
			++cnt;
			file << calcVectorIndex( aeroporto.getConstRefCompanhias(), (*it)->getCompanhia() ) << SAVE_DELIM;
			file << calcVectorIndex( (*it)->getCompanhia()->getConstRefVoos(), (*it) );

			if( (aeroporto.getConstRefHashSetVoos().size() == 1) || (aeroporto.getConstRefHashSetVoos().size() == cnt) )
				file << endl;
			else
				file << SAVE_DELIM;
		}

		file.close();
		return;
	}

	throw ExNoOpenFile();
}
