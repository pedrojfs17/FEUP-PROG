#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "defs.h"

using namespace std;

class Address{
 private:
  string street; // street name
  string doorNumber; // door number
  string floor; // floor number ("-" is not applicable)
  string postalCode; // postal code
  string location; // site

 public:
  Address();
  Address(string line);

  // GET methods
  string getStreet() const;
  string getDoorNumber() const;
  string getFloor() const;
  string getPostalCode() const;
  string getLocation() const;
  
  // SET methods
  void setStreet(string street);
  void setDoorNumber(string doorNumber);
  void setFloor(string floor);
  void setPostalCode(string postalCode);
  void setLocation(string  location);

  // other methods
  
  friend ostream& operator<<(ostream& out, const Address & address);

};
