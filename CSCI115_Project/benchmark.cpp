#include "benchmark.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>
#include <cstdlib>

double randomWeight(int minW, int maxW) {
    return minW + rand() % (maxW - minW + 1);
}

GraphAL* createSparseConnectedAL(int n, int minEdges, int maxEdges, int minW, int maxW) {
    GraphAL* g = new GraphAL(n, true, false);

    // Step 1: chain guarantees connectedness
    for (int i = 0; i < n - 1; i++) {
        g->addEdge(i, i + 1, randomWeight(minW, maxW));
    }

    // Step 2: add extra sparse random edges
    int attempts = 0;
    int maxAttempts = n * n * 5;

    while (attempts < maxAttempts) {
        int u = rand() % n;
        int v = rand() % n;

        if (u != v) {
            if (!g->edgeExists(u, v)) {
                g->addEdge(u, v, randomWeight(minW, maxW));
            }
        }

        attempts++;
    }

    return g;
}
double timeGraphALBFS(GraphAL& g) {
    std::streambuf* oldCout = std::cout.rdbuf();
    std::ofstream nullOut("/dev/null");
    std::cout.rdbuf(nullOut.rdbuf());

    auto start = std::chrono::high_resolution_clock::now();
    g.BFS(0);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout.rdbuf(oldCout);

    return std::chrono::duration<double, std::milli>(end - start).count();
}
double computeMean(double* times, int trials) {
    double sum = 0.0;

    for (int i = 0; i < trials; i++) {
        sum += times[i];
    }

    return sum / trials;
}

double computeStdDev(double* times, int trials, double mean) {
    double sum = 0.0;

    for (int i = 0; i < trials; i++) {
        double diff = times[i] - mean;
        sum += diff * diff;
    }

    return sqrt(sum / trials);
}
BenchmarkStats benchmarkSparseListBFS(int n, int trials) {
    double* times = new double[trials];

    for (int i = 0; i < trials; i++) {
        GraphAL* g = createSparseConnectedAL(n, 1, 4, 1, 20);
        times[i] = timeGraphALBFS(*g);
        delete g;
    }

    double mean = computeMean(times, trials);
    double stdDev = computeStdDev(times, trials, mean);

    delete[] times;

    BenchmarkStats result;
    result.graphType = "Sparse Connected Undirected";
    result.representation = "Adjacency List";
    result.algorithm = "BFS";
    result.n = n;
    result.trials = trials;
    result.meanMs = mean;
    result.stdDevMs = stdDev;

    return result;
}
double timeMatrixBFS(myGraphM& g) {
    auto start = std::chrono::high_resolution_clock::now();
    g.BFS(0);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

BenchmarkStats benchmarkDenseMatrixBFS(int n, int trials) {
    double* times = new double[trials];

    for (int i = 0; i < trials; i++) {
        myGraphM g;
        g.generateFullyConnectedUndirected(n, 1, 20);
        times[i] = timeMatrixBFS(g);
    }

    double mean = computeMean(times, trials);
    double stdDev = computeStdDev(times, trials, mean);

    delete[] times;

    BenchmarkStats result;
    result.graphType = "Dense Fully Connected Undirected";
    result.representation = "Adjacency Matrix";
    result.algorithm = "BFS";
    result.n = n;
    result.trials = trials;
    result.meanMs = mean;
    result.stdDevMs = stdDev;

    return result;
}
double timeMatrixDijkstra(myGraphM& g) {
    auto start = std::chrono::high_resolution_clock::now();

    double* d = nullptr;
    int* pi = nullptr;

    g.dijkstraAlgo(0, d, pi);

    delete[] d;
    delete[] pi;

    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

BenchmarkStats benchmarkDenseMatrixDijkstra(int n, int trials) {
    double* times = new double[trials];

    for (int i = 0; i < trials; i++) {
        myGraphM g;
        g.generateFullyConnectedDirected(n, 1, 20);
        times[i] = timeMatrixDijkstra(g);
    }

    double mean = computeMean(times, trials);
    double stdDev = computeStdDev(times, trials, mean);

    delete[] times;

    BenchmarkStats result;
    result.graphType = "Dense Fully Connected Directed";
    result.representation = "Adjacency Matrix";
    result.algorithm = "Dijkstra";
    result.n = n;
    result.trials = trials;
    result.meanMs = mean;
    result.stdDevMs = stdDev;

    return result;
}
void writeCSVHeader(const char* filename) {
    std::ofstream fout(filename);

    fout << "graph_type,representation,algorithm,n,trials,mean_ms,stddev_ms\n";

    fout.close();
}

void appendCSV(const char* filename, const BenchmarkStats& result) {
    std::ofstream fout(filename, std::ios::app);

    fout << result.graphType << ","
         << result.representation << ","
         << result.algorithm << ","
         << result.n << ","
         << result.trials << ","
         << result.meanMs << ","
         << result.stdDevMs << "\n";

    fout.close();
}
void runProjectBenchmarks() {
    const char* filename = "project_results.csv";

    writeCSVHeader(filename);

    int sizes[] = {100, 500, 1000};
    int sizeCount = 3;
    int trials = 30;

    for (int i = 0; i < sizeCount; i++) {
        int n = sizes[i];

        BenchmarkStats sparseBFS = benchmarkSparseListBFS(n, trials);
        appendCSV(filename, sparseBFS);

        BenchmarkStats denseBFS = benchmarkDenseMatrixBFS(n, trials);
        appendCSV(filename, denseBFS);

        BenchmarkStats denseDijkstra = benchmarkDenseMatrixDijkstra(n, trials);
        appendCSV(filename, denseDijkstra);

        std::cout << "Finished n = " << n << std::endl;
    }

    std::cout << "CSV written to " << filename << std::endl;
}