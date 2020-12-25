#include <iostream>
#include <boost/foreach.hpp>
#include <boost/ratio.hpp>
#include <boost/filesystem.hpp>

int main(int argc, char* argv[])
{
    {
        // 一、 异常处理
        boost::filesystem::path p("/test.txt");
        try {
            boost::filesystem::file_size(p);
        } catch(const boost::filesystem::filesystem_error& e) {
            std::cout << e.path1() << "\n";
            std::cout << e.path2() << "\n";     // 空的而已
            std::cerr << e.what() << '\n';
        }
    }
    
    {
        // 二、 文件状态
        assert(boost::filesystem::status("/dev/null").type() == boost::filesystem::character_file);
        assert(boost::filesystem::status("/bin").type() == boost::filesystem::directory_file);
        assert(boost::filesystem::status("/bin/sh").type() == boost::filesystem::regular_file);

        // 存取权限 owner_exe 更多信息参考 file_status.hpp
        assert((boost::filesystem::status("/bin/sh").permissions() & boost::filesystem::owner_exe) == boost::filesystem::owner_exe);

        // 利用便利的谓词来判断
        boost::filesystem::path p = "/home/topeet/myBoost/chap10_system";

        assert(boost::filesystem::is_directory(p));
        assert(boost::filesystem::exists(p/"_10_4_5.cpp"));            // 文件是否存在
        assert(boost::filesystem::is_regular_file(p/"_10_4_5.cpp"));   // 是否是普通文件
    }

    {
        // 三、 文件属性
        std::cout << boost::filesystem::initial_path() << std::endl;
        std::cout << boost::filesystem::current_path() << std::endl;
        
        boost::filesystem::path p = "chap10_system/_10_3.cpp";
        std::cout << boost::filesystem::file_size(p) << std::endl;      // 文件大小
        time_t t = boost::filesystem::last_write_time(p);               // 最后一次修改时间
        std::cout << ctime(&t) << std::endl;

        boost::filesystem::last_write_time(p, time(0));                 // 更改最后一次修改时间
        t = boost::filesystem::last_write_time(p);                      // 最后一次修改时间
        std::cout << ctime(&t) << std::endl;

        // 获取磁盘容量信息
        auto si = boost::filesystem::space("/");

        typedef boost::ratio<1024 * 1024 * 1024> GB;
        std::cout << "capacity: " << si.capacity / GB::num << "GB" << std::endl;
        std::cout << "available: " << si.available/ GB::num << "GB" << std::endl;
        std::cout << "free: " << si.free/ GB::num << "GB" << std::endl;
    }
}