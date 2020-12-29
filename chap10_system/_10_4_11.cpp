#include <iostream>
#include "_10_4_11.hpp"

int main(int argc, char* argv[])
{
    /**<查找单个文件 */
    auto res = find_file(".", "_10_4.cpp");
    if(res)
        std::cout << *res << std::endl;
    else
        std::cout << "file not found." << std::endl;

    /**<通配符查找 */
    auto ress = find_files(".", R"---(_\d{1}_*.cpp)---");
    for(const auto& e : ress)
        std::cout << e << "\n";

    /**<拷贝文件夹 */
    copy_files(".", "./tmp");
}
