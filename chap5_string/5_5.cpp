#include <iostream>
#include <boost/xpressive/xpressive_dynamic.hpp>


int main(int argc, char* argv[])
{
    {
        // C 字符串正则表达式
        boost::xpressive::cregex reg = boost::xpressive::cregex::compile("a.c");

        assert(boost::xpressive::regex_match("abc", reg));
        assert(boost::xpressive::regex_match("a+c", reg));
        assert(!boost::xpressive::regex_match("ac", reg));  // 不匹配

        // 身份证案例
        reg = boost::xpressive::cregex::compile(R"---(\d{6}(1|2)\d{3}(0|1)\d[0-3]\d\d{3}(X|\d))---", boost::xpressive::icase);  // 忽略大小写
        assert(!boost::xpressive::regex_match("99999912340207151z", reg));
        assert(!boost::xpressive::regex_match("99999912340207151z", reg));
    }

    {
        // what可以输出每一个()的内容！！！
        boost::xpressive::cregex reg = boost::xpressive::cregex::compile(R"---(\d{6}((1|2)\d{3})((0|1)\d)([0-3]\d)(\d{3}(X|\d)))---", boost::xpressive::icase);  // 忽略大小写
        boost::xpressive::cmatch what;
        assert(boost::xpressive::regex_match("999999297002071517", what, reg));
        for(const auto& x : what){
            std::cout << "[" << x << "]";
        }
        std::cout << std::endl;
    }
}
