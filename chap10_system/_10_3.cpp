#include <iostream>
#include <vector>
#include <boost/algorithm/string/join.hpp>  // boost::join
#include <boost/timer/timer.hpp>

int main(int argc, char* argv[])
{
    // 需要-lboost_timer
    boost::timer::cpu_timer t;
    std::vector<std::string> v(10, "hello");
    for (size_t i = 0; i < 10000; i++)
        boost::join(v, "-");

    t.stop();
    assert(t.is_stopped());
    std::cout << t.format() << std::endl;

    {
        boost::timer::auto_cpu_timer t;
        t.report();     // 析构自动调用
    }
}