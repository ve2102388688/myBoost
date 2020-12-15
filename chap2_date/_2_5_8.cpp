#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

int main(int argc, char *argv[])
{
    using namespace boost::gregorian;

    //***************************** date_period ***********************************
    // 构造函数有两个, 区间端点左闭右开并且是小于的关系，狗则是一个无效时间段
    date_period dp1(date(2020, 11, 18), days(10));
    date_period dp2(date(2020, 11, 17), date(2016, 1, 1)); // 无效
    date_period dp3(date(2020, 11, 17), days(-20));        // 无效
    assert(dp2.is_null() == true && dp3.is_null() == true);

    // 成员函数 [begin, last), last=27, end()=28
    assert(dp1.begin().day() == 18);
    assert(dp1.end().day() == 28);
    assert(dp1.last().day() == 27);    // day 是时间点
    assert(dp1.length().days() == 10); // days 是时间段

    // 输出时间段
    std::cout << dp1 << std::endl; // [2020-Nov-18/2020-Nov-27]

    // 日期期间的运算 平移shift 两端扩展(expand)
    {
        date_period dp1(date(2020, 1, 1), days(20));
        dp1.shift(days(3));
        assert(dp1.begin().day() == 4);
        assert(dp1.length().days() == 20);

        dp1.expand(days(3));
        assert(dp1.begin().day() == 1);
        assert(dp1.length().days() == 20 + 6);
    }

    // 日期时间的交集、相邻、包含
    {
        date_period dp(date(2020, 1, 1), days(20));
        date_period dp2(date(2020, 1, 5), days(15));
        date_period dp3(date(2020, 2, 1), days(5));

        assert(!dp.intersects(dp3));             // 是否存在交集
        assert(dp.contains(dp2));                // 是否被包含
        assert(dp.span(dp3).end() == dp3.end()); // 广义交集，即使中间没有元素
        assert(dp.merge(dp3).is_null());         // 交集，极限是相邻哦
    }
}
