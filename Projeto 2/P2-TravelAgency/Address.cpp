#include "Address.h"

Address::Address(){
}

Address::Address(string line){
	vector<string> components;
	string component = "";

	for (size_t x = 0; x < line.size(); x++)
	{
		if (line[x] == '/' || line[x] == '\n')
		{
			components.push_back(component);
			component = "";
			continue;
		}
		component += line[x];
	}
	components.push_back(component);
	components[0].erase(components[0].length() - 1, 1);
	components[1].erase(0, 1); components[1].erase(components[1].length() - 1, 1);
	components[2].erase(0, 1); components[2].erase(components[2].length() - 1, 1);
	components[3].erase(0, 1); components[3].erase(components[3].length() - 1, 1);
	components[4].erase(0, 1);

	this->street = components[0];
	this->doorNumber = components[1];
	this->floor = components[2];
	this->postalCode = components[3];
	this->location = components[4];
}

  // GET methods

string Address::getStreet() const{
	return street;
}

string Address::getDoorNumber() const{
	return doorNumber;
}

string Address::getFloor() const{
	return Address::floor;
}

string Address::getPostalCode() const{
	return postalCode;
}

string Address::getLocation() const{
	return location;
}

  // SET methods

void Address::setStreet(string street){
	this->street = street;
}

void Address::setDoorNumber(string doorNumber){
	this->doorNumber = doorNumber;
}

void Address::setFloor(string floor){
	this->floor = floor;
}

void Address::setPostalCode(string postalCode){
	this->postalCode = postalCode;
}

void Address::setLocation(string  location){
	this->location = location;
}

// displays an address in a nice format
ostream& operator<<(ostream& out, const Address & address){

	out << setw(31) << "ADRESS\n" << endl;
	out << setw(25) << "Street: ";
	out << setw(30) << address.getStreet() << endl;
	out << setw(25) << "Door Number: ";
	out << setw(30) << address.getDoorNumber() << endl;
	out << setw(25) << "Floor: ";
	out << setw(30) << address.getFloor() << endl;
	out << setw(25) << "Postal Code: ";
	out << setw(30) << address.getPostalCode() << endl;
	out << setw(25) << "Location: ";
	out << setw(30) << address.getLocation() << endl;

	return out;
}
