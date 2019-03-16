//include dependencies

#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <ctype.h>
#include <string>
#include <stdlib.h>     /* atoi */

using namespace std;

//input and output filepath

string input_path = "Input2.txt";
string output_path = "Output2.txt";

void printArray(int len, int array[]) {

	for (int i = 0; i < len; i++)
		cout << array[i] << " " << "|";
}

void swap(int *prev, int *next) {
	int temp;
	temp = *prev;
	*prev = *next;
	*next = temp;
}

int partition(int array[], int first, int last) {


	int pivot = array[last];
	int i = (first - 1);

	for (int j = first; j <= last - 1; j++)
	{
		if (array[j] <= pivot)
		{
			i++;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[i + 1], &array[last]);
	return (i + 1);
}

void quickSort(int array[], int first, int last) {

	if (first < last) {
		int partitionIndex = partition(array, first, last);

		quickSort(array, first, partitionIndex - 1);
		quickSort(array, partitionIndex + 1, last);


	}
}

std::string sportsGala(int seniorArrayLen, int juniorArrayLen, int seniorArray[], int juniorArray[]) {
	int SAfirst = 0;
	int SAlast = seniorArrayLen - 1;
	int JAfirst = 0;
	int JAlast = juniorArrayLen - 1;
	bool isShort = false;

	quickSort(seniorArray, SAfirst, SAlast);
	quickSort(juniorArray, JAfirst, JAlast);

	printArray(seniorArrayLen, seniorArray);
	cout << endl;
	printArray(juniorArrayLen, juniorArray);

	for (int i = SAfirst; i <= SAlast; i++) {

		if (seniorArray[i] > juniorArray[i]) {
			isShort = true;
		}
		else {
			isShort = false;
			break;
		}
	}
	if (isShort) {
		cout << "\nYES";
		return "YES";
	}
	cout << "\nNO";
	return "NO";
}

std::vector<int> splitter(string string_to_split) {

	std::string to_split = string_to_split;

	std::vector<int> splitted_string_vector;
	std::size_t pos = 0, found;
	while ((found = to_split.find_first_of(' ', pos)) != std::string::npos) {
		splitted_string_vector.push_back(atoi(to_split.substr(pos, found - pos).c_str()));
		pos = found + 1;
	}
	splitted_string_vector.push_back(atoi(to_split.substr(pos).c_str()));

	return splitted_string_vector;
}

int main() {
	int testCases;
	int noOfSeniors;
	int noOfJuniors;
	string result;
	string line;
	std::vector<int> splitted_int_vector;
	std::vector<int> splitted_senior_vector;
	std::vector<int> splitted_junior_vector;
	ifstream infile;
	infile.open(input_path);
	ofstream outfile;
	outfile.open(output_path, ios::out | ios::trunc);

	if (infile.is_open()) {
		getline(infile, line);
		testCases = atoi(line.c_str());
		cout << "Test cases: " << testCases << endl;

		for (int testCase = 0; testCase < testCases; testCase++) {
			// Get the number of seniors and juniors and creating array to according this number
			getline(infile, line);
			splitted_int_vector =splitter(line);
			noOfSeniors = splitted_int_vector[0];
			noOfJuniors = splitted_int_vector[1];

			cout << noOfSeniors << " " << noOfJuniors << endl;

			int *seniors = new int[noOfSeniors];
			int *juniors = new int[noOfJuniors];
			
			// Get the height of seniors
			getline(infile, line);
			splitted_senior_vector = splitter(line);
			seniors = &splitted_senior_vector[0];

			// Get the height of juniors
			getline(infile, line);;
			splitted_junior_vector = splitter(line);
			juniors = &splitted_junior_vector[0];

			result = sportsGala(noOfSeniors, noOfJuniors, seniors, juniors);
			outfile << result << endl;
			cout << endl;
		}
		infile.close();
		outfile.close();
	}
	else {
		cout << "Unable to open file";
	}
	system("pause");
	return 0;
}