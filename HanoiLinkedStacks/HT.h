
#pragma once
#include <iostream>
using namespace std;
static char _Name = 'A';
static int _Moves = 0;
//-------------------------------------------------Disk/Node----------------------------------------//
class Disk { // linked list node 
private:
	//members
	int _size;
	Disk* _next;
public:

	//Ctors& Dtors

	Disk(int diskSize, Disk* nextDisk) :_size(diskSize), _next(nextDisk) {}
	Disk(int diskSize): _size(diskSize),_next(nullptr) {}
	//getters & setters

	int getSize() { return _size; }
	void setSize(int DiskSize) { this->_size = DiskSize; }
	Disk* getNext() { return this->_next; }
	void setNext(Disk* n) { this->_next = n; }

	//methods

	void PrintDisk() const { cout << this->_size << endl; }
};
//------------------------------------------------Linked List----------------------------------------//
class LinkedList {
	char _name;
	Disk* _head;
	//T* _iterator;
	int _numOfDisks;
	friend class Disk;
public:

	//Ctors & Dtors
	LinkedList() :_head(nullptr), _numOfDisks(0), _name(_Name++) {};
	LinkedList(int numOfDisks) {
		_head = nullptr;
		_numOfDisks = 0;
		_name = _Name++;
		//_iterator = _head;
		for (int i = numOfDisks; i >= 1; i--)
		{
			if (!_head)
			{
				this->Insert(&Disk(i));
			}
			else
			this->Insert(&Disk(i,_head));
		}
	}
	~LinkedList()
	{
		Remove();
	}
	
	//setters & getters
	char getName() const { return _name; }
	int getNumOfDisks() { return _numOfDisks; }
	Disk* getHead()  { return _head; }
	void setHead(Disk* head) { _head = head; }
	
	//methods
	void Insert(Disk * d); // insert disk to the beggining list
	Disk * Remove();	   // remove the first disk in the list
	

};

//--------------------------------------------------Stack-------------------------------------------//
class Stack {
private:
	//members
	LinkedList * List;
	Disk *top;                 // top of stack
	
public:
	//Ctors & Dtors
	Stack(int disks) { List = new LinkedList(disks); top = List->getHead(); }
	Stack() :top(0) { List = new LinkedList(); }
	~Stack() {
		while (!isEmpty()) {
			Pop();
		}
		//isEmpty();
	}

	//methods
	void Push(Disk obj);
	Disk & Pop();
	bool isEmpty();
	Disk * topElement();
	LinkedList* getList() { return List; };
	char getName() const { return List->getName(); }
};
	
//-----------------------------------------------Static Functions-------------------------------------//
static void Move(Stack & from, Stack & to);
static void MoveSomething(Stack & from, Stack & help, Stack & to, Disk* smallest);
static void MoveSmallestCW(Stack & from, Stack & help, Stack & to, Disk* smallest);
static void MoveSmallestCCW(Stack & from, Stack & help, Stack & to, Disk* smallest);
void SolveHanoiProblem(Stack & from, Stack & help, Stack & to, int disks);

