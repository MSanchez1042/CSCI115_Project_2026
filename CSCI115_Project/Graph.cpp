#include "Graph.h"

Graph::Graph(int v, bool isWeighted, bool isDirected)
{
	vertices = v;
	weighted = isWeighted;
	directed = isDirected;

	adj = new Edge*[vertices];
	for (int i = 0; i < vertices; i++)
	{
		adj[i] = nullptr;
	}
}

Graph::~Graph()
{
	for (int i = 0; i < vertices; i++)
	{
		Edge* curr = adj[i];
		while (curr != nullptr)
		{
			Edge* temp = curr;
			curr = curr->next;
			delete temp;
		}
	}

	delete[] adj;
}

bool Graph::edgeExists(int v1, int v2)
{
	// check if v1 and v2 are out of bounds
	if (v1 < 0 || v1 >= vertices || v2 < 0 || v2 >= vertices)
		return false;

	Edge* currEdge = adj[v1];

	while (currEdge != nullptr)
	{
		if (currEdge->to == v2)
			return true;
		currEdge = currEdge->next;
	}

	return false;
}

void Graph::addEdge(int v1, int v2, double w)
{
	// check if v1 and v2 are out of bounds
	if (v1 < 0 || v1 >= vertices || v2 < 0 || v2 >= vertices)
	{
		cerr << "ERROR: Vertices are out of bounds" << endl;
		return;
	}

	if (edgeExists(v1, v2))
		return;

	if (!weighted)
		w = 1;

	// insert v1 --> v2
	Edge* newEdge = new Edge(v2, w);
	newEdge->next = adj[v1];
	adj[v1] = newEdge;

	// If undirected, insert v2 --> v1
	if (!directed)
	{
		Edge* newEdge2 = new Edge(v1, w);
		newEdge2->next = adj[v2];
		adj[v2] = newEdge2;
	}
}

void Graph::removeEdge(int v1, int v2)
{
	if (v1 < 0 || v1 >= vertices || v2 < 0 || v2 >= vertices)
		return;

	// Remove v1 --> v2
	Edge* currEdge = adj[v1];
	Edge* prevEdge = nullptr;

	while (currEdge != nullptr)
	{
		if (currEdge->to == v2)
		{
			if (prevEdge == nullptr)
			{
				// removing head
				adj[v1] = currEdge->next;
			}
			else
			{
				prevEdge->next = currEdge->next;
			}

			delete currEdge;
			break;
		}

		prevEdge = currEdge;
		currEdge = currEdge->next;
	}

	// If undirected, also remove v2 --> v1
	if (!directed)
	{
		currEdge = adj[v2];
		prevEdge = nullptr;

		while (currEdge != nullptr)
		{
			if (currEdge->to == v1)
			{
				if (prevEdge == nullptr)
				{
					adj[v2] = currEdge->next;
				}
				else
				{
					prevEdge->next = currEdge->next;
				}

				delete currEdge;
				break;
			}

			prevEdge = currEdge;
			currEdge = currEdge->next;
		}
	}
}

void Graph::displayAdjList()
{
	for (int i = 0; i < vertices; i++)
	{
		cout << i << ": ";
		Edge* currEdge = adj[i];

		while (currEdge != nullptr)
		{
			cout << "(" << currEdge->to << ", " << currEdge->weight << ")";
			if (currEdge->next != nullptr)
				cout << ", ";

			currEdge = currEdge->next;
		}

		cout << endl;
	}

	cout << endl;
}