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

    {
        // 四、 文件操作
        boost::filesystem::path p = "chap10_system/_10_3";
        if(boost::filesystem::exists(p)){
            if(boost::filesystem::is_empty(p))  // 文件夹是否为空
                boost::filesystem::remove(p);           // 删除空目录或者单个文件
            else
                boost::filesystem::remove_all(p);       // 递归删除该目录下所有的文件
        }


        assert(!boost::filesystem::exists(p));
        boost::filesystem::create_directory(p);         // 创建目录
        boost::filesystem::copy_file("chap10_system/_10_3.cpp", "chap10_system/_10_3/_10_3.cpp");   // 拷贝文件
        boost::filesystem::rename(p / "_10_3.cpp", p / "_10_3_old.cpp");        // 修改名字

        // 创建多层目录
        boost::filesystem::create_directories(p/"a"/"b");
    }

    {
        // 五、 和文件流对接
        boost::filesystem::path p = "chap10_system/_10_3.cpp";

        {
            // IF complier not support C++17, must convert path to char* or std::string
            // Method1, not easy
            std::ifstream ifs(p.c_str());
        }

        {
            // Method2 和文件流对接
            boost::filesystem::ifstream ifs(p);
            assert(ifs.is_open());
            std::cout << ifs.rdbuf() << std::endl;       // 输出内容
        }
    }
}