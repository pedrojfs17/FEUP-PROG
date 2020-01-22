#include "Date.h"

Date::Date() {
	year = month = day = 0;
}

Date::Date(string date) {

	int counter = 0;
	string num;

	for (size_t i = 0; i < date.length(); i++)
	{
		if (isdigit(date[i]))
		{
			num += date[i];
		}
		else
		{
			if (counter == 0)
				this->year = stoi(num);
			else if (counter == 1)
				this->month = stoi(num);	
			counter++;
			num = "";
			continue;
		}
	}
	this->day = stoi(num);
}

Date::Date(unsigned short day, unsigned short month, unsigned year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

 // GET Methods

unsigned short Date::getDay() const {
	return day;
}

unsigned short Date::getMonth() const {
	return month;
}

unsigned Date::getYear() const {
	return year;
}

 // SET Methods

void Date::setDay(unsigned short day) {
	this->day = day;
}

void Date::setMonth(unsigned short month) {
	this->month = month;
}

void Date::setYear(unsigned year) {
	this->year = year;
}

 // display a Date in a nice format
ostream& operator<<(ostream& out, const Date& date) {

	string dateStr = "";

	dateStr = to_string(date.year) + "/";
	if (date.month < 10)
		dateStr += "0" + to_string(date.month) + "/";
	else
		dateStr += to_string(date.month) + "/";
	if (date.day < 10)
		dateStr += "0" + to_string(date.day);
	else
		dateStr += to_string(date.day);

	out << dateStr;

	return out;
}
