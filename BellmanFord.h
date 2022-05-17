#pragma once
#include"List1.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//consts
const int NA = INT_MIN; //no arrive
const int number = -1;

//class graph
class GraphCities {

public:

	//members
	int price; //the price of flight
	string departureCity; //the city you go from
	int departNumber = number;
	string arrivalCity; //the city you go to
	int arriveNumber = number;

	//constructor
	GraphCities(string departureCity, string arrivalCity, int price, int departNumber, int arriveNumber) {
		this->departureCity = departureCity;
		this->arrivalCity = arrivalCity;
		this->price = price;
		this->departNumber = departNumber;
		this->arriveNumber = arriveNumber;
	}

	//destructor
	GraphCities() {
		this->departureCity = "\0";
		this->arrivalCity = "\0";
		this->price = 0;
		this->departNumber = number;
		this->arriveNumber = number;
	}
};

//forming graph, name the vertexes, destination "from" "to"
void createGraph(List<GraphCities>* namesPath, List<string>* amountStrings) {

	int amountPaths = namesPath->getSize(); //how are paths named there?
	int sizeAmountStrings = amountStrings->getSize(); //how are strings named there?

	//"ordered pair"
	for (int i = 0; i < amountPaths; i++) {
		for (int j = 0; j < sizeAmountStrings; j++) {

			//depart city
			if ((*namesPath)[i].departureCity == (*amountStrings)[j])
				(*namesPath)[i].departNumber = j;

			//arrive city
			if ((*namesPath)[i].arrivalCity == (*amountStrings)[j])
				(*namesPath)[i].arriveNumber = j;
		}
	}
}

//get vertexes (tops of graph), there're cities counted
int getVertexesCities(List<string>* cities) {

	if (cities->getSize() == 0) //empty?
		return number;
	else {
		int amount = cities->getSize(); //how are cities there?

		for (int i = 0; i < amount - 1; i++) {
			for (int j = i + 1; j < amount; j++) {
				if ((*cities)[i] == (*cities)[j]) {
					cities->remove(j);
					amount--;
					j--;
				}
			}
		}

		return cities->getSize();
	}
}

//Bellman-Ford algorithm
int bellmanFord(List<GraphCities>* namesPath, List<string>* amountStrings, string departureCity, string arrivalCity) {

	int infinity = INT_MAX - 10000; //for ordering V

	//counters
	int amountPaths = namesPath->getSize();
	int sizeAmountStrings = getVertexesCities(amountStrings);

	//create graph
	createGraph(namesPath, amountStrings);


	//create table with strings
	int* table = new int[sizeAmountStrings];

	//choosed the start node and set the rest to infinity
	for (int i = 0; i < sizeAmountStrings; i++) {

		//loop or the same node, else infinity
		if ((*amountStrings)[i] == departureCity)
			table[i] = 0;
		else
			table[i] = infinity;
	}

	//create table
	for (int i = 0; i < sizeAmountStrings - 1; i++) {
		for (int j = 0; j < amountPaths; j++) {
			if (table[(*namesPath)[j].departNumber] + (*namesPath)[j].price
				< table[(*namesPath)[j].arriveNumber])

				table[(*namesPath)[j].arriveNumber] =
				table[(*namesPath)[j].departNumber] + (*namesPath)[j].price;
		}
	}

	//for print the information about flights
	for (int i = 0; i < sizeAmountStrings; i++) {
		if (departureCity == arrivalCity) {
			std::cout << "\n No arrive from " <<
				departureCity << " to " << arrivalCity << "\n";
			return NA;
		}
		else
			if ((*amountStrings)[i] == arrivalCity) {
				std::cout << "\n The cheapest price is " << table[i] << " from " <<
					departureCity << " to " << arrivalCity << "\n";
				return table[i];
			}
	}
}


//parse strings in file
void parse(List<GraphCities>* namesPath, List<string>* amountStrings) {

	//open file
	fstream file;
	file.open("flight.txt", ios_base::in);

	//check, then parse
	if (file.good()) {

		//elements for separate, counters
		int counterPos = 0;
		string line;
		string subline;

		while (getline(file, line)) { //read

			//set the paths
			GraphCities firstCityPath;
			GraphCities secondCityPath;

			//go ;
			subline = line;
			counterPos = line.find(';');

			//new size and add (increase amount counter)
			subline.resize(counterPos);
			amountStrings->pushBack(subline);

			//there are cities
			firstCityPath.departureCity = subline;
			secondCityPath.arrivalCity = subline;

			//clear at position in line
			line.erase(0, counterPos + 1);

			//the back path
			subline = line;
			counterPos = line.find(';');
			subline.resize(counterPos);
			amountStrings->pushBack(subline);
			firstCityPath.arrivalCity = subline;
			secondCityPath.departureCity = subline;
			line.erase(0, counterPos + 1);

			//definite the price for straight and back paths
			subline = line;
			counterPos = line.find(';');
			subline.resize(counterPos);

			if (subline != "N/A") { //it's arrive
				firstCityPath.price = stoi(subline);
				namesPath->pushBack(firstCityPath);
			}

			//clear
			line.erase(0, counterPos + 1);

			if (line != "N/A") {
				secondCityPath.price = stoi(line);
				namesPath->pushBack(secondCityPath);
			}
		}
	}
	else
		std::cout << "Error";

	file.close(); //close
}