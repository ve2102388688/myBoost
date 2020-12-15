#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <iostream>
#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG // ns精度，默认是us(6位)
#include <boost/date_time/posix_time/posix_time.hpp>

int main(int argc, char *argv[])
{
    using namespace boost::posix_time;
    using namespace boost::gregorian;
    using std::cout;
    using std::endl;

    //***************************** p_time ***********************************
    ptime p(date(2020, 1, 1), hours(1)); // 2020-1-1 01:00:00
    cout << to_simple_string(p) << endl;
    cout << to_iso_string(p) << endl;
    cout << to_iso_extended_string(p) << endl;
    cout << p << endl;

    // 使用字符串构造
    ptime p1 = time_from_string("2020-1-1 01:00:00");
    ptime p2 = from_iso_string("20200101T010000"); // 中间用T分割
    cout << p1 << endl;
    cout << p2 << endl;

    // 提供本地时间
    {
        ptime p1 = second_clock::local_time();   // 精确度s
        ptime p2 = microsec_clock::local_time(); // 精确度us
        cout << p1 << endl;
        cout << p2 << endl;
    }

    // 分割p_time成 date+time_duration
    {
        ptime p(date(2020, 11, 20), hours(12) + minutes(30));
        date d = p.date();                  // 获得 date
        time_duration td = p.time_of_day(); // 获得 time_duration
        assert(d.month() == 11 && d.day() == 20);
        assert(td.total_seconds() == 12 * 3600 + 30 * 60);

        // 进一步+ - * /
        ptime p1 = p + hours(3);
        assert(p1 - p == hours(3));
    }

    // 转换成C结构
    {
        // tm <---> ptime
        ptime p(date(2020, 11, 20), hours(12));
        tm t = to_tm(p);

        // time_t <---> p_time
        ptime p1 = from_time_t(std::time(0));
        assert(p1.date() == day_clock::local_day());

        cout << to_time_t(p1) << endl;
    }

    // 时间迭代器
    {
        ptime p(date(2020, 11, 20), hours(12));
        for (time_iterator t_iter(p, minutes(10)); t_iter < p + hours(1); ++t_iter)
        {
            cout << *t_iter << endl;
        }
    }
}
