/*
* Programmer: Samuel Aguirre
* Purpose: Simulates a database of bikes
* Data: 4/13/2020
* Class: CSCI 222
*
*/
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <list>
#include <string.h>
#include "bike.h"


using namespace std;

int main() {

	// linked list
	std::list<shared_ptr<Bike>> bikeList;

	fstream bikeData("data.txt");
	//if the file is opened successfully opened read the first line of data from the file
	if (bikeData.is_open()) {
		string line;
		int branchTo = 0;
		//while loops executes until the end of the file
		while (!bikeData.eof()) {

			getline(bikeData, line);
			branchTo = stoi(line);

			switch (branchTo) {
			case 1:
				//creates a bike object from data in bikeData
				readBike(bikeData, bikeList);
				break;
			case 2:
				//prints all bikes in no particular order
				printBikes(bikeList, status::ALL, order::NO_ORDER);
				break;
			case 3:
				//prints the bikes by id
				printBikes(bikeList, status::ALL, order::ID);
				break;
			case 4:
				//prints the bikes order by manuf
				printBikes(bikeList, status::ALL, order::MANUF);
				break;
			case 5:
				//prints bikes available for rent
				printBikes(bikeList, status::NOT_RENTED, order::NO_ORDER);
				break;
			case 6:
				//prints bikes not available for rent
				printBikes(bikeList, status::RENTED, order::NO_ORDER);
				break;
			case 7:
				//performs a transaction
				do_transact(bikeData, bikeList, status::NOT_RENTED);
				break;
			case 8:
				//returns the bike
				do_transact(bikeData, bikeList, status::RENTED);
				break;
			case 9:
				//deletes a bike from the list
				del_id_bike(bikeData, bikeList);
				break;
			case 10:
				//deletes a bike from the list
				del_manuf(bikeData, bikeList);
				break;
			}

		}

	}
	//displays en erroe message if the data file could not open
	else {
		cerr << "[ERROR - File Could Not Open]";
		return -1;
	}

	//deletes all bike objects 
	bikeList.clear();

	//closes the file
	bikeData.close();
	return 0;
}
void readBike(fstream& bikeData, list<shared_ptr<Bike>>& bikeList) {

	// creating a new bike node
	shared_ptr<Bike>newBike(new Bike);
	
	init(newBike);

	string line;
	int n = 1;
	while (n != 5) {

		getline(bikeData, line);
		switch (n) {
		case 1:

			//assgins the id_num field using the data from file
			newBike->id_num = stoi(line);
			break;
		case 2:

			//assgins the siz field using the data from file
			newBike->size = stoi(line);
			break;
		case 3:

			//assgins the cost_per_day field using the data from file
			newBike->cost_per_day = stof(line);
			break;
		case 4:

			//assgins the manufact field using the data from file
			strcpy_s(newBike->manufact, line.c_str());
			break;
		}

		++n;
	}

	if (bikeList.max_size() != bikeList.size()) {
		bikeList.push_back(newBike);
	}
	else {
		cerr << "[ERROR - LIST IS FULL]";
		return;
	}

}
void printBikes(list<shared_ptr<Bike>> temp, status print1, order print2) {

	//prints all bikes in no particular order
	if (print1 == status::ALL && print2 == order::NO_ORDER) {
		cout << "[ALL BIKES]:\n\n";
		cout << setw(9) << "[ID]" << setw(14) << "[BIKE]" << setw(14) << "[COST]" << setw(10) << "[SIZE]\n";
		cout << "----------------------------------------------\n";
		
		for (list<shared_ptr<Bike>>::iterator it = temp.begin(); it != temp.end(); ++it) {

			if ((*it)->deleted == false && (*it)->rented_code == status::NOT_RENTED) {
				cout << "  " << setw(7) << (*it)->id_num << setw(7) << "  " << setw(7) << (*it)->manufact;
				cout << setw(7) << "  " << setw(7) << (*it)->cost_per_day << setw(7) << "  " << (*it)->size;
				cout << "\n";
			}
		}
		cout << "\n";
	}
	else if(print1 == status::ALL && print2 == order::ID){
		cout << "[BIKES SORTED BY ID]:\n\n";
		cout << setw(9) << "[ID]" << setw(14) << "[BIKE]" << setw(14) << "[COST]" << setw(10) << "[SIZE]\n";
		cout << "----------------------------------------------\n";

		//sorts the list by id before printing
		temp.sort(comp_id);

		for (list<shared_ptr<Bike>>::iterator it = temp.begin(); it != temp.end(); ++it) {

			if ((*it)->deleted == false && (*it)->rented_code == status::NOT_RENTED) {
				cout << "  " << setw(7) << (*it)->id_num << setw(7) << "  " << setw(7) << (*it)->manufact;
				cout << setw(7) << "  " << setw(7) << (*it)->cost_per_day << setw(7) << "  " << (*it)->size;
				cout << "\n";
			}
		}
		cout << "\n";

	}
	else if (print1 == status::ALL && print2 == order::MANUF) {

		cout << "[BIKES SORTED BY MANUF]:\n\n";
		cout << setw(9) << "[ID]" << setw(14) << "[BIKE]" << setw(14) << "[COST]" << setw(10) << "[SIZE]\n";
		cout << "----------------------------------------------\n";
		//sorts the list by manuf
		temp.sort(comp_manuf);

		for (list<shared_ptr<Bike>>::iterator it = temp.begin(); it != temp.end(); ++it) {

			if ((*it)->deleted == false && (*it)->rented_code == status::NOT_RENTED) {
				cout << "  " << setw(7) << (*it)->id_num << setw(7) << "  " << setw(7) << (*it)->manufact;
				cout << setw(7) << "  " << setw(7) << (*it)->cost_per_day << setw(7) << "  " << (*it)->size;
				cout << "\n";
			}
		}
		cout << "\n";
	}
	else if (print1 == status::NOT_RENTED) {
		cout << "[BIKES AVALIABLE TO RENT]:\n\n";
		cout << setw(9) << "[ID]" << setw(14) << "[BIKE]" << setw(14) << "[COST]" << setw(10) << "[SIZE]\n";
		cout << "----------------------------------------------\n";
		for (list<shared_ptr<Bike>>::iterator it = temp.begin(); it != temp.end(); ++it) {

			if ((*it)->rented_code == status::NOT_RENTED) {
				cout << "  " << setw(7) << (*it)->id_num << setw(7) << "  " << setw(7) << (*it)->manufact;
				cout << setw(7) << "  " << setw(7) << (*it)->cost_per_day << setw(7) << "  " << (*it)->size;
				cout << "\n";
			}
		}
		cout << "\n";
	}
	else if (print1 == status::RENTED) {
		cout << "[BIKES NOT AVALIABLE TO RENT]:\n\n";
		cout << setw(9) << "[ID]" << setw(14) << "[BIKE]" << setw(14) << "[COST]" << setw(10) << "[SIZE]\n";
		cout << "----------------------------------------------\n";
		for (list<shared_ptr<Bike>>::iterator it = temp.begin(); it != temp.end(); ++it) {

			if ((*it)->rented_code == status::RENTED) {
				cout << "  " << setw(7) << (*it)->id_num << setw(7) << "  " << setw(7) << (*it)->manufact;
				cout << setw(7) << "  " << setw(7) << (*it)->cost_per_day << setw(7) << "  " << (*it)->size;
				cout << "\n";
			}
		}
		cout << "\n";
	}
	

}
void do_transact(fstream& bikeData, list<shared_ptr<Bike>>& temp, status print1) {


	 
	if (print1 == status::NOT_RENTED) {
		string line;
		// grabs the ID from file
		getline(bikeData, line);
		// loop will iterate while not end of list or ID of bike not found
		for (list<shared_ptr<Bike>>::iterator it = temp.begin(); it != temp.end(); ++it) {
			// if bike is found in list by id and bike is not rented execute conditional
			if ((*it)->id_num == stoi(line) && (*it)->rented_code == status::NOT_RENTED) {
				//set status as rented
				(*it)->rented_code = status::RENTED;

				cout << "[TRANSACTION]:\n\n";
				cout << setw(9) << "[ID]" << setw(14) << "[Days]" << setw(14) << "[COST]" << setw(10) << "[RENTER]\n";
				cout << "----------------------------------------------\n";


				cout << "  " << setw(7) << line;
				getline(bikeData, line);

				//prints out number of days and cost for rental
				cout << "  " << setw(12) << line << "  " << setw(12) << stoi(line) * (*it)->cost_per_day << setw(2);

				//grabs the last piece of data for transaction and then prints of the size of bike
				getline(bikeData, line);
				//assigns to whom the bike is rented to in the struct
				strcpy_s((*it)->to_whom, line.c_str());
				cout << " " << line;
				cout << "\n\n";

				// return after the transaction has been processed
				return;
			}
			else if ((*it)->id_num == stoi(line) && (*it)->rented_code == status::RENTED) {

				cout << "[The Current Bike Is Rented]";
				return;
			}
			
		}
	}
	else if (print1 == status::RENTED) {

		string line;
		// grabs the ID from file
		getline(bikeData, line);
		// loop will iterate while not end of list or ID of bike not found
		for (list<shared_ptr<Bike>>::iterator it = temp.begin(); it != temp.end(); ++it) {
			// if bike is found in list by id and bike is not rented execute conditional
			if ((*it)->id_num == stoi(line) && (*it)->rented_code == status::RENTED) {

				//sets the rented_code to NOT_RENTED
				(*it)->rented_code = status::NOT_RENTED;

				cout << "[RETURING BIKE]:\n\n";
				cout << setw(9) << "[ID]" << setw(14) << "[Days]" << setw(14) << "[COST]" << setw(10) << "[RENTER]\n";
				cout << "----------------------------------------------\n";

				cout << "  " << setw(7) << line;
				getline(bikeData, line);

				//prints out number of days and cost for rental
				cout << "  " << setw(12) << line << "  " << setw(12) << stoi(line) * (*it)->cost_per_day << setw(2)
					<< " " << (*it)->to_whom << setw(3);
				cout << "\n\n";

				//return after the bike has been retuned
				return;
			}
			else if ((*it)->id_num == stoi(line) && (*it)->rented_code == status::NOT_RENTED) {

				cout << "[SORRY - BIKE HAS BEEN RETURNED]:\n\n";
				cout << setw(9) << "[ID]" << setw(14) << "[Days]" << setw(14) << "[COST]" << setw(10) << "[RENTER]\n";
				cout << "----------------------------------------------\n";

				cout << "  " << setw(7) << line;
				getline(bikeData, line);

				//prints out number of days and cost for rental
				cout << "  " << setw(12) << line << "  " << setw(12) << stoi(line) * (*it)->cost_per_day << setw(2)
					<< " " << (*it)->to_whom << setw(3);
				cout << "\n\n";
				return;
			}
		}

	}

}
void del_id_bike(fstream& bikeData, list<shared_ptr<Bike>>& temp) {


	string line;
	getline(bikeData, line);
	int searchID = stoi(line);

	//while not the end of the list
	for (list<shared_ptr<Bike>>::iterator it = temp.begin(); it != temp.end(); ++it) {

		//deletes the desired bike by id and returns
		if ((*it)->id_num == searchID) {
			cout << "[DELETING BIKE]:\n\n";
			cout << setw(9) << "[ID]" << setw(14) << "[BIKE]" << setw(14) << "[COST]" << setw(10) << "[SIZE]\n";
			cout << "----------------------------------------------\n";
			cout << "  " << setw(7) << (*it)->id_num << setw(7) << "  " << setw(7) << (*it)->manufact;
			cout << setw(7) << "  " << setw(7) << (*it)->cost_per_day << setw(7) << "  " << (*it)->size;
			cout << "\n\n";
			(*it)->deleted = true;
			return;
		}
		
	}
	
}
void del_manuf(fstream& bikeData, list<shared_ptr<Bike>>& temp) {


	string line;
	getline(bikeData, line);

	//while not the end of the list
	for (list<shared_ptr<Bike>>::iterator it = temp.begin(); it != temp.end(); ++it) {

		//deletes the manufact by setting its flag to true
		if (!strcmp((*it)->manufact, line.c_str())) {
			cout << "[DELETING BIKE]:\n\n";
			cout << setw(9) << "[ID]" << setw(14) << "[BIKE]" << setw(14) << "[COST]" << setw(10) << "[SIZE]\n";
			cout << "----------------------------------------------\n";
			cout << "  " << setw(7) << (*it)->id_num << setw(7) << "  " << setw(7) << (*it)->manufact;
			cout << setw(7) << "  " << setw(7) << (*it)->cost_per_day << setw(7) << "  " << (*it)->size;
			cout << "\n\n";
			(*it)->deleted = true;
			return;
		}

	}
}
bool comp_id(shared_ptr<Bike>& b1, shared_ptr<Bike>& b2) {

	return b1->id_num < b2->id_num; 
}
bool comp_manuf(shared_ptr<Bike>& b1, shared_ptr<Bike>& b2) {

	return (strcmp(b1->manufact,b2->manufact) < 0 ? true : false);
}
void init(shared_ptr<Bike> newBike) {
	strcpy_s(newBike->manufact, "");
	newBike->id_num = 0;
	newBike->size = 0;
	newBike->cost_per_day = 0.0;
	newBike->rented_code = status::NOT_RENTED;
	newBike->deleted = false;
	strcpy_s(newBike->to_whom, "");

}
