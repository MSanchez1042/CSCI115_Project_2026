#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "myGraph.h"
#include "GraphAL.h"

struct BenchmarkStats {
    const char* graphType;
    const char* representation;
    const char* algorithm;
    int n;
    int trials;
    double meanMs;
    double stdDevMs;
};

void runProjectBenchmarks();
void writeCSVHeader(const char* filename);
void appendCSV(const char* filename, const BenchmarkStats& result);

BenchmarkStats benchmarkDenseMatrixBFS(int n, int trials);
BenchmarkStats benchmarkDenseMatrixDijkstra(int n, int trials);
BenchmarkStats benchmarkSparseListBFS(int n, int trials);

#endif