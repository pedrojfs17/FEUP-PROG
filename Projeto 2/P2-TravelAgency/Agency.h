#pragma once
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include "defs.h"

using namespace std;

class Agency;

#include "Address.h"
#include "Client.h"
#include "Utils.h"

class Agency {
private:
	string name; // name of the  agency
	string VATnumber; // VAT number of the agency
	Address address; // address of the agency
	string URL; // URL of the agency Web site
	vector<Client> clients; // vector to store the existing clients
	vector<Packet> packets; // vector to store the existing packets

	string clientsFileName;
	string packetsFileName;
	bool clientsInfoHasChanged; // flag that is set to "true" if at least one client has been changed/added/deleted
	bool packetsInfoHasChanged; // flag that is set to "true" if at least one packet has been changed/added/deleted
	
public:
	Agency(string fileName);

	// methods GET
	string getName() const;
	string getVATnumber() const;
	Address getAddress() const;
	string getURL() const;
	vector<Client> getClients() const;
	vector<Packet> getPackets() const;
	string getClientsFileName() const;
	string getPacketsFileName() const;
	bool getClientsChange() const;
	bool getPacketsChange() const;

	// methods SET
	void setName(string name);
	void setVATnumber(string VATnumber);
	void setAddress(Address address);
	void setURL(string url);
	void setClients(vector<Client> &clients);
	void setPackets(vector<Packet> &packets);
	void setClientsChange(bool change);
	void setPacketsChange(bool change);

	// other methods 

	friend ostream& operator<<(ostream& out, const Agency& agency);
};
