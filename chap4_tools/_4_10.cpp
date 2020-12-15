#include <iostream>
#include <string>
#include <bitset>
#include <boost/current_function.hpp>
#include <boost/utility.hpp>

void fun()
{
    std::cout << BOOST_CURRENT_FUNCTION << std::endl;
}

std::string str = BOOST_CURRENT_FUNCTION;       // top level 无效

int main(int argc, char *argv[])
{
    {
        std::cout << str << std::endl;
        std::cout << __FUNCTION__ << std::endl;     // 函数名和BOOST_CURRENT_FUNCTION功能一致
        std::cout << BOOST_CURRENT_FUNCTION << std::endl;
        fun();
    }

    {
        // 二进制常量
        std::cout << std::hex << BOOST_BINARY(0110) << std::endl;
        std::cout << BOOST_BINARY(0110 1101 1101 1101 0110 1101 1101 1101 0110 1101 1101 1101) << std::endl;
        std::cout << std::bitset<5>(BOOST_BINARY(0110)) << std::endl;
        std::cout << std::dec <<BOOST_BINARY_UL(101 1001) << std::endl;    // hex 59,dec 89
    }
}
