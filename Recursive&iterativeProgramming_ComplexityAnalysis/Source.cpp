#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
using namespace std;

string out_path = "output.csv";

long factorial_itr(long el) {

	int fact = el;
	for (int i = el - 1; i > 0; i--) {
		fact *= i;
	}
	return fact;
}

long factorial_rec(long el) {
	if (el == 1 || el == 0) {
		return 1;
	}
	else
		return el * factorial_rec(el - 1);
}

int fibonacci_itr(int input) {
	long prev = 0;
	long curr = 1;
	long next;

	if (input == 0)
	{
		return 0;
	}
	else if (input == 1)
	{
		return 1;
	}
	else
	{
		for (long i = 2; i <= input; i++) {
			next = prev + curr;
			prev = curr;
			curr = next;
		}
		return next;
	}

}

int fibonacci_rec(long input)
{
	if (input == 0)
	{
		return 0;
	}
	else if (input == 1)
	{
		return 1;
	}
	else
	{
		return fibonacci_rec(input - 1) + fibonacci_rec(input - 2);
	}
}
int main() {

	ofstream outfile;
	outfile.open(out_path, ios::out | ios::app);
	clock_t begin;
	clock_t	end;
	int n = 1000;

	outfile << "n is:" << n << endl;
	begin = clock();
	for (long i = 0; i < n; i++) {
		factorial_itr(i);
	}
	end = clock();
	double seconds = (double)(end - begin) * 1000 / CLOCKS_PER_SEC;
	outfile << "The run time for iterative factorial is: " << seconds << " nanoseconds!" << endl;

	begin = clock();
	for (int i = 0; i < n; i++) {

		factorial_rec(i * 2);
	}
	end = clock();
	seconds = (double)(end - begin) * 1000 / CLOCKS_PER_SEC;
	outfile << "The run time for recursive factorial is: " << seconds << " nanoseconds!" << endl;

	begin = clock();
	for (long x = 0; x<n; x++) {
		fibonacci_itr(x * 2);
	}
	end = clock();
	seconds = (double)(end - begin) * 1000 / CLOCKS_PER_SEC;
	outfile << "The run time for iterative fibonacci is: " << seconds << " nanoseconds!" << endl;

	for (long i = 24; i <= 40; i += 4) {
		begin = clock();
		fibonacci_rec(i);
		end = clock();
	}
	seconds = (double)(end - begin) * 1000000 / CLOCKS_PER_SEC;
	outfile << "The run time for recursive fibonacci is: " << seconds << " milliseconds!" << endl;
	outfile.close();
	system("pause");
}
