#pragma once
#include <list>
#include <string>

// * Struct de armazenamento para o cadastro dos produtos
struct produto
{
	long long int codigo; // codigo do produto
	std::string descricao;     // descricao do produto
	float valor;          // valor unitário do produto
	bool status;          // status do vetor de struct para saber se há um produto cadastrado ou não
};

// * Struct de armazenamento dos dados de cada compra cadastrada
struct compra
{
	int dia, mes, ano; // quando a compra foi feita
	// lista de produtos da compra
	std::list<long long int> codigo;
	std::list<std::string> descricao;
	std::list<float> valor;
	std::list<float> quantidade;
	float total;     // valor total da compra
	int total_itens; // numero de itens na compra
	bool status;     // status do vetor de struct para saber se há uma compra cadastrada ou não
	// iteradores para varrer as listas declaradas acima
	std::list<long long int>::iterator c;
	std::list<std::string>::iterator d;
	std::list<float>::iterator v;
	std::list<float>::iterator q;
};

class s
{
public:
	// Inicializar os structs
	void iniciar(compra cadastro_c[1000], produto cadastro_p[1000], produto cadastro_ps[1000]);
	
	// Realizar cadastro de uma nova compra feita
	void cadastrarCompra(compra cadastro[1000], produto cadastro_p[1000], produto cadastro_ps[1000]);

	// Cadastrar itens adicionais a uma compra ja cadastrada
	void cadastrarItens(compra cadastro[1000], produto cadastro_p[1000], produto cadastro_ps[1000]);

	// Cadastrar um produto
	void cadastrarProdutos(produto cadastro_p[1000], produto cadastro_ps[1000]);

	// Mostrar todas as compras já cadastradas
	void todasCompras(compra cadastro[1000]);
};
