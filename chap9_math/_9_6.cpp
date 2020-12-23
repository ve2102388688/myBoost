#include <iostream>
#include <vector>
#include <boost/random.hpp>

int main(int argc, char* argv[])
{
    {
        boost::mt19937 rng(time(0));            // 随机数发生器，以时间为种子
        std::cout << boost::mt19937::min() << " <-> " << boost::mt19937::max() << std::endl;
        for(int i = 0; i < 10;  ++i){
            std::cout << rng() << ", ";
        }
        std::cout << std::endl;
        rng.discard(5);                         // 丢弃5个

        std::vector<int> vec(10);
        rng.generate(vec.begin(), vec.end());   // 调用generate填充标准容器

        // 支持复制、拷贝，用于复现测试
        boost::random::uniform_smallint<> u(0, 30);

    }
}
