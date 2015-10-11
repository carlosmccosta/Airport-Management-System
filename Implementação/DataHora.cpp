/**\file DataHora.cpp
 * \brief Ficheiro com a implementa��o da classe DataHora.
 *
 * PROJECTO: Projecto 2 - Gest�o do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: DataHora.cpp \n
 * DESCRI��O: Ficheiro com a implementa��o da classe DataHora. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - V�tor Am�lio Maia Martins Moreira
 */

#include "DataHora.h"


DataHora DataHora::Parser_DataHora(string data_hora) {
	//Devis�o da string em duas subtrings (data e hora)
	vector<string> datahora = split(data_hora, ' ');

	//Verifica se a string est� no formato AAAA/MM/DD HH:mm
	if (datahora.size() == 2) {
		//Divis�o da string data nos seus componetes ano, m�s e dia
		vector<string> data = split(datahora[0], '/');

		//Devis�o da string hora nas componentes hora e minutos
		vector<string> hora = split(datahora[1], ':');

		if ((data.size() == 3) && (hora.size() == 2)) {
			int a = atoi(data[0].c_str());
			int m = atoi(data[1].c_str());
			int d = atoi(data[2].c_str());
			int h = atoi(hora[0].c_str());
			int min = atoi(hora[1].c_str());

			//Verifica��o da validade dos dados obtidos
			if ((d > 0 && d <= 31) && (m > 0 && m <= 12) && (a > 0) && (h >= 0 && h <= 23) && (min >= 0 && min <= 59)) {
				//Cria��o da DataHora
				DataHora ret(a, m, d, h, min);
				return ret;
			}
		}
	}

	//Caso n�o seja fornecido uma data v�lida � lan�ada uma excep��o
	throw ExInvalidDateTime(data_hora);
}


void DataHora::getDataHoraCin(const char* mensagem) {
	string data_temp; 	//String tempor�ria para guardar o input
	DataHora data; 		//Data a ser retornada depois de correctamente inicializada

	bool data_invalida = true; //Flag a ser usada para sair do ciclo de input
	//Enquanto o utilizador n�o introduzir uma DataHora no formato correcto, continua a pedir a DataHora
	do {
		try {
			cout << mensagem << flush;
			getlineCin(data_temp);
			data = DataHora(data_temp);
			data_invalida = false;
		} catch (ExInvalidDateTime &e) {
			cout << e << endl << endl;
		}
	} while (data_invalida);

	*this = data;
}


bool DataHora::operator==(const DataHora &data_hora) const
{
	if( (_ano == data_hora._ano) &&
		(_mes == data_hora._mes) &&
		(_dia == data_hora._dia) &&
		(_hora == data_hora._hora) &&
		(_min == data_hora._min) )
		return true;
	else
		return false;
}

bool DataHora::operator<(const DataHora &data_hora) const
{
	if (_ano < data_hora._ano)
		return true;
	else if (_ano > data_hora._ano)
		return false;
	else if (_mes < data_hora._mes)
		return true;
	else if (_mes > data_hora._mes)
		return false;
	else if (_dia < data_hora._dia)
		return true;
	else if (_dia > data_hora._dia)
		return false;
	else if (_hora < data_hora._hora)
		return true;
	else if (_hora > data_hora._hora)
		return false;
	else if (_min < data_hora._min)
		return true;
	else
		return false;
}


ostream& operator<<(ostream &os, const DataHora &obj) {
	//Impress�o da DataHora no formato AAAA/MM/DD HH:mm
	os << obj.getAno() << "/" << obj.getMes() << "/" << obj.getDia() << " " << obj.getHora() << ":" << obj.getMin();
	return os;
}


istream& operator>>(istream &is, DataHora &obj) {
	string str;

	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	//Obten��o da string com informa��o da data e hora
	getline(is, str);

	obj = obj.Parser_DataHora(str);
	return is;
}

