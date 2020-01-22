#include "Agency.h"


Agency::Agency(string fileName) {

	ifstream agencyFile, clientsFile, packetsFile;
	agencyFile.open(fileName);

	if (agencyFile.is_open())
	{
		for (int i = 0; i < 6; i++)
		{
			string linha;
			getline(agencyFile, linha);

			switch (i) //collects agency information
			{
			case 0:
				this->name = linha;
				break;
			case 1:
				this->VATnumber = linha;
				break;
			case 2:
				this->URL = linha;
				break;
			case 3:
				this->address = Address(linha);
				break;
			case 4:
				this->clientsFileName = linha;
				break;
			case 5:
				this->packetsFileName = linha;
				break;
			}
		}

		packetsFile.open(packetsFileName);

		if (packetsFile.is_open())
		{
			int lineNum = 0;
			vector<string> sites;
			string id, pricePerPerson, beginDate, endDate, maxPersons, soldTickets;

			while (!packetsFile.eof())
			{
				string line;
				getline(packetsFile, line);

				switch (lineNum) //collects packages information
				{
				case 1:
					id = line;
					break;
				case 2:
					sites = SitesConstructor(line);
					break;
				case 3:
					beginDate = line;
					break;
				case 4:
					endDate = line;
					break;
				case 5:
					pricePerPerson = line;
					break;
				case 6:
					maxPersons = line;
					break;
				case 7:
					soldTickets = line;
					//maxPersons = to_string(stoi(maxPersons) - stoi(soldTickets));
					break;
				default:
					break;
				}

				lineNum++;

				if (line == "::::::::::")
				{
					Date begin(beginDate);
					Date end(endDate);
					lineNum = 1;
					Packet packet(id, sites, begin, end, pricePerPerson, maxPersons, soldTickets);
					this->packets.push_back(packet);
				}
			}
			Date begin(beginDate);
			Date end(endDate);
			this->packets.push_back(Packet(id, sites, begin, end, pricePerPerson, maxPersons, soldTickets));
		}
		else
			cout << "Error loading Packs file!" << endl;

		clientsFile.open(clientsFileName);

		if (clientsFile.is_open())
		{
			int lineNum = 0;
			string name;
			string VATnumber , address, totalPurchased , familySize ;
			vector<Packet> clientPackets;

			while (!clientsFile.eof())
			{
				string line;
				getline(clientsFile, line);

				switch (lineNum) //collects clients information
				{
				case 0:
					name = line;
					break;
				case 1:
					VATnumber = line;
					break;
				case 2:
					familySize = line;
					break;
				case 3:
					address = line;
					break;
				case 4:
					clientPackets = PacketsBoughtConstructor(line,packets);
					break;
				case 5:
					totalPurchased = line;
					break;
				default:
					break;
				}

				lineNum++;

				if (line == "::::::::::")
				{
					lineNum = 0;
					this->clients.push_back(Client(name, VATnumber, familySize, Address(address), clientPackets, totalPurchased));
				}
			}
			this->clients.push_back(Client(name, VATnumber, familySize, Address(address), clientPackets, totalPurchased));
		}
		else
			cout << "Error loading Clients file!" << endl;
	}
	else
		cout << "File not found! " << endl;
}

// metodos GET
string Agency::getName() const {
	return name;
}

string Agency::getVATnumber() const {
	return VATnumber;
}

Address Agency::getAddress() const {
	return address;
}

string Agency::getURL() const {
	return URL;
}

vector<Client> Agency::getClients() const {
	return clients;
}

vector<Packet> Agency::getPackets() const {
	return packets;
}

string Agency::getClientsFileName() const {
	return clientsFileName;
}

string Agency::getPacketsFileName() const {
	return packetsFileName;
}

bool Agency::getClientsChange() const {
	return clientsInfoHasChanged;
}

bool Agency::getPacketsChange() const {
	return packetsInfoHasChanged;
}

// SET Methods

void Agency::setName(string name) {
	this->name = name;
}

void Agency::setVATnumber(string VATnumber) {
	this->VATnumber = VATnumber;
}

void Agency::setAddress(Address address) {
	this->address = address;
}

void Agency::setURL(string url) {
	this->URL = URL;
}

void Agency::setClients(vector<Client>& clients) {
	this->clients = clients;
}

void Agency::setPackets(vector<Packet>& packets) {
	this->packets = packets;
}

void Agency::setClientsChange(bool change) {
	this->clientsInfoHasChanged = change;
}

void Agency::setPacketsChange(bool change) {
	this->packetsInfoHasChanged = change;
}

 // ´shows the agency's content
ostream& operator<<(ostream& out, const Agency& agency) {

	out << "_______________________________________________________\n" << endl;
	out << setw(37) << right << "AGENCY INFORMATION" << endl;
	out << "_______________________________________________________\n" << endl;
	out << setw(25) << "Name: ";
	out << setw(30) << agency.name << endl;
	out << setw(25) << "NIF: ";
	out << setw(30) << agency.VATnumber << endl;
	out << setw(25) << "Website: ";
	out << setw(30) << agency.URL << endl;
	out << "_______________________________________________________\n" << endl;
	out << agency.address << endl;
	out << "_______________________________________________________\n" << endl;

	return out;
}
