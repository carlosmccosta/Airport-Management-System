/**\file Exceptions.cpp
 * \brief Ficheiro com a implementa��o da classe exception e suas subclasses.
 *
 * PROJECTO: Projecto 2 - Gest�o do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: exception.cpp \n
 * DESCRI��O: Ficheiro com a implementa��o da classe exception e suas subclasses. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - V�tor Am�lio Maia Martins Moreira
 */

#include "Exceptions.h"

template<class T>
ostream & operator<<(ostream & obj, const ExElementAlreadyExists<T> & exception) {
	obj << "O elemento " << exception.getElementoRepetido() << " j� existe no contentor.";
	return obj;
}

ostream & operator<<(ostream & obj, const ExInvalidDateTime & data) {
	obj << "O formato da data que introduziu (" << data.getData() << ") � inv�lido!";
	return obj;
}

ostream & operator<<(ostream & obj, const ExInvalidAtraso & atraso) {
	obj << "O formato do atraso que introduziu (" << atraso.getAtraso() << ") � inv�lido!";
	return obj;
}

ostream & operator<<(ostream & obj, const ExCorruptedFile & exception) {
	obj << "O ficheiro de dados\"" << exception.getFilename() << "\" est� corrompido!";
	return obj;
}

ostream & operator<<(ostream & obj, const ExNoOpenFile & exception) {
	obj << "N�o foi poss�vel abrir o ficheiro\"" << exception.getFilename() << "\"!";
	return obj;
}
