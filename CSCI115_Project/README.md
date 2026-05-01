File structure is split between the header files and the files containing the computation/logic
Files:

benchmark.cpp/.h - This file contains the functions needed to time the functions and record the times by algorithm/data structure (adjacancy matrix or adjacancy list).

GraphAL.cpp/.h - contains the adjacancy list structure for the graph.

myGraph.cpp/.h  - contains the adjacancy matrix structure for the graph.

myPriorityQueue.cpp/.h - contains the priority queue structure needed for the dijkstra and bfs algorithms.

Queue.cpp/.h - contians the queue structure needed for the priority queue.

myMatrix.h - contains the matrix data structure and operation needed for the graph.

project.cpp - is the main file, it allows the runProjectsBenchmark() function to be ran and produce needed metrics.

graphs.py - this file constructs the graphs needed for the documentation portion of the project.

# Output

The program outputs performance results for BFS and Dijkstra’s algorithm. This includes:
- Mean runtime (in milliseconds)
- Standard deviation
- Graph representation (Adjacency List or Matrix)
- Graph type (Sparse or Dense)
- Number of vertices (n)

These results are then used in graphs.py to generate tables and graphs for the report.

# Graph Generation

The algorithms are tested on different types of graphs:

- Sparse connected undirected graphs:
  Each vertex has a limited number of edges, but the graph is still fully connected.

- Dense fully connected graphs:
  Most vertices are connected to each other, creating a large number of edges.

- Directed and undirected weighted graphs:
  These are used for testing Dijkstra’s algorithm.

This setup allows us to compare how each algorithm performs under different conditions.

How to compile:
g++ *.cpp -o project

How to run:
./project