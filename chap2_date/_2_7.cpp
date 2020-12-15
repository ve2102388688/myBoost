#include <iostream>
#include <locale>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::gregorian;
using namespace boost::posix_time;

// 自定义字面值
days operator"" _D(unsigned long long n)
{
    return days(n);
}

weeks operator"" _W(unsigned long long n)
{
    return weeks(n);
}

date operator"" _YMD(const char *s, std::size_t) // 为什么要加
{
    return from_string(s);
}

int main(int argc, char *argv[])
{
    auto d = 100_D; // 100天
    auto w = 1_W;   // 1周

    assert(d.days() == 100);
    assert(w.days() == (7_D).days()); // 可以直接使用-字面值变量

    auto today = "2020/11/21"_YMD;
    std::cout << today << std::endl;

    using std::cout;
    using std::endl;

    // 格式化时间
    date d1(2020, 11, 20);
    date_facet *dfacet = new date_facet("%Y年%m月%d日");

    cout.imbue(std::locale(cout.getloc(), dfacet));
    cout << d1 << endl;

    ptime p1(date(2020, 11, 20), hours(21) + minutes(50) + millisec(100));
    time_facet *tfacet = new time_facet("%Y年%m月%d日%H点%H分%S%F秒");

    cout.imbue(std::locale(cout.getloc(), tfacet));
    cout << p1 << endl;

    delete dfacet;
    delete tfacet;
}