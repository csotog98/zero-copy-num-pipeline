#include "benchmark.hpp"

#include <random>
// #include <floatx.hpp>
#include <vector>
// #include <cstddef>
#include "num_types.hpp"


size_t kNumElements = 5000000;
size_t kIterations = 1000;

int main() {
    std::vector<float> new_input(kNumElements);

    std::mt19937 rng(-1);
    std::uniform_real_distribution<float> dist(-100.0f, 100.0f);

    for (float& val : new_input) {
        val = dist(rng);
    }


    benchmark::run_benchmark(new_input, 10, 5, kIterations);

    return 0;
}