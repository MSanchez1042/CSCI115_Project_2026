#include <iostream>

#include "Queue.h"
#include "Graph.h"

using namespace std;

int main()
{
	Queue myQ;

	myQ.enqueue(5);
	myQ.enqueue(7);
	myQ.printQueue();
}