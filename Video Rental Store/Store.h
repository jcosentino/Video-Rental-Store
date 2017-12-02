#pragma once
#include "Rental.h"
#include "Movie.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Store {
private:
	vector<Rental> catalog;
public:
	Store();
	bool inCatalog(string movieTitle);
	Rental getRental(string movieTitle);
	void addToCatalog(Movie movie);
	bool borrow(string movieTitle, string pNumber);
	void returnMovie(string movieTitle, string pNumber);
	void availableRentals();
	void prompt();
	void options(char c);
	void takeMoviesFromFile();
	void sendCurrentRentalsToFile();
	void listMoviesCurrentlyRented();
	void print();
};
Store::Store() {
	takeMoviesFromFile();
	remove("rentals.txt"); //So we don't have lingering items from a previous run
}
bool Store::inCatalog(string movieTitle) {
	for (int i = 0; i < catalog.size(); i++) {
		if (movieTitle == catalog[i].getMovie().getMovieName()) {
			return true;
		}
	}
	return false;
}
Rental Store::getRental(string movieTitle) {
	for (int i = 0; i < catalog.size(); i++) {
		if (movieTitle == catalog[i].getMovie().getMovieName()) {
			return catalog[i];
		}
	}
}
void Store::addToCatalog(Movie movie) {
	catalog.push_back(Rental(movie, 5)); //We buy 5 copies by default
}
bool Store::borrow(string movieTitle, string pNumber) {
	if (!inCatalog(movieTitle)) {
		cout << "That movie is not in the catalog. Please enter another movie."
			<< endl;
		return false;
	}
	if (getRental(movieTitle).getQuantity() == 0) {
		cout << "That movie is not available." << endl;
		return false;
	}
	else {
		for (int i = 0; i < catalog.size(); i++) {
			if (movieTitle == catalog[i].getMovie().getMovieName()
				&& !catalog[i].isCustomerRenting(pNumber)) {
				catalog[i].addCustomer(pNumber);
				cout << "You are now renting " << movieTitle << endl;
				cout << "There are " << catalog[i].getQuantity()
					<< " copies remaining" << endl;
				return true;
			}
		}
		cout << "You are already renting that movie." << endl;
		return false;
	}
}
void Store::returnMovie(string movieTitle, string pNumber) {
	for (int i = 0; i < catalog.size(); i++) {
		if (movieTitle == catalog[i].getMovie().getMovieName()
			&& catalog[i].isCustomerRenting(pNumber)) {
			catalog[i].removeCustomer(pNumber);
			cout << "You have returned " << movieTitle << "." << endl;
			return;
		}
	}
	cout << "You are not borrowing that movie." << endl;
}
void Store::availableRentals() {
	bool available = false;
	for (int i = 0; i < catalog.size(); i++) {
		if (catalog[i].getQuantity() != 0) {
			catalog[i].getMovie().print();
			available = true;
		}
	}
	if (available == false) {
		cout << "There are no available rentals" << endl;
	}
}
void Store::prompt() {
	sendCurrentRentalsToFile(); //Sends to rentals.txt
	cout << "What would you like to do?" << endl;
	cout << "Type A to see a list of available movies." << endl;
	cout << "Type B to rent a movie." << endl;
	cout << "Type C to return a movie." << endl;
	cout << "Type D to see which movies are currently being rented." << endl;
	options(cin.get()); //This will return us to the prompt menu
}
void Store::options(char c) {
	if (c == 'a' || c == 'A') { //This option repeats the prompt
		availableRentals();
	}
	else if (c == 'b' || c == 'B') {
		string pNumber, opt, movie;
		cout << "You would to to rent a movie. Please type your phone number:"
			<< endl;
		getline(cin, pNumber); //partially broken
		//Can I redesign this? I can probably make a single function
		cout << pNumber << ", is that correct? Type YES or NO." << endl;
		getline(cin, opt);
		while (opt == "NO") {
			cout << "Please retype your phone number:" << endl;
			getline(cin, pNumber);
			cout << pNumber << ", is that correct? Type YES or NO." << endl;
			getline(cin, opt);
		}
		cout << "Which movie did you want to rent?" << endl;
		getline(cin, movie);
		borrow(movie, pNumber);
	} else if (c == 'c' || c == 'C'){
		string pNumber, opt, movie;
		cout << "You would like to return a movie." << endl;
		cout << "Please type your phone number:" << endl;
		getline(cin, pNumber);
		//Can I redesign this? I can probably make a single function
		cout << pNumber << ", is that correct? Type YES or NO." << endl;
		getline(cin, opt);
		while (opt == "NO") {
			cout << "Please retype your phone number:" << endl;
			getline(cin, pNumber);
			cout << pNumber << ", is that correct? Type YES or NO." << endl;
			getline(cin, opt); //partially broken
		}
		cout << "Which movie would you like to return?" << endl;
		getline(cin, movie);
		returnMovie(movie, pNumber);
	}
	else if (c == 'd' || c == 'D') {
		listMoviesCurrentlyRented();
	}
	else {
		cout << "That is not an option. Please reselect A/B/C" << endl;
	}
	cout << endl;
	prompt();
}
void Store::takeMoviesFromFile() {
	ifstream storeFile;
	storeFile.open("store.txt");
	if (!storeFile.is_open()) {
		cout << "store.txt is not found." << endl;
		exit(1);
	}
	char category, whitespace;
	string isbn, title;
	int year, sendCategory;
	while (!storeFile.eof()) {
		getline(storeFile, isbn, '\t');
		getline(storeFile, title, '\t');
		storeFile >> year;
		storeFile >> category;
		if (category == 'f') {
			sendCategory = 1;
		}
		else if (category == 'c') {
			sendCategory = 2;
		}
		else {
			sendCategory = 3;
		}
		storeFile.get(whitespace);
		addToCatalog(Movie(isbn, title, year, sendCategory));
	}
	storeFile.close();
}
void Store::sendCurrentRentalsToFile() {
	ofstream storeFile("rentals.txt");
	for (int i = 0; i < catalog.size(); i++) {
		if (catalog[i].getQuantity() != 5) { //If it's 5, then all items are in stock
			storeFile << catalog[i].getMovie().getMovieName() << '\t';
			storeFile << catalog[i].getMovie().getIsbn() << '\t';
			storeFile << catalog[i].getMovie().getYear() << '\t';
			storeFile << catalog[i].getMovie().getCategory() << '\t';
			storeFile << catalog[i].getQuantity() << '\n';
		}
	}
	storeFile.close();
}
void Store::listMoviesCurrentlyRented() {
	cout << "Here are the movies currently being rented:" << endl;
	ifstream storeFile;
	storeFile.open("rentals.txt");
	if (!storeFile.is_open()) {
		cout << "rentals.txt is not found." << endl;
		exit(1);
	}
	char whitespace;
	string isbn, title;
	int year, category, quantity;
	while (!storeFile.eof()) {
		getline(storeFile, isbn, '\t');
		cout << isbn << '\t';
		getline(storeFile, title, '\t');
		cout << title << '\t';
		storeFile >> year;
		cout << year << '\t';
		storeFile >> category;
		cout << category << '\t';
		storeFile >> quantity;
		if (category == 1) {
			cout << "Feature" << endl;
		}
		else if (category == 2) {
			cout << "Comedy" << endl;
		}
		else {
			cout << "Horror" << endl;
		}
	}
	storeFile.close();
}
void Store::print() {
	cout << "Here are our rentals:" << endl;
	for (int i = 0; i < catalog.size(); i++) {
		catalog[i].print();
	}
}