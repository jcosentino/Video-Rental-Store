#pragma once
#include <iostream>
#include <string>

using namespace std;

class Movie{
private:
	string isbn;
	string movieName;
	int year, category;
public:
	Movie();
	Movie(string isbn, string movieName, int year, int category);
	string getIsbn();
	void setIsbn(string isbn);
	string getMovieName();
	void setMovieName(string movieName);
	int getYear();
	void setYear(int year);
	int getCategory();
	void setCategory(int category);
	void print();
};
Movie::Movie() {
	isbn = "";
	movieName = "";
	year = 0;
	category = 0;
}
Movie::Movie(string isbn, string movieName, int year, int category) {
	this->isbn = isbn;
	this->movieName = movieName;
	this->year = year;
	this->category = category;
}
string Movie::getIsbn() {
	return isbn;
}
void Movie::setIsbn(string isbn) {
	this->isbn = isbn;
}
string Movie::getMovieName() {
	return movieName;
}
void Movie::setMovieName(string movieName) {
	this->movieName = movieName;
}
int Movie::getYear() {
	return year;
}
void Movie::setYear(int year) {
	this->year = year;
}
int Movie::getCategory() {
	return category;
}
void Movie::setCategory(int category) {
	this->category = category;
}
void Movie::print() {
	cout << "ISBN: " << isbn << endl;
	cout << "Movie Name: " << movieName << endl;
	cout << "Year: " << year << endl;
	if (category == 1) {
		cout << "Category: feature" << endl;
	}
	else if (category == 2) {
		cout << "Category: comedy" << endl;
	}
	else if (category == 3) {
		cout << "Category: horror" << endl;
	}
	else {
		cout << "There is no category." << endl;
	}
}