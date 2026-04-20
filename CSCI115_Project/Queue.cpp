#include "Queue.h"

Queue::Queue()
{
	front = nullptr;
	rear = nullptr;
}

Queue::~Queue()
{
	while (!isEmpty())
		dequeue();
}

void Queue::enqueue(int val)
{
	Node* newNode = new Node(val);

	if (isEmpty())
	{
		front = newNode;
		rear = newNode;
	}
	else
	{
		rear->next = newNode;
		rear = newNode;
	}
}

int Queue::dequeue()
{
	if (isEmpty())
		return -1;

	Node* tempNode = front;
	int popped = tempNode->data;

	front = front->next;

	if (front == nullptr)
		rear = nullptr;

	delete tempNode;
	return popped;
}

bool Queue::isEmpty() const
{
	return (front == nullptr);
}

void Queue::printQueue()
{
	if (isEmpty()) return;

	Node* currNode = front;

	cout << "Queue: ";
	while (currNode != nullptr)
	{
		cout << currNode->data << " ";
		currNode = currNode->next;
	}

	cout << endl;
}

