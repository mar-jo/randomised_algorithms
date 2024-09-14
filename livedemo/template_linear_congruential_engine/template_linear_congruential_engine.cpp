#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>

// BOOST
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int_distribution.hpp>

int main()
{
    // Seed with a real random value, if available
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();

    // C++ Standard Library: Linear Congruential Engine
    std::linear_congruential_engine<std::uint_fast32_t, 48271, 0, 2147483647> std_engine(seed1);
    // Generate random numbers
    std::uniform_int_distribution<int> dist(1, 100);
    int std_random_number = dist(std_engine);
    std::cout << "Random number generated using std::linear_congruential_engine: " << std_random_number << std::endl;

    unsigned seed2 = std::chrono::system_clock::now().time_since_epoch().count();

    // BOOST: Linear Congruential Engine
    boost::random::linear_congruential<std::uint_fast32_t, 48271, 0, 2147483647> boost_engine(seed2);
    boost::random::uniform_int_distribution<int> boost_dist(1, 100);
    int boost_random_number = boost_dist(boost_engine);
    std::cout << "Random number generated using boost::linear_congruential: " << boost_random_number << std::endl;



    return 0;
}