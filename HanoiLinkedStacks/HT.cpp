#include "HT.h"



//------------------------------------LinkedList---------------------------------------//
void LinkedList::Insert(Disk *d) {
	if ((_head != nullptr) && (_head->getSize() != 0) && (d->getSize() > _head->getSize())) {
		cout << "Error - trying to put a big disk on a smaller one" << endl;
		return;
	}
	Disk *temp = new Disk(d->getSize(), _head);
	_head = temp;
	this->_numOfDisks++;

}


Disk * LinkedList::Remove() {
	Disk* popped = _head;
	_head = _head->getNext();
	this->_numOfDisks--;
	popped->setNext(nullptr);
	return popped;
}
//---------------------------------------Disk-----------------------------------------//

//                                  ----<inline>----

//---------------------------------------Stack----------------------------------------//

Disk * Stack::topElement() {
	//std::cout << "In topElement Operation" << std::endl;
	if (!isEmpty()) {
		return (new Disk(top->getSize()));
	}
	else
		return (new Disk(99999999999));
}

void Stack::Push(Disk obj) { this->List->Insert(&obj); top = List->getHead(); }
Disk & Stack::Pop() {
	if (!isEmpty()) {
		top = top->getNext();
		return *(List->Remove());
	}
	throw "Error! - Can't Pop from an Empty Stack";
	//return 0;
}
bool Stack::isEmpty() {
	return (top == nullptr);
}
//---------------------------------------Static methods----------------------------------------//

static void Move(Stack & from, Stack & to)
{
	cout << "Moving disk with size of " << from.topElement()->getSize() << " from Tower " << from.getName() << " to tower " << to.getName() << endl;
	to.Push(from.Pop());
	_Moves++;
}
static void MoveSomething(Stack & from, Stack & help, Stack & to, Disk* smallest)
{
	if(!from.isEmpty()) {
		if ((from.topElement()->getSize() == smallest->getSize()))
			if (!help.isEmpty() && (help.topElement()->getSize() < to.topElement()->getSize()))
				Move(help, to);
			else
				Move(to, help);
		else if ((!help.isEmpty()) && (help.topElement()->getSize() == smallest->getSize()))
		{
			if (from.topElement()->getSize() < to.topElement()->getSize())
				Move(from, to);
			else
				Move(to, from);
		}
		else if (from.topElement()->getSize() < help.topElement()->getSize())
			Move(from, help);
		else
			Move(help, from);
	}
	else if (!help.isEmpty())
	{
		if ((!help.isEmpty()) && (help.topElement()->getSize() == smallest->getSize()))
		
			Move(to, from);
		else
			Move(help, from);
		
	}
	else if (!to.isEmpty())
	{
		if (to.topElement()->getSize() == smallest->getSize())
		{
			if (help.topElement()->getSize() < to.topElement()->getSize())
				Move(help, to);
			else
				Move(to, help);
		}
	}
}
static void MoveSmallestCW(Stack & from, Stack & help, Stack & to, Disk* smallest)
{
	if (!from.isEmpty() && (smallest->getSize() == from.topElement()->getSize()))
		Move(from, help);
	else if (!help.isEmpty() && (smallest->getSize() == help.topElement()->getSize()))
		Move(help, to);
	else
		Move(to, from);
}
static void MoveSmallestCCW(Stack & from, Stack & help, Stack & to, Disk* smallest)
{
	if (!from.isEmpty() && (smallest->getSize() == from.topElement()->getSize()))
		Move(from, to);
	else if (!help.isEmpty() && (smallest->getSize() == help.topElement()->getSize()))
		Move(help, from);
	else
		Move(to, help);
}
void SolveHanoiProblem(Stack & from, Stack & help, Stack & to, int disks) {
	bool KeepRunning = true;
	Disk* smallest = from.topElement();
//	smallest->setNext(nullptr);
	while (KeepRunning) {

		if (disks % 2 == 0)
		{
			while (to.getList()->getNumOfDisks() != disks)
			{
				MoveSmallestCW(from, help, to, smallest);
				if (to.getList()->getNumOfDisks() != disks)
					MoveSomething(from, help, to, smallest);
			}
		}
		else
		{
			while (to.getList()->getNumOfDisks() != disks)
			{
				MoveSmallestCCW(from, help, to, smallest);
				if (to.getList()->getNumOfDisks() != disks)
					MoveSomething(from, help, to, smallest);
			}
		}
		KeepRunning = false;
		cout << "The Problem is solved with " << _Moves <<" moves :)" << endl;
	}

}

