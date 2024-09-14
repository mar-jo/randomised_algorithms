#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>

// BOOST
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/ranlux.hpp>

const int NUM_SAMPLES = 1000000;

template <typename RNG>
void measure_performance(const std::string& name) {
    RNG rng;
    std::uniform_int_distribution<int> dist(0, 100);

    std::vector<int> samples(NUM_SAMPLES);

    // Measure initialization time
    auto init_start = std::chrono::high_resolution_clock::now();
    rng.seed(42);  // Seed the generator
    auto init_end = std::chrono::high_resolution_clock::now();
    auto init_duration = std::chrono::duration_cast<std::chrono::microseconds>(init_end - init_start).count();
    std::cout << "Initialization time for " << name << ": " << init_duration << " microseconds" << std::endl;

    // Start time measurement for random number generation
    auto start_time = std::chrono::high_resolution_clock::now();

    // Generate random numbers
    for (int i = 0; i < NUM_SAMPLES; ++i) {
        samples[i] = dist(rng);
    }

    // End time measurement
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    // Output results
    std::cout << "Time taken by " << name << ": " << duration << " ms" << std::endl;

    // Calculate mean and standard deviation for randomness analysis
    double mean = std::accumulate(samples.begin(), samples.end(), 0.0) / NUM_SAMPLES;
    double sq_sum = std::inner_product(samples.begin(), samples.end(), samples.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / NUM_SAMPLES - mean * mean);
    std::cout << "Mean for " << name << ": " << mean << ", Standard Deviation: " << stdev << std::endl;

    // Measure memory usage
    std::cout << "Memory usage of " << name << ": " << sizeof(RNG) << " bytes" << std::endl;
}

int main() 
{
    // Measure performance for std::mt19937
    measure_performance<std::mt19937>("std::mt19937");

    // Measure performance for boost::mt19937
    measure_performance<boost::random::mt19937>("boost::random::mt19937");

    // Measure performance for std::minstd_rand
    measure_performance<std::minstd_rand>("std::minstd_rand");

    // Measure performance for boost::minstd_rand
    measure_performance<boost::random::minstd_rand>("boost::random::minstd_rand");

    // Measure performance for std::ranlux24_base
    measure_performance<std::ranlux24_base>("std::ranlux24_base");

    // Measure performance for boost::ranlux24_base
    measure_performance<boost::random::ranlux24_base>("boost::random::ranlux24_base");

    return 0;
}