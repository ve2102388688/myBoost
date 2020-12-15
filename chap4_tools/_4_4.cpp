#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <stack>
#include <deque>
#include <boost/assign.hpp>

int main(int argc, char *argv[])
{
    using namespace boost::assign;

    std::vector<int> v;
    v += 1, 2, 3, 4, 5, 6 * 6;

    for (const auto &e : v)
        std::cout << e << " ";
    std::cout << "\n";

    // example 2
    std::set<std::string> s;
    s += "c", "cpp", "h", "hpp";
    for (const auto &e : s)
        std::cout << e << " ";
    std::cout << "\n";

    // example 3
    std::map<int, std::string> m;
    m += std::make_pair(1, "one"), std::make_pair(2, "two");
    for (const auto &e : m)
        std::cout << e.first << ", " << e.second << " ";
    std::cout << "\n";

    {
        // 如果容器有push_back，push_front的化，可以用下面的方式初始化
        std::vector<int> v;
        boost::assign::push_back(v)(1)(2)(3)(4)(5);

        for (const auto &e : v)
            std::cout << e << " ";
        std::cout << "\n";

        // example 2
        std::list<std::string> s;
        boost::assign::push_front(s)("c")("cpp")("h")("hpp");
        for (const auto &e : s)
            std::cout << e << " ";
        std::cout << "\n";

        // 如果容器没有push_back，push_front，如set、map，要用insert
        std::map<int, std::string> m;
        boost::assign::insert(m)(1, "one")(2, "two");
        for (const auto &e : m)
            std::cout << e.first << ", " << e.second << " ";
        std::cout << "\n";
    }

    // list_of
    {
        std::vector<int> v = boost::assign::list_of(1)(2)(3)(4)(5);
        std::deque<std::string> d = (boost::assign::list_of("1"), "2", "3", "4", "5");

        // 等价
        std::map<int, std::string> m = boost::assign::list_of(std::make_pair(1, "one"))(std::make_pair(2, "two"));
        std::map<int, std::string> m1 = boost::assign::pair_list_of(1, "one")(2, "two");
    }

    {
        // 重复输入
        std::vector<int> v = (boost::assign::list_of(1).repeat(3, 2), 3, 4, 5);
        for (const auto &e : v)
            std::cout << e << " ";
        std::cout << "\n";

        std::multiset<int> ms;
        boost::assign::insert(ms).repeat_fun(3, &rand).repeat(3, 1), 10;
        for (const auto &e : ms)
            std::cout << e << " ";
        std::cout << "\n";

        std::deque<int> d;
        push_front(d).range(v.begin(), v.begin() + 3);
        for (const auto &e : d)
            std::cout << e << " ";
        std::cout << "\n";
    }

    {
        // 操作非标准库容器 stack、queue、priority_queue，需要to_adapter()进行转换
        std::stack<int> stk;
        // = (boost::assign::list_of(1), 2, 3).to_adapter();
        stk += 4, 5, 6; // 只有stack支持+=

        std::queue<std::string> q; // = (boost::assign::list_of("1"), "2", "3").repeat(2, "4").to_adapter();
        q += "5";

        std::priority_queue<std::string> pq = (boost::assign::list_of("1"), "2", "3").repeat(2, "4").to_adapter();
        pq += "5";
    }

    {
        // 接受引用参数
        int a = 1, b = 2, c = 3;
        std::vector<int> v = boost::assign::ref_list_of<3>(a)(b)(c);
        assert(v.size() == 3);
    }
}