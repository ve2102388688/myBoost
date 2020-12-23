#include <iostream>
#include <cassert>
#include <boost/ratio.hpp>

int main(int argc, char* argv[])
{
    {
        // ratio是类型名，只能用::访问
        typedef  boost::ratio<1, 2> half;

        assert(half::num == 1);     // 分子
        assert(half::den == 2);     // 分母
    }

}
