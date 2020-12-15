#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

int main(int argc, char *argv[])
{
    using namespace boost::gregorian;

    //***************************** 日期迭代器 ***********************************
    date d(2020, 11, 19);
    day_iterator d_iter(d); // 天数迭代器

    ++d_iter;
    assert(d_iter == date(2020, 11, 20));

    year_iterator y_iter(*d_iter, 10); // 默认加1，这里加10年
    ++y_iter;
    assert(y_iter->year() == 2030);

    // 只有前置运算，没有后置的（效率原因）；也没有+=
    day_iterator iter(day_clock::local_day());
    ++iter;
    // iter += 10; // 错误，编译失败

    // gregorian_calendar 判断是否是瑞年，已知年份，月份获得最后一天end_of_month_day
    std::cout << "2017 is " << (gregorian_calendar::is_leap_year(2017) ? "" : "not") << " a leap year." << std::endl;

    assert(gregorian_calendar::end_of_month_day(2017, 2) == 28);
}
