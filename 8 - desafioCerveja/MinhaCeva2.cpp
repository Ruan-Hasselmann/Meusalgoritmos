#include <iostream>
#include <string>
#include <locale.h>
#include <sstream>
#include <time.h>
#include <ctime>
#include <fstream>
#include<bits/stdc++.h>

#define TAM 10
#define NOMEARQUIVO "ceva.dat"

using namespace std;

typedef struct
{
	string data;
	string estilo;
	int nota;
	string fabricante;
} Degustacao;

string pegaDataString()
{
	time_t tempo = time(NULL);
	stringstream data;

	tm *horaLocal = localtime(&tempo);

	data << horaLocal->tm_mday << "/" << 1 + horaLocal->tm_mon << "/"
		 << 1900 + horaLocal->tm_year;

	return data.str();
}

string paraMaiusculo(string palavra)
{
	int i = 0;
	do
	{
		if (palavra[i] == '\n' || palavra[i] == '\0')
		{
			break;
		}
		palavra[i] = toupper(palavra[i]);
		i++;
	} while (1);

	return palavra;
}

void atualizaArquivoComCeva(Degustacao vetor[], int qtdCeva)
{
	ofstream procuradorEscrita;
	procuradorEscrita.open(NOMEARQUIVO);

	for (int i = 0; i < qtdCeva; i++)
	{
		if (vetor[i].data != "")
		{
			procuradorEscrita << vetor[i].data
							  << " " << vetor[i].estilo
							  << " " << vetor[i].nota
							  << " " << vetor[i].fabricante << endl;
		}
	}

	procuradorEscrita.close();
}

void cadastraCerveja(Degustacao vetor[], int n, int qtdCeva)
{
	int i;

	for (i = 0; i < n; i++)
	{
		if (vetor[i].estilo == "")
		{
			break;
		}
	}

	vetor[i].data = pegaDataString();

	cout << "Estilo: ";
	cin >> vetor[i].estilo;

	do
	{
		cout << "Nota geral [0 a 5]: ";
		cin >> vetor[i].nota;
	} while (vetor[i].nota < 0 || vetor[i].nota > 5);

	cout << "Fabricante: ";
	cin >> vetor[i].fabricante;

	vetor[i].estilo = paraMaiusculo(vetor[i].estilo);

	vetor[i].fabricante = paraMaiusculo(vetor[i].fabricante);

	atualizaArquivoComCeva(vetor, qtdCeva);

	cout << "Cerveja cadastrada na degustação!" << endl;

	system("cls");
}

void listaCevaDegustacao(Degustacao vetor[], int qtdCeva)
{
	system("cls");

	for (int i = 0; i < qtdCeva; i++)
	{
		if (vetor[i].data != "")
		{
			cout << "-------------------------" << endl;
			cout << "Data      : " << vetor[i].data << endl;
			cout << "Estilo    : " << vetor[i].estilo << endl;
			cout << "Nota      : " << vetor[i].nota << endl;
			cout << "Fabricante: " << vetor[i].fabricante << endl;
			cout << "-------------------------" << endl;
		}
	}
}

void listaCevaTipo(Degustacao vetor[], int i, int qtdCeva)
{
	system("cls");

	int tipoCeva = 0;
	cout << "Listagem por estilo de cerveja" << endl;
	if (qtdCeva == -1)
	{
		cout << "Nenhuma degusta��o cadastrada..." << endl;
	}
	else
	{
		string estiloPesquisa;

		cout << "Digite o estilo de cerveja para pesquisar: ";
		cin >> estiloPesquisa;

		estiloPesquisa = paraMaiusculo(estiloPesquisa);

		for (int i = 0; i <= qtdCeva; i++)
		{
			if (estiloPesquisa == vetor[i].estilo)
			{
				cout << "-------------------------" << endl;
				cout << "Data      : " << vetor[i].data << endl;
				cout << "Estilo    : " << vetor[i].estilo << endl;
				cout << "Nota      : " << vetor[i].nota << endl;
				cout << "Fabricante: " << vetor[i].fabricante << endl;
				cout << "-------------------------" << endl;
				tipoCeva++;
			}
		}

		cout << "Total de degusta��es do estilo: " << tipoCeva << endl;
	}
}

void organizaNota(Degustacao vetor[], int qtdCeva, int n){
	system("cls");
    cout<<"Enter number of element you want to store: ";
    int arr[qtdCeva],i,j;
    cout<<"Enter array values:\n";
    //taking the array value 
    //from user
    for(i=0;i<n;i++)
    {
        arr[i] = vetor[i].nota;
    }
    //Now we will sort the array
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            //checking if previous value is
            //grater than next one or not
            if(arr[j]>arr[j+1])
            {
                //temp will temporarly store
                //the value of arr[j]
                //then we will swap the values
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    cout<<"After Bubble sort the array is:\n";
    for(i=0;i<n;i++){
    	cout<<arr[i]<<" ";
	}
	cout << endl;
}

void converte(string linha, string *data, string *estilo, int *nota, string *fabricante)
{
	stringstream sData, sEstilo, Nota, sFabricante;

	int parteLinha = 0;
	int i;

	for (i = 0; linha[i] != ' '; i++)
	{
		sData << linha[i];
	}
	sData << "\0";
	stringstream conversaoData(sData.str());
	conversaoData >> *data;

	for (++i; linha[i] != ' '; i++)
	{
		sEstilo << linha[i];
	}
	sEstilo << "\0";
	stringstream conversaoEstilo(sEstilo.str());
	conversaoEstilo >> *estilo;

	for (++i; linha[i] != ' '; i++)
	{
		Nota << linha[i];
	}
	Nota << "\0";
	stringstream conversaoNota(Nota.str());
	conversaoNota >> *nota;

	for (++i; i < linha.length(); i++)
	{
		sFabricante << linha[i];
	}
	sFabricante << "\0";
	stringstream conversaoFabricante(sFabricante.str());
	conversaoFabricante >> *fabricante;
}

int populaCevaArquivo(ifstream &procurador, Degustacao vetor[], int n)
{
	string conteudoLinha;
	int i = 0;

	while (getline(procurador, conteudoLinha))
	{
		converte(conteudoLinha, &vetor[i].data,
				 &vetor[i].estilo,
				 &vetor[i].nota,
				 &vetor[i].fabricante);
		i++;
	}
	return i;
}

void inicializaCeva(Degustacao vetor[], int n)
{
	for (int i = 0; i < n; i++)
	{
		vetor[i].data = "";
		vetor[i].estilo = "";
		vetor[i].nota = 0;
		vetor[i].fabricante = "";
	}
}

int main()
{
	setlocale(LC_ALL, "Portuguese");
	int opcao;
	int qtdCeva = 0;
	Degustacao vetor[TAM];
	inicializaCeva(vetor, TAM);
	ofstream procuradorEscrita;
	ifstream procuradorLeitura;
	procuradorLeitura.open(NOMEARQUIVO);
	if (procuradorLeitura)
	{
		qtdCeva = populaCevaArquivo(procuradorLeitura, vetor, TAM);
		cout << "Arquivo lido para vetor" << endl;
		procuradorLeitura.close();
	}
	else
	{
		procuradorEscrita.open(NOMEARQUIVO);
		procuradorEscrita.close();
	}

	do
	{
		cout << "Menu Degusta Cerveja Artesanal" << endl;
		cout << "1 - Cadastrar degusta��o" << endl;
		cout << "2 - Listar degusta��es" << endl;
		cout << "3 - Lista degusta��es por estilo de cerveja" << endl;
		cout << "4 - Ranking das cervejas" << endl;
		cout << "5 - Sair" << endl;
		cout << "Op��o: ";
		cin >> opcao;

		switch (opcao)
		{
		case 1:
			cout << "Cadastrar degusta��o" << endl;
			if (qtdCeva == TAM)
			{
				cout << "Arquivo lotado." << endl;
			}
			else
			{
				qtdCeva++;
				cadastraCerveja(vetor, TAM, qtdCeva);
			}
			break;
		case 2:
			cout << "Listar degusta��es" << endl;
			if (qtdCeva == 0)
			{
				cout << "Arquivo vazio." << endl;
			}
			else
			{
				listaCevaDegustacao(vetor, qtdCeva);
			}
			break;
		case 3:
			cout << "Lista degusta��es por estilo de cerveja" << endl;
			if (qtdCeva == 0)
			{
				cout << "Arquivo vazio." << endl;
			}
			else
			{
				listaCevaTipo(vetor, TAM, qtdCeva);
			}
			break;
		case 4: //ranking ceva //alterar posição dos vetores de acordo com a maior nota
			cout << "Lista degusta��es por ranking de cerveja" << endl;
			if (qtdCeva == 0)
			{
				cout << "Arquivo vazio." << endl;
			}
			else
			{
				organizaNota(vetor, TAM, qtdCeva);
			}
			break;
		case 5:
			cout << "Obrigado por usar o sistema." << endl;
			break;
		default:
			cout << "Op��o inv�lida." << endl;
		}
	} while (opcao != 5);
	return 1;
}