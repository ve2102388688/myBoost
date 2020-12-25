#include <iostream>
#include <boost/chrono.hpp>

typedef boost::chrono::duration<long, boost::ratio<30>>     half_min;       // 半分钟
typedef boost::chrono::duration<int, boost::ratio<60*15>>     quater;       // 15min
typedef boost::chrono::duration<double, boost::ratio<3600*24>>   day;       // 一天

// 小时
boost::chrono::hours operator"" _h(unsigned long long n) {
    return boost::chrono::hours(n);
}
// 分钟
boost::chrono::minutes operator"" _min(unsigned long long n) {
    return boost::chrono::minutes(n);
}
// 秒
boost::chrono::seconds operator"" _s(unsigned long long n) {
    return boost::chrono::seconds(n);
}
// 毫秒
boost::chrono::milliseconds operator"" _ms(unsigned long long n) {
    return boost::chrono::milliseconds(n);
}

class MySteadyTimer final
{
private:
    typedef boost::chrono::steady_clock clock_type;     // 何种计时源
    typedef clock_type::time_point time_point_type;     // 时间点
    typedef boost::chrono::microseconds duration_type;  // 时间段, us
    time_point_type m_start;

public:
    MySteadyTimer() : m_start( clock_type::now() ) { }

    void restart(){
        m_start = clock_type::now();
    }

    // 流逝时间
    duration_type elapsed() const {
        return boost::chrono::round<duration_type>(clock_type::now() - m_start);
    }
};



int main(int argc, char* argv[])
{
    {
        auto h = 1_h;
        auto min = 30_min;
        auto s = 30_s;
        auto ms = 100_ms;
        auto total = h + min + s + ms;
        std::cout << total << std::endl;
    }

    {
        MySteadyTimer mytimer;

        std::cout << mytimer.elapsed() << std::endl;
    }
}