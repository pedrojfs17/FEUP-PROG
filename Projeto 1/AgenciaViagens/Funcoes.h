#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <stdlib.h>
#include "DataType.h"

//LEITURAS

int Read_Number(string msg);
Date Read_Date();
string Read_String(string msg);
string Read_String_With_Numbers(string msg);

//CONSTRUCTORS

void Adress_Constructor(string line, Adress &adress);
void Date_Constructor(string line, Date &date);
void Packs_Boought_Constructor(string line, vector<int> &boughtPacksList);
vector<string> Places_To_Visit(string line);
void Total_transactions(vector<TravelPack> packsList, Client &client);

//MENU

void menuCompra(vector<TravelPack> &packsList, vector<Client> &clientsList, string clientsFileName, string packsFileName);
void menuClientes(string clientsFileName, vector<Client> &clientsList, Agency agency, vector<TravelPack> packsList);
void menuPacotesVendidos(vector<TravelPack> packsList, vector<Client> clientsList);
void menuVerPacotes(vector<TravelPack> packsList, vector<Client> clientsList);
void menuPacotes(string packsFileName, vector<TravelPack> &packsList, Agency agency, vector<Client> clientsList);
int menuInicial(Agency &agency, vector<Client> &clientsList, vector<TravelPack> &packsList);

//FUNCOES

bool Load_Agency(Agency &agency, string agencyFileName);
void Load_Clients(vector<Client> &clientsList, Agency agency, vector<TravelPack> packsList);
void Load_Packs(vector<TravelPack> &packsList, Agency agency);
void Write_Clients_File(vector<Client> clientsList, string ClientsFileName);
void Write_Packs_File(vector<TravelPack> packsList, string PacksFileName);
void Add_Client(string clientsFileName, vector<Client> clientsList);
void Add_Pack(string packsFileName, vector<TravelPack> packsList);
void Modify_Client(vector<Client> &clientsList, string ClientsFileName);
void Modify_Pack(vector<TravelPack> &packsList, string PacksFileName);
void Remove_Client(vector<Client> &clientsList, string ClientsFileName);
void Remove_Pack(vector<TravelPack> &packsList, string PacksFileName);
void Client_Information(vector<Client> clientsList);
void Pack_Information(vector<TravelPack> packsList);
bool Compare_Dates(Date d1, Date d2);
void Filter_By_Availability(vector<TravelPack> packsList);
void Filter_By_Local(string local, vector<TravelPack> packsList, bool FilterDate = false);
void Filter_By_Date(vector<TravelPack> packsList, vector<TravelPack> packsListCopy);
void Buy_Pack(Client &client, TravelPack &pack);
void Agency_Transactions(vector<TravelPack> packsList);
void Sold_Client_Packs(vector<Client> clientsList, vector<TravelPack> packsList);
bool bissexto(int ano);
string lowercase(string str);