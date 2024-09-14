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
void measure_performance(const std::string& name) 
{
    RNG rng;
    std::uniform_int_distribution<int> dist(0, 100);

    std::vector<int> samples(NUM_SAMPLES);

    // init
    auto init_start = std::chrono::high_resolution_clock::now();
    rng.seed(42);
    auto init_end = std::chrono::high_resolution_clock::now();
    auto init_duration = std::chrono::duration_cast<std::chrono::microseconds>(init_end - init_start).count();
    std::cout << "TIME TAKEN TO INITIALIZE " << name << ": " << init_duration << " microseconds" << std::endl;

    // start
    auto start_time = std::chrono::high_resolution_clock::now();

    // generate numbers
    for (int i = 0; i < NUM_SAMPLES; ++i) {
        samples[i] = dist(rng);
    }

    // end 
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "TIME TAKEN BY            " << name << ": " << duration << " milliseconds\n\n";
}

int main() 
{
    // std::mt19937 VS boost::random::mt19937
    measure_performance<std::mt19937>("std::mt19937");
    measure_performance<boost::random::mt19937>("boost::random::mt19937");

    // std::minstd_rand VS boost::random::minstd_rand
    measure_performance<std::minstd_rand>("std::minstd_rand");
    measure_performance<boost::random::minstd_rand>("boost::random::minstd_rand");

    // std::ranlux24_base VS boost::random::ranlux24_base
    measure_performance<std::ranlux24_base>("std::ranlux24_base");
    measure_performance<boost::random::ranlux24_base>("boost::random::ranlux24_base");

    return 0;
}