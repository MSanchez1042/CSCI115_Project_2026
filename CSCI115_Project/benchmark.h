#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "myGraph.h"
#include "myMatrix.h"

struct TestCase {
    int n;
    double p;
    bool runFloyd;
};

struct BenchmarkResult {
    int n;
    double p;
    double floydTime;
    double dijkstraTime;
    double bfsTime;
};

double timeFloydWarshall(myGraphM& g);
double timeBFS(myGraphM& g);
double timeRepeatedDijkstra(myGraphM& g);
BenchmarkResult runBenchmark(int n, double p, bool runFloyd);
void printBenchmarkResult(const BenchmarkResult& result);
void runAllBenchmarks(const TestCase tests[], int count);
void printHeader();

#endif