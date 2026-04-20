#ifndef GRAPH_H
#define GRAPH_H

#include "Queue.h"

struct Edge
{
	int to;	// destination
	double weight;
	Edge* next;

	Edge(int to, double w)
	{
		this->to = to;
		weight = w;
		next = nullptr;
	}
};

class Graph
{
public:
	Graph(int, bool, bool);
	~Graph();

	bool weighted;
	bool directed;

	bool edgeExists(int, int);
	void addEdge(int, int, double);
	void removeEdge(int, int);

	void displayAdjList();

private:
	int vertices;

	Edge** adj;
};

#endif
