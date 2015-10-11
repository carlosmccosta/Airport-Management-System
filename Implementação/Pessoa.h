/**\file Pessoa.h
 * \brief Classe que cont�m informa��o acerca de uma Pessoa.
 *
 * PROJECTO: Projecto 2 - Gest�o do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: Pessoa.h \n
 * DESCRI��O: Classe que cont�m informa��o acerca de uma Pessoa. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - V�tor Am�lio Maia Martins Moreira
 */

#ifndef PESSOA_H_
#define PESSOA_H_

#include <string>

using std::string;

/**
 * \brief Classe que cont�m informa��o acerca de uma Pessoa.
 * \details Supeclasse de Passageiro e Tripulante.
 */
class Pessoa {
private:
	string _nome;
	string _morada;
	string _nacionalidade;
	unsigned _contacto;
	unsigned _BI;
	unsigned _idade;

public:
	///Construtor vazio que inicializa uma Pessoa com valores inv�lidos para sinalizar que � necess�rio modifica-los mais tarde.
	Pessoa() : _nome(), _morada(), _nacionalidade(), _contacto(0), _BI(0), _idade(0) {}
	Pessoa(string nome, string morada, string nacionalidade, unsigned contacto, unsigned BI, unsigned idade) :
		_nome(nome), _morada(morada), _nacionalidade(nacionalidade), _contacto(contacto), _BI(BI), _idade(idade) {}

	string getNome() const { return _nome; }
	string getMorada() const { return _morada; }
	string getNacionalidade() { return _nacionalidade; }
	unsigned getContacto() const { return _contacto; }
    unsigned getBI() const { return _BI; }
	unsigned getIdade() const { return _idade; }

	void setNome(string nome) { _nome = nome; }
	void setMorada(string morada) { _morada = morada; }
	void setNacionalidade(string nacionalidade) { _nacionalidade = nacionalidade; }
	void setContacto(unsigned contacto) { _contacto = contacto; }
	void setBI(unsigned BI) { _BI = BI; }
	void setIdade(unsigned idade) { _idade = idade; }

	///Operador que verifica se duas pessoas s�o equivalentes, comparando o seu BI.
	bool operator==(const Pessoa &pessoa);

	/**
	 * \brief Operador que verifica se o nome de uma Pessoa � "menor" do que outra.
	 * \details Caso tenham o mesmo nome, compara os BIs.
	 */
	bool operator<(const Pessoa &pessoa);
};

#endif
