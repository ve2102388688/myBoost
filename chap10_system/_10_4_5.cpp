#include <iostream>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

int main(int argc, char* argv[])
{
    {
        // 异常处理
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
        // 文件属性
        assert(boost::filesystem::status("/dev/null").type() == boost::filesystem::character_file);
        assert(boost::filesystem::status("/bin").type() == boost::filesystem::directory_file);
        assert(boost::filesystem::status("/bin/sh").type() == boost::filesystem::regular_file);

        // 存取权限 owner_exe 更多信息参考 file_status.hpp
        assert((boost::filesystem::status("/bin/sh").permissions() & boost::filesystem::owner_exe) == boost::filesystem::owner_exe);
    }

    {
        // 利用便利的谓词来判断
        boost::filesystem::path p = "/home/topeet/myBoost/chap10_system";

        assert(boost::filesystem::is_directory(p));
        assert(boost::filesystem::exists(p/"_10_4_5.cpp"));
        assert(boost::filesystem::is_regular_file(p/"_10_4_5.cpp"));
    }
}