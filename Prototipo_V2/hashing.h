#pragma once
#include "cadastro.h"

class hashing
{
public:
	// função para retornar o resto da chave(long long int) em relacao a tabela
	long long int h1(long long int k, int m);

	// auxiliar para o double hashing
	long long int h2(long long int k, int m);

	// double hashing
	long long int hash1(long long int k, int i, int m);

	// retorna a posicao da chave inserida, ou -1 caso nao tenha sido inserida
	long long int hash_insert(produto t[], int m, long long int k, std::string produto, float valor);

	// procurar uma chave na tabela de insert
	long long int hash_search(produto t[], int m, long long int k);

	// remover algum dado da tabela
	long long int hash_remove(produto t[], int m, long long int k);

	// função para retornar o resto da chave(string) em relacao a tabela
	int h1s(std::string k, int m);

	// auxiliar para o double hashing
	int h2s(std::string k, int m);

	// double hashing
	int hash1s(std::string k, int i, int m);

	// retorna a posicao da chave inserida, ou -1 caso nao tenha sido inserida
	int hash_inserts(produto t[], int m, std::string k, long long int codigo, float valor);

	// procurar uma chave na tabela de insert
	int hash_searchs(produto t[], int m, std::string k);

	// remover algum dado da tabela
	int hash_removes(produto t[], int m, std::string k);
};

