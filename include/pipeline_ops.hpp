#pragma once

#include <vector>
#include "num_types.hpp"

namespace pipeline {
    float run_with_copies(const std::vector<float>& input, 
        float scale, 
        float bias, 
        size_t& bytes_saved);

    float run_without_copies(const std::vector<float>& input, 
        float scale, 
        float bias, 
        size_t& bytes_saved);

}