#include "hashing.h"
#include <string>
#include "cadastro.h"

// função para retornar o resto da chave em relacao a tabela
long long int hashing::h1(long long int k, int m)
{
	long long int res;

	res = k % m;

	if (res < 0)
		res += m;

	return res;
}

// auxiliar para o double hashing
long long int hashing::h2(long long int k, int m)
{
	long long int res;

	res = 1 + (k % (m - 1));

	if (res < 0)
		res += m;

	return res;
}

// double hashing
long long int hashing::hash1(long long int k, int i, int m)
{
	return ((h1(k, m) + i * h2(k, m)) % m);
}

// retorna a posicao da chave inserida, ou -1 caso nao tenha sido inserida
long long int hashing::hash_insert(produto t[], int m, long long int k, std::string produto, float valor)
{
	int i = 0;

	do
	{
		long long int j = hash1(k, i, m);

		if (t[j].status != 1)
		{
			t[j].codigo = k;
			t[j].descricao = produto;
			t[j].valor = valor;
			t[j].status = 1;
			return j;
		}
		else
			i++;
	} while (i != m);

	return -1;
}

// procurar uma chave na tabela de insert
long long int hashing::hash_search(produto t[], int m, long long int k)
{
	int i = 0; // contadora
	long long int j;     // auxiliar

	do
	{
		j = hash1(k, i, m);
		if (t[j].codigo == k)
			return j;
		else
			i++;
	} while (t[j].status != 0 && i < m);

	return -1;
}

// remover algum dado da tabela
long long int hashing::hash_remove(produto t[], int m, long long int k)
{
	long long int j;

	j = hash_search(t, m, k);

	if (j != -1)
	{
		t[j].status = 0;
		t[j].codigo = -1;
		t[j].descricao = "";
		t[j].valor = -1;
		return 0;
	}
	else
		return -1;
}

// fun??o para retornar o resto da chave em relacao a tabela
int hashing::h1s(std::string k, int m)
{
	int sum = 0;
	int res = 0;

	for (int i = 1; i <= (int)k.size(); i++)
	{
		sum += k[i - 1] * pow(13, i - 1);
	}

	res = sum % m;

	if (res < 0)
		res += m;

	return res;
}

// auxiliar para o double hashing
int hashing::h2s(std::string k, int m)
{
	int sum = 0;
	int res = 0;

	for (int i = 1; i <= (int)k.size(); i++)
	{
		sum += k[i - 1] * pow(13, i - 1);
	}

	res = 1 + (sum % (m - 1));

	if (res < 0)
		res += m;

	return res;
}

// double hashing
int hashing::hash1s(std::string k, int i, int m)
{
	return ((h1s(k, m) + i * h2s(k, m)) % m);
}

// retorna a posicao da chave inserida, ou -1 caso nao tenha sido inserida
int hashing::hash_inserts(produto t[], int m, std::string k, long long int codigo, float valor)
{
	int i = 0;

	do
	{
		int j = hash1s(k, i, m);

		if (t[j].status != 1)
		{
			t[j].descricao = k;
			t[j].codigo = codigo;
			t[j].valor = valor;
			t[j].status = 1;
			return j;
		}
		else
			i++;
	} while (i != m);

	return -1;
}

// procurar uma chave na tabela de insert
int hashing::hash_searchs(produto t[], int m, std::string k)
{
	int i = 0; // contadora
	int j; // auxiliar

	do
	{
		j = hash1s(k, i, m);
		if (t[j].descricao == k)
			return j;
		else
			i++;
	} while (t[j].status != 0 && i < m);

	return -1;
}

// remover algum dado da tabela
int hashing::hash_removes(produto t[], int m, std::string k)
{
	int j;

	j = hash_searchs(t, m, k);

	if (j != -1)
	{
		t[j].status = 0;
		t[j].descricao = "";
		t[j].valor = -1;
		t[j].codigo = -1;
		return 0;
	}
	else
		return -1;
}