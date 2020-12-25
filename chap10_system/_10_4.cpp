#include <iostream>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

int main(int argc, char* argv[])
{
    {
        boost::filesystem::path p;      // 默认路径为空
        assert(p.empty());

        // 下面通过append、/=、+=、concat; 其中前面两个会自动添加/，后面两个不会添加/
        // 一、自动添加/
        char str[] = "the path is (/home).";
        p.append(str+13, str+18);       // 尾后元素
        p /= "topeet";
        // 二、不会添加/
        p += "/myBoost";
        std::string filename = "/chap10_system";
        p.concat(filename.begin(), filename.end());

        // 输出绝对路径
        std::cout << boost::filesystem::system_complete(p) << std::endl;
        std::cout << p << std::endl;
    }

    {
        // 判断是否是windows/linux合法文件名
        std::string fname("w+abc.xxx");
        assert(!boost::filesystem::portable_posix_name(fname));
        assert(boost::filesystem::windows_name(fname));

        // 同时满足portable_posix_name && windows_name，且开头!!!不能是.
        assert(!boost::filesystem::portable_name("/wabc.txt") && !boost::filesystem::portable_name("w+abc.txt"));

        // 合法文件名，在portable_name之上不能有.
        assert(boost::filesystem::portable_directory_name("wabc"));
        
        // 后缀名最多三个字母
        assert(boost::filesystem::portable_file_name("w.abc") && !boost::filesystem::portable_file_name("w.abcd"));

        // native判断是否符合本地命名规则,这里不知道在啥系统下
        assert(boost::filesystem::native("w+.abc"));
    }

    {
        std::cout << "****************************" << std::endl;
        boost::filesystem::path p("/home/topeet/myBoost/chap10_system/xxx.cpp");
        //boost::filesystem::path p("F:/study/C++/boost_Eigen_test/boost_Eigen_test/main.cpp");
        BOOST_FOREACH(const auto& x, p){                // 常量迭代器
            std::cout << "[" << x << "]";
        }

        std::cout << "\n" << p.string() << std::endl;   // 全路径名
        std::cout << p.parent_path() << std::endl;      // 父目录
        std::cout << p.filename() << std::endl;         // 文件名 filename = stem + extension
        std::cout << p.stem() << std::endl;             // 去后缀
        std::cout << p.extension() << std::endl;        // 后缀名
        std::cout << p.relative_path() << std::endl;    // 去掉root_path

        assert(p.is_absolute());            // 判断是否是绝对完整路径，注意和操作系统有关，比如这里Linux,windows有盘符才合法

        // 关于根目录
        std::cout << p.root_name() << std::endl;         // 根目录名字
        std::cout << p.root_directory() << std::endl;    // 根目录
        std::cout << p.root_path() << std::endl;         // 根路径

        assert(!p.has_root_name());              // Linux的root_name是空，Windows是盘符+:

        // 删除/修改后缀名
        std::cout << p.replace_extension("h") << std::endl;    // 替换后缀名
        std::cout << p.replace_extension() << std::endl;       // 删除后缀名
        std::cout << p.remove_filename() << std::endl;         // 删除文件名
    }

    {
        // 比较操作
        boost::filesystem::path p1("/home/topeet/myBoost/chap10_system/1.cpp");
        boost::filesystem::path p2("/home/topeet/myBoost/chap10_system/2.cpp");
        boost::filesystem::path p3("/home/topeet/myBoost/chap10_system/3.cpp");
        assert(p1 != p2 && p1 < p2);
    }
}