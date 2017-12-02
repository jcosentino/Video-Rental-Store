#pragma once
#include <iostream>
#include <string>

using namespace std;

class Person {
private:
	string name;
	string phoneNumber;
public:
	Person();
	Person(string name, string phoneNumber);
	string getName();
	void setName(string name);
	string getPhoneNumber();
	void setPhoneNumber(string phoneNumber);
	void print();
};
Person::Person() {
	name = "";
	phoneNumber = "";
}
Person::Person(string name, string phoneNumber) {
	this->name = name;
	this->phoneNumber = phoneNumber;
}
string Person::getName() {
	return name;
}
void Person::setName(string name) {
	this->name = name;
}
string Person::getPhoneNumber() {
	return phoneNumber;
}
void Person::setPhoneNumber(string phoneNumber) {
	this->phoneNumber = phoneNumber;
}
void Person::print() {
	cout << "Name: " << name << endl;
	cout << "Phone number: " << phoneNumber << endl;
}