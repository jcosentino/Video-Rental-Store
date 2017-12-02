#pragma once
#include "Movie.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Rental {
private:
	Movie movie;
	vector<string> pNumbers;
	int quantity;
public:
	Rental();
	Rental(Movie movie, int quantity);
	Movie getMovie();
	void setMovie(Movie movie);
	int getQuantity();
	void setQuantity(int quantity);
	void incrementQuantity();
	void decrementQuantity();
	bool isAvailable();
	void addCustomer(string pNumber);
	void removeCustomer(string pNumber);
	void listCustomersRenting();
	bool isCustomerRenting(string pNumber);
	void print();
};
Rental::Rental() {
	quantity = 0;
}
Rental::Rental(Movie movie, int quantity) {
	this->movie = movie;
	this->quantity = quantity;
}
Movie Rental::getMovie() {
	return movie;
}
void Rental::setMovie(Movie movie) {
	this->movie = movie;
}
int Rental::getQuantity() {
	return quantity;
}
void Rental::setQuantity(int quantity) {
	this->quantity = quantity;
}
void Rental::incrementQuantity() {
	quantity++;
}
void Rental::decrementQuantity() {
	quantity--;
}
bool Rental::isAvailable() {
	return quantity != 0;
}
void Rental::addCustomer(string pNumber) {
	if (!isAvailable()) {
		cout << "This movie is not available." << endl;
	}
	else {
		this->pNumbers.push_back(pNumber);
		this->decrementQuantity();
	}
}
void Rental::removeCustomer(string pNumber) {
	vector<string>::iterator position = find(pNumbers.begin(), pNumbers.end(), pNumber);
	if (position != pNumbers.end()) {
		pNumbers.erase(position);
	}
	this->incrementQuantity();
}
void Rental::listCustomersRenting() {
	cout << "Here are the phone numbers of people renting this movie:" << endl;
	for (int i = 0; i < pNumbers.size(); i++) {
		cout << pNumbers[i] << endl;
	}
}
bool Rental::isCustomerRenting(string pNumber) {
	for (int i = 0; i < pNumbers.size(); i++) {
		if (pNumber == pNumbers[i]) {
			return true;
		}
	}
	return false;
}
void Rental::print() {
	movie.print();
	cout << "Quantity: " << quantity << endl;
	if (pNumbers.size() == 0) {
		cout << "There are no customers renting this movie." << endl;
	}
	else {
		listCustomersRenting();
	}
}