//#include "stdafx.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <ctype.h>
#include <string>
#include <stdlib.h>     /* atoi */

using namespace std;

int maxAgeBunny = 5;
int adultAge = 2;
string in_path = "InputFile3.txt";
string out_path = "output3.txt";


class Bunny {
public:
	string gender;
	string name;
	string color;
	int age;

	Bunny *next;
	bool alive;

	Bunny()
	{
		gender = genders();
		name = names(gender);
		color = colors();
		age = 0;
		alive = true;
		next = NULL;
	}

	Bunny(vector<string> constructor_fields_vector){
		name = constructor_fields_vector[0];
		gender = constructor_fields_vector[1];
		color = constructor_fields_vector[2];
		age = atoi(constructor_fields_vector[3].c_str());
		//age = std::stoi( constructor_fields_vector[3], NULL, 10 ); 
		alive = true;
		next = NULL;
	}

	string genders()
	{
		int randNum = rand() % 5 + 1;  // generates randon number from 1 to 5. where if number is 1 female is born else if number is in [2,3,4,5], male is born
		string gender = "";

		if (randNum == 1)
		{
			gender = "F";
		}
		else
		{
			gender = "M";
		}
		return gender;
	}

	string names(string gender)
	{
		int random = rand() % 4 + 1;
		string name = "";

		if (gender == "M")
		{
			switch (random)
			{
			case 1: name = "Thumper";
				break;

			case 2: name = "Jerry";
				break;

			case 3: name = "Dumper";
				break;

			case 4: name = "Tom";
				break;

			};
		}
		else if (gender == "F")
		{
			switch (random)
			{
			case 1: name = "Moana";
				break;

			case 2: name = "Daisy";
				break;

			case 3: name = "Alice";
				break;

			case 4: name = "Ariel";
				break;
			};
		}
		return name;
	}

	string colors()
	{
		int randNum = rand() % 4 + 1;
		string color = "";
		switch (randNum)
		{
		case 1: color = "white";
			break;

		case 2: color = "brown";
			break;

		case 3: color = "black";
			break;

		case 4: color = "spotted";
			break;
		};

		return color;
	}

};

void bunnyStatus(Bunny *bunny, char status = 'd')
{
	ofstream outfile;
	outfile.open(out_path, ios::out | ios::app);
	if (status == 'b')
	{
		outfile << "New bunny " << bunny->name << " was born" << endl;
		//cout << "New bunny " << bunny->name << " was born" << endl;
		
	}
	else if (bunny->alive)
	{
		outfile << "Bunny " << bunny->name << " has passed away" << endl;
		//cout << "Bunny " << bunny->name << " has passed away" << endl;
		
	}

	outfile.close();

}

void incrementAllBunniesAge(Bunny *first) {
	while (first != NULL)
	{
		first->age = first->age + 1;
		first = first->next;
	}
}

void addBunny(Bunny *bunny)
{
	int maleCount = 0;
	int totalPopulation = 0;
	Bunny *first = bunny;
	Bunny *mother;


	while (bunny != NULL)
	{
		totalPopulation++;
		if (bunny->gender == "M" && bunny->age >= adultAge && bunny->alive)
			maleCount++;
		bunny = bunny->next;
	}

	while (first != NULL)
	{
		Bunny *temp = new Bunny();
		if (maleCount > 0 && first->gender == "F" && first->age >= adultAge && first->alive)
		{

			mother = first;
			temp->color = mother->color;
			temp->next = mother->next;
			mother->next = temp;
			first = temp->next;
			bunnyStatus(temp, 'b');
		}
		else
		{
			first = first->next;
		}
	}
}


void printAllBunnies(Bunny *first) 
{
	ofstream outfile;
	outfile.open(out_path, ios::out | ios::app);
	int i = 1;
	//int bunnyCount = 0;
	//Bunny *bunnyHead;
	while (first != NULL)
	{
		if (first->alive)
		{
			outfile  << i++ << '\t' << first->name << '\t' << first->gender << '\t' << first->color << '\t' << "Age: " << first->age << endl;
			//cout << i << '\t' << first->name << '\t' << first->gender << '\t' << "Age: " << first->age << endl;
		}
		first = first->next;
		//bunnyCount++;
	}
	//outfile << "Total bunnies " << bunnyCount - killBunnies(bunnyHead)<< endl;
	outfile.close();
	//return bunnyCount;
}

void killBunnies(Bunny *first)
{
	bool alive = true;
	while (first != NULL)
	{Bunny *b3 = new Bunny();
		if (first->age > maxAgeBunny)
		{
			bunnyStatus(first);
			first->alive = false;

		}
		first = first->next;
	}

}

bool terminates(Bunny *first)
{
	bool terminate = false;
	int countDead = 0;
	int totalPopulation = 0;

	while (first != NULL)
	{
		totalPopulation++;

		if (!first->alive)
		{
			countDead++;
		}

		first = first->next;
	}

	if (countDead == totalPopulation)
	{
		terminate = true;
	}

	return terminate;
};

// We define a function to split a whole line into individual words

std::vector<string> splitter(string string_to_split){

	std::string to_split = string_to_split;

	//cout << string_to_split << endl;
	//cout << to_split << endl;
	std::vector<std::string> splitted_string_vector;
	std::size_t pos = 0, found;
	while((found = to_split.find_first_of(' ', pos)) != std::string::npos) {
		splitted_string_vector.push_back(to_split.substr(pos, found - pos));
		//cout << to_split.substr(pos, found-pos);
		pos = found+1;
	}
	splitted_string_vector.push_back(to_split.substr(pos));

	return splitted_string_vector;
}

int main()
{
	//srand(time(0));

	string line;
	ifstream infile; 
	ofstream outfile;

	Bunny *bunnypointer = NULL;
	Bunny *bunnyhead = NULL;

	infile.open(in_path);

	if (infile.is_open())
	{
		while (getline(infile, line))
		{
	//		if (!isdigit(line[0])){ // ctype.h 
			if(bunnypointer == NULL){
				bunnypointer = new Bunny(splitter(line));
			}
			else {
				bunnypointer->next = new Bunny(splitter(line));
				bunnypointer = bunnypointer->next;
			}
			if (bunnyhead == NULL) {
				bunnyhead = bunnypointer;
			}
	//		}
			cout << line << '\n';
			line.clear();
/* 			else{
				bunnypointer = NULL;
				bunnyhead = bunnypointer;
			}
			*/
		}
		infile.close();
	}
	else cout << "Unable to open file";

/* 	Bunny *b1 = new Bunny();
	Bunny *b2 = new Bunny();
	Bunny *b3 = new Bunny();
	Bunny *b4 = new Bunny();
	Bunny *b5 = new Bunny();
	b1->next = b2;
	b2->next = b3;
	b3->next = b4;
	b4->next = b5; */

	//cout << bunnyhead->name;
	
	int cycle = 1;
	while (!terminates(bunnyhead))
	{
		outfile.open(out_path, ios::out | ios::app);
		outfile << endl << "Cycle " <<  cycle++ << endl;
		//outfile << "Total Bunnies: " << printAllBunnies(bunnyhead) << endl;

		outfile.close();
		killBunnies(bunnyhead);
		addBunny(bunnyhead);

		printAllBunnies(bunnyhead);
		cout << '\t'<< " Press Enter" << '\t' << endl;
		incrementAllBunniesAge(bunnyhead);
		cin.get();
	}
	cin.get();

	infile.open(out_path);
	
	if (infile.is_open())
	{
		while (getline(infile, line))
		{
			cout << line << '\n';
		}
		infile.close();
	}
	else cout << "Unable to open file";
}