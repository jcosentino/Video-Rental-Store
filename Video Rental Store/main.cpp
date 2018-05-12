/*
This is my first project from CSC 330 - Oject Oriented Software Design
This program will offer the user a menu where they may:
->See a list of movies available for rent
->Rent a movie
->Return a movie
->See a list of movies being currently rented
The program will export the currently rented movies to a text file called rentals.txt
The list of movies in the catalog are stored in store.txt
*/
#include "Person.h"
#include "Customer.h"
#include "Movie.h"
#include "Rental.h"
#include "Store.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	Store s;
	s.prompt();

	cin.get();
	return 0;
}