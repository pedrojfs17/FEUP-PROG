#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <stdlib.h>
#include <sstream>
#include "DataType.h"
#include "Funcoes.h"

using namespace std;


//LEITURAS

//Ler um numero inteiro.
int Read_Number(string msg)
{
	string line;
	int num = 0;
	float fnum = 0;
	bool error = false;

	do
	{
		cout << msg;
		getline(cin, line);

		error = any_of(line.begin(), line.end(), isalpha); //Ver se tem alguma letra

		if (error)
			cout << "Invalid Input. Can not have letters." << endl;

		if (!error)
		{
			for (auto x : line)  //Ver se tem espaços
			{
				if (isspace(x))
				{
					error = true;
					break;
				}
			}
			if (error)
				cout << "Invalid Input. Can not have spaces." << endl;
		}
		
		if (!error && line == "") // Ver se esta vazio
		{
			error = true;
			cout << "Empty Input. " << endl;
		}

		if (!error)
		{
			try {
				num = stoi(line);
			}
			catch (invalid_argument&) //Ver se tem caracter especial
			{
				error = true;
				cout << "Invalid Input. Can not have special characters." << endl;
			}
			catch (out_of_range&) //Ver se o numero e demasiado grande
			{
				error = true;
				cout << "Invalid Input. Number is to big." << endl;
			}
		}

		if (!error && line.size() != to_string(stoi(line)).size())
		{
			for (auto x : line) 
			{
				if (ispunct(x))
				{
					error = true;
					break;
				}
			}
			if (error)
				cout << "Invalid Input. Can not have special characters." << endl;
		}

	} while (error);

	num = stoi(line);
	return num;
}

//Ler uma data.
Date Read_Date()
{
	Date date;

	do {
		date.year = Read_Number("- Year: ");
		if (date.year < 1000 || date.year > 9999)
			cout << "The year must have 4 digits.\n";
	} while (date.year < 1000 || date.year > 9999);

	if (bissexto(date.year))
	{
		do {
			date.month = Read_Number("- Month: ");
			if (date.month < 1 || date.month > 12)
				cout << "Invalid Month (choose between 1 and 12).\n";
		} while (date.month < 1 || date.month > 12);

		if (date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12)
		{
			do {
				date.day = Read_Number("- Day: ");
				if (date.day < 1 || date.day > 31)
					cout << "Invalid Day (choose between 1 and 31).\n";
			} while (date.day < 1 || date.day > 31);
		}
		else if (date.month == 2)
		{
			do {
				date.day = Read_Number("- Day: ");
				if (date.day < 1 || date.day > 31)
					cout << "Invalid Day (choose between 1 and 29).\n";
			} while (date.day < 1 || date.day > 29);

		}
		else
		{
			do {
				date.day = Read_Number("- Day: ");
				if (date.day < 1 || date.day > 31)
					cout << "Invalid Day (choose between 1 and 30).\n";
			} while (date.day < 1 || date.day > 30);

		}
	}
	else
	{
		do {
			date.month = Read_Number("- Month: ");
			if (date.month < 1 || date.month > 12)
				cout << "Invalid Month (choose between 1 and 12).\n";
		} while (date.month < 1 || date.month > 12);

		if (date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12)
		{
			do {
				date.day = Read_Number("- Day: ");
				if (date.day < 1 || date.day > 31)
					cout << "Invalid Day (choose between 1 and 31).\n";
			} while (date.day < 1 || date.day > 31);
		}
		else if (date.month == 2)
		{
			do {
				date.day = Read_Number("- Day: ");
				if (date.day < 1 || date.day > 31)
					cout << "Invalid Day (choose between 1 and 28).\n";
			} while (date.day < 1 || date.day > 28);

		}
		else
		{
			do {
				date.day = Read_Number("- Day: ");
				if (date.day < 1 || date.day > 31)
					cout << "Invalid Day (choose between 1 and 30).\n";
			} while (date.day < 1 || date.day > 30);

		}
	}

	return date;
}

//Ler uma string.
string Read_String(string msg)
{
	string line;
	bool error = false;

	do
	{
		line = Read_String_With_Numbers(msg);

		error = any_of(line.begin(), line.end(), isdigit); //Ver se tem algum numero

		if (error)
			cout << "Invalid Input. Can not contain numbers." << endl;
	} while (error);

	return line;
}

//Ler string que pode conter qualquer tipo de caracter (minimo uma letra) 
string Read_String_With_Numbers(string msg)
{
	string line;
	bool error = false;

	do
	{
		cout << msg;
		getline(cin, line);

		error = !(any_of(line.begin(), line.end(), isalpha)); //Ver se nao tem letras

		if (error)
			cout << "Invalid Input. It must contain at least one letter." << endl;
	} while (error);

	return line;
}



//CONSTRUCTORS

//Atraves da linha, dividir a morada por caracteristicas.
void Adress_Constructor(string line, Adress &adress)
{
	int count = 0;
	string word = "";

	for (auto x : line)
	{
		if (x == '/')
		{
			while (word[0] == ' ')
				word.erase(0, 1);
			while (word.back() == ' ')
				word.erase(word.size() - 1);

			switch (count) //Atribuir os valores aos parametros de adress
			{
			case 0:
				adress.StreetName = word;
				break;
			case 1:
				adress.Door = word;
				break;
			case 2:
				adress.Floor = word;
				break;
			case 3:
				adress.PostalCode = word;
				break;
			}
			word = "";
			count++;
		}
		else
			word = word + x;
	}
	while (word[0] == ' ')
		word.erase(0, 1);
	while (word.back() == ' ')
		word.erase(word.size() - 1);

	adress.Local = word;
}

//Atraves da linha, dividir a data em dia, mes e ano.
void Date_Constructor(string line, Date &date)
{
	date.day = stoi(line.substr(8, 2));
	date.month = stoi(line.substr(5, 2));
	date.year = stoi(line.substr(0, 4));
}

//Atraves da linha, criar um vetor com os pacotes comprados por um cliente.
void Packs_Boought_Constructor(string line, vector<int> &boughtPacksList)
{
	string word = "";

	if (line == "0")
		boughtPacksList.clear();
	else
	{
		for (auto x : line)
		{
			if (x == ';')
			{
				while (word[0] == ' ')
					word.erase(0, 1);
				while (word.back() == ' ')
					word.erase(word.size() - 1);

				boughtPacksList.push_back(stoi(word));

				word = "";
			}
			else
				word = word + x;
		}
		while (word[0] == ' ')
			word.erase(0, 1);
		while (word.back() == ' ')
			word.erase(word.size() - 1);

		boughtPacksList.push_back(stoi(word));
	}
}

//Atraves da linha, criar um vetor com os locais a visitar de um certo pacote
vector<string> Places_To_Visit(string line)
{
	vector<string> places;

	string local = "";

	for (auto x : line)
	{
		if (x == '-' || x == ',')
		{
			while (local[0] == ' ')
				local.erase(0, 1);
			while (local.back() == ' ')
				local.erase(local.size() - 1);

			places.push_back(local);

			local = "";
		}
		else
			local += x;
	}
	while (local[0] == ' ')
		local.erase(0, 1);
	while (local.back() == ' ')
		local.erase(local.size() - 1);

	places.push_back(local);

	return places;
}

//Fazer o total de transacoes de cada cliente
void Total_transactions(vector<TravelPack> packsList, Client &client)
{
	client.totalTrans = 0;

	for (unsigned int i = 0; i < client.packsBought.size(); i++)
	{
		for (unsigned int j = 0; j < packsList.size(); j++)
		{
			if (client.packsBought[i] == abs(stoi(packsList[j].identifier)))
				client.totalTrans += packsList[j].personCost * client.famAgre;
		}
	}
}



//MENU

void menuCompra(vector<TravelPack> &packsList, vector<Client> &clientsList, string clientsFileName, string packsFileName)
{
	system("cls");

	cout << "__________________________________________________\n" << endl;
	cout << setw(28) << right << "BUY PACK" << endl;
	cout << "__________________________________________________\n" << endl;

	string NIF, identifier;
	bool Found;
	int nif, numClient, numPack;

	do
	{
		Found = false;

		do
		{
			nif = Read_Number("Client's NIF ('0' to go back): ");
			if (nif > 999999999 || (nif < 100000000 && nif != 0))
				cout << "Invalid Input. NIF must contain 9 digits.\n";
		} while (nif > 999999999 || (nif < 100000000 && nif != 0));

		NIF = to_string(nif);

		if (NIF == "0")
			Found = true;

		for (unsigned int j = 0; j < clientsList.size(); j++)
			if (clientsList[j].NIF == NIF)
			{
				Found = true;
				numClient = j;
				break;
			}

		if (!Found)
		{
			cout << "__________________________________________________\n" << endl;
			cout << setw(40) << right << "Client not found! Try again.\n" << endl;
		}
	} while (!Found);

	if (NIF != "0")
	{
		vector<TravelPack> newPacks;
		TravelPack emptypack;
		emptypack.identifier = "0";

		//Mostrar lista dos pacotes disponiveis para compra.
		cout << "__________________________________________________\n" << endl;
		cout << setw(29) << right << "PACKS LIST" << endl;
		cout << "__________________________________________________\n" << endl;
		for (unsigned int i = 0; i < packsList.size(); i++)
		{
			if (stoi(packsList[i].identifier) >= 0 and packsList[i].availableSpots >= clientsList[numClient].famAgre)
			{
				newPacks.push_back(packsList[i]);
				cout << " - " << packsList[i].travelPlaces << " (" << packsList[i].identifier << ")" << endl;
			}
			else
				newPacks.push_back(emptypack);
		}
		cout << "__________________________________________________\n" << endl;

		do
		{
			Found = false;

			identifier = to_string(Read_Number("Pack Identifier ('0' to go back): "));

			if (identifier == "0")
				Found = true;

			for (unsigned int k = 0; k < newPacks.size(); k++)
				if (newPacks[k].identifier == identifier)
				{
					Found = true;
					numPack = k;
					break;
				}

			if (!Found)
			{
				cout << "__________________________________________________\n" << endl;
				cout << setw(39) << right << "Pack not found! Try again.\n" << endl;
			}
		} while (!Found);

		if (identifier != "0")
		{
			if (packsList[numPack].availableSpots < clientsList[numClient].famAgre)
			{
				cout << "__________________________________________________\n" << endl;
				cout << setw(49) << right << "There aren't enough available spots in the pack!\n" << endl;
			}
			else
			{
				Buy_Pack(clientsList[numClient], packsList[numPack]);
				Write_Clients_File(clientsList, clientsFileName);
				Write_Packs_File(packsList, packsFileName);
			}
		}
	}
}

void menuClientes(string clientsFileName, vector<Client> &clientsList, Agency agency, vector<TravelPack> packsList)
{
	Load_Clients(clientsList, agency, packsList);

	system("cls");

	cout << "__________________________________________________\n" << endl;
	cout << setw(28) << right << "CLIENTS" << endl;
	cout << "__________________________________________________\n" << endl;
	cout << "1 - Search Clients\n2 - Add Client\n3 - Remove Client\n4 - Modifiy Client\n\n0 - Back" << endl;
	cout << "__________________________________________________\n" << endl;
	cout << "(Choose one option)" << endl;

	int op;

	do
	{
		op = Read_Number("Option: ");
	} while (cin.fail() || op < 0 || op > 4);

	switch (op)
	{
	case 0:
		break;
	case 1:
		Client_Information(clientsList);
		menuClientes(clientsFileName, clientsList, agency, packsList);
		break;
	case 2:
		Add_Client(clientsFileName, clientsList);
		menuClientes(clientsFileName, clientsList, agency, packsList);
		break;
	case 3:
		Remove_Client(clientsList, clientsFileName);
		menuClientes(clientsFileName, clientsList, agency, packsList);
		break;
	case 4:
		Modify_Client(clientsList, clientsFileName);
		menuClientes(clientsFileName, clientsList, agency, packsList);
		break;
	default:
		break;
	}
}

void menuPacotesVendidos(vector<TravelPack> packsList, vector<Client> clientsList)
{
	system("cls");

	cout << "__________________________________________________\n" << endl;
	cout << setw(29) << right << "SOLD PACKS" << endl;
	cout << "__________________________________________________\n" << endl;
	cout << "1 - All Packs\n2 - Search by Client\n\n0 - Back" << endl;
	cout << "__________________________________________________\n" << endl;
	cout << "(Choose one option)" << endl;

	int op;

	do
	{
		op = Read_Number("Option: ");
	} while (cin.fail() || op < 0 || op > 2);

	switch (op)
	{
	case 0:
		break;
	case 1:
		for (unsigned int i = 0; i < packsList.size(); i++)
		{
			if (packsList[i].soldSpots == 0)
			{
				packsList.erase(packsList.begin() + i);
				i--;
			}
		}
		Pack_Information(packsList);
		break;
	case 2:
		Sold_Client_Packs(clientsList, packsList);
		break;
	default:
		break;
	}
}

void menuVerPacotes(vector<TravelPack> packsList, vector<Client> clientsList)
{
	system("cls");

	cout << "__________________________________________________\n" << endl;
	cout << setw(30) << right << "SEARCH PACKS" << endl;
	cout << "__________________________________________________\n" << endl;
	cout << "1 - All Packs\n2 - Available Packs\n3 - Search by Place\n4 - Search by Date\n5 - Search by Place & Date\n6 - Sold packs\n\n0 - Back" << endl;
	cout << "__________________________________________________\n" << endl;
	cout << "(Choose one option)" << endl;

	int op;

	do
	{
		op = Read_Number("Option: ");
	} while (cin.fail() || op < 0 || op > 6);

	string local;

	switch (op)
	{
	case 0:
		break;
	case 1:
		Pack_Information(packsList);
		menuVerPacotes(packsList, clientsList);
		break;
	case 2:
		Filter_By_Availability(packsList);
		menuVerPacotes(packsList, clientsList);
		break;
	case 3:
		cout << "\n__________________________________________________\n" << endl;
		local = Read_String("Place to visit: ");
		Filter_By_Local(local, packsList);
		menuVerPacotes(packsList, clientsList);
		break;
	case 4:
		Filter_By_Date(packsList, packsList);
		menuVerPacotes(packsList, clientsList);
		break;
	case 5:
		cout << "\n__________________________________________________\n" << endl;
		local = Read_String("Place to visit: ");
		Filter_By_Local(local, packsList, true);
		menuVerPacotes(packsList, clientsList);
	case 6:
		menuPacotesVendidos(packsList, clientsList);
		menuVerPacotes(packsList, clientsList);
		break;
	default:
		break;
	}

}

void menuPacotes(string packsFileName, vector<TravelPack> &packsList, Agency agency, vector<Client> clientsList)
{
	Load_Packs(packsList, agency);

	system("cls");

	cout << "__________________________________________________\n" << endl;
	cout << setw(27) << right << "PACKS" << endl;
	cout << "__________________________________________________\n" << endl;
	cout << "1 - Search Packs\n2 - Add Pack\n3 - Remove Pack\n4 - Modify Pack\n\n0 - Back" << endl;
	cout << "__________________________________________________\n" << endl;
	cout << "(Choose one option)" << endl;

	int op;

	do
	{
		op = Read_Number("Option: ");
	} while (op < 0 || op > 4);

	switch (op)
	{
	case 0:
		break;
	case 1:
		menuVerPacotes(packsList, clientsList);
		menuPacotes(packsFileName, packsList, agency, clientsList);
		break;
	case 2:
		Add_Pack(packsFileName, packsList);
		menuPacotes(packsFileName, packsList, agency, clientsList);
		break;
	case 3:
		Remove_Pack(packsList, packsFileName);
		menuPacotes(packsFileName, packsList, agency, clientsList);
		break;
	case 4:
		Modify_Pack(packsList, packsFileName);
		menuPacotes(packsFileName, packsList, agency, clientsList);
		break;
	default:
		break;
	}

}

int menuInicial(Agency &agency, vector<Client> &clientsList, vector<TravelPack> &packsList)
{
	Load_Clients(clientsList, agency, packsList);
	Load_Packs(packsList, agency);

	system("cls");

	cout << "__________________________________________________\n" << endl;
	cout << setw(23) << right << "AGENCY: " << agency.name << endl;
	cout << "__________________________________________________\n" << endl;
	cout << "1 - Buy Packs\n2 - Clients\n3 - Packs\n4 - Total sales\n\n0 - Leave" << endl;
	cout << "__________________________________________________\n" << endl;
	cout << "(Choose one option)" << endl;

	int op;

	do
	{
		op = Read_Number("Option: ");
	} while (op < 0 || op > 4);

	return op;
}



//FUNCOES

//Ler o ficheiro agency.txt e atribuir os valores à struct agency.
bool Load_Agency(Agency &agency, string agencyFileName)
{
	ifstream agencyFile;
	agencyFile.open(agencyFileName);

	if (agencyFile.is_open())
	{
		for (int i = 0; i < 6; i++)
		{
			string linha;
			int k;
			getline(agencyFile, linha);

			switch (i)
			{
			case 0:
				try {
					k = stoi(linha);
					return false;
				}
				catch (invalid_argument&) {}
				agency.name = linha;
				break;
			case 1:
				agency.NIF = linha;
				break;
			case 2:
				try {
					k = stoi(linha);
					return false;
				}
				catch (invalid_argument&) {}
				agency.url = linha;
				break;
			case 3:
				Adress_Constructor(linha, agency.adress);
				break;
			case 4:
				agency.clientsList = linha;
				break;
			case 5:
				agency.packsList = linha;
				break;
			}
		}
		return true;
	}
	else
		return false;
}

//Ler o ficheiro clients.txt, criar um vetor com os clientes e atriuir os valores à struct clients.
void Load_Clients(vector<Client> &clientsList, Agency agency, vector<TravelPack> packsList)
{
	clientsList.clear();

	ifstream clientsFile;
	clientsFile.open(agency.clientsList);

	if (clientsFile.is_open())
	{
		Client client;
		clientsList.push_back(client);
		int lineNum = 0;
		int clientNum = 0;
		string identifier;

		while (!clientsFile.eof())
		{
			string linha;
			getline(clientsFile, linha);

			switch (lineNum)
			{
			case 0:
				clientsList[clientNum].name = linha;
				break;
			case 1:
				clientsList[clientNum].NIF = linha;
				break;
			case 2:
				clientsList[clientNum].famAgre = stoi(linha);
				break;
			case 3:
				Adress_Constructor(linha, clientsList[clientNum].adress);
				break;
			case 4:
				Packs_Boought_Constructor(linha, clientsList[clientNum].packsBought);
				Total_transactions(packsList, clientsList[clientNum]);
				break;
			default:
				break;
			}

			lineNum++;

			if (linha == "::::::::::")
			{
				lineNum = 0;
				clientNum++;
				clientsList.push_back(client);
			}
		}
	}
	else
		cout << "Error loading Clients file!" << endl;
}

//Ler o ficheiro packs.txt, criar um vetor com os packs e atriuir os valores à struct packs.
void Load_Packs(vector<TravelPack> &packsList, Agency agency)
{
	packsList.clear();

	ifstream packsFile;
	packsFile.open(agency.packsList);

	if (packsFile.is_open())
	{
		TravelPack pack;
		packsList.push_back(pack);
		int lineNum = 0;
		int packNum = 0;

		while (!packsFile.eof())
		{
			string linha;
			getline(packsFile, linha);
			int inicialSpots = 0, soldSpots = 0;

			switch (lineNum)
			{
			case 1:
				packsList[packNum].identifier = linha;
				break;
			case 2:
				packsList[packNum].travelPlaces = linha;
				break;
			case 3:
				Date_Constructor(linha, packsList[packNum].startDate);
				break;
			case 4:
				Date_Constructor(linha, packsList[packNum].endDate);
				break;
			case 5:
				packsList[packNum].personCost = stoi(linha);
				break;
			case 6:
				packsList[packNum].initSpots = stoi(linha);
				break;
			case 7:
				packsList[packNum].soldSpots = stoi(linha);
				packsList[packNum].availableSpots = packsList[packNum].initSpots - packsList[packNum].soldSpots;
				if (packsList[packNum].availableSpots == 0)
					packsList[packNum].identifier = "-" + to_string(abs(stoi(packsList[packNum].identifier)));
				break;
			default:
				break;
			}

			lineNum++;

			if (linha == "::::::::::")
			{
				lineNum = 1;
				packNum++;
				packsList.push_back(pack);
			}
		}
	}
	else
		cout << "Error loading Packs file!" << endl;
}

//Voltar a escrever o ficheiro dos clientes atraves do vector com os clientes todos.
void Write_Clients_File(vector<Client> clientsList, string ClientsFileName)
{
	ofstream newFile;
	newFile.open("newClients.txt");

	for (unsigned int i = 0; i < clientsList.size(); i++)
	{
		newFile << clientsList[i].name << "\n";
		newFile << clientsList[i].NIF << "\n";
		newFile << clientsList[i].famAgre << "\n";
		newFile << clientsList[i].adress.StreetName << " / " << clientsList[i].adress.Door << " / " << clientsList[i].adress.Floor << " /" << clientsList[i].adress.PostalCode << " / " << clientsList[i].adress.Local << "\n";
		for (unsigned int j = 0; j < clientsList[i].packsBought.size(); j++)
		{
			if (j == clientsList[i].packsBought.size() - 1)
				newFile << clientsList[i].packsBought[j];
			else
				newFile << clientsList[i].packsBought[j] << " ; ";
		}
		if (i != clientsList.size() - 1)
			newFile << "\n::::::::::\n";
	}

	const char* fileName = ClientsFileName.c_str();

	newFile.close();
	remove(fileName);
	rename("newClients.txt", fileName);
}

//Voltar a escrever o ficheiro dos pacotes atraves do vector com os pacotes todos.
void Write_Packs_File(vector<TravelPack> packsList, string PacksFileName)
{
	ofstream newFile;
	newFile.open("newPacks.txt");

	newFile << packsList[packsList.size() - 1].identifier << "\n";

	for (unsigned int i = 0; i < packsList.size(); i++)
	{
		newFile << packsList[i].identifier << "\n";
		newFile << packsList[i].travelPlaces << "\n";

		newFile << packsList[i].startDate.year << "/";
		if (packsList[i].startDate.month < 10)
			newFile << "0" << packsList[i].startDate.month << "/";
		else
			newFile << packsList[i].startDate.month << "/";
		if (packsList[i].startDate.day < 10)
			newFile << "0" << packsList[i].startDate.day << "\n";
		else
			newFile << packsList[i].startDate.day << "\n";

		newFile << packsList[i].endDate.year << "/";
		if (packsList[i].endDate.month < 10)
			newFile << "0" << packsList[i].endDate.month << "/";
		else
			newFile << packsList[i].endDate.month << "/";
		if (packsList[i].endDate.day < 10)
			newFile << "0" << packsList[i].endDate.day << "\n";
		else
			newFile << packsList[i].endDate.day << "\n";

		newFile << packsList[i].personCost << "\n";
		newFile << packsList[i].initSpots << "\n";
		newFile << packsList[i].soldSpots;

		if (i != packsList.size() - 1)
			newFile << "\n::::::::::\n";
	}

	const char* fileName = PacksFileName.c_str();

	newFile.close();
	remove(fileName);
	rename("newPacks.txt", fileName);
}

//Adicionar um cliente ao ficheiro dos clientes.
void Add_Client(string clientsFileName, vector<Client> clientsList)
{
	system("cls");

	ofstream clientsFile;
	clientsFile.open(clientsFileName, ios_base::app);

	string rua, andar, postalCode, localidade;
	int NIF, agrFam, numPacotes, pacote, door;
	bool sameNIF;

	clientsFile << "\n::::::::::\n";

	cout << "__________________________________________________\n" << endl;
	cout << setw(29) << right << "NEW CLIENT" << endl;
	cout << "__________________________________________________\n" << endl;

	clientsFile << Read_String("Name: ") << "\n";

	do 
	{
		sameNIF = false;
		NIF = Read_Number("NIF: ");

		for (unsigned int i = 0; i < clientsList.size(); i++)
		{
			if (to_string(NIF) == clientsList[i].NIF)
			{
				cout << "NIF already used." << endl;
				sameNIF = true;
			}
		}

		if ((NIF > 999999999 && !sameNIF) || (NIF < 100000000 && NIF != 0 && !sameNIF))
			cout << "Invalid Input. NIF must contain 9 digits.\n";

	} while (sameNIF || NIF > 999999999 || (NIF < 100000000 && NIF != 0));
	clientsFile << NIF << "\n";

	do
	{
		agrFam = Read_Number("Household: ");
		if (agrFam <= 0)
			cout << "Invalid Input. Household must be higger than 0.\n";
	} while (agrFam <= 0);
	clientsFile << agrFam << "\n";

	cout << "Adress:\n";
	rua = Read_String_With_Numbers(" - Street: ");
	clientsFile << rua << " / ";
	do
	{
		door = Read_Number(" - Door: ");
		if (door <= 0)
			cout << "Invalid Input. Door number must be higher than 0.\n";
	} while (door <= 0);
	clientsFile << door << " / ";
	cout << " - Floor ('-' if it doesn't exist): ";
	getline(cin, andar);
	clientsFile << andar << " /";
	bool error = false;
	int count = 0;
	do
	{
		if (error)
			cout << "Invalid Input. Postal Code must be of type XXXX-XXX (X are digits).\n";
		error = false;
		cout << " - Postal Code: ";
		getline(cin, postalCode);
		for (unsigned int i = 0; i < postalCode.size(); i++)
		{
			if ((i >= 0 && i < 4) || (i < 8 && i > 4))
				if (!isdigit(postalCode[i]))
				{
					error = true;
					break;
				}
			
			if (i == 4)
				if (postalCode[i] != '-')
				{
					error = true;
					break;
				}

			count = i;
		}
		if (postalCode == "" || count != 7)
			error = true;
	} while (error);
	clientsFile << postalCode << " / ";
	clientsFile << Read_String(" - City: ") << "\n";

	do
	{
		numPacotes = Read_Number("Number of bought packs: ");
		if (numPacotes < 0)
			cout << "Invalid Input. It must be higher or equal to 0.\n";
	} while (numPacotes < 0);

	if (numPacotes < 1)
		clientsFile << "0";
	else
	{
		string str;
		for (int i = 1; i <= numPacotes; i++)
		{
			str = "Pack " + to_string(i) + ": ";
			do
			{
				pacote = Read_Number(str);
				if (pacote <= 0)
					cout << "Invalid Input. Identifier must be higher than 0.\n";
			} while (pacote < 0);
			if (i == numPacotes)
				clientsFile << pacote;
			else
				clientsFile << pacote << " ; ";
		}
	}

	cout << "__________________________________________________\n" << endl;
	cout << setw(38) << "Client successfully added!" << endl;
	cout << "__________________________________________________\n" << endl;
	system("pause");
}

//Adicionar um pacote ao ficheiro dos pacotes.
void Add_Pack(string packsFileName, vector<TravelPack> packsList)
{
	system("cls");

	ofstream packsFile;
	packsFile.open(packsFileName, ios_base::app);

	string bestLocal, local;
	int identifier, numLoc, availablespots, soldspots, cost;
	Date beg, end;
	bool sameIdent;
	packsFile << "\n::::::::::\n";

	cout << "__________________________________________________\n" << endl;
	cout << setw(28) << right << "NEW PACK" << endl;
	cout << "__________________________________________________\n" << endl;

	do
	{
		sameIdent = false;

		identifier = Read_Number("Identifier: ");

		for (unsigned int i = 0; i < packsList.size(); i++)
		{
			if (to_string(identifier) == to_string(abs(stoi(packsList[i].identifier))))
			{
				cout << "Identifier already in use." << endl;
				sameIdent = true;
			}
		}

		if (identifier <= 0)
			cout << "Invalid Input. Identifier must be higher than 0." << endl;

	} while (sameIdent || identifier <= 0);
	packsFile << identifier << "\n";
	
	packsFile << Read_String("Main place to visit: ");

	numLoc = Read_Number("Number os places to visit: ");
	if (numLoc < 1)
		packsFile << "\n";
	else
	{
		string str;
		packsFile << " - ";
		for (int i = 1; i <= numLoc; i++)
		{
			str = "Place " + to_string(i) + ": ";
			if (i == numLoc)
				packsFile << Read_String(str) << "\n";
			else
				packsFile << Read_String(str) << " , ";
		}
	}

	do
	{
		cout << "Beginning Date:" << endl;
		beg = Read_Date();
		cout << "End Date:" << endl;
		end = Read_Date();

		if (Compare_Dates(beg, end))
			cout << "\nInvalid Input. The beginning date must be before the end date.\n";
	} while (Compare_Dates(beg, end));

	packsFile << beg.year << "/";
	if (beg.month < 10)
		packsFile << "0" << beg.month << "/";
	else
		packsFile << beg.month << "/";
	if (beg.day < 10)
		packsFile << "0" << beg.day << "\n";
	else
		packsFile << beg.day << "\n";

	packsFile << end.year << "/";
	if (end.month < 10)
		packsFile << "0" << end.month << "/";
	else
		packsFile << end.month << "/";
	if (end.day < 10)
		packsFile << "0" << end.day << "\n";
	else
		packsFile << end.day << "\n";

	do
	{
		cost = Read_Number("Cost (per person): ");
		if (cost < 0)
			cout << "The cost must be higher than 0.\n";
	} while (cost < 0);
	packsFile << cost << "\n";

	do
	{
		availablespots = Read_Number("Initial spots: ");
		if (availablespots <= 0)
			cout << "Invalid Input. Initial spots must be higher than 0.\n";
	} while (availablespots <= 0);
	packsFile << availablespots << "\n";

	do
	{
		soldspots = Read_Number("Sold spots: ");
		if (soldspots < 0)
			cout << "Invalid Input. Sold spots must be higher or equal to 0.\n";
		else if (soldspots > availablespots)
			cout << "Invalid Input. Initial spots must be higher or equal to sold spots.\n";
	} while (soldspots < 0 || soldspots > availablespots);
	packsFile << soldspots;

	cout << "__________________________________________________\n" << endl;
	cout << setw(37) << "Pack successfully added!" << endl;
	cout << "__________________________________________________\n" << endl;
	system("pause");
}

//Modificar a informacao de um cliente e voltar a escrever o ficheiro.
void Modify_Client(vector<Client> &clientsList, string ClientsFileName)
{
	string NIF;
	int nif;
	int numClient;
	bool clientFound = false;

	system("cls");

	cout << "__________________________________________________\n" << endl;
	cout << setw(30) << right << "UPDATE DATA" << endl;
	cout << "__________________________________________________\n" << endl;

	do
	{
		nif = Read_Number("Client's NIF ('0' to go back): ");
		if (nif > 999999999 || (nif < 100000000 && nif != 0))
			cout << "Invalid Input. NIF must contain 9 digits.\n";
	} while (nif > 999999999 || (nif < 100000000 && nif != 0));

	NIF = to_string(nif);

	do
	{
		for (unsigned int i = 0; i < clientsList.size(); i++)
		{
			if (clientsList[i].NIF == NIF)
			{
				clientFound = true;
				numClient = i;
				break;
			}

			if (NIF == "0")
			{
				clientFound = true;
				break;
			}
		}

		if (!clientFound)
		{
			cout << "__________________________________________________\n" << endl;
			cout << setw(40) << right << "Client not found! Try again.\n" << endl;
			NIF = to_string(Read_Number("Clients NIF ('0' to go back): "));
		}
	} while (!clientFound);

	int op;
	bool sameNIF;

	if (NIF != "0")
	{
		do
		{
			system("cls");
			cout << "__________________________________________________\n" << endl;
			cout << setw(30) << right << "UPDATE DATA" << endl;
			cout << "__________________________________________________\n" << endl;
			cout << "1 - Name\n2 - NIF\n3 - Household\n4 - Adress\n5 - Bought Packs\n\n0 - Back" << endl;
			cout << "__________________________________________________\n" << endl;
			cout << "(Choose one option)" << endl;

			do
			{
				op = Read_Number("Option: ");
			} while (op < 0 || op > 5);

			bool error = false;
			int count = 0, agrFam, door;
			string str;

			cout << "__________________________________________________\n" << endl;

			switch (op)
			{
			case 0:
				break;
			case 1:
				clientsList[numClient].name = Read_String("Name: ");
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				system("pause");
				break;
			case 2:
				do
				{
					sameNIF = false;
					nif = Read_Number("NIF: ");

					for (unsigned int i = 0; i < clientsList.size(); i++)
					{
						if (to_string(nif) == clientsList[i].NIF && to_string(nif) != clientsList[numClient].NIF)
						{
							cout << "NIF already in use." << endl;
							sameNIF = true;
							break;
						}
					}

					if ((nif > 999999999 && !sameNIF) || (nif < 100000000 && nif != 0 && !sameNIF))
						cout << "Invalid Input. NIF must contain 9 digits.\n"; 
				} while (nif > 999999999 || (nif < 100000000 && nif != 0) || sameNIF);
				clientsList[numClient].NIF = to_string(nif);
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				system("pause");
				break;
			case 3:
				do
				{
					agrFam = Read_Number("Household: ");
					if (agrFam <= 0)
						cout << "Invalid Input. Household must be higher than 0.\n";
				} while (agrFam <= 0);
				clientsList[numClient].famAgre = agrFam;
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				system("pause");
				break;
			case 4:
				cout << "ADRESS\n";
				clientsList[numClient].adress.StreetName = Read_String_With_Numbers("- Street: ");
				do
				{
					door = Read_Number("- Door: ");
					if (door <= 0)
						cout << "Invalid Input. Door must be higher than 0.\n";
				} while (door <= 0);
				clientsList[numClient].adress.Door = door;
				cout << "- Floor ('-' if it doesn't exist): ";
				getline(cin, clientsList[numClient].adress.Floor);
				do
				{
					if (error)
						cout << "Invalid Input. Postal Code must be of type XXXX-XXX (X are digits).\n";
					error = false;
					cout << "- Postal Code: ";
					getline(cin, clientsList[numClient].adress.PostalCode);
					for (unsigned int i = 0; i < clientsList[numClient].adress.PostalCode.size(); i++)
					{
						if ((i >= 0 && i < 4) || (i < 8 && i > 4))
							if (!isdigit(clientsList[numClient].adress.PostalCode[i]))
							{
								error = true;
								break;
							}

						if (i == 4)
							if (clientsList[numClient].adress.PostalCode[i] != '-')
							{
								error = true;
								break;
							}

						count = i;
					}
					if (clientsList[numClient].adress.PostalCode == "" || count != 7)
						error = true;
				} while (error);
				clientsList[numClient].adress.Local = Read_String("- City: ");
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				system("pause");
				break;
			case 5:
				int numPacotes, pacote;
				do
				{
					numPacotes = Read_Number("Bought packs: ");
					if (numPacotes < 0)
						cout << "Invalid Input. Bought packs must be higher or equal to 0.\n";
				} while (numPacotes < 0);
				
				if (numPacotes < 1)
					clientsList[numClient].packsBought.clear();
				else
				{
					clientsList[numClient].packsBought.clear();
					for (int i = 1; i <= numPacotes; i++)
					{
						str = "Pack " + to_string(i) + ": ";
						do
						{
							pacote = Read_Number(str);
							if (pacote <= 0)
								cout << "Invalid Input. Pack identifier must be higher than 0.\n";
						} while (pacote < 0);
						clientsList[numClient].packsBought.push_back(pacote);
					}
				}
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				system("pause");
				break;
			}
		} while (op != 0);

		Write_Clients_File(clientsList, ClientsFileName);
	}
}

//Modificar a informacao de um pacote e voltar a escrever o ficheiro.
void Modify_Pack(vector<TravelPack> &packsList, string PacksFileName)
{
	string identifier;
	int numPack;
	bool packFound = false;

	system("cls");

	cout << "__________________________________________________\n" << endl;
	cout << setw(30) << right << "UPDATE DATA" << endl;
	cout << "__________________________________________________\n" << endl;

	identifier = to_string(abs(Read_Number("Pack Identifier ('0' to go back): ")));

	do
	{
		for (unsigned int i = 0; i < packsList.size(); i++)
		{
			if (to_string(abs(stoi(packsList[i].identifier))) == identifier)
			{
				cout << "\nPack found!\n";
				packFound = true;
				numPack = i;
				break;
			}

			if (identifier == "0")
			{
				packFound = true;
				break;
			}
		}

		if (!packFound)
		{
			system("cls");
			cout << "__________________________________________________\n" << endl;
			cout << setw(39) << right << "Pack not found! Try again.\n" << endl;
			identifier = to_string(Read_Number("Pack Identifier ('0' to go back): "));
		}
	} while (!packFound);

	int op;

	if (identifier != "0")
	{
		do
		{
			system("cls");
			cout << "__________________________________________________\n" << endl;
			cout << setw(30) << right << "UPDATE DATA" << endl;
			cout << "__________________________________________________\n" << endl;
			cout << "1 - Identifier\n2 - Places to Visit\n3 - Beginning Date\n4 - End Date\n5 - Cost\n6 - Add Sold Spots\n7 - Availability\n\n0 - Back" << endl;
			cout << "__________________________________________________\n" << endl;
			cout << "(Choose one option)" << endl;

			do
			{
				op = Read_Number("Option: ");
			} while (op < 0 || op > 7);

			cout << "__________________________________________________\n" << endl;

			//PARA O CASO 2 PRECISO DESTAS VARIAVEIS MAS NAO POSSO INICIALIZA-LAS DENTRO DO SWITCH
			string str = "", bestLocal, local, str2;
			int numLoc, ident, disp, soldspots;
			bool sameIdent;

			switch (op)
			{
			case 0:
				break;
			case 1:
				do
				{
					sameIdent = false;

					ident = Read_Number("Identifier (same identifier to go back): ");

					for (unsigned int i = 0; i < packsList.size(); i++)
					{
						if (to_string(ident) == to_string(abs(stoi(packsList[i].identifier))) && numPack != i)
						{
							cout << "Identifier already in use." << endl;
							sameIdent = true;
						}
					}

					if (ident <= 0)
						cout << "Invalid Input. Identifier must be higher than 0." << endl;

				} while (sameIdent || ident <= 0);
				packsList[numPack].identifier = to_string(ident);
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				system("pause");
				break;
			case 2:
				str += Read_String("Main place to visit: ");
				numLoc = Read_Number("Number of places to visit : ");
				if (numLoc < 1)
				{
					packsList[numPack].travelPlaces = str;
				}
				else
				{
					str += " - ";
					for (int i = 1; i <= numLoc; i++)
					{
						str2 = "Place " + to_string(i) + ": ";
						local = Read_String(str2);
						if (i == numLoc)
						{
							str += local;
							packsList[numPack].travelPlaces = str;
						}
						else
							str += local + " , ";
					}
				}
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				system("pause");
				break;
			case 3:
				do
				{
					cout << "BEGINNING DATE\n";
					packsList[numPack].startDate = Read_Date();
					if (Compare_Dates(packsList[numPack].startDate, packsList[numPack].endDate))
						cout << "Invalid Input. Beginning date must be before end date.\n";
				} while (Compare_Dates(packsList[numPack].startDate, packsList[numPack].endDate));
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				system("pause");
				break;
			case 4:
				do
				{
					cout << "END DATE\n";
					packsList[numPack].endDate = Read_Date();
					if (Compare_Dates(packsList[numPack].startDate, packsList[numPack].endDate))
						cout << "Invalid Input. End date must be after the beginning date.\n";
				} while (Compare_Dates(packsList[numPack].startDate, packsList[numPack].endDate));
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				system("pause");
				break;
			case 5:
				packsList[numPack].personCost = Read_Number("Cost: ");
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				system("pause");
				break;
			case 6:
				do
				{
					soldspots = Read_Number("How many sold spots: ");
					if (packsList[numPack].availableSpots < soldspots)
						cout << "There aren't enough available spots.\n";
					if (soldspots < 0)
						cout << "Invalid Input. Sold spots must be higher or equal to 0.\n";
				} while (packsList[numPack].availableSpots < soldspots || soldspots < 0);
				packsList[numPack].availableSpots -= soldspots;
				packsList[numPack].soldSpots += soldspots;
				if (packsList[numPack].availableSpots == 0)
				{
					cout << "Pack became Unavailable because there aren't any available spots left.\n";
					packsList[numPack].identifier = "-" + packsList[numPack].identifier;
				}
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				system("pause");
				break;
			case 7:
				if (packsList[numPack].availableSpots == 0)
				{
					cout << "There aren't any available spots left. Can't be available.\n";
					system("pause");
				}
				else
				{
					if (stoi(packsList[numPack].identifier) < 0)
					{
						cout << "The pack is Unavailable. Do you want to make it Available?\n1 - Yes\n0 - No\n\n";
						do
						{
							disp = Read_Number("Option: ");
						} while (disp < 0 || disp > 1);
						if (disp == 1)
							packsList[numPack].identifier = to_string(abs(stoi(packsList[numPack].identifier)));
					}
					else
					{
						cout << "The pack is Available. Do you want to make it Unavailable?\n1 - Yes\n0 - No\n\n";
						do
						{
							disp = Read_Number("Option: ");
						} while (disp < 0 || disp > 1);
						if (disp == 1)
							packsList[numPack].identifier = "-" + packsList[numPack].identifier;
					}
					cout << "__________________________________________________\n" << endl;
					cout << setw(37) << "Successful modification!" << endl;
					cout << "__________________________________________________\n" << endl;
					system("pause");
				}
			}
		} while (op != 0);

		Write_Packs_File(packsList, PacksFileName);
	}
}

//Remover um cliente do vetor dos clientes e voltar a escrever o ficheiro.
void Remove_Client(vector<Client> &clientsList, string ClientsFileName)
{
	system("cls");

	bool clientFound;
	string NIF;
	int nif, clientNum;

	cout << "__________________________________________________\n" << endl;
	cout << setw(31) << right << "REMOVE CLIENT" << endl;
	cout << "__________________________________________________\n" << endl;

	do
	{
		clientFound = false;

		do
		{
			nif = Read_Number("Client's NIF ('0' to go back): ");
			if (nif > 999999999 || (nif < 100000000 && nif != 0))
				cout << "Invalid Input. NIF must contain 9 digits.\n";
		} while (nif > 999999999 || (nif < 100000000 && nif != 0));

		NIF = to_string(nif);

		for (unsigned int i = 0; i < clientsList.size(); i++)
		{
			if (clientsList[i].NIF == NIF || NIF == "0")
			{
				clientFound = true;
				clientNum = i;
			}
		}

		if (!clientFound)
		{
			cout << "__________________________________________________\n" << endl;
			cout << setw(40) << right << "Client not found! Try again.\n" << endl;
		}
	} while (!clientFound);

	if (NIF != "0")
	{
		clientsList.erase(clientsList.begin() + clientNum);

		Write_Clients_File(clientsList, ClientsFileName);
		cout << "__________________________________________________\n" << endl;
		cout << setw(38) << "Client successfully removed!" << endl;
		cout << "__________________________________________________\n" << endl;
		system("pause");
	}
}

//Remover um pacote do vetor dos pacotes e voltar a escrever o ficheiro.
void Remove_Pack(vector<TravelPack> &packsList, string PacksFileName)
{
	system("cls");

	bool packFound = false;
	string identifier;
	int packNum;

	cout << "__________________________________________________\n" << endl;
	cout << setw(30) << right << "REMOVE PACK" << endl;
	cout << "__________________________________________________\n" << endl;

	do
	{
		identifier = to_string(Read_Number("Pack Identifier ('0' to go back): "));

		for (unsigned int i = 0; i < packsList.size(); i++)
		{
			if (abs(stoi(packsList[i].identifier)) == abs(stoi(identifier)))
			{
				packFound = true;
				packNum = i;
			}
		}

		if (!packFound)
		{
			cout << "__________________________________________________\n" << endl;
			cout << setw(39) << right << "Pack not found! Try again.\n" << endl;
		}
	} while (!packFound);

	packsList.erase(packsList.begin() + packNum);

	Write_Packs_File(packsList, PacksFileName);
	cout << "__________________________________________________\n" << endl;
	cout << setw(37) << "Pack successfully removed!" << endl;
	cout << "__________________________________________________\n" << endl;
	system("pause");
}

//Mostrar a informacao de um cliente à escolha.
void Client_Information(vector<Client> clientsList)
{
	system("cls");

	//Mostrar lista dos clientes todos.
	cout << "__________________________________________________\n" << endl;
	cout << setw(34) << right << "CLIENTS LIST" << endl;
	cout << "__________________________________________________\n" << endl;
	
	for (unsigned int i = 0; i < clientsList.size(); i++)
	{
		cout << i + 1 << " - " << clientsList[i].name << " (" << clientsList[i].NIF << ")" << endl;
	}
	cout << "\n0 - Back" << endl;
	cout << "__________________________________________________\n" << endl;

	//Escolher cliente para ver informacao detalhada, ou sair.
	unsigned int op;
	do
	{
		op = Read_Number("Option: ");
	} while (op < 0 || op > clientsList.size());

	if (op != 0)
	{
		Client client = clientsList[op - 1];

		system("cls");

		cout << "_______________________________________________________\n" << endl;
		cout << setw(37) << right << "CLIENT INFORMATION" << endl;
		cout << "_______________________________________________________\n" << endl;
		cout << setw(25) << "Name: ";
		cout << setw(30) << client.name << endl;
		cout << setw(25) << "NIF: ";
		cout << setw(30) << client.NIF << endl;
		cout << setw(25) << "Household: ";
		cout << setw(30) << client.famAgre << endl;
		cout << "_______________________________________________________\n" << endl;
		cout << setw(31) << "ADRESS\n" << endl;
		cout << setw(25) << "Street: ";
		cout << setw(30) << client.adress.StreetName << endl;
		cout << setw(25) << "Door: ";
		cout << setw(30) << client.adress.Door << endl;
		cout << setw(25) << "Floor: ";
		cout << setw(30) << client.adress.Floor << endl;
		cout << setw(25) << "Postal Code: ";
		cout << setw(30) << client.adress.PostalCode << endl;
		cout << setw(25) << "City: ";
		cout << setw(30) << client.adress.Local << endl;
		cout << "_______________________________________________________\n" << endl;
		cout << setw(25) << "Bought Packs: ";
		string str = "";
		if (!client.packsBought.empty())
		{
			for (unsigned int j = 0; j < client.packsBought.size(); j++)
			{
				if (j == client.packsBought.size() - 1)
				{
					str += to_string(client.packsBought[j]);
					cout << setw(30) << str << endl;
				}
				else
					str += to_string(client.packsBought[j]) + " ; ";
			}
		}
		else
			cout << setw(30) << "-" << endl;
		cout << setw(25) << "Total Transactions: ";
		cout << setw(30) << client.totalTrans << endl;
		cout << "_______________________________________________________\n" << endl;

		system("pause");
	}
}

//Mostrar a informacao de um pacote à escolha.
void Pack_Information(vector<TravelPack> packsList)
{
	system("cls");

	//Mostrar lista dos pacotes todos.
	cout << "__________________________________________________\n" << endl;
	cout << setw(29) << right << "PACKS LIST" << endl;
	cout << "__________________________________________________\n" << endl;
	
	for (unsigned int i = 0; i < packsList.size(); i++)
	{
		cout << i + 1 << " - " << packsList[i].travelPlaces << " (" << packsList[i].identifier << ")" << endl;
	}
	cout << "\n0 - Back" << endl;
	cout << "__________________________________________________\n" << endl;

	//Escolher pacote para ver informacao detalhada, ou sair.
	unsigned int op;
	do
	{
		op = Read_Number("Option: ");
	} while (op < 0 || op > packsList.size());

	if (op != 0)
	{
		TravelPack pacote = packsList[op - 1];

		system("cls");

		cout << "_______________________________________________________________________________________________\n" << endl;
		cout << setw(56) << right << "PACK INFORMATION" << endl;
		cout << "_______________________________________________________________________________________________\n" << endl;
		cout << setw(35) << "Identifier: ";
		cout << setw(60) << pacote.identifier << endl;
		cout << setw(35) << "Places to Visit: ";
		cout << setw(60) << pacote.travelPlaces << endl;
		cout << "_______________________________________________________________________________________________\n" << endl;
		cout << setw(35) << "Beginning date: ";
		string str = "";
		str = to_string(pacote.startDate.year) + "/";
		if (pacote.startDate.month < 10)
			str += "0" + to_string(pacote.startDate.month) + "/";
		else
			str += to_string(pacote.startDate.month) + "/";
		if (pacote.startDate.day < 10)
			str += "0" + to_string(pacote.startDate.day);
		else
			str += to_string(pacote.startDate.day);
		cout << setw(60) << str << endl;
		cout << setw(35) << "End Date: ";
		str = to_string(pacote.endDate.year) + "/";
		if (pacote.endDate.month < 10)
			str += "0" + to_string(pacote.endDate.month) + "/";
		else
			str += to_string(pacote.endDate.month) + "/";
		if (pacote.endDate.day < 10)
			str += "0" + to_string(pacote.endDate.day);
		else
			str += to_string(pacote.endDate.day);
		cout << setw(60) << str << endl;
		cout << "_______________________________________________________________________________________________\n" << endl;
		cout << setw(35) << "Cost (per person): ";
		cout << setw(60) << pacote.personCost << endl;
		cout << setw(35) << "Initial Spots: ";
		cout << setw(60) << pacote.initSpots << endl;
		cout << setw(35) << "Sold Spots: ";
		cout << setw(60) << pacote.soldSpots << endl;
		cout << setw(35) << "Available Spots: ";
		cout << setw(60) << pacote.availableSpots << endl;
		cout << "_______________________________________________________________________________________________\n" << endl;

		system("pause");
	}
}

//comparar duas datas (falso se d1 é antes de d2, verdade se d1 é depois de d2)
bool Compare_Dates(Date d1, Date d2)
{
	if (d1.year < d2.year)
		return false;
	else if (d1.year > d2.year)
		return true;
	else if (d1.year == d2.year && d1.month < d2.month)
		return false;
	else if (d1.year == d2.year && d1.month > d2.month)
		return true;
	else if (d1.year == d2.year && d1.month == d2.month && d1.day < d2.day)
		return false;
	else
		return true;
}

//Mostrar a informacao dos pacotes disponiveis
void Filter_By_Availability(vector<TravelPack> packsList)
{
	for (unsigned int i = 0; i < packsList.size(); i++)
	{
		if (stoi(packsList[i].identifier) < 0)
		{
			packsList.erase(packsList.begin() + i);
			i--;
		}
	}

	Pack_Information(packsList);
}

//Mostrar a informacao dos pacotes que contem uma certa localidade.
void Filter_By_Local(string local, vector<TravelPack> packsList, bool FilterDate)
{
	bool check;
	vector<string> places;

	for (unsigned int i = 0; i < packsList.size(); i++)
	{
		check = false;

		places.clear();
		places = Places_To_Visit(packsList[i].travelPlaces);

		for (unsigned int j = 0; j < places.size(); j++)
		{
			if (lowercase(places[j]) == lowercase(local))
			{
				check = true;
				break;
			}
		}

		if (!check)
		{
			packsList.erase(packsList.begin() + i);
			i--;
		}
	}

	if (FilterDate)
		Filter_By_Date(packsList, packsList);
	else
		Pack_Information(packsList);
}

//Mostrar a informacao dos pacotes que estao disponiveis numa certa data.
void Filter_By_Date(vector<TravelPack> packsList, vector<TravelPack> packsListCopy)
{
	Date startdate, enddate;
	bool check;

	cout << "__________________________________________________\n" << endl;
	do
	{
		cout << "Beginning Date:" << endl;
		startdate = Read_Date();
		cout << "End Date:" << endl;
		enddate = Read_Date();

		if (Compare_Dates(startdate, enddate))
			cout << "\nInvalid Input. The beginning date must be before the end date.\n";
	} while (Compare_Dates(startdate, enddate));
	

	for (unsigned int i = 0; i < packsList.size(); i++)
	{
		check = false;

		if (!Compare_Dates(startdate, packsList[i].startDate) && Compare_Dates(enddate, packsList[i].startDate))
			check = true;
		else if (Compare_Dates(startdate, packsList[i].startDate) && !Compare_Dates(startdate, packsList[i].endDate))
			check = true;

		if (!check)
		{
			packsList.erase(packsList.begin() + i);
			i--;
		}
	}

	if (packsList.size() > 0)
		Pack_Information(packsList);
	else
	{
		cout << "__________________________________________________\n" << endl;
		cout << setw(49) << right << "There aren't any available packs in that period." << endl;
		cout << "__________________________________________________\n" << endl;
		cout << "Choose other dates?\n1 - Yes\n0 - No" << endl;
		cout << "__________________________________________________\n" << endl;
		cout << "(Choose one option)" << endl;
		

		int op;

		do
		{
			op = Read_Number("Option: ");
		} while (cin.fail() || op < 0 || op > 1);

		if (op == 1)
		{
			system("cls");
			Filter_By_Date(packsListCopy, packsListCopy);
		}
	}
		
}

//Compra de um pacote que esteja disponivel.
void Buy_Pack(Client &client, TravelPack &pack)
{
	client.packsBought.push_back(stoi(pack.identifier));
	pack.soldSpots += client.famAgre;
	pack.availableSpots -= client.famAgre;
	client.totalTrans += pack.personCost * client.famAgre;

	system("cls");
	cout << "__________________________________________________\n" << endl;
	cout << setw(37) << "Pack successfully bought!" << endl;
	cout << "__________________________________________________\n" << endl;
	system("pause");
}

//Mostrar o total de transacoes da agencia.
void Agency_Transactions(vector<TravelPack> packsList)
{
	int totalTrans = 0;

	for (unsigned int i = 0; i < packsList.size(); i++)
	{
		totalTrans += packsList[i].soldSpots * packsList[i].personCost;
	}

	cout << "__________________________________________________\n" << endl;
	cout << "Total Agency Transactions: " << totalTrans << " euros" << endl;
	cout << "__________________________________________________\n" << endl;
	system("pause");
}

//Mostrar os pacotes vendidos a um certo cliente.
void Sold_Client_Packs(vector<Client> clientsList, vector<TravelPack> packsList)
{
	bool Found;
	string NIF;
	int numClient, nif;

	cout << "__________________________________________________\n" << endl;

	do
	{
		Found = false;

		do
		{
			nif = Read_Number("Client's NIF ('0' to go back): ");
			if (nif > 999999999 || (nif < 100000000 && nif != 0))
				cout << "Invalid Input. NIF must contain 9 digits.\n";
		} while (nif > 999999999 || (nif < 100000000 && nif != 0));

		NIF = to_string(nif);

		if (NIF == "0")
			Found = true;

		for (unsigned int j = 0; j < clientsList.size(); j++)
			if (clientsList[j].NIF == NIF)
			{
				Found = true;
				numClient = j;
				break;
			}

		if (!Found)
		{
			cout << "__________________________________________________\n" << endl;
			cout << setw(40) << right << "Client not found! Try again.\n" << endl;
		}
	} while (!Found);

	if (NIF != "0")
	{
		for (unsigned int i = 0; i < packsList.size(); i++)
		{
			Found = false;

			for (unsigned int k = 0; k < clientsList[numClient].packsBought.size(); k++)
			{
				if (stoi(packsList[i].identifier) == clientsList[numClient].packsBought[k])
					Found = true;
			}

			if (!Found)
			{
				packsList.erase(packsList.begin() + i);
				i--;
			}
		}

		Pack_Information(packsList);
	}
}

//Ver se um ano é bissexto.
bool bissexto(int ano)
{
	if (ano % 4 == 0)
	{
		if (ano % 100 == 0)
			if (ano % 400 == 0)
				return true;
			else
				return false;
		else
			return false;
	}
	else
		return false;
}

//Por uma string em lowercase através do codigo de cada caracter.
string lowercase(string str)
{
	string newstr = "";
	for (auto x : str)
	{
		if (x <= 'Z' && x >= 'A')
			newstr += (x - ('Z' - 'z'));
		else
			newstr += x;
	}

	return newstr;
}