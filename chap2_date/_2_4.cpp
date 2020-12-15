#include <iostream>
#include <cassert>
#undef BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES
#include <boost/date_time/gregorian/gregorian.hpp>   // 处理日期
#include <boost/date_time/posix_time/posix_time.hpp> // 处理时间

int main(int argc, char *argv[])
{
    boost::gregorian::date d1; // 默认构造函数产生一个无效日期
    // 等价
    assert(d1 == boost::gregorian::date(boost::gregorian::not_a_date_time)); // 断言为假，产生异常；为真则继续执行
    assert(d1.is_not_a_date());                                              // 断言为假，产生异常；为真则继续执行

    // 3中常见的构造函数
    boost::gregorian::date d2(2020, 11, 17); // Method 1
    // enum months_of_year {Jan=1,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec,NotAMonth,NumMonths};
    boost::gregorian::date d3(2020, boost::gregorian::Nov, 17); // Method 2
    boost::gregorian::date d4(d3);                              // Method 3
    // 使用字符串方式，这是需要工厂函数的帮助
    // from_string 支持常见的段句方式 sep_char[] = {',','-','.',' ','/','\0'};
    // from_undelimited_string 年月日连在一起 offsets[] = {4,2,2};
    {
        boost::gregorian::date d1 = boost::gregorian::from_string("2020-11-17");
        boost::gregorian::date d2(boost::gregorian::from_string("2020/11/17"));
        boost::gregorian::date d3 = boost::gregorian::from_undelimited_string("20201117");
    }

    // date对象的输出
    // to_simple_string         YYYY-mmm-DD, 其中mmm是英文的方式(默认，即<<)
    // to_iso_string            YYYYmmDD
    // to_iso_extended_string   YYYY-mm-DD
    std::cout << boost::gregorian::to_simple_string(d2) << '\n';
    std::cout << boost::gregorian::to_iso_string(d2) << '\n';
    std::cout << boost::gregorian::to_iso_extended_string(d2) << '\n';
    std::cout << d2 << '\n';

    // // 一个用户输入的案例
    // {
    //     boost::gregorian::date d;
    //     std::cin >> d; // 必须以默认默认的格式输入，否则返回的是not_a_date_time
    //     std::cout << d << '\n';
    // }

    // 一些特殊的date
    {
        boost::gregorian::date d1(boost::gregorian::neg_infin);       // 负无穷时间
        boost::gregorian::date d2(boost::gregorian::pos_infin);       // 正无穷时间
        boost::gregorian::date d3(boost::gregorian::not_a_date_time); // 无效时间
        boost::gregorian::date d4(boost::gregorian::max_date_time);   // 最大的时间9999-Dec-31
        boost::gregorian::date d5(boost::gregorian::min_date_time);   // 最小的时间1400-Jan-01
        std::cout << d1 << " " << d2 << " " << d3 << " " << d4 << " " << d5 << '\n';
    }

    // 得到本机时间及UTC时间，注意只能获取年月日，精确到天而已
    std::cout << boost::gregorian::day_clock::local_day() << std::endl;     // 本地时间，领先UTC八个小时
    std::cout << boost::gregorian::day_clock::universal_day() << std::endl; // UTC时间

    // 输入的日期非法，例如上溢、下溢、不存在的日期
    {
        //boost::gregorian::date d1(1399, 12, 1);     // what():  Year is out of valid range: 1400..9999
        //boost::gregorian::date d2(10000, 12, 1);    // what():  Year is out of valid range: 1400..9999
        //boost::gregorian::date d3(2017, 2, 29);     // what():  Day of month is not valid for year
    }

    // 获得年 月 日等简单函数
    {
        boost::gregorian::date d(2020, 11, 17);
        assert(d.year() == 2020);
        assert(d.month() == 11);
        assert(d.day() == 17);

        // 直接返回年月日，直接取成员变量即可
        boost::gregorian::date::ymd_type ymd = d.year_month_day();
        assert(ymd.year == 2020);
        assert(ymd.month == 11);
        assert(ymd.day == 17);

        // 获得星期几，一年中第多少天，第几周，本月最后一天的对象
        std::cout << d.day_of_week() << std::endl; // Tue
        std::cout << d.week_number() << std::endl; // 47
        std::cout << d.day_of_year() << std::endl; // 322
        assert(d.end_of_month() == boost::gregorian::date(2020, 11, 30));
    }

    // 转换成C结构
    {
        boost::gregorian::date d(2020, 11, 17);
        tm t = boost::gregorian::to_tm(d);
        assert(t.tm_hour == 0 && t.tm_min == 0);                       // 自动把小时，分钟，秒置为0
        assert(t.tm_year == 120 && t.tm_mon == 10 && t.tm_mday == 17); // 年是从1900开始，月份是0-11

        boost::gregorian::date d2 = boost::gregorian::date_from_tm(t); // 从tm转换成date
        assert(d2 == d);
    }

    // 日期长度 date_duration,度量时间长度，可正可负，也支持四则运算
    boost::gregorian::days dd1(10), dd2(-100), dd3(255);
    assert(dd1 > dd2 && dd1 < dd3);
    assert((dd1 + dd3).days() == 265);
    assert(dd3 / 5 == boost::gregorian::days(51));

    // weeks months years 特殊的三个时间段
    {
        boost::gregorian::weeks w(3);
        assert(w.days() == 21);

        boost::gregorian::months m(5);
        boost::gregorian::years y(2);

        boost::gregorian::months m2 = m + y;
        assert(m2.number_of_months() == 29);
        assert((y * 2).number_of_years() == 4);
    }

    // 日期运算 支持加减特殊日期
    {
        boost::gregorian::date d1(2000, 1, 1), d2(2017, 11, 18);
        std::cout << d2 - d1 << std::endl;
        // std::cout << d2 + d1 << std::endl;   // 加法报错

        d1 += boost::gregorian::days(10);
        assert(d1.day() == 11);

        d1 += boost::gregorian::days(boost::gregorian::not_a_date_time);
        assert(d1.is_not_a_date());
    }
}
