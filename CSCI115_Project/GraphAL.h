#ifndef GRAPH_AL_H
#define GRAPH_AL_H

#include "Queue.h"
#include "PriorityQueue.h"

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

class GraphAL
{
public:
	GraphAL(int v, bool isWeighted, bool isDirected);
	~GraphAL();

	bool weighted;
	bool directed;

	bool edgeExists(int, int);
	void addEdge(int, int, double);
	void removeEdge(int, int);

	bool isConnected(int);

	void BFS(int);

	void displayAdjList();

private:
	int vertices;

	Edge** adj;
};

#endif
