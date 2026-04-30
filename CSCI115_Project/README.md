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
