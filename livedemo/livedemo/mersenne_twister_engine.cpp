#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>

// BOOST
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

int main()
{
    // C++ Standard Library: Mersenne Twister Engine
    std::mt19937 mt_engine;
    std::uniform_int_distribution<int> dist(1, 100);
    int std_random_number = dist(mt_engine);
    std::cout << "Random number generated using std::mt19937: " << std_random_number << std::endl;

    // BOOST: Mersenne Twister Engine
    boost::random::mt19937 boost_mt_engine;
    boost::random::uniform_int_distribution<int> boost_dist(1, 100);
    int boost_random_number = boost_dist(boost_mt_engine);
    std::cout << "Random number generated using boost::mt19937: " << boost_random_number << std::endl;

    return 0;
}
