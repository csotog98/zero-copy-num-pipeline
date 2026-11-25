#include "pipeline_ops.hpp"

#include <algorithm>
#include <vector>
#include "num_types.hpp"

using std::vector;
using std::max;
using std::int64_t;
using std::int32_t;
using std::size_t;



namespace pipeline {

    float min_val = 0.0f;
    float max_val = 100.0f;

    void ReLU(float& data){
        data = max(float(0), data);
    }

    float run_with_copies(const vector<float>& input, 
        float scale, 
        float bias, 
        size_t& bytes_saved) {

            bytes_saved = 0;
            vector<float> scaled(input.size());
            for (size_t i = 0; i < input.size(); ++i) {
                scaled[i] = input[i] * scale + bias;
            }

            bytes_saved += scaled.size() * sizeof(float);

            for (float& val : scaled) {
                ReLU(val);
            }

            vector<float> clamped(scaled.size());

            for (size_t i = 0; i<scaled.size(); ++i) {
                clamped[i] = std::clamp(scaled[i], min_val, max_val);
            }

            bytes_saved += clamped.size() * sizeof(float);

            float sum = 0.0f;
            for (float val : clamped) {
                sum += val;
            }

            return sum;
    }

    float run_without_copies(const vector<float>& input, 
        float scale, 
        float bias, 
        size_t& bytes_saved) {

            bytes_saved = 0;
            float sum = 0.0f;

            for (float val: input) {
                
                float scaled_val = val * scale + bias;
                ReLU(scaled_val);
                scaled_val = std::clamp(scaled_val, min_val, max_val);
                sum += scaled_val;
            }

            return sum;
        }

}