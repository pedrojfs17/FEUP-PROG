#include "Utils.h"
#include <algorithm>

vector<Packet> PacketsBoughtConstructor(string line, vector<Packet> packetsList) //reads a string, separates the various ids and recognizes the respective package, inserting it into a vector
{
	vector<Packet> packets;
	string packet = "";
	int packID, testID;

	if (line == "-")
	{
		packets.clear();
		return packets;
	}

	for (size_t x = 0; x < line.length(); x++)
	{
		if (line[x] != ';' && line[x] != ' ')
		{
			packet += line[x];
		}
		else if (packet == "")
			continue;
		else
		{
			packID = stoi(packet);
			packet = "";
			for (size_t i = 0; i < packetsList.size(); i++)
			{
				testID = abs(stoi(packetsList[i].getId()));
				if (packID == testID)
				{
					packets.push_back(packetsList[i]);
					break;
				}
			}
			continue;
		}

		if (packet != "")
		{
			packID = stoi(packet);
			packet = "";
			for (size_t i = 0; i < packetsList.size(); i++)
			{
				testID = abs(stoi(packetsList[i].getId()));
				if (packID == testID)
				{
					packets.push_back(packetsList[i]);
					break;
				}
			}
		}
	}
	return packets;
}

vector<string> SitesConstructor(string line) //reads a line, separates the various places inside a package and returns a vector of said places
{
	vector<string> sites;
	string site = "";

	for (size_t x = 0; x < line.length(); x++)
	{
		if (line[x] == '-' || line[x] == ',' || line[x] == '\n')
		{
			site = site.substr(site.find_first_not_of(" "), site.find_last_not_of(" ") + 1);
			sites.push_back(site);
			site = "";
			continue;
		}
		else
		{
			site += line[x];
		}
	}
	site = site.substr(site.find_first_not_of(" "), site.find_last_not_of(" ") + 1);
	sites.push_back(site);
	return sites;
}

bool is_accent(char c)
{
	if ((int)c < -1)
		return true;
	if ((int)c > 255)
		return true;
	return false;
}

string CheckForErrorsMenus(unsigned menucode) //checks for any error in the menus and returns a correctly inserted user iunput
{ 
	string number = "";
		
	switch (menucode)
	{
	case 5:
		while (CheckReturn(number, 1) || !all_of(number.begin(), number.end(), isdigit) || stoi(number) > 4 ) {
			cout << "Invalid input\nTry again: ";
		}
		break;
	case 4:
		while (CheckReturn(number,1) || !all_of(number.begin(), number.end(), isdigit) || stoi(number) > 3 ) {
			cout << "Invalid input\nTry again: ";
		}
		break;
	case 6:
		while (CheckReturn(number,1) || !all_of(number.begin(), number.end(), isdigit) || stoi(number) > 5 ) {
			cout << "Invalid input\nTry again: ";
		}
		break;
	case 7:
		while (CheckReturn(number,1) || !all_of(number.begin(), number.end(), isdigit) || stoi(number) > 6 ) {
			cout << "Invalid input\nTry again: ";
		}
		break;
	case 8:
		while (CheckReturn(number,1) || !all_of(number.begin(), number.end(), isdigit) || stoi(number) > 7 ) {
			cout << "Invalid input\nTry again: ";
		}
		break;
	}

	return number;
}

struct comp	//struct that allows to compare the values of two keys in a set, ordering it by descending value
{
	template<typename T>
	bool operator()(const T& l, const T& r) const
	{
		if (l.second != r.second)
			return l.second > r.second;

		return l.first > r.first;
	}
};

void PauseOperation()	//pauses the current operation, letting the user see the information before skipping to the next operation
{
	cout << "\nPress any key to continue...";
	cin.get();
}

string CheckForErrorsDate() //checks for any error in a date, and returns a correctly inserted date or returns an empty string if the user wants to cancel an operation (CTRL+Z)
{
	string date, year, month, day;

	do {
		cout << "Year: ";
		year = CheckForNumberErrors();
		if (year == "")
			return "";
		if (stoi(year) < 1900 || stoi(year) > 9999)
			cout << "The year must have 4 digits.\n";
	} while (stoi(year) < 1900 || stoi(year) > 9999);

	if (bissexto(stoi(year)))
	{
		do {
			cout << "Month: ";
			month = CheckForNumberErrors();
			if (month == "")
				return "";
			if (stoi(month) < 1 || stoi(month) > 12)
				cout << "Invalid Month (choose between 1 and 12).\n";
		} while (stoi(month) < 1 || stoi(month) > 12);

		if (stoi(month) == 1 || stoi(month) == 3 || stoi(month) == 5 || stoi(month) == 7 || stoi(month) == 8 || stoi(month) == 10 || stoi(month) == 12)
		{
			do {
				cout << "Day: ";
				day = CheckForNumberErrors();
				if (day == "")
					return "";
				if (stoi(day) < 1 || stoi(day) > 31)
					cout << "Invalid Day (choose between 1 and 31).\n";
			} while (stoi(day) < 1 || stoi(day) > 31);
		}
		else if (stoi(month) == 2)
		{
			do {
				cout << "Day: ";
				day = CheckForNumberErrors();
				if (day == "")
					return "";
				if (stoi(day) < 1 || stoi(day) > 29)
					cout << "Invalid Day (choose between 1 and 29).\n";
			} while (stoi(day) < 1 || stoi(day) > 29);

		}
		else
		{
			do {
				cout << "Day: ";
				day = CheckForNumberErrors();
				if (day == "")
					return "";
				if (stoi(day) < 1 || stoi(day) > 30)
					cout << "Invalid Day (choose between 1 and 30).\n";
			} while (stoi(day) < 1 || stoi(day) > 30);

		}
	}
	else
	{
		do {
			cout << "Month: ";
			month = CheckForNumberErrors();
			if (month == "")
				return "";
			if (stoi(month) < 1 || stoi(month) > 12)
				cout << "Invalid Month (choose between 1 and 12).\n";
		} while (stoi(month) < 1 || stoi(month) > 12);

		if (stoi(month) == 1 || stoi(month) == 3 || stoi(month) == 5 || stoi(month) == 7 || stoi(month) == 8 || stoi(month) == 10 || stoi(month) == 12)
		{
			do {
				cout << "Day: ";
				day = CheckForNumberErrors();
				if (day == "")
					return "";
				if (stoi(day) < 1 || stoi(day) > 31)
					cout << "Invalid Day (choose between 1 and 31).\n";
			} while (stoi(day) < 1 || stoi(day) > 31);
		}
		else if (stoi(month) == 2)
		{
			do {
				cout << "Day: ";
				day = CheckForNumberErrors();
				if (day == "")
					return "";
				if (stoi(day) < 1 || stoi(day) > 28)
					cout << "Invalid Day (choose between 1 and 28).\n";
			} while (stoi(day) < 1 || stoi(day) > 28);
		}
		else
		{
			do {
				cout << "Day: ";
				day = CheckForNumberErrors();
				if (day == "")
					return "";
				if (stoi(day) < 1 || stoi(day) > 30)
					cout << "Invalid Day (choose between 1 and 30).\n";
			} while (stoi(day) < 1 || stoi(day) > 30);
		}
	}

	date = year + "/";
	if (stoi(month) < 10)
		date += "0" + month + "/";
	else
		date += month + "/";
	if (stoi(day) < 10)
		date += "0" + day;
	else
		date += day;

	return date;
}

bool CompareDates(Date d1, Date d2) //compares two dates (false if the d1 is before d2, true if d1 is after d2)
{
	if (d1.getYear() < d2.getYear())
		return false;
	else if (d1.getYear() > d2.getYear())
		return true;
	else if (d1.getYear() == d2.getYear() && d1.getMonth() < d2.getMonth())
		return false;
	else if (d1.getYear() == d2.getYear() && d1.getMonth() > d2.getMonth())
		return true;
	else if (d1.getYear() == d2.getYear() && d1.getMonth() == d2.getMonth() && d1.getDay() < d2.getDay())
		return false;
	else
		return true;
}

bool SameId(Agency & agency, string id) //checks if an id exists inside the agency packages (returns true if it exists, otherwise returns false)
{
	vector<Packet> packets = agency.getPackets();

	for (size_t i = 0; i < packets.size(); i++)
	{
		if (to_string(abs(stoi(packets[i].getId()))) == id)
			return true;
	}

	return false;
}

bool SameNIF(Agency & agency, string nif) //checks if the NIF of a client exists in the agency's clients (returns true if it does, false if it doesn't)
{
	vector<Client> packets = agency.getClients();

	for (size_t i = 0; i < packets.size(); i++)
	{
		if (packets[i].getVATnumber() == nif)
			return true;
	}

	return false;
}

string TotalPurchased(string familySize, vector<Packet> boughtPackets, vector<Packet> packets) //calculates the amount of money a client has spent overall
{
	int totalPurchased = 0;

	for (size_t i = 0; i < boughtPackets.size(); i++)
	{
		for (size_t j = 0; j < packets.size(); j++)
		{
			if (boughtPackets[i].getId() == packets[j].getId())
			{
				totalPurchased += stoi(familySize) * stoi(packets[j].getPricePerPerson());
				break;
			}
			else
				continue;
		}
	}

	return to_string(totalPurchased);
}

bool CheckReturn(string &stringe, unsigned emptyCode) //checks for "CTRL+Z" or "Enter" in an input (true if it is inserted)
{

	getline(cin, stringe);
	if (cin.fail())
		if (cin.eof()) {
			cin.ignore(1000, '\n');
			cin.clear();
			return true;
		}
	if (emptyCode == 1 && stringe.empty())
		return true;
	if (any_of(stringe.begin(), stringe.end(), is_accent))
		return true;
	return false;
}

string CheckForErrorIdentifier(Agency & agency, unsigned functioncode) { //checks for an id error, functioncode is used to see if  a package already exists or doesn´t exist (useful for creating and modifying/removing packages)
	string id;

	if (CheckReturn(id))
		return "";
			
	while (id.empty())
	{
		cout << "Invalid input\nTry again: ";
		if (CheckReturn(id))
			return "";
	}
	switch (functioncode) {
	case 0://criar
		while ((!all_of(id.begin(), id.end(), isdigit)) || cin.fail() || SameId(agency, id))
		{
			cout << "Invalid input \\ Packet already exists\nTry again: ";
			if (CheckReturn(id))
				return "";
		}
		break;
	case (1 or 2)://modificar ou remover
		while ((!all_of(id.begin(), id.end(), isdigit)) || cin.fail() || !SameId(agency, id)||stoi(id)<0)
		{
			cout << "Invalid input \\ Pack does not exist\nTry again: ";
			if (CheckReturn(id))
				return "";
		}
		break;
	case 3:
		while ((!all_of(id.begin(), id.end(), isdigit)) || cin.fail())
		{
			cout << "Invalid input\nTry again: ";
			if (CheckReturn(id))
				return "";
		}
		break;
	}
	return id;
}

string CheckForErrorSites() //checks for errors in sites primarly, also used to check for errors in names
{
	string site;

	if (CheckReturn(site))
		return "";

	while (site.empty())
	{
		cout << "Invalid input\nTry again: ";
		if (CheckReturn(site))
			return "";
	}

	while (any_of(site.begin(), site.end(), isdigit) || cin.fail())
	{
		cout << "Invalid input\nTry again: ";
		if (CheckReturn(site))
			return "";
	}
	return site;
}

string CheckForNumberErrors(unsigned previousseats, unsigned functioncode)//checks for a number error (prices,tickets,...), functioncode is useful for checking if ,for example, the sold tickets the user inserts are higher than the available tickets
{ 
	string number;
	if (CheckReturn(number))
		return "";

	while (number.empty())
	{
		cout << "Invalid input\nTry again: ";
		if (CheckReturn(number))
			return "";
	}

	switch (functioncode)
	{
	case 0:
		if (previousseats == 0) {
			while ((!all_of(number.begin(), number.end(), isdigit)) || cin.fail() || stoi(number) <= 0)
			{
				cout << "Invalid input\nTry again: ";
				if (CheckReturn(number))
					return "";
			}
		}
		else {
			while ((!all_of(number.begin(), number.end(), isdigit)) || cin.fail() || stoi(number) <= 0 || stoul(number) > previousseats)
			{
				cout << "Invalid input\nTry again: ";
				if (CheckReturn(number))
					return "";
			}
		}
		break;
	case 1:
		while ((!all_of(number.begin(), number.end(), isdigit)) || cin.fail() || stoi(number) < 0)
		{
			cout << "Invalid input\nTry again: ";
			if (CheckReturn(number))
				return "";
		}
		break;
	}

	return number;
}

string CheckForErrorNIF(Agency & agency, unsigned functioncode = 0) //checks for error in a NIF, functioncode is useful for alternating between create or modify/remove package
{ 
	string id;

	if (CheckReturn(id))
		return "";

	while (id.empty())
	{
		cout << "Invalid input\nTry again: ";
		if (CheckReturn(id))
			return "";
	}

	switch (functioncode) {
	case 0:
		while ((!all_of(id.begin(), id.end(), isdigit)) || cin.fail() || SameNIF(agency, id))
		{
			cout << "Invalid input \\ Client already exists\nTry again: ";
			if (CheckReturn(id))
				return "";
		}
		break;
	case (1 or 2):
		while ((!all_of(id.begin(), id.end(), isdigit)) || cin.fail() || !SameNIF(agency, id))
		{
			cout << "Invalid input \\ Client does not exist\nTry again: ";
			if (CheckReturn(id))
				return "";
		}
		break;
	case 3:
		while ((!all_of(id.begin(), id.end(), isdigit)) || cin.fail() || SameNIF(agency, id))
		{
			if (SameNIF(agency, id))
				cout << "Invalid input \\ Client already exists\nTry again: ";
			else
				cout << "Invalid Input\nTry again: ";

			if (CheckReturn(id))
				return "";
		}
		break;
	}
	return id;
}

string CheckForErrorStreet(Agency & agency, unsigned functioncode = 0) //check for a street error, returning a correctly inserted user input
{
	string street, copy;
	if (CheckReturn(street))
		return "";

	while (street.empty())
	{
		cout << "Invalid input\nTry again: ";
		if (CheckReturn(street))
			return "";
	}

	copy = street;
	copy.erase(remove(copy.begin(), copy.end(), ' '), copy.end());

	while ((copy.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != copy.npos) || cin.fail())
	{
		cout << "Invalid input\nTry again: ";
		if (CheckReturn(street))
			return "";
		copy = street;
		copy.erase(remove(copy.begin(), copy.end(), ' '), copy.end());
	}
	return street;
}

string CheckForErrorFloor(Agency & agency, unsigned functioncode = 0) //checks for an error in the client's floor, returns a correctly inserted user input
{
	string floor;

	if (CheckReturn(floor))
		return "";

	while (floor.empty())
	{
		cout << "Invalid input\nTry again: ";
		if (CheckReturn(floor))
			return "";
	}

	if (floor == "-")
		return floor;
	else
	{
		while ((floor.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != floor.npos) || cin.fail())
		{
			cout << "Invalid input\nTry again: ";
			if (CheckReturn(floor))
				return "";
		}
		return floor;
	}
}

string CheckForErrorPostalCode(Agency & agency, unsigned functioncode = 0) //checks if the user inserts the postal code correctly
{
	string code;

	if (CheckReturn(code))
		return "";

	while (code.empty() || code.length() < 8)
	{
		cout << "Invalid input\nTry again: ";
		if (CheckReturn(code))
			return "";
	}

	while ((!all_of(code.begin(), code.end() - 4, isdigit)) || (!all_of(code.begin() + 5, code.end(), isdigit)) || code[4] != '-' || cin.fail())
	{
		cout << "Invalid input\nTry again: ";
		if (CheckReturn(code))
			return "";
	}
	return code;
}

void PacketManager(Agency & agency, unsigned functioncode) //uses the functioncode to alternate between the different functions
{
	string new_identifier, new_place, new_date_begin, new_date_end, new_price, new_available, new_sold, site, id;
	string date_begin, date_end;
	vector<string> sites;
	vector<Packet> update, pack_list;
	vector<Client> updateClients;
	int count = 0, new_count = 0, index;
	Packet pack;
	int client;
	string input;

	cout << "\033[2J";
	switch (functioncode) {
	case 0://create package
		cout << "__________________________________________________\n" << endl;
		cout << setw(27) << right << "NEW PACKET" << endl;
		cout << "__________________________________________________\n" << endl;

		cout << "Identifier (Enter Ctrl+Z to exit): ";
		new_identifier = CheckForErrorIdentifier(agency, functioncode);
		if (new_identifier == "")
			break;

		cout << "Destination (Enter Ctrl+Z to exit) (\"Main destination - Site1, Site2, ..., SiteN\" or \"Main Destination\") \n";
		new_place = CheckForErrorSites();
		if (new_place == "")
			break;
		sites = SitesConstructor(new_place);

		cout << "Beginning of trip (Enter Ctrl+Z to exit): " << endl;
		date_begin = CheckForErrorsDate();
		if (date_begin == "")
			break;

		cout << "End of trip (Enter Ctrl+Z to exit): \n";
		do
		{
			date_end = CheckForErrorsDate();
			if (date_end == "")
				break;
			if (CompareDates(Date(date_begin), Date(date_end)))
				cout << "End date must be after the beginning date. Try again.\n";
		} while (CompareDates(Date(date_begin), Date(date_end)));

		cout << "Price (per person) (Enter Ctrl+Z to exit): ";
		new_price = CheckForNumberErrors();
		if (new_price == "")
			break;

		cout << "Available seats (Enter Ctrl+Z to exit): ";
		new_available = CheckForNumberErrors();
		if (new_available == "")
			break;

		do
		{
			cout << "Sold seats (Enter Ctrl+Z to exit): ";
			new_sold = CheckForNumberErrors(stoi(new_available), 1);
			if (new_sold == "")
				break;
			if (stoi(new_sold) > stoi(new_available))
				cout << "The number of sold seats can not be higher than the available seats. Try again.\n";
		} while (stoi(new_sold) > stoi(new_available));
		if (new_sold == "")
			break;
		
		if (new_available == new_sold)
			new_identifier = to_string(-1 * stoi(new_identifier));

		for (size_t x = 0; x < agency.getPackets().size(); x++)
		{
			update.push_back(agency.getPackets()[x]);
		}

		update.push_back(Packet(new_identifier, sites, Date(date_begin), Date(date_end), new_price, new_available, new_sold));			//inserts new packet into vector
		agency.setPackets(update);																										//sets the new agency vector
		agency.setPacketsChange(true);
		cout << "__________________________________________________\n" << endl;
		cout << setw(36) << "Packet successfully added!" << endl;
		cout << "__________________________________________________\n" << endl;
		PauseOperation();
		break;

	case 1://modify package
		cout << "__________________________________________________\n" << endl;
		cout << setw(30) << right << "UPDATE DATA" << endl;
		cout << "__________________________________________________\n" << endl;

		cout << "Identifier of the package you wish to modify (Enter Ctrl+Z to exit): ";
		new_identifier = CheckForErrorIdentifier(agency, 1);
		if (new_identifier == "")
			break;

		update = agency.getPackets();

		for (unsigned i = 0; i < update.size(); i++)
		{
			if (new_identifier == to_string(abs(stoi(update[i].getId()))))
			{
				index = i;
				break;
			}
		}

		int op;

		do
		{
			cout << "__________________________________________________\n" << endl;
			cout << "1 - Destination\n2 - Beginning date\n3 - End date\n4 - Price (per person)\n5 - Available Seats\n6 - Sold seats\n\n0 - Back" << endl;
			cout << "__________________________________________________\n" << endl;
			cout << "Choose one option: ";

			do
			{
				op = stoi(CheckForNumberErrors(0, 1));
			} while (op < 0 || op > 6);

			cout << "__________________________________________________\n" << endl;

			switch (op)
			{
			case 0://returns to menu
				break;
			case 1://modify destinations
				cout << "Destination (Enter Ctrl+Z to cancel) (\"Main destination - Site1, Site2, ..., SiteN\" or \"Main Destination\") \n";
				new_place = CheckForErrorSites();
				if (new_place == "")
					break;
				sites = SitesConstructor(new_place);
				update[index].setSites(sites);
				agency.setPacketsChange(true);
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				PauseOperation();
				break;
			case 2://modify start of the trip
				cout << "Beginning Date (Enter Ctrl+Z to cancel):\n";
				new_date_begin = CheckForErrorsDate();
				if (new_date_begin == "")
					break;
				update[index].setBeginDate(new_date_begin);
				agency.setPacketsChange(true);
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				PauseOperation();
				break;
			case 3://modify end of the trip
				cout << "End Date (Enter Ctrl+Z to cancel):\n";
				do
				{
					new_date_end = CheckForErrorsDate();
					if (new_date_end == "")
						break;
					if (CompareDates(update[index].getBeginDate(), Date(new_date_end)))
						cout << "End date must be after the beginning date. Try again.\n";
				} while (CompareDates(update[index].getBeginDate(), Date(new_date_end)));
				update[index].setEndDate(new_date_end);
				agency.setPacketsChange(true);
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				PauseOperation();
				break;
			case 4://modify price per person
				cout << "Price (per person) (Enter Ctrl+Z to cancel): ";
				new_price = CheckForNumberErrors();
				if (new_price == "")
					break;
				update[index].setPricePerPerson(new_price);
				agency.setPacketsChange(true);
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				PauseOperation();
				break;
			case 5://modify the max seats available
				cout << "Available seats (Enter Ctrl+Z to cancel): ";
				new_available = CheckForNumberErrors();
				if (new_available == "")
					break;
				update[index].setMaxPersons(new_available);
				agency.setPacketsChange(true);
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				PauseOperation();
				break;
			case 6://modify the sold seats
				do
				{
					cout << "Sold seats (Enter Ctrl+Z to exit): ";
					new_sold = CheckForNumberErrors(stoi(update[index].getMaxPersons()), 1);
					if (new_sold == "")
						break;
					if (stoi(new_sold) > stoi(update[index].getMaxPersons()))
						cout << "The number of sold seats can not be higher than the available seats. Try again.\n";
				} while (stoi(new_sold) > stoi(update[index].getMaxPersons()));
				if (new_sold == "")
					break;
				update[index].setSoldTickets(new_sold);
				agency.setPacketsChange(true);
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				PauseOperation();
				break;
			}
		} while (op != 0);
		agency.setPackets(update);		//sets the new agency vector
		break;
	case 2://removes package
		cout << "__________________________________________________\n" << endl;
		cout << setw(29) << right << "REMOVE PACKET" << endl;
		cout << "__________________________________________________\n" << endl;

		cout << "Identifier of the package you wish to remove (Enter Ctrl+Z to exit): ";
		new_identifier = CheckForErrorIdentifier(agency, functioncode);
		if (new_identifier == "")
			break;

		for (size_t z = 0; z < agency.getPackets().size(); z++)
		{
			update.push_back(agency.getPackets()[z]);

		}

		for (size_t x = 0; x < agency.getPackets().size(); x++)
		{
			if (new_identifier == agency.getPackets()[x].getId())
			{
				new_count = (int)x+1;
				update[x].setId(to_string(-1 * new_count));
				agency.setPackets(update);
				agency.setPacketsChange(true);
				break;
			}
		}
		cout << "__________________________________________________\n" << endl;
		cout << setw(36) << "Packet successfully removed!" << endl;
		cout << "__________________________________________________\n" << endl;
		PauseOperation();
		break;
	case 3://buys package
		cout << "__________________________________________________\n" << endl;
		cout << setw(29) << right << "BUY PACKET" << endl;
		cout << "__________________________________________________\n" << endl;

		for (size_t x = 0; x < agency.getClients().size(); x++)
		{
			updateClients.push_back(agency.getClients()[x]);

			if (count >= 1 && x != agency.getPackets().size())
			{
				cout << "\n" << agency.getClients()[x].getName() << " - " << agency.getClients()[x].getVATnumber();
			}
			else {
				count += 1;
				cout << agency.getClients()[x].getName() << " - " << agency.getClients()[x].getVATnumber();
			}
		}
		cout << "\n__________________________________________________\n" << endl;
		cout << "NIF of the client you wish to select (Enter Ctrl+Z to exit): ";
		site = CheckForErrorNIF(agency, 1);
		if (site == "")
			break;

		for (size_t w = 0; w < agency.getClients().size(); w++)
		{
			if (agency.getClients()[w].getVATnumber() == site)
			{
				client = (int)w;
				break;
			}
		}

		cout << "\n__________________________________________________" << endl;

		for (size_t z = 0; z < agency.getPackets().size(); z++)
		{
			update.push_back(agency.getPackets()[z]);

			if (count >= 1 && z != agency.getPackets().size() && stoi(agency.getPackets()[z].getId()) > 0)
			{
				cout << "\n" << agency.getPackets()[z].getId() << " - " << agency.getPackets()[z].getSites()[0];
			}
			else if (stoi(agency.getPackets()[z].getId()) > 0) {
				count += 1;
				cout << agency.getPackets()[z].getId() << " - " << agency.getPackets()[z].getSites()[0];
			}
		}
		cout << "\n__________________________________________________\n" << endl;
		cout << "ID of the package you wish to select (Enter Ctrl+Z to exit): ";
		id = CheckForErrorIdentifier(agency, 1);
		if (id == "")
			break;

		for (size_t m = 0; m < agency.getPackets().size(); m++) {
			if (id == agency.getPackets()[m].getId())
			{
				index = (int)m;
				pack = agency.getPackets()[m];
				break;
			}
		}

		for (size_t q = 0; q < agency.getClients()[client].getPacketList().size(); q++)
		{
			if (agency.getClients()[client].getPacketList()[q].getId() == pack.getId() && (stoi(pack.getSoldTickets()) + stoi(agency.getClients()[client].getFamilySize()))<stoi(pack.getMaxPersons()))
			{
				new_count = stoi(pack.getSoldTickets()) + stoi(agency.getClients()[client].getFamilySize());
				update[index].setSoldTickets(to_string(new_count));
				agency.setPackets(update);
				agency.setClientsChange(true);
				agency.setPacketsChange(true);
				cout << "__________________________________________________\n" << endl;
				cout << setw(36) << "Packet successfully bought!" << endl;
				cout << "__________________________________________________\n" << endl;
				break;
			}
			else if ((agency.getClients()[client].getPacketList()[q].getId() != pack.getId()) && (q == agency.getClients()[client].getPacketList().size() - 1) && (stoi(pack.getSoldTickets()) + stoi(agency.getClients()[client].getFamilySize())) < stoi(pack.getMaxPersons()))
			{
				new_count = stoi(pack.getSoldTickets()) + stoi(agency.getClients()[client].getFamilySize());
				update[index].setSoldTickets(to_string(new_count));
				agency.setPackets(update);
				pack_list = agency.getClients()[client].getPacketList();
				pack_list.push_back(pack);
				updateClients[client].setPacketList(pack_list);
				agency.setClients(updateClients);
				agency.setClientsChange(true);
				agency.setPacketsChange(true);
				cout << "__________________________________________________\n" << endl;
				cout << setw(36) << "Packet successfully bought!" << endl;
				cout << "__________________________________________________\n" << endl;
				break;
			}
			else if ((stoi(pack.getSoldTickets()) + stoi(agency.getClients()[client].getFamilySize())) == stoi(pack.getMaxPersons()))
			{
				new_count =stoi(pack.getMaxPersons());
				update[index].setSoldTickets(to_string(new_count));
				new_count = stoi(pack.getId());
				update[index].setId(to_string(-1 * new_count));
				agency.setPackets(update);
				pack_list = agency.getClients()[client].getPacketList();
				pack_list.push_back(pack);
				updateClients[client].setPacketList(pack_list);
				agency.setClients(updateClients);
				agency.setClientsChange(true);
				agency.setPacketsChange(true);
				break;
			}
			else if ((stoi(pack.getSoldTickets()) + stoi(agency.getClients()[client].getFamilySize())) > stoi(pack.getMaxPersons()))
			{
				cout << "__________________________________________________\n" << endl;
				cout << setw(36) << "Not enough available seats!" << endl;
				cout << "__________________________________________________\n" << endl;
				break;
			}

		}
		PauseOperation();
		break;
	}
}

void ShowInfo(Agency & agency, unsigned functioncode = 0, unsigned subfunctioncode = 0) {

	string site;
	string year_i, month_i, day_i, year_f, month_f, day_f;
	int days_i = 0, days_f = 0, days_ini = 0, days_fi = 0;
	int count = 0;
	int sum = 0;
	int value = 0;
	string n_mostvisited;
	string begDateStr, endDateStr;
	vector<Date> dates;
	map<string, int> mostvisited;

	switch (functioncode)
	{
	case 1://view a single client information
		cout << "\033[2J";
		cout << "__________________________________________________\n" << endl;
		cout << setw(29) << right << "VIEW DATA" << endl;
		cout << "__________________________________________________\n" << endl;

		for (size_t x = 0; x < agency.getClients().size(); x++)
		{
			if (count >= 1 && x != agency.getPackets().size())
			{
				cout << "\n" << agency.getClients()[x].getName() << " - " << agency.getClients()[x].getVATnumber();
			}
			else {
				count += 1;
				cout << agency.getClients()[x].getName() << " - " << agency.getClients()[x].getVATnumber();
			}
		}
		cout << "\n__________________________________________________\n" << endl;
		cout << "Choose a client (Enter Ctrl+Z to exit): ";
		site = CheckForErrorNIF(agency, 1);
		if (site == "")
			break;

		cout << "\033[2J";

		for (size_t x = 0; x < agency.getClients().size(); x++)
		{
			if (agency.getClients()[x].getVATnumber() == site)
			{
				cout << agency.getClients()[x];
				break;
			}
		}
		PauseOperation();
		break;
	case 2://view all clients
		cout << "\033[2J";
		for (size_t x = 0; x < agency.getClients().size(); x++)
		{
			cout << agency.getClients()[x] << endl;
		}
		cout << setw(47) << "Scroll up to see the other clients\n\n";
		PauseOperation();
		break;
	case 3://view package information
		switch (subfunctioncode)
		{
		case 1://view all packages
			cout << "\033[2J";
			cout << "__________________________________________________\n" << endl;
			cout << setw(35) << right << "AVAILABLE DESTINATIONS" << endl;
			cout << "__________________________________________________\n" << endl;
			
			for (size_t x = 0; x < agency.getPackets().size(); x++)
			{
				if (stoi(agency.getPackets()[x].getId()) > 0) //wtf dá merda a comrpar pacotes
				{
					if (count >= 1 && x != agency.getPackets().size())
					{
						cout << "\n--------------------------------------------------\n" << endl;
						cout << agency.getPackets()[x];
					}
					else {
						count += 1;
						cout << agency.getPackets()[x];
					}
				}
			}

			if (count == 0)
				cout << "No available packages";

			PauseOperation();
			break;
		case 2://view package by destination
			cout << "__________________________________________________\n";
			cout << "\nChoose a destination (Enter Ctrl+Z to exit): ";
			site = CheckForErrorSites();
			if (site == "")
				break;
			cout << "\033[2J";
			cout << "__________________________________________________\n" << endl;
			cout << setw(35) << right << "AVAILABLE DESTINATIONS" << endl;
			cout << "__________________________________________________\n" << endl;

			for (size_t x = 0; x < agency.getPackets().size(); x++)
			{
				for (size_t z = 0; z < agency.getPackets()[x].getSites().size(); z++)
				{
					if (agency.getPackets()[x].getSites()[z] == site && stoi(agency.getPackets()[x].getId()) > 0)
					{
						if (count >= 1 && x != agency.getPackets().size())
						{
							cout << "\n--------------------------------------------------\n" << endl;
							cout << agency.getPackets()[x];
						}
						else {
							count += 1;
							cout << agency.getPackets()[x];
						}
						break;
					}
				}
			}

			if (count == 0)
				cout << "No available packages";

			PauseOperation();
			break;
		case 3://view package by dates
			cout << "__________________________________________________\n";
			cout << "\nBeginning of trip (Enter Ctrl+Z to exit)" << endl;
			dates.clear();
			begDateStr = CheckForErrorsDate();
			if (begDateStr == "")
				break;
			dates.push_back(Date(begDateStr));

			cout << "\nEnd of trip (Enter Ctrl+Z to exit)" << endl;
			do
			{
				endDateStr = CheckForErrorsDate();
				if (endDateStr == "")
					break;
				if (CompareDates(dates[0], Date(endDateStr)))
					cout << "End date must be after the beginning date. Try again.\n";
			} while (CompareDates(dates[0], Date(endDateStr)));

			dates.push_back(Date(endDateStr));

			year_i = to_string(dates[0].getYear());
			month_i = to_string(dates[0].getMonth());
			day_i = to_string(dates[0].getDay());

			year_f = to_string(dates[1].getYear());
			month_f = to_string(dates[1].getMonth());
			day_f = to_string(dates[1].getDay());

			days_i = stoi(year_i) * 365 + stoi(month_i) * 12 + stoi(day_i);
			days_f = stoi(year_f) * 365 + stoi(month_f) * 31 + stoi(day_f);

			cout << "\033[2J";
			cout << "__________________________________________________\n" << endl;
			cout << setw(35) << right << "AVAILABLE DESTINATIONS" << endl;
			cout << "__________________________________________________\n" << endl;

			for (size_t x = 0; x < agency.getPackets().size(); x++) {

				days_ini = agency.getPackets()[x].getBeginDate().getDay() + agency.getPackets()[x].getBeginDate().getMonth() * 31 + agency.getPackets()[x].getBeginDate().getYear() * 365;
				days_fi = agency.getPackets()[x].getEndDate().getDay() + agency.getPackets()[x].getEndDate().getMonth() * 31 + agency.getPackets()[x].getEndDate().getYear() * 365;

				if (days_i <= days_ini && days_fi <= days_f && stoi(agency.getPackets()[x].getId()) > 0)
				{
					if (count >= 1 && x != agency.getPackets().size())
					{
						cout << "\n--------------------------------------------------\n" << endl;
						cout << agency.getPackets()[x];
					}
					else {
						count += 1;
						cout << agency.getPackets()[x];
					}
					continue;
				}
			}

			if (count == 0)
				cout << "No available packages";

			PauseOperation();
			break;
		case 4://view packages by destination and dates
			cout << "__________________________________________________\n";
			cout << "\nChoose a destination (Enter Ctrl+Z to exit): ";
			site = CheckForErrorSites();
			if (site == "")
				break;

			cout << "__________________________________________________\n";
			cout << "\nBeginning of trip (Enter Ctrl+Z to exit)" << endl;
			dates.clear();
			begDateStr = CheckForErrorsDate();
			if (begDateStr == "")
				break;
			dates.push_back(Date(begDateStr));

			cout << "\nEnd of trip (Enter Ctrl+Z to exit)" << endl;
			do
			{
				endDateStr = CheckForErrorsDate();
				if (endDateStr == "")
					break;
				if (CompareDates(dates[0], Date(endDateStr)))
					cout << "End date must be after the beginning date. Try again.\n";
			} while (CompareDates(dates[0], Date(endDateStr)));

			dates.push_back(Date(endDateStr));

			year_i = to_string(dates[0].getYear());
			month_i = to_string(dates[0].getMonth());
			day_i = to_string(dates[0].getDay());

			year_f = to_string(dates[1].getYear());
			month_f = to_string(dates[1].getMonth());
			day_f = to_string(dates[1].getDay());
			
			days_i = stoi(year_i) * 365 + stoi(month_i) * 12 + stoi(day_i);
			days_f = stoi(year_f) * 365 + stoi(month_f) * 31 + stoi(day_f);

			cout << "\033[2J";
			cout << "__________________________________________________\n" << endl;
			cout << setw(35) << right << "AVAILABLE DESTINATIONS" << endl;
			cout << "__________________________________________________\n" << endl;

			for (size_t x = 0; x < agency.getPackets().size(); x++) {

				days_ini = agency.getPackets()[x].getBeginDate().getDay() + agency.getPackets()[x].getBeginDate().getMonth() * 31 + agency.getPackets()[x].getBeginDate().getYear() * 365;
				days_fi = agency.getPackets()[x].getEndDate().getDay() + agency.getPackets()[x].getEndDate().getMonth() * 31 + agency.getPackets()[x].getEndDate().getYear() * 365;

				for (size_t z = 0; z < agency.getPackets()[x].getSites().size(); z++)
				{
					if (agency.getPackets()[x].getSites()[z] == site && stoi(agency.getPackets()[x].getId()) > 0 && days_i <= days_ini && days_fi <= days_f)
					{
						if (count >= 1 && x != agency.getPackets().size())
						{
							cout << "\n--------------------------------------------------\n" << endl;
							cout << agency.getPackets()[x];
						}
						else {
							count += 1;
							cout << agency.getPackets()[x];
						}
					}
				}
			}
			if (count == 0)
				cout << "No available packages";
			PauseOperation();
			break;
		}
		break;
	case 4://view sold packages (packages that have at least one sold ticket)

		cout << "\033[2J";
		cout << "__________________________________________________\n" << endl;
		cout << setw(31) << right << "SOLD PACKAGES" << endl;
		cout << "__________________________________________________\n" << endl;

		for (size_t x = 0; x < agency.getPackets().size(); x++)
		{
			if (stoi(agency.getPackets()[x].getSoldTickets()) > 0) {
				if (count >= 1 && x != agency.getPackets().size())
				{
					cout << "\n----------------------\n\n";
					cout << agency.getPackets()[x];
				}
				else {
					count += 1;
					cout << agency.getPackets()[x];
				}
			}
		}

		if (count == 0)
			cout << "No available packages";
		PauseOperation();
		break;
	case 5://view revenue per package and total revenue of the agency

		cout << "\033[2J";
		cout << "__________________________________________________\n" << endl;
		cout << setw(35) << right << "REVENUE PER PACKAGE" << endl;
		cout << "__________________________________________________\n" << endl;
		for (size_t x = 0; x < agency.getPackets().size(); x++)
		{
			for (size_t z = 0; z < agency.getPackets()[x].getSites().size(); z++)
			{
				if (stoi(agency.getPackets()[x].getSoldTickets()) > 0) {
					if (count >= 1 && x != agency.getPackets().size())
					{
						cout << "\n--------------------------------------------------\n" << endl;
						cout << agency.getPackets()[x].getSites()[z] << " - " << stoi(agency.getPackets()[x].getSoldTickets()) * stoi(agency.getPackets()[x].getPricePerPerson());
						sum += stoi(agency.getPackets()[x].getSoldTickets()) * stoi(agency.getPackets()[x].getPricePerPerson());
						break;
					}
					else {
						count += 1;
						cout << agency.getPackets()[x].getSites()[z] << " - " << stoi(agency.getPackets()[x].getSoldTickets()) * stoi(agency.getPackets()[x].getPricePerPerson());
						sum += stoi(agency.getPackets()[x].getSoldTickets()) * stoi(agency.getPackets()[x].getPricePerPerson());
						break;
					}
				}
			}
		}
		cout << "\n__________________________________________________\n" << endl;
		cout << setw(30) << right << "TOTAL REVENUE - " << sum << endl;
		cout << "__________________________________________________\n" << endl;
		PauseOperation();
		break;

	case 6://view the most visited destinations
	{
		for (size_t x = 0; x < agency.getPackets().size(); x++)
		{
			for (size_t z = 0; z < agency.getPackets()[x].getSites().size(); z++)
			{
				if (stoi(agency.getPackets()[x].getSoldTickets()) > 0) {
					if (mostvisited.find(agency.getPackets()[x].getSites()[z]) == mostvisited.end())
						mostvisited[agency.getPackets()[x].getSites()[z]] = stoi(agency.getPackets()[x].getSoldTickets());
					else
					{
						value = mostvisited.at(agency.getPackets()[x].getSites()[z]);
						value += stoi(agency.getPackets()[x].getSoldTickets());
						mostvisited[agency.getPackets()[x].getSites()[z]] = value;
					}
				}
			}

		}
		cout << "__________________________________________________\n";
		cout << "\nChoose the number of most visited places: ";
		n_mostvisited = CheckForNumberErrors((int)mostvisited.size(), 0);
		if (n_mostvisited == "")
			break;

		set<pair<string, int>, comp> set(mostvisited.begin(), mostvisited.end());

		cout << "\033[2J";
		cout << "__________________________________________________\n" << endl;
		cout << setw(33) << right << "MOST VISITED PLACES" << endl;
		cout << "__________________________________________________\n" << endl;

		for (auto const& pair : set) {
			if (count < stoi(n_mostvisited))
			{
				cout << pair.first << " - " << pair.second;
				cout << "\n--------------------------------------------------\n" << endl;
				count++;
			}
			else
				break;
		}
		PauseOperation();
	}
	break;

	case 7://view packages with the most visited destinations, that the client has visited yet
	{
		cout << "\033[2J";

		for (size_t x = 0; x < agency.getPackets().size(); x++)
		{
			for (size_t z = 0; z < agency.getPackets()[x].getSites().size(); z++)
			{
				if (stoi(agency.getPackets()[x].getSoldTickets()) > 0) {
					if (mostvisited.find(agency.getPackets()[x].getSites()[z]) == mostvisited.end())
						mostvisited[agency.getPackets()[x].getSites()[z]] = stoi(agency.getPackets()[x].getSoldTickets());
					else
					{
						value = mostvisited.at(agency.getPackets()[x].getSites()[z]);
						value += stoi(agency.getPackets()[x].getSoldTickets());
						mostvisited[agency.getPackets()[x].getSites()[z]] = value;
					}
				}
			}

		}

		set<pair<string, int>, comp> set(mostvisited.begin(), mostvisited.end());

		bool gone;
		vector<string> suggestions;
		auto firstSetElement = set.begin();
		string firstElem = firstSetElement->first;

		for (size_t x = 0; x < agency.getClients().size(); x++)
		{
			suggestions.clear();
			cout << "__________________________________________________\n" << endl;
			cout << " Cliente - " << agency.getClients()[x].getName() << endl;
			cout << "__________________________________________________" << endl;
			gone = false;
			count = 0;
			
			for (auto const& pair : set) {
				for (size_t y = 0; y < agency.getClients()[x].getPacketList().size(); y++) {
					for (size_t z = 0; z < agency.getClients()[x].getPacketList()[y].getSites().size(); z++) {
						if (agency.getClients()[x].getPacketList()[y].getSites()[z] == pair.first)
						{
							gone = true;
							break;
						}
					}
				}
				if (gone == false)
				{
					suggestions.push_back(PackIdFromSite(pair.first, agency));
					count++;
					break;
				}
				else
					gone = false;
				if (count == 1)
					break;
				else
					continue;
			}

			if (suggestions.size() == 0)
			{
				cout << "Already visited all locations.\nYou could repeat this trip\n";
				suggestions.push_back(PackIdFromSite(firstElem, agency));
			}

			cout << "\n--------------------------------------------------\n";

			for (size_t j = 0; j < agency.getPackets().size(); j++)
			{
				if (suggestions[0] == to_string(abs(stoi(agency.getPackets()[j].getId())))) 
				{
					cout << agency.getPackets()[j] << "--------------------------------------------------\n";
				}
			}

			suggestions.clear();
		}

		PauseOperation();
	}
	break;
	}
}

void ClientManager(Agency & agency, unsigned functioncode) { //uses the function code to alternate between functions
	string new_name, new_vat_number, new_family_size, new_address = "", new_packs_bought = "", new_total_purchased = "0";
	string new_street, new_door, new_floor, new_postal_code, new_location, num_packs, new_pack, nif;
	vector<Packet> new_packets_bought;
	vector<Client> update;
	vector<Client> clientsList = agency.getClients();
	int count = 0;

	cout << "\033[2J";
	switch (functioncode) {
	case 0: //create client
		cout << "__________________________________________________\n" << endl;
		cout << setw(29) << right << "NEW CLIENT" << endl;
		cout << "__________________________________________________\n" << endl;

		cout << "Name (Enter Ctrl+Z to exit): ";
		new_name = CheckForErrorSites();
		if (new_name == "")
			break;

		cout << "NIF (Enter Ctrl+Z to exit): ";
		new_vat_number = CheckForErrorNIF(agency, 3);
		if (new_vat_number == "")
			break;

		cout << "Family Size (Enter Ctrl+Z to exit): ";
		new_family_size = CheckForNumberErrors();
		if (new_family_size == "")
			break;

		cout << "Address (Enter Ctrl+Z to exit): " << endl;
		cout << " - Street: ";
		new_street = CheckForErrorStreet(agency);
		if (new_street == "")
			break;
		new_address += new_street + " / ";

		cout << " - Door Number: ";
		new_door = CheckForNumberErrors();
		if (new_door == "")
			break;
		new_address += new_door + " / ";

		cout << " - Floor: ";
		new_floor = CheckForErrorFloor(agency);
		if (new_floor == "")
			break;
		new_address += new_floor + " / ";

		cout << " - Postal-code: ";
		new_postal_code = CheckForErrorPostalCode(agency);
		if (new_postal_code == "")
			break;
		new_address += new_postal_code + " / ";

		cout << " - Location: ";
		new_location = CheckForErrorSites();
		if (new_location == "")
			break;
		new_address += new_location;

		cout << "Bought Packs (Enter Ctrl+Z to exit): \n How many? ";
		num_packs = CheckForNumberErrors(0,1);
		if (num_packs == "")
			break;
		if (stoi(num_packs) > 0)
		{
			for (int i = 0; i < stoi(num_packs); i++)
			{
				cout << "Pacote " << i + 1 << ": ";
				new_pack = CheckForErrorIdentifier(agency, 1);
				if (new_pack == "")
					break;
				new_packs_bought += new_pack;
			}
			new_packets_bought = PacketsBoughtConstructor(new_packs_bought, agency.getPackets());
			new_total_purchased = TotalPurchased(new_family_size, new_packets_bought, agency.getPackets());
		}
		else
		{
			new_packets_bought.clear();
			new_total_purchased = "0";
		}

		for (size_t x = 0; x < agency.getClients().size(); x++)
		{
			update.push_back(agency.getClients()[x]);
		}

		update.push_back(Client(new_name, new_vat_number, new_family_size, Address(new_address), new_packets_bought, new_total_purchased));			//inserts new packet into vector
		agency.setClients(update);																													//sets the new agency vector
		agency.setClientsChange(true);
		cout << "__________________________________________________\n" << endl;
		cout << setw(38) << "Client successfully added!" << endl;
		cout << "__________________________________________________\n" << endl;
		PauseOperation();
		break;

	case 1: //modify client
		int numClient;

		cout << "__________________________________________________\n" << endl;
		cout << setw(30) << right << "UPDATE DATA" << endl;
		cout << "__________________________________________________\n" << endl;

		for (size_t x = 0; x < agency.getClients().size(); x++)
		{
			if (count >= 1 && x != agency.getPackets().size())
			{
				cout << "\n" << agency.getClients()[x].getName() << " - " << agency.getClients()[x].getVATnumber();
			}
			else {
				count += 1;
				cout << agency.getClients()[x].getName() << " - " << agency.getClients()[x].getVATnumber();
			}
		}
		cout << "\n__________________________________________________\n" << endl;
		cout << "Choose a client (write the NIF, Enter Ctrl+Z to exit): ";
		nif = CheckForErrorNIF(agency, 1);
		if (nif == "")
			break;

		for (unsigned i = 0; i < clientsList.size(); i++)
		{
			if (nif == clientsList[i].getVATnumber())
			{
				numClient = i;
				break;
			}
		}

		int op;

		do
		{
			cout << "__________________________________________________\n" << endl;
			cout << "1 - Name\n2 - NIF\n3 - Family Size\n4 - Address\n5 - Bought Packs\n\n0 - Back" << endl;
			cout << "__________________________________________________\n" << endl;
			cout << "Choose one option: ";

			do
			{
				op = stoi(CheckForNumberErrors(0, 1));
			} while (op < 0 || op > 5);

			bool error = false;
			int count = 0;
			string str;
			string new_address;

			cout << "__________________________________________________\n" << endl;

			switch (op)
			{
			case 0://returns to menu
				break;
			case 1://modify client
				cout << "Name (Enter Ctrl+Z to cancel): ";
				new_name = CheckForErrorSites();
				if (new_name == "")
					break;
				clientsList[numClient].setName(new_name);
				agency.setClientsChange(true);
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				PauseOperation();
				break;
			case 2://modify NIF
				cout << "NIF (Enter Ctrl+Z to cancel): ";
				new_vat_number = CheckForErrorNIF(agency, 3);
				if (new_vat_number == "")
					break;
				clientsList[numClient].setVATnumber(new_vat_number);
				agency.setClientsChange(true);
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				PauseOperation();
				break;
			case 3://modify family size
				cout << "Family size (Enter Ctrl+Z to cancel): ";
				new_family_size = CheckForNumberErrors();
				if (new_family_size == "")
					break;
				clientsList[numClient].setFamilySize(new_family_size);
				agency.setClientsChange(true);
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				PauseOperation();
				break;
			case 4://modify address
				cout << "Address (Enter Ctrl+Z to cancel): " << endl;
				cout << " - Street: ";
				new_street = CheckForErrorStreet(agency);
				if (new_street == "")
					break;
				new_address += new_street + " / ";

				cout << " - Door Number: ";
				new_door = CheckForNumberErrors();
				if (new_door == "")
					break;
				new_address += new_door + " / ";

				cout << " - Floor: ";
				new_floor = CheckForErrorFloor(agency);
				if (new_floor == "")
					break;
				new_address += new_floor + " / ";

				cout << " - Postal-code: ";
				new_postal_code = CheckForErrorPostalCode(agency);
				if (new_postal_code == "")
					break;
				new_address += new_postal_code + " / ";

				cout << " - Location: ";
				new_location = CheckForErrorSites();
				if (new_location == "")
					break;
				new_address += new_location;

				clientsList[numClient].setAddress(Address(new_address));
				agency.setClientsChange(true);
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				PauseOperation();
				break;
			case 5://modify the bought packages
				string num_packs, new_total_purchased;
				vector<Packet> new_packets_bought;

				cout << "Bought Packs (Enter Ctrl+Z to cancel): \nHow many? ";
				num_packs = CheckForNumberErrors(0,1);
				if (num_packs == "")
					break;
				if (stoi(num_packs) > 0)
				{
					for (int i = 0; i < stoi(num_packs); i++)
					{
						cout << "Pacote " << i + 1 << ": ";
						new_pack = CheckForErrorIdentifier(agency, 1);
						if (new_pack == "")
							break;
						new_packs_bought += new_pack;
					}
					new_packets_bought = PacketsBoughtConstructor(new_packs_bought, agency.getPackets());
					new_total_purchased = TotalPurchased(clientsList[numClient].getFamilySize(), new_packets_bought, agency.getPackets());
				}
				else
				{
					new_packets_bought.clear();
					new_total_purchased = "0";
				}
				clientsList[numClient].setPacketList(new_packets_bought);
				clientsList[numClient].setTotalPurchased(new_total_purchased);
				agency.setClientsChange(true);
				cout << "__________________________________________________\n" << endl;
				cout << setw(37) << "Successful modification!" << endl;
				cout << "__________________________________________________\n" << endl;
				PauseOperation();
				break;
			}
		} while (op != 0);
		agency.setClients(clientsList);
		break;

	case 2: //removes client
		cout << "__________________________________________________\n" << endl;
		cout << setw(31) << right << "REMOVE CLIENT" << endl;
		cout << "__________________________________________________\n" << endl;
		for (size_t x = 0; x < agency.getClients().size(); x++)
		{
			if (count >= 1 && x != agency.getPackets().size())
			{
				cout << "\n" << agency.getClients()[x].getName() << " - " << agency.getClients()[x].getVATnumber();
			}
			else {
				count += 1;
				cout << agency.getClients()[x].getName() << " - " << agency.getClients()[x].getVATnumber();
			}
		}
		cout << "\n__________________________________________________\n" << endl;
		cout << "NIF of the client you wish to remove (Enter Ctrl+Z to exit): ";
		new_vat_number = CheckForErrorNIF(agency, functioncode);
		if (new_vat_number == "")
			break;

		for (size_t x = 0; x < agency.getClients().size(); x++)
		{
			if (new_vat_number != agency.getClients()[x].getVATnumber())
				update.push_back(agency.getClients()[x]);
		}
		agency.setClients(update);
		agency.setClientsChange(true);
		cout << "__________________________________________________\n" << endl;
		cout << setw(38) << "Client successfully removed!" << endl;
		cout << "__________________________________________________\n" << endl;
		PauseOperation();
		break;
	}
}

bool bissexto(int ano) //checks if it's leap year
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

void WriteClientsFile(Agency & agency) //writes in the clients file
{
	ofstream newFile;
	newFile.open(agency.getClientsFileName());

	string str;

	for (size_t i = 0; i < agency.getClients().size(); i++)
	{
		newFile << agency.getClients()[i].getName() << "\n";
		newFile << agency.getClients()[i].getVATnumber() << "\n";
		newFile << agency.getClients()[i].getFamilySize() << "\n";
		newFile << agency.getClients()[i].getAddress().getStreet() << " / " << agency.getClients()[i].getAddress().getDoorNumber() << " / " << agency.getClients()[i].getAddress().getFloor() << " / " << agency.getClients()[i].getAddress().getPostalCode() << " / " << agency.getClients()[i].getAddress().getLocation() << "\n";
		str = "";
		if (!agency.getClients()[i].getPacketList().empty())
		{
			for (size_t j = 0; j < agency.getClients()[i].getPacketList().size(); j++)
			{
				if (j == agency.getClients()[i].getPacketList().size() - 1)
				{
					str += (to_string(abs(stoi(agency.getClients()[i].getPacketList()[j].getId()))));
					newFile << str << endl;
				}
				else
					str += (to_string(abs(stoi(agency.getClients()[i].getPacketList()[j].getId()))) + " ; ");
			}
		}
		else
			newFile << "-" << endl;

		newFile << agency.getClients()[i].getTotalPurchased() << endl;
		if (i != agency.getClients().size() - 1)
			newFile << "::::::::::\n";
	}
}

void WritePacksFile(Agency & agency) //writes in the packs file
{
	ofstream newFile;
	newFile.open(agency.getPacketsFileName());

	newFile << agency.getPackets()[agency.getPackets().size() - 1].getId();

	for (size_t i = 0; i < agency.getPackets().size(); i++)
	{
		newFile << "\n" << agency.getPackets()[i].getId() << "\n";
		for (size_t j = 0; j < agency.getPackets()[i].getSites().size(); j++)
		{
			if (j == 0 && agency.getPackets()[i].getSites().size() != 1)
				newFile << agency.getPackets()[i].getSites()[j] << " - ";
			else if (j == agency.getPackets()[i].getSites().size() - 1 || agency.getPackets()[i].getSites().size() == 1)
				newFile << agency.getPackets()[i].getSites()[j] << endl;
			else
				newFile << agency.getPackets()[i].getSites()[j] << ", ";
		}
		newFile << agency.getPackets()[i].getBeginDate() << "\n";
		newFile << agency.getPackets()[i].getEndDate() << "\n";
		newFile << agency.getPackets()[i].getPricePerPerson() << "\n";
		newFile << agency.getPackets()[i].getMaxPersons() << "\n";
		newFile << agency.getPackets()[i].getSoldTickets();

		if (i != agency.getPackets().size() - 1)
			newFile << "\n::::::::::";
	}

}

string PackIdFromSite(string site, Agency & agency) //returns the corresponding id of the desired destination
{
	vector<Packet> packetsList = agency.getPackets();
	string packid;

	for (size_t i = 0; i < packetsList.size(); i++)
	{
		for (size_t j = 0; j < packetsList[i].getSites().size(); j++)
		{
			if (site == packetsList[i].getSites()[j])
			{
				return to_string(abs(stoi(packetsList[i].getId())));
				break;
			}
		}
	}
	return packid;
}