#pragma once

#include <string>
#include <vector>
#include "Agency.h"
#include "Packet.h"

using namespace std;

vector<Packet> PacketsBoughtConstructor(string line, vector<Packet> packetsList);
vector<string> SitesConstructor(string line);
bool is_accent(char c);
string CheckForErrorsMenus(unsigned menucode);
string CheckForErrorsDate();
bool CheckReturn(string& stringe, unsigned emptyCode = 0);
void PauseOperation();
bool CompareDates(Date d1, Date d2);
bool SameId(Agency &agency, string id);
bool SameNIF(Agency &agency, string nif);
string CheckForErrorNIF(Agency &agency, unsigned functioncode);
string CheckForErrorIdentifier( Agency &agency, unsigned functioncode);
string CheckForErrorSites();
string CheckForNumberErrors( unsigned previousseats = 0, unsigned functioncode = 0);
string CheckForErrorStreet(Agency &agency, unsigned functioncode);
string CheckForErrorFloor(Agency &agency, unsigned functioncode);
string CheckForErrorPostalCode( Agency &agency, unsigned functioncode);
string TotalPurchased(string familySize, vector<Packet> boughtPackets, vector<Packet> packets);

void PacketManager(Agency &agency, unsigned functioncode); //permite criar / alterar / remover um pacote
void ShowInfo(Agency &agency, unsigned functioncode, unsigned subfunctioncode);
void ClientManager(Agency &agency, unsigned functioncode);

bool bissexto(int ano);

void WriteClientsFile(Agency& agency);
void WritePacksFile(Agency& agency);
string PackIdFromSite(string site, Agency& agency);