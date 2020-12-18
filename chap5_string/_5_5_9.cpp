#include <iostream>
#include <boost/xpressive/xpressive_dynamic.hpp>
#include <boost/xpressive/xpressive_static.hpp>
#include <boost/algorithm/string.hpp>


int main(int argc, char *argv[])
{
    {
        // 另一个工厂函数cregex_compiler
        boost::xpressive::cregex_compiler rc;

        rc["reg1"] = rc.compile("a|b|c");
        rc["reg2"] = rc.compile("\\d*");

        assert(!boost::xpressive::regex_match("ab", rc["reg1"]));
        assert(boost::xpressive::regex_match("123", rc["reg2"]));
    }

    {
        // 函数对象
        struct Formater
        {
            std::string operator()(boost::xpressive::cmatch const &m) const{
                return boost::to_upper_copy(m[0].str());
            }
        };
        
        const char str[] = "*Samus*||+samus+||-Link-||Zelda!!!||Mario";

        boost::xpressive::cregex reg =  boost::xpressive::cregex::compile("\\w+", boost::xpressive::icase);
        std::cout << boost::xpressive::regex_replace(str, reg, Formater()) << std::endl;   // 调用5次 Formater
    }

    {
        // 静态正则表达式 
        using namespace boost::xpressive;
        const char str[] = "123abc";
        
        // ^\d*\w+
        cregex reg = bos >> *_d >> +_w;
        assert(regex_match(str, reg));
    }
} 
