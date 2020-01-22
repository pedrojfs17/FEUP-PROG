#include "Packet.h"
#include "Utils.h"

Packet::Packet() {
	id = maxPersons = soldTickets = pricePerPerson = "";
	sites.empty();
	begin = end = Date();
}

Packet::Packet(string id, vector<string> sites, Date inicio, Date fim, string precoPessoa, string maxPessoas, string Pessoasatuais) {
	this->id = id;
	this->sites = sites;
	this->begin = inicio;
	this->end = fim;
	this->pricePerPerson = precoPessoa;
	this->maxPersons = maxPessoas;
	this->soldTickets = Pessoasatuais;
}

// GET methods

string Packet::getId() const {
	return id;
}

vector<string> Packet::getSites() const {
	return sites;
}

Date Packet::getBeginDate() const {
	return Packet::begin;
}

Date Packet::getEndDate() const {
	return Packet::end;
}

string Packet::getPricePerPerson() const {
	return pricePerPerson;
}

string Packet::getMaxPersons() const {
	return maxPersons;
}

string Packet::getSoldTickets() const {
	return soldTickets;
}

// SET methods

void Packet::setId(string id) {
	this->id = id;
}

void Packet::setSites(vector<string> sites) {
	this->sites = sites;
}

void Packet::setBeginDate(Date begin) {
	this->begin = begin;
}

void Packet::setEndDate(Date end) {
	this->end = end;
}

void Packet::setPricePerPerson(string pricePerPerson) {
	this->pricePerPerson = pricePerPerson;
}

void Packet::setMaxPersons(string maxPersons) {
	this->maxPersons = maxPersons;
}

void Packet::setSoldTickets(string soldTicket) {
	this->soldTickets = soldTicket;
}

 // shows a package's content
ostream& operator<<(ostream& out, const Packet& packet) {

	out << "Sites - ";
	for (size_t i = 0; i < packet.getSites().size(); i++)
	{
		if (i == 0 && packet.getSites().size()!=1)
			out << packet.getSites()[i] << " - ";
		else if(i== packet.getSites().size()-1|| packet.getSites().size() == 1)
			out << packet.getSites()[i] << endl;
		else
			out << packet.getSites()[i] << ", ";
	}
	out << "Beginning of trip - " << packet.getBeginDate() << endl;
	out << "End of trip - " << packet.getEndDate() << endl;
	out << "Price per person - " << packet.getPricePerPerson() << endl;
	out << "Maximum capacity - " << packet.getMaxPersons() << endl;
	out << "Sold tickets - " << packet.getSoldTickets() << endl;

	return out;
}
