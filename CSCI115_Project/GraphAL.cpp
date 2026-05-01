#include "GraphAL.h"

GraphAL::GraphAL(int v, bool isWeighted, bool isDirected)
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

GraphAL::~GraphAL()
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

bool GraphAL::edgeExists(int v1, int v2)
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

void GraphAL::addEdge(int v1, int v2, double w)
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

void GraphAL::removeEdge(int v1, int v2)
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

bool GraphAL::isConnected(int source)
{
	if (vertices == 0)
		return true; // technically true

	bool* visited = new bool[vertices];
	for (int i = 0; i < vertices; i++)
		visited[i] = false;

	Queue q;
	visited[source] = true;
	q.enqueue(source);

	while (!q.isEmpty())
	{
		int current = q.dequeue();

		Edge* currEdge = adj[current];
		while (currEdge != nullptr)
		{
			int neighor = currEdge->to;

			if (!visited[neighor])
			{
				visited[neighor] = true;
				q.enqueue(neighor);
			}

			currEdge = currEdge->next;

		}
	}

	for (int i = 0; i < vertices; i++)
	{
		if (visited[i] == false)
		{
			delete[] visited;
			return false;
		}
	}
	delete[] visited;
	return true;
}

void GraphAL::BFS(int source)
{
	if (source < 0 || source >= vertices)
	{
		cerr << "Invalid source" << endl;
		return;
	}

	// create visited array
	bool* visited = new bool[vertices];
	for (int i = 0; i < vertices; i++)
		visited[i] = false;

	// create queue
	Queue Q;

	// mark source and enqueue
	visited[source] = true;
	Q.enqueue(source);

	// BFS loop
	while (!Q.isEmpty())
	{
		int v = Q.dequeue();

		// print vertex (convert to A, B, C...)
		cout << v << " ";

		// traverse adjacency list
		Edge* curr = adj[v];
		while (curr != nullptr)
		{
			int u = curr->to;

			if (!visited[u])
			{
				visited[u] = true;
				Q.enqueue(u);
			}

			curr = curr->next;
		}
	}

	cout << endl;

	delete[] visited;
}

void GraphAL::displayAdjList()
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