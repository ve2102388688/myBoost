#include <iostream>
#include <cmath>
#include <boost/rational.hpp>

int main(int argc, char* argv[])
{
    {
        // 分式
        boost::rational<int> a;         // 默认构造，值为0
        a.assign(7, 8);
        boost::rational<int> b(20);     // 分母为1
        boost::rational<int> c(22,7);
        std::cout << c.numerator() << "/" << c.denominator() << "=" << boost::rational_cast<double>(c) << std::endl;
    }

    {
        // 支持所有的算数运算
        boost::rational<int> a(1, 3);
        assert(a * 3 == 1);
    }

    {
        boost::rational<int> a(1, 3);
        std::cout << std::pow(boost::rational_cast<double>(a), 2)  << std::endl;
    }
}