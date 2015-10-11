/**\file Atraso.cpp
 * \brief Ficheiro com a implementação da classe Voo.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Atraso.cpp \n
 * DESCRIÇÃO: Ficheiro com a implementação da classe Aviao. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#include "Atraso.h"


Atraso Atraso::Parser_Atraso(string str) {
	//Devisão da string em 2 ou 3 subtrings consoante esteja no formato HH:mm ou DD:HH:mm
	vector <string> atraso_split = split(str, ':');

	//Verifica se o atraso está no formato DD:HH:mm
	if (atraso_split.size() == 3) {
		int dia = atoi(atraso_split[2].c_str());
		int hora = atoi(atraso_split[0].c_str());
		int min = atoi(atraso_split[1].c_str());

		if ((dia >= 0 && dia <= 31) && (hora >= 0 && hora <= 23) && (min >= 0 && min <= 59))
			return Atraso(hora, min, dia);
		else
			throw ExInvalidAtraso(str);
	}

	//Verifica se o atraso está no formato HH:mm
	if (atraso_split.size() == 2) {
		int hora = atoi(atraso_split[0].c_str());
		int min = atoi(atraso_split[1].c_str());

		if ((hora >= 0 && hora <= 23) && (min >= 0 && min <= 59))
			return Atraso(hora, min);
		else
			throw ExInvalidAtraso(str);
	}

	//Se não for fornecido o atraso num formato válido é lançada uma excepção
	throw ExInvalidAtraso(str);

}


void Atraso::getAtrasoCin(const char* mensagem) {
	string atraso_temp; 	//String temporária para guardar o input
	Atraso atraso; 			//Atraso a ser retornado depois de correctamente inicializado

	bool atraso_invalido = true; //Flag a ser usada para sair do ciclo de input
	//Enquanto o utilizador não introduzir um Atraso no formato correcto, continua a pedir a DataHora
	do {
		try {
			cout << mensagem << flush;
			getlineCin(atraso_temp);
			atraso = Atraso(atraso_temp);
			atraso_invalido = false;
		} catch (ExInvalidAtraso &e) {
			cout << e << endl << endl;
		}
	} while (atraso_invalido);

	*this = atraso;
}


bool Atraso::operator==(const Atraso &atraso) const {
	if ( (_dia == atraso._dia) &&
		 (_hora == atraso._hora) &&
		 (_min == atraso._min) )
		return true;
	else
		return false;
}


bool Atraso::operator<(const Atraso &atraso) const {
	if (_dia < atraso._dia)
		return true;
	else if (_dia > atraso._dia)
		return false;
	else if (_hora < atraso._hora)
		return true;
	else if (_hora > atraso._hora)
		return false;
	else if (_min < atraso._min)
		return true;
	else
		return false;
}


ostream& operator<<(ostream &os, const Atraso &obj) {
	//Impressão da DataHora no formato AAAA/MM/DD HH:mm
	os << obj.getDia() << " " << obj.getHora() << ":" << obj.getMin();
	return os;
}


istream& operator>>(istream &is, Atraso &obj) {
	string str;

	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//Obtenção da string com informação do atraso
	getline(is, str);

	obj = obj.Parser_Atraso(str);
	return is;
}
