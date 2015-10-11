/**\file TipoAviaoDB.cpp
 * \brief Ficheiro com a implementação da classe TipoAviaoDB.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: TipoAviaoDB.cpp \n
 * DESCRIÇÃO: Ficheiro com a implementação da classe TipoAviaoDB. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#include "TipoAviaoDB.h"

TipoAviaoDB::~TipoAviaoDB()
{
	for(vector<TipoAviao* >::iterator it = _tipos_aviao.begin() ; it!=_tipos_aviao.end() ; ++it)
		delete (*it);
}


string TipoAviaoDB::getNomeTipoAviaoCin(const char* mensagem) {
	//Verifica-se se o nome do tipo de avião já existe.
	string nome_tipo;
	bool nome_repetido;
	do {
		nome_repetido = false;
		cout << mensagem << flush;
		getlineCin(nome_tipo);

		for (vector<TipoAviao*>::const_iterator it = _tipos_aviao.begin(); it != _tipos_aviao.end(); ++it)
			if (nome_tipo == (*it)->getNomeTipo()) {
				nome_repetido = true;
				cout << "O nome introduzido já existe!" << endl << endl;
				break;
			}
	} while(nome_repetido);

	return nome_tipo;
}

void TipoAviaoDB::addTipoAviao() {
	cout << endl << endl;
	//Variáveis a recolher
	string nome_tipo;				//Ex: A321
	string descricao;				//Ex: Airbus 321
	unsigned categoria;				//Ex: Médio curso

	string fabricante;				//Ex: Airbus
	DataHora data_lancamento; 		//Data do primeiro voo deste tipo de avião
	unsigned preco;					//Preço deste tipo de avião
	unsigned maximo_passageiros; 	//Nº de passageiros máximo
	unsigned autonomia;				//Em km
	unsigned velocidade_maxima;		//Em km/h
	unsigned numero_motores;
	unsigned peso_vazio;			//Em kg
	unsigned peso_maximo;			//Em kg
	//Medidas em metros
	unsigned comprimento;
	unsigned envergadura;
	unsigned altura;
	unsigned altitude_maxima;

	//Recolha dos dados

	nome_tipo = getNomeTipoAviaoCin("Introduza o nome do tipo de avião: ");

	cout << "Introduza a descrição: " << flush;
	getlineCin(descricao);

	cout << "Categorias de Aviões a associar ao tipo de avião:\n" << endl;
	PortaEmbarque::listCategoriasAvioesInfo();
	categoria = get_uint_cin <unsigned>("Introduza a categoria do avião:\n", PortaEmbarque::getRefCategoriasAvioesInfo().size(), 0, false);

	cout << "Introduza o fabricante: " << flush;
	getlineCin(fabricante);

	data_lancamento.getDataHoraCin("Introduza a data/hora do primeiro voo (AAAA/MM/DD HH:mm): ");
	preco = get_int_cin("Introduza o preço (em euros): ");
	maximo_passageiros = get_int_cin("Introduza o número de passageiros máximo: ");
	autonomia = get_int_cin("Introduza a autonomia (km): ");
	velocidade_maxima = get_int_cin("Introduza a velocidade máxima (km/h): ");
	numero_motores = get_int_cin("Introduza o número de motores: ");
	peso_vazio = get_int_cin("Introduza o peso vazio (kg): ");
	peso_maximo = get_int_cin("Introduza o peso máximo (kg): ");
	comprimento = get_int_cin("Introduza o comprimento (m): ");
	envergadura = get_int_cin("Introduza a envergadura (m): ");
	altura = get_int_cin("Introduza a altura (m):");
	altitude_maxima = get_int_cin("Introduza a altitude máxima (m):");

	//Criação do avião a partir dos dados recolhidos
	TipoAviao* novo_aviao = new TipoAviao(nome_tipo,
			descricao,
			categoria,
			fabricante,
			data_lancamento,
			preco,
			maximo_passageiros,
			autonomia,
			velocidade_maxima,
			numero_motores,
			peso_vazio,
			peso_maximo,
			comprimento,
			envergadura,
			altura,
			altitude_maxima);


	//Adicionamento do tipo de aviao criado à base de dados
	try {
		addTipoAviao(novo_aviao);
		cout << "Adicionado com sucesso!" << endl;
	} catch (ExElementAlreadyExists<TipoAviao> &e) {
		delete novo_aviao;
		cout << e.what() << endl;
	}

	getch();
}


void TipoAviaoDB::addTipoAviao(TipoAviao *tipo_aviao) {
	vector<TipoAviao*>::const_iterator it;

	for (it = _tipos_aviao.begin(); it != _tipos_aviao.end(); ++it)
		if ((*tipo_aviao) == *(*it))
			throw ExElementAlreadyExists<TipoAviao> (*tipo_aviao);

	_tipos_aviao.push_back(tipo_aviao);
}

bool cmpTipoAviaoTipo(const TipoAviao *ta1, const TipoAviao *ta2) {
	return (ta1->getNomeTipo() < ta2->getNomeTipo());
}

bool cmpTipoAviaoDescricao(const TipoAviao *ta1, const TipoAviao *ta2) {
	return (ta1->getDescricao() < ta2->getDescricao());
}

bool cmpTipoAviaoCategoria(const TipoAviao *ta1, const TipoAviao *ta2) {
	return (ta1->getCategoria() < ta2->getCategoria());
}

void TipoAviaoDB::listTipoAviao(bool final_pause) {
	cout << endl << endl;
	if (_tipos_aviao.size() == 0) {
		throw ExEmptyVector("Não existem tipos de aviao na base de dados!");
	}

	//Selecção do método de ordenação
	string str_title_ordenacao = "Método de ordenação";

	vector <string> colNames_ordenacao;
	colNames_ordenacao.push_back(string("Critério de ordenação"));

	vector < vector<string> > col_ordenacao;
	vector <string> parametros_ordenacao;
	parametros_ordenacao.push_back((string)"Tipo");
	parametros_ordenacao.push_back((string)"Descrição");
	parametros_ordenacao.push_back((string)"Categoria");
	col_ordenacao.push_back(parametros_ordenacao);

	cout << endl << endl;
	printMenu(str_title_ordenacao, col_ordenacao, colNames_ordenacao);

	cout << endl << endl;
	size_t metodo = get_uint_cin("Selecione o critério de ordenação que quer usar: ", parametros_ordenacao.size());
	cout << endl;

	//Listagem ordenada dos tipos de avião
	string str_title = "Lista de avioes";
	vector < vector<string> > col;

	col.push_back(vector<string> ());
	col.push_back(vector<string> ());
	col.push_back(vector<string> ());

	vector <string> colNames;


	//Ordenação do vector de acordo com o parâmetro fornecido
	switch (metodo) {
		case 0: {
			sort(_tipos_aviao.begin(), _tipos_aviao.end(), cmpTipoAviaoTipo);
			colNames.push_back((string)"Tipo");
			colNames.push_back((string)"Descrição");
			colNames.push_back((string)"Categoria");

			size_t i = 0;
			for (vector <TipoAviao*>::const_iterator it_tipoaviao = _tipos_aviao.begin(); it_tipoaviao != _tipos_aviao.end(); ++it_tipoaviao) {
				col[i++].push_back((*it_tipoaviao)->getNomeTipo());
				col[i++].push_back((*it_tipoaviao)->getDescricao());
				col[i].push_back( PortaEmbarque::getInfoEnumCategoriasAvioes((*it_tipoaviao)->getCategoria() ) );
				i = 0;
			}
			break;
		}

		case 1: {
			sort(_tipos_aviao.begin(), _tipos_aviao.end(), cmpTipoAviaoDescricao);
			colNames.push_back((string)"Descrição");
			colNames.push_back((string)"Tipo");
			colNames.push_back((string)"Categoria");

			size_t i = 0;
			for (vector <TipoAviao*>::const_iterator it_tipoaviao = _tipos_aviao.begin(); it_tipoaviao != _tipos_aviao.end(); ++it_tipoaviao) {
				col[i++].push_back((*it_tipoaviao)->getNomeTipo());
				col[i++].push_back((*it_tipoaviao)->getDescricao());
				col[i].push_back( PortaEmbarque::getInfoEnumCategoriasAvioes((*it_tipoaviao)->getCategoria() ) );
				i = 0;
			}
			break;
		}

		case 2: {
			sort(_tipos_aviao.begin(), _tipos_aviao.end(), cmpTipoAviaoCategoria);
			colNames.push_back((string)"Categoria");
			colNames.push_back((string)"Tipo");
			colNames.push_back((string)"Descrição");

			size_t i = 0;
			for (vector <TipoAviao*>::const_iterator it_tipoaviao = _tipos_aviao.begin(); it_tipoaviao != _tipos_aviao.end(); ++it_tipoaviao) {
				col[i++].push_back( PortaEmbarque::getInfoEnumCategoriasAvioes((*it_tipoaviao)->getCategoria() ) );
				col[i++].push_back((*it_tipoaviao)->getNomeTipo());
				col[i].push_back( (*it_tipoaviao)->getDescricao() );
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


size_t TipoAviaoDB::selTipoAviao() {
	listTipoAviao();
	cout << endl << endl;
	size_t indice = get_uint_cin<size_t>("\nIntroduza o índice (0 para retroceder): ", _tipos_aviao.size(), 0, true);
	return indice;
}


TipoAviao* TipoAviaoDB::selTipoAviaoPtr() {
	return _tipos_aviao[ selTipoAviao() ];
}

void TipoAviaoDB::infoTipoAviao() {
	cout << endl << endl;
	size_t indice = selTipoAviao();

	TipoAviao *tipo_aviao = _tipos_aviao[indice];

	string str_title = "Informações sobre o tipo de avião";

	vector <string> colNames;					// nomes de colunas não são usados, logo vão strings vazias
	colNames.push_back(string(""));
	colNames.push_back(string(""));

	vector < vector<string> > col;
	vector <string> dados;

	//Nomes dos atributos
	col.push_back(Comandos::_tipo_aviao_op_list);

	dados.push_back( tipo_aviao->getNomeTipo() );
	dados.push_back( tipo_aviao->getDescricao() );
	dados.push_back( PortaEmbarque::getInfoEnumCategoriasAvioes( tipo_aviao->getCategoria() ) );
	dados.push_back( tipo_aviao->getFabricante() );
	dados.push_back( to_string<DataHora>(tipo_aviao->getDataLancamento()) );
	dados.push_back( to_string<unsigned>(tipo_aviao->getPreco()) );
	dados.push_back( to_string<unsigned>(tipo_aviao->getMaximoPassageiros()) );
	dados.push_back( to_string<unsigned>(tipo_aviao->getAutonomia()) );
	dados.push_back( to_string<unsigned>(tipo_aviao->getVelocidadeMaxima()) );
	dados.push_back( to_string<unsigned>(tipo_aviao->getNumeroMotores()) );
	dados.push_back( to_string<unsigned>(tipo_aviao->getPesoVazio()) );
	dados.push_back( to_string<unsigned>(tipo_aviao->getPesoMaximo()) );
	dados.push_back( to_string<unsigned>(tipo_aviao->getComprimento()) );
	dados.push_back( to_string<unsigned>(tipo_aviao->getEnvergadura()) );
	dados.push_back( to_string<unsigned>(tipo_aviao->getAltura()) );
	dados.push_back( to_string<unsigned>(tipo_aviao->getAltitudeMaxima()) );


	//Dados relativos aos atributos
	col.push_back(dados);

	cout << endl << endl;
	printMenu(str_title, col, colNames, false, false, true, true);
	getch();
}


void TipoAviaoDB::editTipoAviao() {
	bool continuar;
	do {
		cout << endl << endl;
		//Selecção do avião
		TipoAviao* tipo_aviao = selTipoAviaoPtr();

		//Escolha do atr5ibuto a editar
		string titulo("Atributos dos tipos de aviões");
		string col_name("Atributos");
		vector <string> nome_coluna;
		vector < vector <string> > colunas;
		colunas.push_back(Comandos::_tipo_aviao_op_list);
		nome_coluna.push_back(col_name);

		cout << endl << endl;
		printMenu(titulo, colunas, nome_coluna);
		int indice_atributo = get_int_cin("Escolha o atributo que quer editar: ", Comandos::_tipo_aviao_op_list.size());
		cout << endl << endl;

		string str_temp;
		unsigned uns_temp;
		DataHora data_hora_temp;

		switch (indice_atributo) {
		case 0:
			{
				str_temp = getNomeTipoAviaoCin("Introduza o novo nome para o tipo de avião: ");
				tipo_aviao->setNomeTipo(str_temp);
				break;
			}

		case 1:
			{
				cout << "Introduza a nova descrição para o tipo de avião: ";
				getlineCin(str_temp);
				tipo_aviao->setDescricao(str_temp);
				break;
			}

		case 2:
			{
				cout << "Categorias de Aviões a associar ao tipo de avião:\n" << endl;
				PortaEmbarque::listCategoriasAvioesInfo();
				unsigned uns_temp = get_uint_cin <unsigned>("Introduza a nova categoria do tipo de avião:\n", PortaEmbarque::getRefCategoriasAvioesInfo().size(), 0, false);
				tipo_aviao->setCategoria(uns_temp);
				break;
			}

		case 3:
			{
				cout << "Introduza o novo fabricante para o tipo de avião: ";
				getlineCin(str_temp);
				tipo_aviao->setFabricante(str_temp);
				break;
			}

		case 4:
			{
				data_hora_temp.getDataHoraCin("Introduza a nova data de lançamento deste tipo de avião (AAAA/MM/DD HH:mm): ");
				tipo_aviao->setDataLancamento(data_hora_temp);
				break;
			}

		case 5:
			{
				uns_temp = get_int_cin("Introduza o novo preço para este tipo de avião (euros): ");
				tipo_aviao->setPreco(uns_temp);
				break;
			}

		case 6:
			{
				uns_temp = get_int_cin("Introduza o número máximo de passageiros para este tipo de avião: ");
				tipo_aviao->setMaximoPassageiros(uns_temp);
				break;
			}

		case 7:
			{
				uns_temp = get_int_cin("Introduza a autonomia para este tipo de avião (km): ");
				tipo_aviao->setAutonomia(uns_temp);
				break;
			}

		case 8:
			{
				uns_temp = get_int_cin("Introduza a velocidade máxima que este tipo de avião atinge (km/h): ");
				tipo_aviao->setVelocidadeMaxima(uns_temp);
				break;
			}

		case 9:
			{
				uns_temp = get_int_cin("Introduza o número de motores que este tipo de avião tem: ");
				tipo_aviao->setNumeroMotores(uns_temp);
				break;
			}

		case 10:
			{
				uns_temp = get_int_cin("Introduza o peso vazio que deste tipo de avião (kg): ");
				tipo_aviao->setPesoVazio(uns_temp);
				break;
			}

		case 11:
			{
				uns_temp = get_int_cin("Introduza o peso máximo que este tipo de avião pode suportar(kg): ");
				tipo_aviao->setPesoMaximo(uns_temp);
				break;
			}

		case 12:
			{
				uns_temp = get_int_cin("Introduza o comprimento deste tipo de avião (m): ");
				tipo_aviao->setComprimento(uns_temp);
				break;
			}

		case 13:
			{
				uns_temp = get_int_cin("Introduza a envergadura deste tipo de avião (m): ");
				tipo_aviao->setEnvergadura(uns_temp);
				break;
			}

		case 14:
			{
				uns_temp = get_int_cin("Introduza a altura deste tipo de avião (m): ");
				tipo_aviao->setAltura(uns_temp);
				break;
			}

		case 15:
			{
				uns_temp = get_int_cin("Introduza a altitude máxima a que este tipo de avião pode voar (m): ");
				tipo_aviao->setAltitudeMaxima(uns_temp);
				break;
			}
		}

		//Pergunta ao utilizador se quer continuar a editar o tipo de avião
		continuar = get_yes_no("\n\nDeseja continuar a editar este tipo de avião (S/N): ");

	} while (continuar);
}


void TipoAviaoDB::delTipoAviao() {
	try {
		size_t indice = selTipoAviao();
		delTipoAviao(indice);
		cout << "Removido com sucesso!" << endl;
	} catch (exception & e) {
		cout << e.what() << endl;
	}

	getch();
}


void TipoAviaoDB::delTipoAviao(size_t indice) {
	if ((indice < 0) && (indice >= _tipos_aviao.size()))
		throw ExOutOfRange();

	const vector <Aviao*>& avioes_associados = _tipos_aviao[indice]->getConstRefAvioesAssociados();
	if (avioes_associados.size() > 0)
		throw ExElementInUse<const vector <Aviao*>& >(avioes_associados);

	vector<TipoAviao*>::iterator it = _tipos_aviao.begin();

	delete *(it + indice);
	_tipos_aviao.erase(it + indice);
}


void TipoAviaoDB::loaddb_tipos_aviao() {
	loaddb_tipos_aviao(FILE_SAVE_DB_TIPOS_AVIAO);
}


void TipoAviaoDB::loaddb_tipos_aviao(string filename) {
	ifstream file;
	file.open(filename.c_str());

	if (file.is_open()) {
		string linha;
		vector<string> vec_str;

		getline(file, linha);

		size_t numero_tipo_aviao = atoi(linha.c_str());

		for (size_t i = 0; i < numero_tipo_aviao; ++i) {
			getline(file, linha);
			vec_str = split(linha, SAVE_DELIM);

			if (vec_str.size() != CLASS_TIPO_AVIAO_ATTR_SIZE)
				throw ExCorruptedFile();

			TipoAviao* novo_tipo_aviao = new TipoAviao(
					vec_str[0],
					vec_str[1],
					atoi(vec_str[2].c_str()),
					vec_str[3],
					vec_str[4],
					atoi(vec_str[5].c_str()),
					atoi(vec_str[6].c_str()),
					atoi(vec_str[7].c_str()),
					atoi(vec_str[8].c_str()),
					atoi(vec_str[9].c_str()),
					atoi(vec_str[10].c_str()),
					atoi(vec_str[11].c_str()),
					atoi(vec_str[12].c_str()),
					atoi(vec_str[13].c_str()),
					atoi(vec_str[14].c_str()),
					atoi(vec_str[15].c_str()) );

			_tipos_aviao.push_back(novo_tipo_aviao);
		}
	}

	file.close();
}


void TipoAviaoDB::savedb_tipos_aviao() {
	savedb_tipos_aviao(FILE_SAVE_DB_TIPOS_AVIAO);
}


void TipoAviaoDB::savedb_tipos_aviao(string filename) {
	ofstream file;
	file.open(filename.c_str());

	if (file.is_open()) {
		file << _tipos_aviao.size() << endl;

		for (vector<TipoAviao*>::const_iterator it = getRefTiposAviao().begin(); it != getRefTiposAviao().end(); ++it) {
			file << (*it)->getNomeTipo() << SAVE_DELIM;
			file << (*it)->getDescricao() << SAVE_DELIM;
			file << (*it)->getCategoria() << SAVE_DELIM;
			file << (*it)->getFabricante() << SAVE_DELIM;
			file << (*it)->getDataLancamento() << SAVE_DELIM;
			file << (*it)->getPreco() << SAVE_DELIM;
			file << (*it)->getMaximoPassageiros() << SAVE_DELIM;
			file << (*it)->getAutonomia() << SAVE_DELIM;
			file << (*it)->getVelocidadeMaxima() << SAVE_DELIM;
			file << (*it)->getNumeroMotores() << SAVE_DELIM;
			file << (*it)->getPesoVazio() << SAVE_DELIM;
			file << (*it)->getPesoMaximo() << SAVE_DELIM;
			file << (*it)->getComprimento() << SAVE_DELIM;
			file << (*it)->getEnvergadura() << SAVE_DELIM;
			file << (*it)->getAltura() << SAVE_DELIM;
			file << (*it)->getAltitudeMaxima() << endl;
		}

		file.close();
		return;
	}

	throw ExNoOpenFile();
}

