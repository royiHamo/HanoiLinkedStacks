#include "HT.h"
using namespace std;
#include <iostream>
#include <stdio.h>


int main()
{
	int disks;
	cout << "Insert desired amount of disks to move:____" ; cin >> disks;
	Stack From(disks);
	Stack Help;
	Stack To;
	SolveHanoiProblem(From,Help,To,disks);
	system("pause");
}