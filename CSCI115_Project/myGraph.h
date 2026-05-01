#ifndef MYGRAPH_H
#define MYGRAPH_H

#include"myMatrix.h"
#include"myPriorityQueue.h"

enum class color{
    white,
    gray, 
    black
};

class myGraphM {
    public:
        myGraphM();
        myGraphM(int n);
        ~myGraphM();
        int getNumberOfVerticies() {return size;}
        int getDegree(int u);
        int getIndex(int u, int v);
        int getSize();
        double getEdgeWeight(int u, int v);
        bool existEdge(int u, int v);
        void setDirectedEdge(int u, int v, int w);
        void setDirectedEdge(int u, int v);
        void setUnDirectedEdgeW(int u, int v, int w);
        void setUndirectedEdge(int u, int v);
        void removeDirectedEdge(int u, int v);
        void removeUndirectedEdge(int u, int v);
        bool hasSelfLoops();
        bool isUndirected();
        void display();
        void printPath(int* pi, int v);
        void displayShortestPath(int source, int destinaiton, int* pi);
        void displayDirectedEdge();
        void displayUndirectedEdge();
        void setCurrentVertex(int u);
        bool getNextAdjacent(int u, int& vout);
        void BFS(int s);
        void DFS();
        void printAllPairs(myMatrix* pi, int i, int j);
        void transitiveClousure(myMatrix* &tCout);
        void MSTKruskal();
        void MSTprim();
        int minKey(int* key, bool* mstSet);
        void displayMST(int* parent);
        bool existAdjacent(int v);
        //Dijkstra's algorithm
        void dijkstraAlgo(int s, double* &d, int* &pi);
        void dijkstraAll(int s);
        void dijkstraOneDestination(int s, int destination);
        void dijkstraManyDestinations(int s, int* destinations, int count);
        void displayShortestPathTable(double* d, int* pi);
        //floyd warshall
        void floydWarshall(myMatrix* &dout, myMatrix* &piout);
        //random graph generator
        void generateRandomGraph(int n, double p, int minW, int maxW);
        bool isConnected(int s, double* &d, int* &pi);
        void generateFullyConnectedDirected(int n, int minW, int maxW);
        //generates graphs that are guaranteed to be connected
        void generateFullyConnectedUndirected(int n, int minW, int maxW);
        void generateSparseConnectedUndirected(int n, int minEdges, int maxEdges, int minW, int maxW);
        void resetGraph(int n);
        int randomWeight(int minW, int maxW);
    private:
        int size;
        double* m;
        int* current;
};

#endif