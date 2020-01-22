#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "DataType.h"
#include "Funcoes.h"

using namespace std;

int main()
{
	bool LoadAgency = true;
	string agencyFileName;
	Agency agency;
	vector<Client> clientsList;
	vector<TravelPack> packsList;

	do
	{
		if (!LoadAgency)
		{
			cout << "--------------------------------------------------\nFile not found! Try again.\n\n";
		}

		cout << "Agency file name: ";
		getline(cin, agencyFileName);

		LoadAgency = Load_Agency(agency, agencyFileName);
	} while (!LoadAgency);

	Load_Packs(packsList, agency);
	Load_Clients(clientsList, agency, packsList);

	int op;

	do {
		op = menuInicial(agency, clientsList, packsList);

		switch (op)
		{
		case 0:
			break;
		case 1:
			menuCompra(packsList,clientsList,agency.clientsList, agency.packsList);
			break;
		case 2:
			menuClientes(agency.clientsList, clientsList, agency, packsList);
			break;
		case 3:
			menuPacotes(agency.packsList, packsList, agency, clientsList);
			break;
		case 4:
			Agency_Transactions(packsList);
			break;
		default:
			break;
		}
	} while (op != 0);

	return 0;
}
