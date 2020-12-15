#include <iostream>
#include <sstream>
#include <boost/timer.hpp>    // timer
#include <boost/progress.hpp> // progress_timerp

int main(int argc, char *argv[])
{
    boost::timer t; // 声明计时器对象，开始计时

    std::cout << "max timespan:" << t.elapsed_max() / 3600 << 'h' << std::endl; // 可度量的最大的时间，小时为单位
    std::cout << "min timespan:" << t.elapsed_min() << 's' << std::endl;        // 可度量的最小的时间，小时为单位
    std::cout << "max timespan:" << t.elapsed() << 's' << std::endl;            // 流逝的时间

    // progress_timer在析构中自动输出流逝时间，默认是std::cout
    {
        boost::progress_timer t;
    }

    // 将输出重定向stringstream中
    std::stringstream ss;
    {
        boost::progress_timer t(ss);
    }
    std::cout << ss.str();
}
