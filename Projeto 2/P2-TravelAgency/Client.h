#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "defs.h"
#include "Packet.h"
#include "Address.h"

using namespace std;

class Client {
private:
	string name; // name of the client
	string VATnumber; // VAT number of client
	string familySize;  // number of family members
	Address address; // client's address
	vector<Packet> packets; // vector to store client's packets bought
	string totalPurchased; // total value spent by the client

public:
	Client(string name, string VATnumber, string familySize, Address address);  // for a new client
	Client(string name, string VATnumber, string familySize, Address address, vector<Packet>& packets, string totalPurchased);  // client read from file

	// GET methods

	string getName() const;
	string getVATnumber() const;
	string getFamilySize() const;
	Address getAddress() const;
	vector<Packet> getPacketList() const;
	string getTotalPurchased() const;

	// SET methods

	void setName(string name);
	void setVATnumber(string VATnumber);
	void setFamilySize(string familySize);
	void setAddress(Address address);
	void setPacketList(vector<Packet>& packets);
	void setTotalPurchased(string totalPurchased);

	// other methods

	friend ostream& operator<<(ostream& out, const Client& client);
};
