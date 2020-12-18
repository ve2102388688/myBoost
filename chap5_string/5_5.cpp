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

    {
        // 正则查找
        const char str[] = "there is a POWER-suit item.";
        boost::xpressive::cregex reg = boost::xpressive::cregex::compile("(power)-(.{4})", boost::xpressive::icase);

        assert(boost::xpressive::regex_search(str, reg));
        boost::xpressive::cmatch what;
        assert(boost::xpressive::regex_search(str, what, reg));
        for(const auto& x : what){
            std::cout << "[" << x << "]";
        }
        std::cout << std::endl;
    }

    {
        // 正则查找
        std::string str("README.TXT");
        boost::xpressive::sregex start_reg = boost::xpressive::sregex::compile("^RE");
        boost::xpressive::sregex end_reg = boost::xpressive::sregex::compile("txt$", boost::xpressive::icase);

        assert(boost::xpressive::regex_search(str, start_reg));                                         // starts_with
        assert(boost::xpressive::regex_search(str, end_reg));                                           // ends_with
        assert(boost::xpressive::regex_search(str, boost::xpressive::sregex::compile("ME")));           // contains
    }

    {
        // 正则替换
        std::string str("readme.txt");

        boost::xpressive::sregex reg = boost::xpressive::sregex::compile("(.*)(me)");       // $1 $2 = $&
        boost::xpressive::sregex reg2 = boost::xpressive::sregex::compile("(t)(.)(t)");     // $1 $2 $3 = $&

        std::cout << boost::xpressive::regex_replace(str, reg, "attention") << std::endl;
        std::cout << boost::xpressive::regex_replace(str, reg, "$1Please") << std::endl;
        std::cout << boost::xpressive::regex_replace(str, reg, "$&$&") << std::endl;       
        std::cout << boost::xpressive::regex_replace(str, reg2, "$1N$3") << std::endl;       
        std::cout << std::endl;


        std::string str2("  2020  Good Firend!!!  ");
        boost::xpressive::sregex reg3 = boost::xpressive::sregex::compile("^(\\d| )*");     // 前缀空格和数字
        boost::xpressive::sregex reg4 = boost::xpressive::sregex::compile("(\\s|!)*$");       // 后缀空格和！

        std::cout << boost::xpressive::regex_replace(str2, reg3, "") << std::endl;         // trim_left
        std::cout << boost::xpressive::regex_replace(str2, reg4, "") << std::endl;         // trim_right
    }

    {
        // 正则迭代
        std::string str("Power-bomb, power-suit, pOWER-beam all items\n");
        boost::xpressive::sregex reg = boost::xpressive::sregex::compile("power-(\\w{4})", boost::xpressive::icase);
        boost::xpressive::sregex_iterator pos(str.begin(), str.end(), reg), end;
        for (; pos != end; ++pos)
            std::cout << "[" << (*pos)[0] << "]";   // sub_match<BidiIter> const &
        std::cout << std::endl;
    }

    {
        // 正则分词
        const char str[] = "*Samus*||+samus+||-Link-||Zelda!!!||Mario";
        boost::xpressive::cregex reg = boost::xpressive::cregex::compile("\\w{4}", boost::xpressive::icase);
        boost::xpressive::cregex_token_iterator pos(str, str + strlen(str), reg), end;
        for (; pos != end; ++pos)
            std::cout << "[" << *pos << "]";   // sub_match<BidiIter> const &
        std::cout << std::endl;

        reg = boost::xpressive::cregex::compile("\\|\\|");      // ||
        pos = boost::xpressive::cregex_token_iterator(str, str + strlen(str), reg, -1); // -1将匹配字符视为分隔符
        for (; pos != end; ++pos)
            std::cout << "[" << *pos << "]";   // sub_match<BidiIter> const &
        std::cout << std::endl;
    }
}
