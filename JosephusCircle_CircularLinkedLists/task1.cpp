#include <fstream>
#include <iostream>
#include <string>
using namespace std;
string out_path = "output1.txt";

/* structure for a node in circular
linked list */
struct Node
{
	int pos;
	string name;
	struct Node *next;
};

// To create a new node of circular
// linked list
Node *newNode(int pos, string name)
{
	Node *temp = new Node;
	temp->next = temp;
	temp->pos = pos;
	temp->name = name;
	return temp;
}


void getJosephusPosition(int m, int n)
{
	// Create a circular linked list of
	// size N.
	ifstream infile;
	string line;
	infile.open("InputFile.txt");
	Node *head = NULL;
	Node *prev = NULL;

	if (infile.is_open())
	{
		bool isFirstLine = true;
		int count = 1;

		while (getline(infile, line))
		{
			if (isFirstLine) {
				isFirstLine = false;
				continue;
			}
			else if (isdigit(line[0])) { // ctype.h 
				continue;
			}
			else {
				if (head == NULL) {
					head = newNode(count, line);
					prev = head;
				}
				else {
					prev->next = newNode(count, line);
					prev = prev->next;
				}
				count++;
			}
		}
		prev->next = head;
		infile.close();
	}
	else {
		cout << "Unable to open file";
	}

	Node *ptr1 = head, *ptr2 = head;
	while (ptr1->next != ptr1)
	{
		// Find m-th node
		int count = 1;
		while (count != m)
		{
			ptr2 = ptr1;
			ptr1 = ptr1->next;
			count++;
		}

		/* Remove the m-th node */
		ptr2->next = ptr1->next;
		ptr1 = ptr2->next;
	}

	printf("Last person left standing "
		"(Josephus Position) is %d\n ",
		ptr1->pos);

	cout << "Last person left standing (Josephus Position) is " << ptr1->name << " at position " << ptr1->pos << endl;
}

int main()
{
	ifstream infile;
	string line;
	infile.open("InputFile.txt");
	int n = 0;
	int m = 0;

	if (infile.is_open())
	{
		bool isFirstLine = true;
		while (getline(infile, line))
		{
			if (isFirstLine) {
				n = stoi(line);
				isFirstLine = false;
			}
			line.clear();
		}

		for (int i = 1; i <= n; i++)
		{
			getline(infile, line);
		}
		getline(infile, line);
		m = stoi(line);
		//m = stoi(line);
		infile.close();
	}
	else {
		cout << "Unable to open file";
	}
}