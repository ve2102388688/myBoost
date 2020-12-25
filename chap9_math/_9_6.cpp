#include <iostream>
#include <vector>
#include <boost/random.hpp>

// 随机数块
template <typename Rng>
void rand_bytes(unsigned char *buf, size_t buf_len)
{
    typedef boost::variate_generator<Rng, boost::uniform_smallint<>> var_gen_t;
    // 静态变量，防止多次初始化
    static var_gen_t gen(Rng(time(0)), boost::uniform_smallint<>(1, 255));          // 这里用的是uniform_smallint

    for (size_t i = 0; i < buf_len; ++i)
        buf[i] = gen();
}

int main(int argc, char* argv[])
{
    {
        // 随机数发生器
        boost::mt19937 rng(time(0));            // 随机数发生器，以时间为种子
        std::cout << boost::mt19937::min() << " <-> " << boost::mt19937::max() << std::endl;
        for(int i = 0; i < 10;  ++i){
            std::cout << rng() << ", ";
        }
        std::cout << std::endl;
        rng.discard(5);                         // 丢弃5个

        std::vector<int> vec(10);
        rng.generate(vec.begin(), vec.end());   // 调用generate填充标准容器

        {
            // 支持复制、拷贝，用于复现测试
            boost::mt19937 rng(time(0));
            boost::mt19937 rng2(rng);
            for (size_t i = 0; i < 10; i++)
                assert(rng() == rng2());
        }   
    }

    {
        // 随机数分布器
        boost::mt19937 rng(time(0));            // 随机数发生器，以时间为种子
        boost::random::uniform_smallint<> u(0, 30);
        for (size_t i = 0; i < 10; i++)
            std::cout << u(rng) << ", ";
        std::cout << std::endl;

        boost::uniform_01<> u01;
        for (size_t i = 0; i < 10; i++)
            std::cout << u01(rng) << ", ";
        std::cout << std::endl;

        boost::normal_distribution<> nd(1, 2);
        int count = 0;
        for (size_t i = 0; i < 1000000; i++)
        {
            if(abs(nd(rng)-1) <= 3*2.0)
                ++count;
        }
        std::cout << 1.0 * count / 1000000 << std::endl;        // 3倍标准差0.9973，2倍标准差0.995，1倍标准差0.683
    }

    {
        // 变量发生器，更加方便的使用
        boost::mt19937 rng(time(0));            // 随机数发生器，以时间为种子
        boost::random::uniform_smallint<> u(0, 30);

        boost::variate_generator<boost::mt19937&, boost::uniform_smallint<>> gen(rng, u);
        for (size_t i = 0; i < 10; i++)
            std::cout << gen() << ", ";
        std::cout << std::endl;
    }

    {
        // 产生随机数块
        unsigned char buf[10];
        rand_bytes<boost::mt19937>(buf, 10);
        for (size_t i = 0; i < 10; i++)
            std::cout << (short)buf[i] << ", ";
        std::cout << std::endl;

        rand_bytes<boost::rand48>(buf, 10);
        for (size_t i = 0; i < 10; i++)
            std::cout << (short)buf[i] << ", ";
        std::cout << std::endl;
    }
}
