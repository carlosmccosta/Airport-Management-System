/**\file TipoAviao.h
 * \brief Classe que contém a informação associada a cada tipo de avião.
 *
 * PROJECTO: Projecto 2 - Gestão do embarque dos passageiros num aeroporto (check-in/embarque) \n
 * FICHEIRO: TipoAviao.h \n
 * DESCRIÇÃO: Classe que contém a informação associada a cada tipo de avião. \n
 *
 * TURMA / GRUPO: 2MIEIC1 / 4 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Daniela Filipa Neves Cardeano
 * - Vítor Amálio Maia Martins Moreira
 */


#ifndef TIPOAVIAO_H_
#define TIPOAVIAO_H_

#include <string>

//Foward declarations de classes necessárias (pointers)
class Aviao;

#include "DataHora.h"

using std::string;
using std::vector;


///Classe que contém informação acerca de um determinadp tipo de avião.
class TipoAviao {
private:
	string _nome_tipo;				///<Ex: A321
	string _descricao;				///<Ex: Airbus 321
	unsigned _categoria;			///<Ex: Médio curso

	string _fabricante;				///<Ex: Airbus
	DataHora _data_lancamento; 		///<Data do primeiro voo deste tipo de avião
	unsigned _preco;				///<Preço deste tipo de avião
	unsigned _maximo_passageiros; 	///<Nº de passageiros máximo
	unsigned _autonomia;			///<Em km
	unsigned _velocidade_maxima;	///<Em km/h
	unsigned _numero_motores;
	unsigned _peso_vazio;			///<Em kg
	unsigned _peso_maximo;			///<Em kg
	//Medidas em metros
	unsigned _comprimento;
	unsigned _envergadura;
	unsigned _altura;
	unsigned _altitude_maxima;

	///Vector de apontador de Aviao, que tem os aviões que actualmente estão a usar este TipoAviao.
	vector <Aviao*> _avioes_associados;


public:
	TipoAviao(): _preco(0), _maximo_passageiros(0), _autonomia(0), _velocidade_maxima(0),
	_numero_motores(0), _peso_vazio(0), _peso_maximo(0), _comprimento(0),
	_envergadura(0), _altura(0), _altitude_maxima(0), _avioes_associados() {}
	TipoAviao(string nome_tipo, string descricao, unsigned categoria):
		_nome_tipo(nome_tipo), _descricao(descricao), _categoria(categoria), _avioes_associados() {}
	TipoAviao(string nome_tipo, string descricao, unsigned categoria, string fabricante, DataHora data_lancamento,
			unsigned preco, unsigned maximo_passageiros, unsigned autonomia, unsigned velocidade_maxima,
			unsigned numero_motores, unsigned peso_vazio, unsigned peso_maximo, unsigned comprimento,
			unsigned envergadura, unsigned altura, unsigned altitude_maxima) :
				_nome_tipo(nome_tipo), _descricao(descricao), _categoria(categoria), _fabricante(fabricante), _data_lancamento(data_lancamento),
				_preco(preco), _maximo_passageiros(maximo_passageiros), _autonomia(autonomia), _velocidade_maxima(velocidade_maxima),
				_numero_motores(numero_motores), _peso_vazio(peso_vazio), _peso_maximo(peso_maximo), _comprimento(comprimento),
				_envergadura(envergadura), _altura(altura), _altitude_maxima(altitude_maxima), _avioes_associados() {}
	virtual ~TipoAviao() {}

	string getNomeTipo() const { return _nome_tipo; }
	string getDescricao() const { return _descricao; }
	unsigned getCategoria() const { return _categoria; }
	string getFabricante() const { return _fabricante; }
	DataHora getDataLancamento() const { return _data_lancamento; }
	unsigned getPreco() const { return _preco; }
	unsigned getMaximoPassageiros() const { return _maximo_passageiros; }
	unsigned getAutonomia() const { return _autonomia; }
	unsigned getVelocidadeMaxima() const { return _velocidade_maxima; }
	unsigned getNumeroMotores() const { return _numero_motores; }
	unsigned getPesoVazio() const { return _peso_vazio; }
	unsigned getPesoMaximo() const { return _peso_maximo; }
	unsigned getComprimento() const { return _comprimento; }
	unsigned getEnvergadura() const { return _envergadura; }
	unsigned getAltura() const { return _altura; }
	unsigned getAltitudeMaxima() const { return _altitude_maxima; }

	void setNomeTipo(string nome_tipo) { _nome_tipo = nome_tipo; }
	void setDescricao(string descricao) { _descricao = descricao; }
	void setCategoria(unsigned categoria) { _categoria = categoria; }
	void setFabricante(string fabricante) { _fabricante = fabricante; }
	void setDataLancamento(DataHora data_lancamento) { _data_lancamento = data_lancamento; }
	void setPreco(unsigned preco) { _preco = preco; }
	void setMaximoPassageiros(unsigned maximo_passageiros) { _maximo_passageiros = maximo_passageiros; }
	void setAutonomia(unsigned autonomia) { _autonomia = autonomia; }
	void setVelocidadeMaxima(unsigned velocidade_maxima) { _velocidade_maxima = velocidade_maxima; }
	void setNumeroMotores(unsigned numero_motores) { _numero_motores = numero_motores; }
	void setPesoVazio(unsigned peso_vazio) { _peso_vazio = peso_vazio; }
	void setPesoMaximo(unsigned peso_maximo) { _peso_maximo = peso_maximo; }
	void setComprimento(unsigned comprimento) { _comprimento = comprimento; }
	void setEnvergadura(unsigned envergadura) { _envergadura = envergadura; }
	void setAltura(unsigned altura) { _altura = altura; }
	void setAltitudeMaxima(unsigned altitude_maxima) { _altitude_maxima = altitude_maxima; }


	vector <Aviao*> getAvioesAssociados() const { return _avioes_associados; }
	//Variante dos gets para os vectores, usadas em iteradores constantes
	const vector <Aviao*>& getConstRefAvioesAssociados() const { return _avioes_associados; }
	//Variante do get do vector que permite alterá-lo através da referência que é dada
	vector <Aviao*>& getRefAvioesAssociados() { return _avioes_associados; }


	/**
	 * \brief Operador que permite verificar se dois Tipos de Avião são equivalentes.
	 * \details Compara o nome do tipo de avião.
	 */
	bool operator==(const TipoAviao &tipo_aviao) const;

	///Oprador que verifica se o nome do tipo de um avião é "menor" do que outro.
	bool operator<(const TipoAviao &tipo_aviao) const;
};

#endif
