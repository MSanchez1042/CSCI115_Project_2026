#include <iostream>

#include "Queue.h"
#include "Graph.h"

using namespace std;

int main()
{
	Graph g(6, false, true);

	g.addEdge(0, 1, 1.0);
	g.addEdge(0, 2, 1.0);
	g.addEdge(1, 3, 1.0);
	g.addEdge(2, 4, 1.0);
	g.addEdge(3, 5, 1.0);

	g.displayAdjList();

	bool graphConnceted = g.isConnected(0);

	if (graphConnceted)
		cout << "The graph is connected.\n";
	else
		cout << "The graph is not connected.\n";
}