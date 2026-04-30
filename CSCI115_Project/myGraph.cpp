#include"myGraph.h"
#include"myQueue.h"
#include<stdexcept>
#include<iomanip>

myGraphM::myGraphM() {
    size = 0;
    m = nullptr;
    current = nullptr;
}
myGraphM::myGraphM(int n) {
    size = n;
    m = new double[size * size];
    for (int i = 0; i < size * size; i++) {
       m[i] = 0; 
    }
    current = new int[size];
    for (int i = 0; i < size; i++) {
       current[i] = 0; 
    }
}
myGraphM::~myGraphM() {
    delete[] m;
    delete[] current;
}
int myGraphM::getDegree(int u) {
    int degree = 0;
    for (int i = 0; i < size; i++) {
        if (existEdge(u, i)) {
            degree++;
        }
    }
    return degree;
}
int myGraphM::getIndex(int u, int v) {
    return u * size + v;
}
int myGraphM::getSize() {
    return size;
}
bool myGraphM::existEdge(int u, int v) {
    return getEdgeWeight(u, v) != 0;
}
void myGraphM::setDirectedEdge(int u, int v, int w) {
    m[getIndex(u,v)] = w;
}
void myGraphM::setDirectedEdge(int u, int v) {
    m[getIndex(u, v)] = 1;
}
void myGraphM::setUnDirectedEdgeW(int u, int v, int w) {
    m[getIndex(u,v)] = w;
    m[getIndex(v,u)] = w;
}
void myGraphM::setUndirectedEdge(int u, int v) {
    m[getIndex(u,v)] = 1;
    m[getIndex(v,u)] = 1;
}
void myGraphM::removeDirectedEdge(int u, int v) {
    m[getIndex(u, v)] = 0;
}
void myGraphM::removeUndirectedEdge(int u, int v) {
    m[getIndex(u, v)] = 0;
    m[getIndex(v, u)] = 0;
}
bool myGraphM::hasSelfLoops() {
    int u = 0;
    while (u < size) {
        if (m[getIndex(u, u)] != 0) {
            return true;
        }
        u++;
    }
    return false;
}
bool myGraphM::isUndirected() {
    for (int u = 0; u < size; u++) {
        for (int v = u; v < size; v++) {
            if (m[getIndex(u,v)] != m[getIndex(v,u)]) {
                return false;
            }
        }
    }
    return !hasSelfLoops();
}
void myGraphM::display() {
    int k = 0;
    std::cout << std::setw(4) << " ";
    for (int v = 0; v < size; v++) {
        std::cout << std::setw(4) << v;
    }
    std::cout << std::endl;
    for (int u = 0; u < size; u++) {
        std::cout << std::setw(4) << u;
        for (int v = 0; v < size; v++) {
            std::cout << std::setw(4) << m[k];
            k++;
        }
        std::cout << std::endl;
    }
}
void myGraphM::printPath(int* pi, int v) {
    if (v == -1) {
       return; 
    }
    
    if (pi[v] != -1) {
       printPath(pi, pi[v]);
       std::cout << "->"; 
    }
    std::cout << v;
}
void myGraphM::displayShortestPath(int source, int destinaiton, int* pi) {
    if(source == destinaiton) {
        std::cout << source << std::endl;
        return;
    }
    
    if (pi[destinaiton] == -1) {
       std::cout << "No paths exist from " << source << " to " << destinaiton << std::endl;  
        return;
    }
    
    std::cout << "path from " << source << " to " << destinaiton << ": ";
    printPath(pi, destinaiton);
    std::cout << "\n";
}
void myGraphM::displayDirectedEdge() {
    std::cout << "List of Edges: " << std::endl;
    for (int u = 0; u < size; u++) {
        for (int v = 0; v < size; v++) {
            if(existEdge(u, v)) {
                std::cout << "(" << u << ", " << v << ") w:" << getEdgeWeight(u, v) << std::endl; 
            }
        }
    }
}
double myGraphM::getEdgeWeight(int u, int v) {
    if (u < 0 || u >= size || v < 0 || v >= size) {
        throw std::out_of_range("Index is out of range");
    }
    return m[getIndex(u, v)];
}
void myGraphM::displayUndirectedEdge() {
    std::cout << "List of Edges :" << std::endl;
    for (int u = 0; u < size; u++) {
        for (int v = u + 1; v < size; v++) {
            if(existEdge(u, v)) {
                std::cout << "(" << u << ", " << v << ") w:" << getEdgeWeight(u, v) << std::endl; 
            }            
        }
    }
}
void myGraphM::setCurrentVertex(int u) {
    current[u] = -1;
}
bool myGraphM::getNextAdjacent(int u, int& vout) {
    int v = current[u] + 1;
    vout = -1;
    bool found = false;
    while (!found && v < size) {
       if (existEdge(u, v)) {
            found = true;
            vout = v;
        }
        v++;
    }
    current[u] = vout;
    return found;
}
void myGraphM::BFS(int s) {
    color* status = new color[size];
    int* d = new int[size];
    int* pi = new int[size];
    myQueue q;
    std::cout << "=== BFS Start ===" << std::endl;
    //initialize the variables
    for (int u = 0; u < size; u++) {
        status[u] = color::white;
        d[u] = -1;
        pi[u] = -1;
    }
    //start implementation of the status checking
    status[s] = color::gray;
    d[s] = 0;
    pi[s] = -1;
    std::cout << "Start at vertex: " << s << std::endl;
    q.enqueue(s);
    while (!q.isEmpty()) {
        int u = q.dequeue();
        std::cout << "\nProcessing vertex: " << std::endl;
        for (int v = 0; v < size; v++) {
            std::cout << "checking edge (" << u << "->" << v << ")";
            if (existEdge(u, v)) {
                if (status[v] == color::white) {
                    status[v] = color::gray;
                    d[v] = d[u] + 1;
                    pi[v] = u;
                    q.enqueue(v);
                }
            }
            std::cout << std::endl;
            if (existEdge(u, v) && status[v] == color::white) {
                std::cout << " Vertex " << v << " is WHITE -> DISCOVERED" << std::endl;
                
                status[v] = color::gray;
                d[v] = d[u] + 1;
                pi[v] = u;
                
                std::cout << " Distance[" << v << "] = " << d[v] << std::endl;
                std::cout << " Parent[" << v << "] = " << d[v] << std::endl;
                
                q.enqueue(v);

                std::cout << " Enqueued " << v << std::endl;
            }
        }
        status[u] = color::black;
        std::cout << "Finished vertex " << u << "(BLACK)" << std::endl;       
    }
    std::cout << "\n=== BFS Complete ===" << std::endl;
    delete[] status;
    delete[] d;
    delete[] pi;
}
/////////////////////LAB 11 ////////////////////////////////////////////
void myGraphM::dijkstraAlgo(int s, double* &d, int* &pi) {
    //initializing variables
    d = new double[size];
    pi = new int[size];
    bool* done = new bool[size];
    myPriorityQueue* pq = new myPriorityQueue(size);

    for (int i = 0; i < size; i++) {
        d[i] = __DBL_MAX__;
        pi[i] = -1;
        done[i] = false; 
    }
    d[s] = 0;
    for (int i = 0; i < size; i++) {
        pq->push(i, d[i]); 
    }
    
    while (!pq->isEmpty()) {
        myData out = pq->pop();
        int u = out.index;
        
        
        if(!done[u]) {
            done[u] = true;
            setCurrentVertex(u);
        
            int v = 0;
            while (getNextAdjacent(u,v)) {
                //relaxation
                double w = getEdgeWeight(u,v);
                if (!done[v] && d[u] != __DBL_MAX__ && d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    pi[v] = u;
                    pq->decreaseKey(v, d[v]);
                }
            }       
        }
    }
    delete pq;
    delete[] done;
}
bool myGraphM::existAdjacent(int v) {
    return m[getIndex(v ,current[v])] != 0;
}
void myGraphM::displayShortestPathTable(double* d, int* pi) {
    for (int i = 0; i < size; i++) {
        std::cout << "Vertex: " << i << " : d = ";
        if (d[i] == __DBL_MAX__) {
            std::cout << "INF";
        } else {
            std::cout << d[i];
        }
        std::cout << " : pi = " << pi[i] << std::endl;
    }
    std::cout << "\n";   
}
void myGraphM::dijkstraAll(int s) {
    double* d = nullptr;
    int* pi = nullptr;

    dijkstraAlgo(s, d, pi);
    std::cout << "Dijkstra from Source" << s << std::endl;
    displayShortestPathTable(d, pi);
    
    delete[] d;
    delete[] pi;
}
void myGraphM::dijkstraOneDestination(int s, int destination) {
    double* d = nullptr;
    int* pi = nullptr;

    dijkstraAlgo(s, d, pi);
    std::cout << "Shortest path from " << s << " to " << destination << std:: endl;

    if (d[destination] == __DBL_MAX__) {
        std::cout << "No path exists. \n";
    } else {
        std::cout << "Distance = " << d[destination] << std::endl;
        displayShortestPath(s, destination, pi);
    }
   delete[] d;
   delete[] pi;
}
void myGraphM::dijkstraManyDestinations(int s, int* destinations, int count) {
   double* d = nullptr;
   int* pi = nullptr;
   
   dijkstraAlgo(s, d, pi);
   std::cout << "Shartest paths from source " << s << std::endl;
   for (int i = 0; i < count; i++) {
        int dest = destinations[i];
        std::cout << "\nDestination: " << dest << std::endl;
        if (d[dest] == __DBL_MAX__) {
            std::cout << "No path exists." << std::endl;
        } else {
            std::cout << d[dest] << std::endl;
            displayShortestPath(s, dest, pi);
        }
   }
   delete[] d;
   delete[] pi; 
}

// void myGraphM::DFS() {

// }
// void myGraphM::printAllPairs(myMatrix* pi, int i, int j) {

// }

//RANDOM GRAPH GENERATOR
void myGraphM::generateRandomGraph(int n, double p, int minW, int maxW){
    delete[] m;
    delete[] current;

    size = n;
    m = new double[size * size];
    current = new int[size];

    for (int i = 0; i < size * size; i++) {
        m[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        current[i] = 0;
    }

    for (int u = 0; u < size; u++) {
        for (int v = u + 1; v < size; v++) {
            double r = (double) rand() / RAND_MAX;

            if (r < p) {
                int w = minW + rand() % (maxW - minW + 1);
                setUnDirectedEdgeW(u, v, w);
            }
        }
    }
}


void myGraphM::floydWarshall(myMatrix* &dout, myMatrix* &piout) {
    myMatrix** d = new myMatrix* [size + 1];
    myMatrix** pi = new myMatrix* [size + 1];

    d[0] = new myMatrix(size, size);
    pi[0] = new myMatrix(size, size);
    //initialization
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double w = getEdgeWeight(i,j);
            if (i == j) {
                d[0]->set(i,j,0);
            } else {
                if (w != 0) {
                    d[0]->set(i,j,w);
                } else {
                    d[0]->set(i,j,__DBL_MAX__);
                }
            }
            if ((i == j) || (w == 0)) {
                pi[0]->set(i, j, -1);
            } else {
                pi[0]->set(i, j, i);
            }
        }
    }
    //dynamic programming
    for (int k = 1; k <= size; k++) {
        d[k] = new myMatrix(size, size);
        pi[k] = new myMatrix(size, size);
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                double direct = d[k - 1]->get(i,j);
                double left = d[k - 1]->get(i, k - 1);
                double right = d[k - 1]->get(k - 1, j);

                double throughk;

                if (left == __DBL_MAX__ || right == __DBL_MAX__) {
                    throughk = __DBL_MAX__;
                } else {
                    throughk = left + right;
                }
                
                if (direct <= throughk) {
                    d[k]->set(i, j, direct);
                    pi[k]->set(i, j, pi[k - 1]->get(i,j));
                } else {
                    d[k]->set(i, j, throughk);
                    pi[k]->set(i, j, pi[k-1]->get(k - 1, j));
                }
            }
        }
    }
    
    dout = d[size];
    piout = pi[size];
    for (int i = 0; i < size; i++) {
        delete d[i];
        delete pi[i];
    }
    delete [] d;
    delete [] pi;
}

//////////FOR PROJECT (IS CONNECTED FUNCITON)///////////////////
bool myGraphM::isConnected(int s, double* &d, int* &pi) {
    //initializing variables
    color* status = new color[size];
    myQueue q;
    for (int i = 0; i < size; i++) {
        status[i] = color::white;
    }
    
    status[0] = color::gray;
    q.enqueue(0);

    int visitedCount = 1;
    while (!q.isEmpty()) {
        int u = q.dequeue();
        for (int v = 0; v < size; v++) {
            if (existEdge(u,v) && status[v] == color::white) {
                status[v] = color::gray;
                visitedCount++;
                q.enqueue(v);
            }
        }
        status[u] == color::black; 
    }
    delete[] status;
    return visitedCount == size;
}
void myGraphM::generateFullyConnectedDirected(int n, int minW, int maxW) {
    resetGraph(n);

    for (int u = 0; u < size; u++) {
        for (int v = 0; v < size; v++) {
           if (u != v) {
            int w = randomWeight(minW, maxW);
            setDirectedEdge(u,v,w);
           }
        }
    }
}
void myGraphM::generateFullyConnectedUndirected(int n, int minW, int maxW) {
    resetGraph(n);

    for (int u = 0; u < size; u++) {
        for (int v = u + 1; v < size; v++) {
            int w = randomWeight(minW, maxW);
            setUnDirectedEdgeW(u,v,w);
        }
    }
}
void myGraphM::generateSparseConnectedUndirected(int n, int minEdges, int maxEdges, int minW, int maxW) {
    resetGraph(n);

    if (minEdges < 1) {
        minEdges = 1;
    }
    
    if (maxEdges >= size) {
        maxEdges = size - 1;
    }
    
    if (minEdges > maxEdges) {
        minEdges = maxEdges;
    }

    //create chain to guarantee correctness
    for (int i = 0; i < size - 1; i++) {
        int w = randomWeight(minW, maxW);
        setUnDirectedEdgeW(i, i + 1, w);
    }
    //add extra edges until every vertex has at least one edge
    int attempts = 0;
    int maxAttempts = size * size * 10;

    while (attempts < maxAttempts) {
        int u = rand() % size;
        int v = rand() % size;

        if (u != v) {
            if (!existEdge(u, v)) {
                if (getDegree(u) < maxEdges && getDegree(v) < maxEdges) {
                    int w = randomWeight(minW, maxW);
                    setUnDirectedEdgeW(u, v, w);
                }
            }
        }

        attempts++;
    }
    //randomly add more edges without exceeding maxEdges
    for (int u = 0; u < size; u++) {
        int v = 0;
        while (getDegree(u) < maxEdges) {
            if (u != v) {
                if (!existEdge(u,v)) {
                    if (getDegree(v) < maxEdges) {
                        int w = randomWeight(minW, maxW);
                        setUnDirectedEdgeW(u, v, w);
                    }
                }
            }
           v++; 
        }
    }
}
void myGraphM::resetGraph(int n) {
    delete[] m;
    delete[] current;

    size = n;
    m = new double[size * size];
    current = new int[size];

    for (int i = 0; i < size; i++) {
        m[i] = 0;
    }
    
    for (int i = 0; i < size; i++) {
        current[i] = -1;
    }
}
int myGraphM::randomWeight(int minW, int maxW) {
    return minW + rand() % (maxW - minW -1);
}
// void myGraphM::transitiveClousure(myMatrix* &tCout) {

// }
// void myGraphM::MSTKruskal() {

// }
// void myGraphM::MSTprim() {

// }
// int myGraphM::minKey(int* key, bool* mstSet) {

// }
// void myGraphM::displayMST(int* parent) {

// }
