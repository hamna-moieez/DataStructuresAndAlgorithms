#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

std::vector<string> splitter(string string_to_split) {

	std::string to_split = string_to_split;

	//cout << string_to_split << endl;
	//
	std::vector<std::string> splitted_string_vector;
	std::size_t pos = 0, found;
	while ((found = to_split.find_first_of(' ', pos)) != std::string::npos) {
		splitted_string_vector.push_back(to_split.substr(pos, found - pos));
		cout << to_split.substr(pos, found - pos) << endl;
		pos = found + 1;
	}
	splitted_string_vector.push_back(to_split.substr(pos));
	cout << to_split.substr(pos) << endl;

	std::cout << "myvector stores " << int(splitted_string_vector.size()) << " strings.\n";

	//printing the elements of vector

	cout << "Original String: " << to_split << endl;

	for (std::vector<string>::const_iterator i = splitted_string_vector.begin(); i != splitted_string_vector.end(); ++i)
		std::cout << *i << '|';

	cout << endl << "End of one vector " << endl;

	return splitted_string_vector;
}

int main() {

	//splitter("Roger M Black 3");
	//splitter("Dumper M White 3");
	ifstream infile;
	string line;
	infile.open("InputFile.txt");

	if (infile.is_open())
	{
		while (getline(infile, line))
		{
			if (!isdigit(line[0])) { // ctype.h 
				cout << line << "Additional\n";
				splitter(line);
			}
			line.clear();
			//else{
			//	bunnypointer = NULL;
			//	bunnyhead = bunnypointer;
		}
		infile.close();
	}
	else {
		cout << "Unable to open file";
	}
	system("pause");

}