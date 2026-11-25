#pragma once

#include <vector>
#include "num_types.hpp"



namespace benchmark {
    void run_benchmark(const std::vector<float>& input, 
        float scale, 
        float bias,
        size_t kIterations
    );
}