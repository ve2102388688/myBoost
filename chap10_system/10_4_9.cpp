#include <iostream>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

// 自定义递归目录
void resursive_dir(const boost::filesystem::path& dir) {
    boost::filesystem::directory_iterator end;
    for(boost::filesystem::directory_iterator pos(dir); pos != end; ++pos){
        if(boost::filesystem::is_directory(*pos))     // 是否是目录
            resursive_dir(*pos);
        else
            std::cout << *pos << std::endl;
    }
}

int main(int argc, char* argv[])
{
    // 迭代目录 method1
    boost::filesystem::directory_iterator end;
    for(boost::filesystem::directory_iterator pos("."); pos != end; ++pos)
        std::cout << *pos << std::endl;

    {
        // 简化访问 method1
        typedef std::pair<boost::filesystem::directory_iterator, boost::filesystem::directory_iterator> Dir_range;
        Dir_range dr(boost::filesystem::directory_iterator("."), boost::filesystem::directory_iterator());

        BOOST_FOREACH(const auto& e, dr)
            std::cout << e << std::endl;
    }

    // 遍历目录
    resursive_dir(".");

    {
        boost::filesystem::recursive_directory_iterator end;
        for (boost::filesystem::recursive_directory_iterator pos("."); pos != end; ++pos)
        {
            // 只遍历第一层
            if(boost::filesystem::is_directory(*pos))
                pos.disable_recursion_pending();    //不深度遍历
            std::cout << "depth: " << pos.depth() << " : " << *pos << std::endl;
        }
    }
}
