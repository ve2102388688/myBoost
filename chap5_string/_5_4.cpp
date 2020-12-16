#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/utility/string_ref.hpp>
#include <deque>
#include <list>
#include <boost/assign.hpp>


int main(int argc, char* argv[])
{
    {
        std::string str("readme.txt");
        if(boost::ends_with(str, "txt")){
            std::cout << boost::to_upper_copy(str) + " UPPER" << std::endl;
            assert(boost::ends_with(str, "txt"));
        }

        boost::replace_first(str, "readme", "attention");
        std::cout << str << std::endl;
    }

    {
        // 1. 大小写转换
        std::string str("Good Friend");
        std::cout << boost::to_upper_copy(str) << std::endl;    // 原始字符串没有改变
        std::cout << str << std::endl;

        boost::to_lower(str); // 原始字符串改变
        std::cout << str << std::endl;
    }

    {
        // 2. 判断式
        std::string str("Good Friend");
        assert(boost::iends_with(str, "friend"));       // 大小写无关
        assert(!boost::ends_with(str, "friend"));        

        assert(boost::starts_with(str, "Good"));
        assert(boost::contains(str, "oo"));

        std::string str2 = boost::to_lower_copy(str);
        assert(boost::iequals(str, str2));              // 大小写无关

        std::string str3("Good man");
        assert(boost::ilexicographical_compare(str, str3)); // 字典比较，f在m前

        // 判定前四个是否都是小写
        assert(boost::all(str2.substr(0, 4), boost::is_lower()));

        // 函数对象
        assert(!boost::is_equal()(str, str2));
        assert(!boost::is_equal()(str, boost::string_ref(str2)));
    }

    {
        // 3. 修剪开始和结尾
        boost::format fmt("|%s|\n");
        std::string str("  2020  Good Firend!!!  ");

        // 剪去左边、右边的空格
        std::cout << fmt % boost::trim_copy(str);
        std::cout << fmt % boost::trim_left_copy(str);
        std::cout << fmt % boost::trim_right_copy(str);
        
        // 满足特点的条件删除
        std::cout << fmt % boost::trim_left_copy_if(str, boost::is_digit() || boost::is_space());   // 删除左边的数字
        std::cout << fmt % boost::trim_copy_if(str, boost::is_digit() || boost::is_space() || boost::is_punct());
    }

    {
        // 4.查找
        boost::format fmt("|%s|. pos = %d\n");
        std::string str("Long long ago, there was a king.");
        boost::iterator_range<std::string::iterator> rge;

        rge = boost::find_first(str, "long");
        std::cout << fmt % rge % (rge.begin() - str.begin());   // 查找的字符串和位置

        rge = boost::ifind_first(str, "long");  // 忽略大小写
        std::cout << fmt % rge % (rge.begin() - str.begin());   // 查找的字符串和位置

        rge = boost::find_nth(str, "ng", 2);  // 第三次出现
        std::cout << fmt % rge % (rge.begin() - str.begin());   // 查找的字符串和位置

        rge = boost::find_head(str, 4);
        std::cout << fmt % rge % (rge.begin() - str.begin());   // 查找的字符串和位置

        rge = boost::find_tail(str, 5);
        std::cout << fmt % rge % (rge.begin() - str.begin());   // 查找的字符串和位置

        rge = boost::find_first(str, "are");  // 找不到
        assert(rge.empty() && !rge);
    }

    {
        // 4.替换和删除
        std::string str("Long long ago, there was a king.");

        std::cout << boost::replace_first_copy(str, "long", "Long") << std::endl;
        std::cout << boost::erase_tail_copy(str, 8) << std::endl;
    }

    {
        // 分割
        std::string str = "Samus,Link.Zelda::Mario-Luigi+zelda";
        std::deque<std::string> d;
        boost::ifind_all(d, str, "zELDA");  // 分割，大小写无关
        assert(d.size() == 2);
        for (const auto& x : d)
            std::cout << "[" << x << "]";
        std::cout << std::endl;

        // 默认token_compress_off
        std::list<boost::iterator_range<std::string::iterator>> l;
        boost::split(l, str, boost::is_any_of(",.:-+"));        //分隔符是其中任何一个
        for (const auto& x : l)
            std::cout << "[" << x << "]";
        std::cout << std::endl;

        // token_compress_on代表连续出现的分隔符认为是同一个
        l.clear();
        boost::split(l, str, boost::is_any_of(",.:-+"), boost::algorithm::token_compress_on);
        for (const auto& x : l)
            std::cout << "[" << x << "]";
        std::cout << std::endl;
    }

    {
        // 合并
        std::vector<std::string> v = (boost::assign::list_of("Samus"),"Link","Zelda","Mario");
        std::cout << boost::join(v, "+") << std::endl;
        // 含有字母a的才连接起来
        std::cout << boost::join_if(v, "*", [](boost::string_ref s) { return boost::contains(s, "a"); }) << std::endl;
    }

    {
        // 查找迭代器
        std::string str("Samus||samus||Link||Zelda||||Mario");

        // 查找string的find_iterator
        typedef boost::find_iterator<std::string::iterator> string_find_iterator;

        string_find_iterator pos, end;
        for (pos = boost::make_find_iterator(str, boost::first_finder("samus", boost::is_iequal())); pos != end; ++pos)
            std::cout << "[" << *pos << "]";
        std::cout << std::endl;

        // 分割string的find_iterator
        typedef boost::split_iterator<std::string::iterator> string_split_iterator;

        // string_split_iterator spos, send;
        // for (spos = boost::make_split_iterator(str, boost::first_finder("||", boost::is_iequal())); spos != send; ++spos)
        //     std::cout << "[" << *spos << "]";
        // std::cout << std::endl;

        auto spos = boost::make_split_iterator(str, boost::first_finder("||", boost::is_iequal()));
        decltype(spos) send;
        for (; spos != send; ++spos)
            std::cout << "[" << *spos << "]";
        std::cout << std::endl;
    }
}