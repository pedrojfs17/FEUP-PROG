#include "Client.h"

Client::Client(string name, string VATnumber, string familySize, Address address) {
	this->name = name;
	this->VATnumber = VATnumber;
	this->familySize = familySize;
	this->address = address;
}

Client::Client(string name, string VATnumber, string familySize, Address address, vector<Packet>& packets, string totalPurchased) {
	this->name = name;
	this->VATnumber = VATnumber;
	this->familySize = familySize;
	this->address = address;
	this->packets = packets;
	this->totalPurchased = totalPurchased;
}

// GET methods

string Client::getName() const {
	return name;
}

string Client::getVATnumber() const {
	return VATnumber;
}

string Client::getFamilySize() const {
	return familySize;
}

Address Client::getAddress() const {
	return address;
}

vector<Packet> Client::getPacketList() const {
	return packets;
}

string Client::getTotalPurchased() const {
	return totalPurchased;
}

// SET methods

void Client::setName(string name) {
	this->name = name;
}

void Client::setVATnumber(string VATnumber) {
	this->VATnumber = VATnumber;
}

void Client::setFamilySize(string familySize) {
	this->familySize = familySize;
}

void Client::setAddress(Address address) {
	this->address = address;
}

void Client::setPacketList(vector<Packet>& packets) {
	this->packets = packets;
}

void Client::setTotalPurchased(string totalPurchased) {
	this->totalPurchased = totalPurchased;
}

// other methods

ostream& operator<<(ostream& out, const Client& client) {

	out << "_______________________________________________________\n" << endl;
	out << setw(37) << right << "CLIENT INFORMATION" << endl;
	out << "_______________________________________________________\n" << endl;
	out << setw(25) << "Name: ";
	out << setw(30) << client.name << endl;
	out << setw(25) << "NIF: ";
	out << setw(30) << client.VATnumber << endl;
	out << setw(25) << "Household: ";
	out << setw(30) << client.familySize << endl;
	out << "_______________________________________________________\n" << endl;
	out << client.address << endl;
	out << "_______________________________________________________\n" << endl;
	out << setw(25) << "Bought Packs: ";
	string str = "";
	if (!client.packets.empty())
	{
		for (size_t j = 0; j < client.packets.size(); j++)
		{
			if (j == client.packets.size() - 1)
			{
				str += (to_string(abs(stoi(client.packets[j].getId()))));
				out << setw(30) << str << endl;
			}
			else
				str += (to_string(abs(stoi(client.packets[j].getId()))) + " ; ");
		}
	}
	else
		out << setw(30) << "-" << endl;
	out << setw(25) << "Total Transactions: ";
	out << setw(30) << client.totalPurchased << endl;
	out << "_______________________________________________________\n" << endl;

	return out;
}
