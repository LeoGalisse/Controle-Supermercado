#include "cadastro.h"
#include <string>
#include <list>
#include <iostream>
#include "clear.h"
#include "hashing.h"
#include <locale>

using namespace std;

clear scr; // limpar a tela do windows
hashing funcoes; // funcoes de hashing dublo

// inicializar status do struct para falso
void s::iniciar(compra cadastro_c[1000], produto cadastro_p[1000], produto cadastro_ps[1000])
{
	for (int i = 0; i < 1000; i++)
	{
		cadastro_c[i].status = false;
		cadastro_p[i].status = false;
		cadastro_ps[i].status = false;
	}
}

// Funcao auxiliar para cadastrar itens
void cadastrar(compra cadastro[1000], produto cadastro_p[1000], produto cadastro_ps[1000], int total, int i)
{
	setlocale(LC_ALL, "Portuguese");
	// variaveis auxiliares para obtencao dos dados
	float valor;
	long long int codigo;
	string descricao;
	float valor_total;
	float quantidade;
	int aux; // auxiliar a obtencao de dados de escolha
	bool auxw = true; // auxiliar para obter os dados corretos
	int k; // obtem retorno da funcao hash
	int j; // contadora

	for (j = 0; j < total; j++)
	{
		auxw = true;
		scr.empty(); // limpar tela

		cout << "\nInsira o código do produto: ";
		cin >> codigo;

		while (cin.fail()) // caso ocorra erro com a entrada de dados, pegue novamente
		{
			cout << "\nSeu c�digo deve conter apenas n�meros!" << endl;
			cin.clear();
			cin.ignore((numeric_limits<int>::max)(), '\n'); // ignora string até o final da mesma
			cout << "Digite o c�digo novamente:" << endl;
			cin >> codigo;
		}

		cadastro[i].codigo.push_back(codigo);

		// procura o código na base da dados e retorna se está cadastrado ou não
		k = funcoes.hash_search(cadastro_p, 1000, codigo);

		if (k == -1) // produto não cadastrado
		{
			while (auxw)
			{
				cout << "\nProduto não cadastrado. Deseja cadastrar (1) ou pular item (2)?" << endl;
				cin >> aux;

				if (aux == 1)
				{
					while (auxw)
					{
						cout << "\nDigite o nome do produto: ";
						cin.ignore();
						getline(cin, descricao);
						cadastro[i].descricao.push_back(descricao);
						cout << "\nInsira a quantidade do item: ";
						cin >> quantidade;

						if (quantidade > 1) // retirando do total quando quantidade
						{					// for maior que 1
							total -= quantidade;
							j--;
						}

						cadastro[i].quantidade.push_back(quantidade);
						cout << "\nDigite o valor unit�rio do produto: ";
						cin >> valor;
						cout << "\nInsira o valor total do produto: ";
						cin >> valor_total;
						cadastro[i].valor.push_back(valor_total);
						cout << endl;

						// conferir se os dados foram inseridos corretamente
						cout << "Você deseja inserir novamente os dados ou estão todos corretos? (inserir novamente - 0)(dados corretos - 1) ";
						cin >> aux;
						cout << endl;

						if (aux == 0) // retirar dados incorretos e continuar while
						{
							auxw = true;
							cadastro[i].descricao.pop_back();
							cadastro[i].quantidade.pop_back();
							cadastro[i].valor.pop_back();

							if (quantidade > 1)
							{
								total += quantidade;
								j++;
							}
						}
						else auxw = false; // dados corretos
					}

					// cadastrar os dados inseridos nos structs, por codigo e descricao
					funcoes.hash_insert(cadastro_p, 1000, codigo, descricao, valor);
					funcoes.hash_inserts(cadastro_ps, 1000, descricao, codigo, valor);

					cout << "\nProduto cadastrado e adicionado às compras, prossiga com os restantes dos itens." << endl;
				}
				else if (aux == 2) // pular item
				{
					cadastro[i].codigo.pop_back();
					auxw = false;
				}
				else cout << "Dados incorretos. Tente novamente" << endl;
			}
		}
		else // produto já cadastrado
		{
			cout << "\n" << cadastro_p[k].codigo << " " << cadastro_p[k].descricao << " " << cadastro_p[k].valor << endl;
			cout << "\nO produto acima é o que você está tentando cadastrar? (sim - 1)(nao - 2): ";
			
			cin >> aux;

			if (aux == 2)
			{
				while (auxw)
				{
					cout << "\nInsira a descrição do produto: ";
					cin.ignore();
					getline(cin, descricao);
					cadastro[i].descricao.push_back(descricao);
					cout << "\nInsira a quantidade do item: ";
					cin >> quantidade;

					if (quantidade > 1)
					{
						total -= quantidade;
						j--;
					}

					cadastro[i].quantidade.push_back(quantidade);
					cout << "\nInsira o valor total dos itens: ";
					cin >> valor_total;
					cadastro[i].valor.push_back(valor_total);
					cout << endl;

					cout << "Você deseja inserir novamente os dados ou estão todos corretos? (inserir novamente - 0)(dados corretos - 1) ";
					cin >> aux;
					cout << endl;

					if (aux == 0)
					{
						auxw = true;

						cadastro[i].descricao.pop_back();
						cadastro[i].quantidade.pop_back();
						cadastro[i].valor.pop_back();

						if (quantidade > 1)
						{
							total += quantidade;
							j++;
						}
					}
					else auxw = false;
				}
			}
			else 
			{
				cadastro[i].descricao.push_back(cadastro_p[k].descricao);
				cout << "\nInsira a quantidade do item: ";
				cin >> quantidade;

				if (quantidade > 1)
				{
					total -= quantidade;
					j--;
					cadastro[i].quantidade.push_back(quantidade);
					cout << "\nInsira o valor total dos itens: ";
					cin >> valor_total;
					cadastro[i].valor.push_back(valor_total);
					cout << endl;
				}
				else
				{
					cadastro[i].valor.push_back(cadastro_p[k].valor);
				}

			}
		}
	}

	cout << "Valor total da compra: ";
	cin >> cadastro[i].total;
	cout << endl;

	cadastro[i].status = true; // compra cadastrada em i
}

void s::cadastrarCompra(compra cadastro[1000], produto cadastro_p[1000], produto cadastro_ps[1000]) // struct para cadastro da compra
{
	setlocale(LC_ALL, "Portuguese");
	int i = 0; // contadora
	int total; // total de itens da compra
	bool finished = true; // quando falsa define que a compra toda foi cadastrada

	do
	{
		if (cadastro[i].status == false)
		{
			cout << "Cadastro de compras" << endl;
			cout << "Coloque o dia, mes e ano da compra respectivamente: ";
			cin >> cadastro[i].dia;
			cin >> cadastro[i].mes;
			cin >> cadastro[i].ano;

			cout << "\nInsira a quantidade de itens totais da compra: ";
			cin >> total;
			cadastro[i].total_itens = total;
			cout << endl;

			cadastrar(cadastro, cadastro_p, cadastro_ps, total, i);

			finished = false; // entrada de dados completa
		}
		else
			i++;

	} while (finished);
}

void s::cadastrarItens(compra cadastro[1000], produto cadastro_p[1000], produto cadastro_ps[1000])
{
	setlocale(LC_ALL, "Portuguese");
	int i = 0; // contadora
	int aux; // auxiliar a contadora
	int dia, mes, ano; // quando a compra foi feita
	int total; // total de itens a serem adicionados

	cout << "Digite dia, mês e ano respectivamente (separado por espaços): ";
	cin >> dia >> mes >> ano;
	cout << endl;

	for (i = 0; i < 1000; i++)
	{
		if (dia == cadastro[i].dia && mes == cadastro[i].mes && ano == cadastro[i].ano)
		{
			aux = i;
			i = 1000;
		}
	}

	i = aux;

	cout << "\nInsira a quantidade de itens a serem adicionados: ";
	cin >> total;
	cadastro[i].total_itens += total;
	cout << endl;

	cadastrar(cadastro, cadastro_p, cadastro_ps, total, i);
}

void s::cadastrarProdutos(produto cadastro_p[1000], produto cadastro_ps[1000])
{
	setlocale(LC_ALL, "Portuguese");
	long long int codigo;
	string descricao;
	float valor;

	cout << "\nDigite o código do produto: ";
	cin >> codigo;

	while (cin.fail())
	{
		cout << "\nSeu código deve conter apenas números!" << endl;
		cin.clear();
		cin.ignore((numeric_limits<int>::max)(), '\n');
		cout << "Digite o código novamente:" << endl;
		cin >> codigo;
	}

	cout << "\nDigite o nome do produto: ";
	cin.ignore();
	getline(cin, descricao);
	cout << "\nDigite o valor unitário do produto: ";
	cin >> valor;

	funcoes.hash_insert(cadastro_p, 1000, codigo, descricao, valor);
	funcoes.hash_inserts(cadastro_ps, 1000, descricao, codigo, valor);
}

void s::todasCompras(compra cadastro[1000])
{
	setlocale(LC_ALL, "Portuguese");
	long long int aux_codigo;
	string aux_descricao;
	float aux_valor, aux_quantidade;
	int i = 0;

	while (cadastro[i].status)
	{
		cout << "Dia  Mês    Ano    Código          Descrição       Valor    Quantidade    " << endl;

		for (cadastro[i].c = cadastro[i].codigo.begin(), cadastro[i].d = cadastro[i].descricao.begin(), cadastro[i].v = cadastro[i].valor.begin(), cadastro[i].q = cadastro[i].quantidade.begin(); cadastro[i].c != cadastro[i].codigo.end(), cadastro[i].d != cadastro[i].descricao.end(), cadastro[i].v != cadastro[i].valor.end(), cadastro[i].q != cadastro[i].quantidade.end(); cadastro[i].c++, cadastro[i].d++, cadastro[i].v++, cadastro[i].q++)
		{
			cout << cadastro[i].dia << "     " << cadastro[i].mes << "     " << cadastro[i].ano << "   ";

			aux_codigo = *cadastro[i].c;
			aux_descricao = *cadastro[i].d;
			aux_quantidade = *cadastro[i].q;
			aux_valor = *cadastro[i].v;

			cout << aux_codigo << "   " << aux_descricao << "   " << aux_valor << "    " << aux_quantidade << endl;
		}

		cout << "Total: " << cadastro[i].total << endl;
		i++;
	}
}
