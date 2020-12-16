#include <iostream>
#include <cassert>
#include <string>
#include <cstring>
#include <boost/utility/string_ref.hpp>

int main(int argc, char* argv[])
{
    const char* ch = "Days of Future Past";
    std::string str(ch);        // 拷贝代价

    boost::string_ref s1(ch);    // 0拷贝
    boost::string_ref s2(str);   // 0拷贝
    assert(s1 == s2 && s1 == ch && s2 == str);

    boost::string_ref s3(ch, 4);    // 截取部分构造
    assert(s3 == str.substr(0, 4));

    // 定义两个空串
    boost::string_ref s4, s5;
    s4 = ch;
    s5 = str;   // 拷贝赋值，0开销
    assert(s4 == s5);

    {
        // 和标准字符串使用方式一致
        const char* ch = "Days of Future Past";
        boost::string_ref s2(ch);   // 0拷贝

        assert(!s2.empty());
        assert(str.size() == strlen(ch));

        for (const auto& x : str)
            std::cout << x;
        std::cout << std::endl;

        assert(str.front() == 'D');
        assert(str.find('a') == 1);     // 查找操作
    }

    {
        // 省略了开始的字符串构造成本，返回值的构造成本
        auto trunk = [](boost::string_ref str) -> boost::string_ref { return str.substr(0,5); };

        std::cout << trunk("abcdefg") << std::endl;
    }
}