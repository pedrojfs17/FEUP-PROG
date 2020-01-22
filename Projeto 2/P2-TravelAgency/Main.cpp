#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "defs.h"
#include "Agency.h"
#include "Menus.h"
#include "Utils.h"
using namespace std;

int main() {
	Agency agency(AGENCY_FILE_NAME);   // create the agency

	mainMenu(agency); // initial menu inicial with the major options of the application

	return 0;
}