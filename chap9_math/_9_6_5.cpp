#include <iostream>
#include <vector>
// #include "_9_6_6.hpp"
#include <boost/random.hpp>
#include "/home/topeet/boost_1_74_0/libs/random/src/random_device.cpp"

int main(int argc, char* argv[])
{
    {
        boost::random_device rng;
        for(int i = 0; i < 10;  ++i)
            std::cout << rng() << ", ";
        std::cout << std::endl;
    }

    {
        boost::random_device rng;
        boost::uniform_real<> ur(1.0, 2.0);
        for (int i = 0; i < 10; ++i)
            std::cout << ur(rng) << ", ";
        std::cout << std::endl;
    }

}
