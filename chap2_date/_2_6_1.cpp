#include <iostream>
#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG // ns精度，默认是us(6位)
#include <boost/date_time/posix_time/posix_time.hpp>

int main(int argc, char *argv[])
{
    using namespace boost::posix_time;

    //***************************** time_duration ***********************************
    time_duration td(1, 10, 30, 1000); // 1h10min30s1000us(1小时10分30.001秒)
    // 两种输出方式
    std::cout << to_simple_string(td) << std::endl; // 01:10:30.000001
    std::cout << to_iso_string(td) << std::endl;    // 011030.000001
    // 获取1000，最后一个参数
    assert(td.fractional_seconds() == 1000);

    // duration_from_string
    time_duration td2(duration_from_string("1:10:30:001"));
    std::cout << to_simple_string(td2) << std::endl; // << 默认
    std::cout << td2 << std::endl;

    // 几个常用的time_duration子类，如hours、minutes、seconds、millisec
    hours h(1);
    minutes m(10);
    seconds s(30);
    millisec ms(1);
    time_duration td3 = h + m + s + ms;
    std::cout << to_simple_string(td3) << std::endl;

    // 改变时间的正负
    {
        hours h(-10);
        assert(h.is_negative());
        time_duration h2 = h.invert_sign();
        assert(!h2.is_negative());
    }

    // 更高的时间精度，默认是us，开启BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG将会达到ns
    {
#ifdef BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
        // unit()等价duration_type(0,0,0,1)，1s=10^9ns
        assert(time_duration::unit() * 1000 * 1000 * 1000 == seconds(1));

        time_duration td(1, 10, 30, 1000); // 1h10min30s1000ns(1小时10分30.000001秒)
        std::cout << td << std::endl;
        assert(td.resolution() == boost::date_time::nano); //单位ns
        assert(td.num_fractional_digits() == 9);           // 9位小数
#endif
    }
}
