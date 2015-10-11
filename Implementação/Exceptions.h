/**\file Exceptions.h
 * \brief Classe que contém a informação associada a todas as excepcoes implementadas.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Exceptions.h \n
 * DESCRIÇÃO: Classe que contém a informação associada a todas as excepcoes implementadas. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <iostream>
#include <string>
#include <exception>

using std::ostream;
using std::string;
using std::exception;


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  Exceptions  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * \brief Superclasse de tratamento de excepções.
 * \details Subclasse de std::exception para no programa ser possível fazer catch das excepções da std e das excepções criadas para o programa.
 */

class Exceptions: public exception {
protected:
	const char* _errorMessage;

public:
	explicit Exceptions(const char* pStr) : _errorMessage(pStr) {}

	/**
	 * Destrutor que garante que não irá lançar uma excepção,
	 * porque a classe std::exception, obriga a que as subclasses que fazem override às suas funções, não podem lançar excepções.
	 * Isso inclui os destrutores e a função what().
	 * Caso não fosse feito o compilador iria dar o erro "looser throw specifier...".
	 */
	virtual ~Exceptions() throw() {}
	const char* what() const throw() { return _errorMessage; }
};



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ExElementAlreadyExists  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que um dado elemento já existe num dado contentor
template <class T>
class ExElementAlreadyExists: public Exceptions {
private:
	T _elementoRepetido;
public:
	explicit ExElementAlreadyExists(T elemento_repetido, const char* pStr = "Elemento já existe no vector!") :
		Exceptions(pStr), _elementoRepetido(elemento_repetido) {}
	virtual ~ExElementAlreadyExists() throw() {}

	T getElementoRepetido() const { return _elementoRepetido; }
};


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ExElementDoesntExists  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que um dado elemento já existe num dado contentor
template <class T>
class ExElementDoesntExists: public Exceptions {
private:
	T _elementoInexistente;
public:
	explicit ExElementDoesntExists(T elementoInexistente, const char* pStr = "Elemento não existe no vector!") :
		Exceptions(pStr), _elementoInexistente(elementoInexistente) {}
	virtual ~ExElementDoesntExists() throw() {}

	T getElementoInexistente() const { return _elementoInexistente; }
};


///Operador que imprime a mensagem de erro da excepção do tipo ExElementAlreadyExists
template <class T>
ostream & operator<<(ostream & obj, const ExElementAlreadyExists<T> & exception);



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ExOutOfRange  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que um elemento que se está a tentar aceder está fora do domínio do contentor.
class ExOutOfRange: public Exceptions {
public:
	explicit ExOutOfRange(const char* pStr = "Valor fora do domínio do vector!") : Exceptions(pStr) {}
	virtual ~ExOutOfRange() throw() {}
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ExEmptyVector  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que um vector se encontra vazio.
class ExEmptyVector: public Exceptions {
public:
	explicit ExEmptyVector(const char* pStr = "O vector encontra-se vazio!") : Exceptions(pStr) {}
	virtual ~ExEmptyVector() throw() {}
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ExNoInterval  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que um vector se encontra vazio.
class ExNoInterval: public Exceptions {
public:
	explicit ExNoInterval(const char* pStr = "O intervalo começa e acaba em zero!") : Exceptions(pStr) {}
	virtual ~ExNoInterval() throw() {}
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ExElementInUse  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que um vector se encontra vazio.
template <class T>
class ExElementInUse: public Exceptions {
	T _dependent_objects;	//Objectos que dependem do elemento que estava a se tentar apagar
public:
	explicit ExElementInUse(T dependent_objects, const char* pStr = "Não é possível eliminar o elemento seleccionado\nporque está a ser usado por outros componentes do programa neste momento!")
	: Exceptions(pStr), _dependent_objects(dependent_objects) {}
	virtual ~ExElementInUse() throw() {}
};


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ExInvalidDateTime  <<<<<>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que o utilizador introduziu uma DataHora num formato errado.
/**
 * Formato aceite: AAAA/MM/DD HH:mm
 */
class ExInvalidDateTime: public Exceptions {
private:
	string _Data;
public:
	explicit ExInvalidDateTime(string data, const char* pStr = "Data/Hora no formato errado! (DD/MM/AAAA HH:mm)") :
		Exceptions(pStr), _Data(data) {}
	virtual ~ExInvalidDateTime() throw() {}

	string getData() const { return _Data; }
};

///Operador que imprime a mensagem de erro da excepção do tipo ExInvalidDateTime
ostream & operator<<(ostream & obj, const ExInvalidDateTime & data);



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ExInvalidAtraso  <<<<<>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que o utilizador introduziu um Atraso num formato inválido.
/**
 * Formatos aceites:
 * - DD:HH:mm
 * - HH:mm
 */
class ExInvalidAtraso: public Exceptions {
private:
	string _Atraso;
public:
	explicit ExInvalidAtraso(string atraso, const char* pStr = "Atraso no formato errado! (HH:mm ou HH:mm:DD)") :
		Exceptions(pStr), _Atraso(atraso) {}
	virtual ~ExInvalidAtraso() throw() {}

	string getAtraso() const { return _Atraso; }
};

///Operador que imprime a mensagem de erro da excepção do tipo ExInvalidAtraso
ostream & operator<<(ostream & obj, const ExInvalidAtraso & atraso);



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<>>>>>  ExCorruptedFile  <<<<<<<<<>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usado no tratamento de excepções que sinaliza que um dado ficheiro que de dados está corrupto ou num formato desconhecido.
class ExCorruptedFile: public Exceptions {
private:
	string _filename;

public:
	explicit ExCorruptedFile(const char* pStr = "Ficheiro com os dados corrompido!") : Exceptions(pStr) {}
	string getFilename() const { return _filename; }
	virtual ~ExCorruptedFile() throw() {}
};

///Operador que imprime a mensagem de erro da excepção do tipo ExCorruptedFile
ostream & operator<< (ostream & obj, const ExCorruptedFile & exception);



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<>>>>>>>  ExNoOpenFile  <<<<<<<<<<<<<<<>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usado no tratamento de excepções que sinaliza que não foi possível abrir o ficheiro especificado.
class ExNoOpenFile: public Exceptions {
private:
	string _filename;

public:
	explicit ExNoOpenFile(const char* pStr = "Não foi possível abrir o ficheiro!") : Exceptions(pStr) {}
	virtual ~ExNoOpenFile() throw() {}
	string getFilename() const { return _filename; }
};

///Operador que imprime a mensagem de erro da excepção do tipo ExNoOpenFile
ostream & operator<< (ostream & obj, const ExNoOpenFile & exception);

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ExPortasFull  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
///Classe usada no tratamento de excepções que sinaliza que as portas de embarque não têm espaco para um voo
class ExPortasFull: public Exceptions {
public:
	explicit ExPortasFull(const char* pStr = "Não existem portas de embarque com lugares suficientes para este voo!") : Exceptions(pStr) {}
	virtual ~ExPortasFull() throw() {}
};

#endif
