#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <ctype.h>
#include <string>
#include <stdlib.h>     /* atoi */

using namespace std;

string input_path = "InputFile2.txt";
string output_path = "OutputFile2.txt";

class QueueLinkedListNode {
public:
	int school;
	int roll_no;
	QueueLinkedListNode *next;

	QueueLinkedListNode(int school_data, int roll_data) {
		this->school = school_data;
		this->roll_no = roll_data;
		this->next = nullptr;	
	}
};

class QueueLinkedList {
public:
	QueueLinkedListNode * head;

	QueueLinkedList() {
		this->head = nullptr;
	}

	QueueLinkedListNode* enqueueNodeAtTail(QueueLinkedListNode* head, QueueLinkedListNode* newNode) {

		if (head == NULL)
		{
			head = newNode;
		}
		else
		{
			QueueLinkedListNode *curr;
			curr = head;
			while (curr->next != NULL)
			{
				curr = curr->next;
			}
			curr->next = newNode;
			newNode->next = NULL;
		}
		return newNode;
	}

	QueueLinkedListNode* enqueueNodeAtHead(QueueLinkedListNode* newNode) {

		newNode->next = head;
		head = newNode;
		return head;
	}

	QueueLinkedListNode* enqueueNodeAtPosition(QueueLinkedListNode* tailPtr, QueueLinkedListNode* newNode) {

		if (!tailPtr) {
			tailPtr = enqueueNodeAtTail(this->head, newNode);
		}
		else
		{
			newNode->next = tailPtr->next;
			tailPtr->next = newNode;
			tailPtr = newNode;
		}
		return tailPtr;
	}

	QueueLinkedListNode* dequeueNode() {
		ofstream outfile;
		outfile.open(output_path, ios::out | ios::app);

		if (!head) {
			return NULL;
		}
		else {
			QueueLinkedListNode* delPtr;
			delPtr = head;
			head = head->next;
			cout << delPtr->school << " " << delPtr->roll_no << endl;
			outfile << delPtr->school << " " << delPtr->roll_no << endl;
			delete delPtr;
			return head;
		}
	}
};

std::vector<string> splitter(string string_to_split) {

	std::string to_split = string_to_split;

	std::vector<std::string> splitted_string_vector;
	std::size_t pos = 0, found;
	while ((found = to_split.find_first_of(' ', pos)) != std::string::npos) {
		splitted_string_vector.push_back(to_split.substr(pos, found - pos));
		pos = found + 1;
	}
	splitted_string_vector.push_back(to_split.substr(pos));

	return splitted_string_vector;
}

int main() {

	QueueLinkedList* studentQueue = new QueueLinkedList();
	string line;
	ifstream infile;
	infile.open(input_path);
	int n = 0;
	int m = 0;

	QueueLinkedListNode* tail1=NULL; 
	QueueLinkedListNode* tail2=NULL;
	QueueLinkedListNode* tail3=NULL;
	QueueLinkedListNode* tail4=NULL;


	std::vector<std::string> splitted_string_vector;
	if (infile.is_open())
	{
		bool isFirstLine = true;
		while (getline(infile, line))
		{
			if (isFirstLine) {
				n = atoi(line.c_str());
				isFirstLine = false;
				//cout << "n: " << n << endl;
			}
			else {
				splitted_string_vector = splitter(line);
				if (!splitted_string_vector[0].compare("D") )
				{
					studentQueue->head = studentQueue->dequeueNode();
				}
				else if (!splitted_string_vector[0].compare("E")) {
					int school = atoi(splitted_string_vector[1].c_str());
					int roll_no = atoi(splitted_string_vector[2].c_str());
					QueueLinkedListNode* newNode = new QueueLinkedListNode(school, roll_no);
					QueueLinkedListNode* ifHeadNode = NULL;

					if (school == 1) {
						tail1 = studentQueue->enqueueNodeAtPosition(tail1, newNode);
						ifHeadNode = tail1;
					}
					else if (school == 2)
					{
						tail2 = studentQueue->enqueueNodeAtPosition(tail2, newNode);
						ifHeadNode = tail2;
					}
					else if (school == 3)
					{
						tail3 = studentQueue->enqueueNodeAtPosition(tail3, newNode);
						ifHeadNode = tail3;
					}
					else
					{
						tail4 = studentQueue->enqueueNodeAtPosition(tail4, newNode);
						ifHeadNode = tail4;
					}
					if (!studentQueue->head) {
						studentQueue->head = ifHeadNode;
					}
				}
			}
		}
		infile.close();
	}
	else {
		cout << "Unable to open file";
	}

	system("pause");
	return 0;
}



