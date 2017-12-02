#pragma once
#include "Person.h"
#include "Movie.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Customer : public Person {
private:
	string customerID;
	vector<Movie> borrowedMovies;
public:
	Customer();
	Customer(string customerID, string name, string pNumber);
	string getCustomerID();
	void setCustomerID(string customerID);
	void listBorrowedMovies();
	void addToBorrowedMovies(Movie movie);
	void print();
};
Customer::Customer() {
	this->setName("");
	this->setPhoneNumber("");
	this->customerID = "";
}
Customer::Customer(string customerID, string name, string pNumber) {
	this->customerID = customerID;
	this->setName(name);
	this->setPhoneNumber(pNumber);
}
string Customer::getCustomerID() {
	return customerID;
}
void Customer::setCustomerID(string customerID) {
	this->customerID = customerID;
}
void Customer::listBorrowedMovies() {
	cout << "Borrowed movies:" << endl;
	for (int i = 0; i < borrowedMovies.size(); i++) {
		cout << borrowedMovies[i].getMovieName() << endl;
	}
}
void Customer::addToBorrowedMovies(Movie movie) {
	borrowedMovies.push_back(movie);
}
void Customer::print() {
	this->Person::print();
	cout << "Customer ID: " << customerID << endl;
	this->listBorrowedMovies();
}