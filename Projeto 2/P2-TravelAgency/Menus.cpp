#include "Menus.h"

unsigned mainMenu(Agency agency) //function that accesses all others
{
	int menu;
	int temp;
	int subtemp;
	Packet packet;

	do
	{
		menu = showMenu(agency);

		if (menu == 1)
		{
			do
			{
				temp = showMenu_Clients();
				
				if (temp == 1)
					ClientManager(agency, 0);
				else if (temp == 2)
					ClientManager(agency, 1);
				else if (temp == 3)
					ClientManager(agency, 2);

			} while (temp != 0);
		}
		if (menu == 2)
		{
			do
			{
				temp = showMenu_Packages();

				if (temp == 1)
					PacketManager(agency, 0);
				else if (temp == 2)
					PacketManager(agency, 1);
				else if (temp == 3)
					PacketManager(agency, 2);

			} while (temp != 0);
		}
		if (menu == 3)
		{
			do
			{
				temp = showMenu_InfoView();
				if (temp == 1)
					ShowInfo(agency, 1, 0);
				if (temp == 2)
					ShowInfo(agency, 2, 0);
				if (temp == 3) {
					do
					{
						subtemp = show_AvailablePackages();

						if (subtemp == 1)
							ShowInfo(agency, 3, 1);
						else if (subtemp == 2)
							ShowInfo(agency, 3, 2);
						else if (subtemp == 3)
							ShowInfo(agency, 3, 3);
						else if (subtemp == 4)
							ShowInfo(agency, 3, 4);
					} while (subtemp != 0);
				}
				if (temp == 4)
					ShowInfo(agency, 4, 0);
				if (temp == 5)
					ShowInfo(agency, 5, 0);
				if (temp == 6)
					ShowInfo(agency, 6, 0);
				if (temp == 7)
					ShowInfo(agency, 7, 0);
			} while (temp != 0);
		}
		 if (menu == 4)
		{
			 PacketManager(agency, 3);
		}
	} while (menu != 0);

	if (agency.getClientsChange())
		WriteClientsFile(agency);
	if (agency.getPacketsChange())
		WritePacksFile(agency);

	cout << "__________________________________________________\n" << endl;
	cout << setw(28) << right << "GOODBYE" << endl;
	cout << "__________________________________________________\n" << endl;
	return 0;
}

int showMenu(Agency agency)					//shows main menu
{
	printf("\033[2J");
	cout << "__________________________________________________\n" << endl;
	cout << setw(23) << right << "AGENCY: " << agency.getName() << endl;
	cout << "__________________________________________________\n" << endl;
	cout << "1 - Clients Management\n";
	cout << "2 - Packages Management\n";
	cout << "3 - Data View\n";
	cout << "4 - Buy package\n";
	cout << "\n0 - Exit\n";
	cout << "__________________________________________________\n" << endl;
	cout << "Choose an option (number): ";

	return stoi(CheckForErrorsMenus(5));
}

int showMenu_Clients() //shows clients menu
{
	printf("\033[2J");
	cout << "__________________________________________________\n" << endl;
	cout << setw(28) << right << "CLIENTS" << endl;
	cout << "__________________________________________________\n" << endl;
	cout << "1 - Create Client\n";
	cout << "2 - Modify Client\n";
	cout << "3 - Remove Client\n";
	cout << "\n0 - Return to Main Menu\n";
	cout << "__________________________________________________\n" << endl;
	cout << "Choose an option (number): ";

	return stoi(CheckForErrorsMenus(4));
}

int showMenu_Packages()			//shows packages menu
{
	printf("\033[2J");
	cout << "__________________________________________________\n" << endl;
	cout << setw(26) << right << "PACKETS" << endl;
	cout << "__________________________________________________\n" << endl;
	cout << "1 - Create Package\n";
	cout << "2 - Modify Package\n";
	cout << "3 - Remove Package\n";
	cout << "\n0 - Return to Main Menu\n";
	cout << "__________________________________________________\n" << endl;
	cout << "Choose an option (number): ";

	return stoi(CheckForErrorsMenus(4));
}

int showMenu_InfoView()			//shows information menu
{
	printf("\033[2J");
	cout << "__________________________________________________\n" << endl;
	cout << setw(29) << right << "INFORMATION" << endl;
	cout << "__________________________________________________\n" << endl;
	cout << "1 - View Client Information\n";
	cout << "2 - View All Clients\n";
	cout << "3 - View Available Packages\n";
	cout << "4 - View Sold Packages\n";
	cout << "5 - View Total Revenue\n";
	cout << "6 - View Most visited places\n";
	cout << "7 - View Suggested Places\n";
	cout << "\n0 - Return to Main Menu\n";
	cout << "__________________________________________________\n" << endl;
	cout << "Choose an option (number): ";

	return stoi(CheckForErrorsMenus(8));
}

int show_AvailablePackages() //shows packages menu
{
	printf("\033[2J");
	cout << "__________________________________________________\n" << endl;
	cout << setw(33) << right << "AVAILABLE PACKETS" << endl;
	cout << "__________________________________________________\n" << endl;
	cout << "1 - Show all packages" << endl;
	cout << "2 - Search by destiny" << endl;
	cout << "3 - Search between two dates" << endl;
	cout << "4 - Search by destiny and dates" << endl;
	cout << "\n0 - Return to Previous Menu\n";
	cout << "__________________________________________________\n" << endl;
	cout << "Choose an option (number): ";

	return stoi(CheckForErrorsMenus(5));
}