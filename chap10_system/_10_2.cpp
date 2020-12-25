#include <iostream>
#include <boost/chrono.hpp>

// 自定义模板别名
template <typename T>
using clock_desc = boost::chrono::clock_string<T, char>;

int main(int argc, char* argv[])
{
    typedef boost::chrono::duration<long, boost::ratio<30>>     half_min;       // 半分钟
    typedef boost::chrono::duration<int, boost::ratio<60*15>>     quater;       // 15min
    typedef boost::chrono::duration<double, boost::ratio<3600*24>>   day;       // 一天
    {
        boost::chrono::seconds s(10);
        boost::chrono::minutes m(5);
        boost::chrono::hours   h(1);
        boost::chrono::milliseconds   ms(100);

        // count()函数
        assert(s.count() == 10);
        assert(h.count() == 1);

        // 算术运算
        s *= 3;
        s += h;
        std ::cout << s << std::endl;

        // 混合不同运算时，前面的单位要小些！！！反过来不一定行
        // m += s;     // error 不能转换

        // 四舍五入、上取整、下取整
        boost::chrono::seconds s2(3600+30);
        std::cout << boost::chrono::floor<boost::chrono::minutes>(s2) << std::endl;  // 截断等价于boost::chrono::duration_cast<>
        std::cout << boost::chrono::ceil<boost::chrono::minutes>(s2) << std::endl;   // 上取整
        std::cout << boost::chrono::round<boost::chrono::minutes>(s2) << std::endl;  // 四舍五入
    }

    {
        std::cout << clock_desc<boost::chrono::system_clock>::name() << std::endl;    // 1970-1-1
        std::cout << clock_desc<boost::chrono::system_clock>::since() << std::endl;

        std::cout << clock_desc<boost::chrono::steady_clock>::name() << std::endl;    // bios
        std::cout << clock_desc<boost::chrono::steady_clock>::since() << std::endl;

        std::cout << clock_desc<boost::chrono::process_real_cpu_clock>::name() << std::endl;    // 进程开始
        std::cout << clock_desc<boost::chrono::process_real_cpu_clock>::since() << std::endl;
    }

    {
        // 需要boost_chrono动态库支持
        // 1970-1-1
        auto tp1 = boost::chrono::system_clock::now();
        std::cout << tp1 << std::endl;

        auto d = tp1.time_since_epoch();        // 时间差，1970.1开始
        std::cout << boost::chrono::floor<boost::chrono::hours>(d) << std::endl;
        std::cout << boost::chrono::floor<day>(d) << std::endl;
        // 与time_t转换
        auto t = boost::chrono::system_clock::to_time_t(tp1);
        std::cout << std::ctime(&t);    // Fri Dec 25 10:13:16 2020

        // 自bios开机的时间
        auto tp2 = boost::chrono::steady_clock::now();
        std::cout << tp2 << std::endl;

        d = tp2.time_since_epoch();     // 时间差，bios开始
        std::cout << boost::chrono::floor<boost::chrono::hours>(d) << std::endl;
        std::cout << boost::chrono::floor<day>(d) << std::endl;
    }
}