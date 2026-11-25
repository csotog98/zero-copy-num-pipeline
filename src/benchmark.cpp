#include "benchmark.hpp"
#include "pipeline_ops.hpp"

#include <chrono>
#include <iostream>
#include "num_types.hpp"

using std::vector;
using Clock = std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::cout;
using std::endl;


namespace benchmark {
    void run_benchmark(const vector<float>& input, 
        float scale, 
        float bias,
        size_t kIterations
    ) 
    {
        
        if (kIterations == 0) {
            cout << "Number of iterations must be greater than 0." << endl;
            return;
        }

        float avg_time_with_copies = 0;
        float avg_time_without_copies = 0;

        size_t bytes_with_copies = 0;
        size_t bytes_without_copies = 0;

        for (size_t i = 0; i < kIterations; ++i) {
            float sum_with_copies = 0;
            float sum_without_copies = 0;

            Clock::time_point start = Clock::now();
            sum_with_copies = pipeline::run_with_copies(input, scale, bias, bytes_with_copies);
            Clock::time_point end_with_copies = Clock::now();
            sum_without_copies = pipeline::run_without_copies(input, scale, bias, bytes_without_copies);
            Clock::time_point end_without_copies = Clock::now();

            if (sum_with_copies == sum_without_copies){
                float time_with_copies = static_cast<float>(duration_cast<microseconds>(end_with_copies - start).count());
                avg_time_with_copies += time_with_copies;

                float time_without_copies = static_cast<float>(duration_cast<microseconds>(end_without_copies - end_with_copies).count());
                avg_time_without_copies += time_without_copies;
            }
            else{
                cout << "Benchmark failed!" << endl;
                cout << "Sum with copies: " << sum_with_copies << endl;
                cout << "Sum without copies: " << sum_without_copies << endl;
                return;
            }

        }

        avg_time_with_copies /= kIterations;
        avg_time_without_copies /= kIterations;

        cout << "Average time with copies: " << avg_time_with_copies << " microseconds" << endl;
        cout << "Average time without copies: " << avg_time_without_copies << " microseconds" << endl;

        cout << "Bytes in buffer with copies: " << bytes_with_copies << " bytes" << endl;
        cout << "Bytes in buffer without copies: " << bytes_without_copies << " bytes" << endl;
            
    }
}