#include "benchmark.h"
#include <iostream>
#include <chrono>
#include <iomanip>

double timeFloydWarshall(myGraphM& g) {
    myMatrix* d = nullptr;
    myMatrix* pi = nullptr;

    auto start = std::chrono::high_resolution_clock::now();
    g.floydWarshall(d, pi);
    auto end = std::chrono::high_resolution_clock::now();

    delete d;
    delete pi;

    return std::chrono::duration<double, std::milli>(end - start).count();
}

double timeBFS(myGraphM& g) {
    myMatrix* d = nullptr;
    myMatrix* pi = nullptr;

    auto start = std::chrono::high_resolution_clock::now();
    g.BFS(0);
    auto end = std::chrono::high_resolution_clock::now();

    delete d;
    delete pi;

    return std::chrono::duration<double, std::milli>(end - start).count();
}

double timeRepeatedDijkstra(myGraphM& g) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int s = 0; s < g.getSize(); s++) {
        double* d = nullptr;
        int* pi = nullptr;
        g.dijkstraAlgo(s, d, pi);
        delete[] d;
        delete[] pi;
    }

    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

BenchmarkResult runBenchmark(int n, double p, bool runFloyd) {
    myGraphM g;
    g.generateRandomGraph(n, p, 1, 20);

    BenchmarkResult result;
    result.n = n;
    result.p = p;
    result.floydTime = -1;
    result.dijkstraTime = -1;

    if (runFloyd) {
        result.floydTime = timeFloydWarshall(g);
    }

    result.dijkstraTime = timeRepeatedDijkstra(g);
    return result;
}

BenchmarkResult runBenchmarkBFSvD(int n, double p, bool runBFS) {
    myGraphM g;
    g.generateRandomGraph(n, p, 1, 20);

    BenchmarkResult result;
    result.n = n;
    result.p = p;
    result.bfsTime = -1;
    result.dijkstraTime = -1;

    if (runBFS) {
        result.bfsTime = timeBFS(g);
    }

    result.dijkstraTime = timeRepeatedDijkstra(g);
    return result;
}

void printBenchmarkResult(const BenchmarkResult& result) {
    std::cout << std::left
              << std::setw(10) << result.n
              << std::setw(10) << result.p;

    if (result.floydTime >= 0) {
        std::cout << std::setw(20) << result.floydTime;
    } else {
        std::cout << std::setw(20) << "skipped";
    }

    std::cout << std::setw(20) << result.dijkstraTime
              << std::endl;
}

void runAllBenchmarks(const TestCase tests[], int count) {
    printHeader();

    for (int i = 0; i < count; i++) {
        BenchmarkResult result =
            runBenchmark(tests[i].n, tests[i].p, tests[i].runFloyd);

        printBenchmarkResult(result);
    }
}
void printHeader() {
    std::cout << std::left
            << std::setw(10) << "n"
            << std::setw(10) << "p"
            << std::setw(20) << "Floyd(ms)"
            << std::setw(20) << "Dijkstra(ms)"
            << std::endl;

    std::cout << std::string(60, '-') << std::endl;
}