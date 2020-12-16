#include <iostream>
#include <boost/config.hpp>


int main(int argc, char* argv[])
{
    std::cout << BOOST_STRINGIZE(__LINE__) << std::endl;        //  string

    // 静态类型常量 BOOST_STATIC_CONSTANT
    // define BOOST_STATIC_CONSTANT(type, assignment) static const type assignment
    BOOST_STATIC_CONSTANT(int, V1 = 10);
}