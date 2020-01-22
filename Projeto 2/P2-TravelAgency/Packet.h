#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "defs.h"
#include "Date.h"
//#include "Utils.h"

using namespace std;

class Packet{
 private:
  string id; // packet unique identifier
  vector<string> sites; // touristic sites to visit
  Date begin;  // begin date
  Date end;  // end date
  string pricePerPerson; // price per person
  string maxPersons; // number of persons still available in the packet (updated whenever the packet is sold to a new client)
  string soldTickets; //number of persons already in the packet
  
 public:
	Packet();
	Packet(string id, vector<string> sites, Date inicio, Date fim, string precoPessoa, string maxPessoas, string Pessoasatuais);

  // GET methods
  string getId() const;
  vector<string> getSites() const;
  Date getBeginDate() const;
  Date getEndDate() const;
  string getPricePerPerson() const;
  string getMaxPersons() const;
  string getSoldTickets() const;
  
  // SET methods
  void setId(string id);  // to set negatve if "deprecated"
  void setSites(vector<string> sites);
  void setBeginDate(Date begin);
  void setEndDate(Date end);
  void setPricePerPerson(string pricePerPerson);
  void setMaxPersons(string maxPersons);
  void setSoldTickets(string soldTickets);

  // other methods

  friend ostream& operator<<(ostream& out, const Packet & packet);
};
