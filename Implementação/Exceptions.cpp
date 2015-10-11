/**\file Exceptions.cpp
 * \brief Ficheiro com a implementação da classe exception e suas subclasses.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: exception.cpp \n
 * DESCRIÇÃO: Ficheiro com a implementação da classe exception e suas subclasses. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#include "Exceptions.h"

template<class T>
ostream & operator<<(ostream & obj, const ExElementAlreadyExists<T> & exception) {
	obj << "O elemento " << exception.getElementoRepetido() << " já existe no contentor.";
	return obj;
}

ostream & operator<<(ostream & obj, const ExInvalidDateTime & data) {
	obj << "O formato da data que introduziu (" << data.getData() << ") é inválido!";
	return obj;
}

ostream & operator<<(ostream & obj, const ExInvalidAtraso & atraso) {
	obj << "O formato do atraso que introduziu (" << atraso.getAtraso() << ") é inválido!";
	return obj;
}

ostream & operator<<(ostream & obj, const ExCorruptedFile & exception) {
	obj << "O ficheiro de dados\"" << exception.getFilename() << "\" está corrompido!";
	return obj;
}

ostream & operator<<(ostream & obj, const ExNoOpenFile & exception) {
	obj << "Não foi possível abrir o ficheiro\"" << exception.getFilename() << "\"!";
	return obj;
}
