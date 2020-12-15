#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>

using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace boost::local_time;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    tz_database tz_db;                              // 时间数据库对象
    tz_db.load_from_file("date_time_zonespec.csv"); // 打开世界各地时区表

    // 中国超前洛杉矶16h
    time_zone_ptr shz = tz_db.time_zone_from_region("Asia/Shanghai");       // 北京时间
    time_zone_ptr sfz = tz_db.time_zone_from_region("America/Los_Angeles"); //洛杉矶时区

    cout << shz->has_dst() << endl;       // 上海无夏令时
    cout << shz->std_zone_name() << endl; // 获取上海的时区名字CST

    // 北京时间2020-11-20 16:00:00
    local_date_time dt_bj(date(2020, 11, 20), hours(16), shz, false); // 最后一个参数是是否是夏令时，需要提前知道
    cout << dt_bj << endl;

    // 假定飞机从北京到洛杉矶需要12小时
    time_duration flight_time = hours(12);

    dt_bj += flight_time; // 飞机达到后，北京时间
    cout << dt_bj << endl;

    local_date_time dt_sf = dt_bj.local_time_in(sfz); // 飞机达到后，洛杉矶时间
    cout << dt_sf << endl;
}
