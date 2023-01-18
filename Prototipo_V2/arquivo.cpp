#include "arquivo.h"
#include <fstream>
#include "cadastro.h"
#include <string>
#include "hashing.h"

constexpr auto mod = 1000;

// variaveis auxiliares a entrada de dados do arquivo.txt
long long int aux_codigo; // codigo do produto
std::string aux_descricao; // descricao do produto
float aux_valor; // valor unitário do item
float aux_quantidade;// quantidade do produto
int aux_total; // valor total da compra(P) - Auxiliar a quantidade de itens(C)
std::list<long long int>::iterator c; // varrer a lista de codigo em cadastro.h
std::list<std::string>::iterator d;// varrer a lista de descricao em cadastro.h
std::list<float>::iterator v;// varrer a lista de valor em cadastro.h
std::list<float>::iterator q;// varrer a lista de quantidade em cadastro.h

hashing fnc; // declara as funções de hash

// Abre o arquivo de produtos.txt para colocar dados no struct de produtos em cadastro.h
void arquivo::abrirProduto(produto cadastro_p[1000], produto cadastro_ps[1000]) 
{
	//Transfere os dados do arquivo de texto <produtos.txt>
	// para o struct de produtos, da biblioteca cadastro.h.
	std::ifstream produtos;

	produtos.open("produtos.txt", std::ifstream::in);

	/* Inserindo dados cadastrados:
	* Código do produto
	* Descrição do produto
	* Valor unitário do produto
	* 
	*/while (produtos >> aux_codigo)
	{
		produtos.ignore();
		std::getline(produtos, aux_descricao);
		produtos >> aux_valor;
		// inserindo dados por hashing, da biblioteca hashing.h,
		//de long long int e string
		fnc.hash_insert(cadastro_p, mod, aux_codigo, aux_descricao, aux_valor);
		fnc.hash_inserts(cadastro_ps, mod, aux_descricao, aux_codigo, aux_valor);
	}

	produtos.close();
}

// Abre o arquivo de compras.txt para colocar dados no struct de compras em cadastro.h
void arquivo::abrirCompras(compra cadastro[1000])
{
	std::ifstream compras;

	int i = 0;

	compras.open("compras.txt", std::ifstream::in);

	/* Inserindo dados cadastrados:
	* Dia que a compra foi realizada
	* Mês
	* Ano
	* Total de itens da compra
	* Código do produto
	* Descrição do produto
	* Valor unitário do produto
	* Quantidade <!>
	* Valor total da compra
	* 
	*/while (compras >> cadastro[i].dia)
	{
		compras >> cadastro[i].mes;
		compras >> cadastro[i].ano;
		compras >> cadastro[i].total_itens;
		aux_total = cadastro[i].total_itens;
		while (aux_total--)
		{
			compras >> aux_codigo;
			cadastro[i].codigo.push_back(aux_codigo);
			compras.ignore();
			std::getline(compras, aux_descricao);
			cadastro[i].descricao.push_back(aux_descricao);
			compras >> aux_valor;
			cadastro[i].valor.push_back(aux_quantidade);
			compras >> aux_quantidade;
			cadastro[i].quantidade.push_back(aux_quantidade);
			if (aux_quantidade > 1)
			{
				aux_total += aux_quantidade;
				aux_total++;
			}
		}

		compras >> cadastro[i].total;
		cadastro[i].status = true;
		i++;
	}

	compras.close();
}

// Fechar o arquivo de compras.txt, trasnferindo os dados do struct de compras, em cadastro.h, para compras.txt
void arquivo::fecharCompras(compra cadastro[1000])
{
	std::ofstream compras_saida;

	compras_saida.open("compras.txt", std::ofstream::out);

	int i = 0; // contadora


	while (cadastro[i].status)
	{
		/* Colocando os dados do struct de compras, em cadastro.h,
		* no arquivo comprar.txt
		* Dia da compra
		* Mês
		* Ano
		* Codigo do produto
		* Descricao do produto
		* Valor unitário do produto
		* Quantidade do produto
		* Total da compra
		* 
		*/
		compras_saida << cadastro[i].dia << " ";
		compras_saida << cadastro[i].mes << " ";
		compras_saida << cadastro[i].ano << std::endl;
		compras_saida << cadastro[i].total_itens << std::endl;

		for (c = cadastro[i].codigo.begin(), d = cadastro[i].descricao.begin(), v = cadastro[i].valor.begin(), q = cadastro[i].quantidade.begin(); c != cadastro[i].codigo.end(), d != cadastro[i].descricao.end(), v != cadastro[i].valor.end(), q != cadastro[i].quantidade.end(); c++, d++, v++, q++)
		{
			aux_codigo = *c;
			aux_descricao = *d;
			aux_quantidade = *q;
			aux_valor = *v;

			compras_saida << aux_codigo << std::endl;
			compras_saida << aux_descricao << std::endl;
			compras_saida << aux_valor << std::endl;
			compras_saida << aux_quantidade << std::endl;
		}
		compras_saida << cadastro[i].total << std::endl;
		i++;
	}
}

// Fechar o arquivo de produto.txt, trasnferindo os dados do struct produtos, em cadastro.h, para produtos.txt
void arquivo::fecharProduto(produto cadastro[1000])
{
	std::ofstream produtos_saida;

	produtos_saida.open("produtos.txt", std::ofstream::out);

	int i = 0; // contadora

	for (i = 0; i < 1000; i++)
	{
		if (cadastro[i].status == true)
		{
			/* Copiando os dados da struct no arquivo de produtos.txt
			* Código do produto
			* Descrição do produto
			* Valor unitário do produto
			*/produtos_saida << cadastro[i].codigo << std::endl;
			produtos_saida << cadastro[i].descricao << std::endl;
			produtos_saida << cadastro[i].valor << std::endl;
		}
	}

	produtos_saida.close();
}