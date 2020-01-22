#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Adress {
	string StreetName;
	string Door;
	string Floor;
	string PostalCode;
	string Local;
};

struct Date {
	int year;
	int month;
	int day;
};

struct Agency {
	string name;
	string NIF;
	Adress adress;
	string url;
	string packsList;
	string clientsList;
};

struct Client {
	string name;
	string NIF;
	int famAgre;
	Adress adress;
	vector<int> packsBought;
	int totalTrans;
};

struct TravelPack {
	string identifier;
	string travelPlaces;
	Date startDate;
	Date endDate;
	int personCost;
	int initSpots;
	int soldSpots;
	int availableSpots;
};
