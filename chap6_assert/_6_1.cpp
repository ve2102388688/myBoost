#define BOOST_DISABLE_ASSERTS
#include <iostream>
#include <boost/assert.hpp>
#include <cassert>

double fun(int x)
{
    // 使用宏失效
    BOOST_ASSERT(x != 0 && "divided by zero");
    std::cout << "boost_assert: " << std::endl;

    // 有效
    assert(x != 0 && "divided by zero");
    std::cout << "asssert: " << std::endl;

    return 1.0 / x;
}

int main(int argc, char* argv[])
{
    {
        BOOST_ASSERT(16 == 0x10);
        fun(0);
    }
}