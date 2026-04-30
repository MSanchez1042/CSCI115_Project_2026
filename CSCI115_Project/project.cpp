#include "benchmark.h"
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(nullptr));

    runProjectBenchmarks();

    return 0;
}