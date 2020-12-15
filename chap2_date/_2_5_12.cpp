#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

int main(int argc, char *argv[])
{
    using namespace boost::gregorian;

    //***************************** 显示月历 ***********************************
    date d(2020, 11, 19);

    date d_start(d.year(), d.month(), 1);
    date d_end = d.end_of_month();

    for (day_iterator d_iter(d_start); d_iter != d_end; ++d_iter)
    {
        std::cout << *d_iter << " " << d_iter->day_of_week() << std::endl;
    }

    // 计算某人23岁的生日是星期几
    date myBirth(1997, 8, 6);
    date d23years = myBirth + years(23);
    std::cout << d23years << " is " << d23years.day_of_week() << std::endl;
}
