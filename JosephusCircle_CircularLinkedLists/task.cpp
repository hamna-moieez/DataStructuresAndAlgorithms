#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>     
using namespace std;

string out_path = "output.csv";

struct Node
{
	int pos;
	string name;
	struct Node *next;
};

Node *newNode(int pos, string name)
{
	Node *temp = new Node;
	temp->pos = pos;
	temp->name = name;
	return temp;
}

void printList(Node* headOfList) {

	ofstream outfile;
	outfile.open(out_path, ios::out | ios::app);
	Node* temp = headOfList->next;
	outfile << headOfList->name << "->";
	cout << headOfList->name << "->";
	while (temp !=headOfList) {
		outfile << temp->name << "->";
		cout << temp->name << "->";
		temp = temp->next;
	}
	outfile << endl;
	cout << endl;

	outfile.close();
}
void getJosephusPosition(int m, int n)
{
	// Create a circular linked list of
	// size N.
	ifstream infile;
	string line;
	infile.open("InputFile2.txt");
	Node *head = NULL;
	Node *prev = NULL;
	ofstream outfile;

	if (infile.is_open())
	{
		bool isFirstLine = true;
		int count = 1;

		while (getline(infile, line))
		{
			if (isFirstLine) {
				isFirstLine = false;
				cout << "First line\n";
				continue;
			}
			else if (isdigit(line[0])) { // ctype.h 
				continue;
			}
			else {
				if (head == NULL) {
					head = newNode(count, line);
					prev = head;
					prev->next = head;
				}
				else {
					prev->next = newNode(count, line);
					prev = prev->next;
					prev->next = head;
				}
				count++;
			}
		}
		//prev->next = head;
		infile.close();
	}
	else {
		cout << "Unable to open file";
	}

	printList(head);
	/* while only one node is left in the
	linked list*/
	Node *ptr1 = head, *ptr2 = head;
	while (ptr1->next != ptr1)
	{
		// Find m-th node
		int count = 0;
		while (count != m)
		{
			ptr2 = ptr1;
			ptr1 = ptr1->next;
			count++;
		}

		/* Remove the m-th node */
		outfile.open(out_path, ios::out | ios::app);
		outfile << ptr1->name << " was executed!\n";

		cout << ptr1->name << " was executed!\n";
		if (ptr1 == head) {
			head = ptr1->next;
		}
		ptr2->next = ptr1->next;
		ptr1 = ptr2->next;
		outfile.close();
		printList(head);
	}
	outfile.open(out_path, ios::out | ios::app);
	outfile << "Last person left standing (Josephus Position) is " << ptr1->name << " at position " << ptr1->pos << endl;
	outfile.close();
}
//Driver program to test above functions 
int main()
{
	ifstream infile;
	string line;
	infile.open("InputFile2.txt");
	int n = 0;
	int m = 0;
	if (infile.is_open())
	{
		bool isFirstLine = true;
		while (getline(infile, line))
		{
			//line.clear();
			if (isFirstLine) {
				n = atoi(line.c_str());
				isFirstLine = false;
				//cout << "n: " << n << endl;
			}
			//cout << line << endl;
		}
		//cout << line << endl;
		m = atoi(line.c_str());
		infile.close();
	}
	else {
		cout << "Unable to open file";
	}
	/* 	getline(infile, line);
	int n = stoi(str);

	cout << str << endl;
	int m = 4; */
	ofstream outfile;
	outfile.open(out_path, ios::out | ios::app);
	outfile << "There are " << n << " people in the circle" << endl;
	outfile.close();

	getJosephusPosition(m, n);
	system("pause");
	return 0;
	//std::cin.get();
}