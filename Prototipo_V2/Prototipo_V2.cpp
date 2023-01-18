#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <windows.h>
#include <cmath>
#include <limits>
#include "clear.h"
#include "cadastro.h"
#include "hashing.h"
#include "arquivo.h"

using namespace std;

clear screen; // limpar a tela do windows
hashing func; // funcoes de hashing dublo
arquivo mode; // acessar arquivos .txt

class mercado
{
private:
	struct dados
	{
		string login; // login para acessar os dados
		int password; // senha
		bool status;
	};

	string login_aux;
	int password_aux;
	dados conta[100];
	int i;        // contadora auxiliar ao struct

	void arquivo()
	{
		for (int j = 0; j < 100; j++)
		{
			conta[j].status = false;
		}

		ifstream login_pass;

		login_pass.open("login.txt", ifstream::in);

		i = 0;

		while (getline(login_pass, conta[i].login))
		{
			login_pass >> conta[i].password;
			login_pass.ignore();
			conta[i].status = true;
			i++;
		}

		login_pass.close();
	}

	void verificar(string log, int pass)
	{
		i = 0;
		bool aux = true;

		while (conta[i].status && aux)
		{
			if (log == conta[i].login && pass == conta[i].password)
			{
				login_aux = log;
				password_aux = pass;
				aux = false;
			}

			i++;
		}
	}

	void fechar()
	{
		i = 0;

		ofstream login_pass;

		login_pass.open("login.txt", ofstream::out);

		while (conta[i].status)
		{
			login_pass << conta[i].login << endl;
			login_pass << conta[i].password << endl;
			i++;
		}

		login_pass.close();
	}

public:
	void criarArquivo()
	{
		arquivo();
	}

	void fecharArquivo()
	{
		fechar();
	}
	// ? Realizar o cadastro do perfil
	void setData(string log, int pass)
	{
		i = 0;

		while (conta[i].status)
		{
			i++;
		}

		conta[i].login = log;
		conta[i].password = pass;
		conta[i].status = true;
	}

	// ? Retorna login para verificação
	string getLogin(string log, int pass)
	{
		verificar(log, pass);
		return login_aux;
	}

	// ? Retorna senha para verificação
	int getPassword()
	{
		return password_aux;
	}
};

int main()
{
	setlocale(LC_ALL, "Portuguese");

	mercado usuario;           // declarando a classe de um usuario
	compra cadastro_c[1000];  // struct para cadastro da compra
	produto cadastro_p[1000]; // struct para cadastro dos produtos por código
	produto cadastro_ps[1000]; // struct para cadastro dos produtos por nome

	list<long long int>::iterator c;
	list<string>::iterator d;
	list<float>::iterator v;
	list<float>::iterator q;

	string auxiliar;
	string login;
	int senha;
	bool exit = true;
	int i = 0;
	long long int aux_codigo;
	string aux_descricao;
	float aux_valor, aux_quantidade;
	int aux_total;
	long long int codigo;
	string descricao;
	float valor;
	int j;

	s comecar; // entrada de dados para o cadastro de itens e compras

	// inicializando struct
	comecar.iniciar(cadastro_c, cadastro_p, cadastro_ps);

	usuario.criarArquivo();

	// criar ou abrir arquivo de produtos e ler os dados dentro dele
	mode.abrirProduto(cadastro_p, cadastro_ps); 
	// criar ou abrir arquivo de compras e ler os dados dentro dele
	mode.abrirCompras(cadastro_c);

	do
	{
		cout << "Controle de supermercado" << endl;
		cout << "\nDeseja se cadastrar ou fazer um login?" << endl;

		cin >> auxiliar;

		if (auxiliar == "cadastrar")
		{
			cin.ignore();
			cout << "Digite um login:" << endl;
			getline(cin, login);
			cout << "Digite uma senha:" << endl;
			cin >> senha;

			usuario.setData(login, senha);

			auxiliar = "login";
		}

		if (auxiliar == "login")
		{
			cin.ignore();
			cout << "\nDigite seu login:" << endl;
			getline(cin, login);
			cout << "Digite sua senha:" << endl;
			cin >> senha;

			while (cin.fail())
			{
				cout << "\nSua senha deve conter apenas nï¿½meros!" << endl;
				cin.clear();
				cin.ignore((numeric_limits<int>::max)(), '\n');
				cout << "Digite sua senha novamente:" << endl;
				cin >> senha;
			}

			do
			{
				if (login == usuario.getLogin(login, senha) && senha == usuario.getPassword())
				{
					do
					{
						int opcao = 0;
						int enter;

						cout << "Digite qualquer nï¿½mero para ir ao menu: ";
						cin >> enter;

						screen.empty();

						cout << "Bem vindo ao controle de gastos" << endl;
						cout << "1 - Cadastrar produtos" << endl;
						cout << "2 - Adicionar nova compra" << endl;
						cout << "3 - Conferir todas as compras" << endl;
						cout << "4 - Verificar se produto estï¿½ cadastrado" << endl;
						cout << "5 - Sair" << endl;

						cin >> opcao;

						switch (opcao)
						{
						case 1:
							comecar.cadastrarProdutos(cadastro_p, cadastro_ps);
							break;
						case 2:
							comecar.cadastrarCompra(cadastro_c, cadastro_p, cadastro_ps);
							break;
						case 3:
							comecar.todasCompras(cadastro_c);
							break;
						case 4:
							cout << "\nDigite o cï¿½digo do produto: ";
							cin >> codigo;

							while (cin.fail())
							{
								cout << "\nSeu cï¿½digo deve conter apenas nï¿½meros!" << endl;
								cin.clear();
								cin.ignore((numeric_limits<int>::max)(), '\n');
								cout << "Digite o cï¿½digo novamente:" << endl;
								cin >> codigo;
							}

							j = func.hash_search(cadastro_p, 1000, codigo);
							cout << endl;
							if (j == -1)
								cout << "Produto nï¿½o cadastrado." << endl;
							else
								cout << cadastro_p[j].codigo << " " << cadastro_p[j].descricao << " " << cadastro_p[j].valor << endl;
							cout << endl;
							break;
						case 5:
							exit = false;
							break;
						default:
							cout << "O numero inserido nï¿½o ï¿½ vï¿½lido" << endl;
							break;
						}
					} while (exit);
				}
				else
				{
					cout << "\nSeus dados estï¿½o invï¿½lidos" << endl;
					cout << "\nDigite seu login:" << endl;
					cin.ignore();
					getline(cin, login);
					cout << "Digite sua senha" << endl;
					cin >> senha;

					while (cin.fail())
					{
						cout << "\nSua senha deve conter apenas nï¿½meros!" << endl;
						cin.clear();
						cin.ignore((numeric_limits<int>::max)(), '\n');
						cout << "Digite sua senha novamente:" << endl;
						cin >> senha;
					}
				}
			} while (exit);
		}

		// Copiando os dados do struct no arquivo de produtos.txt
		mode.fecharProduto(cadastro_p);
		// Copiando os dados do struct no arquivo de compras.txt
		mode.fecharCompras(cadastro_c);

	} while (exit);

	i = 0;
	while (cadastro_c[i].status)
	{
		while (!cadastro_c[i].codigo.empty())
		{
			cadastro_c[i].codigo.pop_front();
			cadastro_c[i].descricao.pop_front();
			cadastro_c[i].quantidade.pop_front();
			cadastro_c[i].valor.pop_front();
		}
		i++;
	}

	usuario.fecharArquivo();

	return 0;
}

