#include <iostream>
#include <vector>
#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/foreach.hpp>

//using namespace boost;

int main(int argc, char *argv[])
{
    // make_shared()
    {
        auto sp = boost::make_shared<std::string>("make_shared");
    }

    {
        auto sp = boost::make_shared<std::string>("make_shared");
        auto sp1 = new std::string("xxxx");
        std::cout << "use_count: " << sp.use_count() << std::endl;
        sp.reset(sp1);
        std::cout << "use_count: " << sp.use_count() << std::endl;
        std::cout << "*sp: " << *sp << std::endl;
    }

    // shared_ptr作为容器的元素
    {
        typedef std::vector<boost::shared_ptr<int>> vs;
        vs v(10);

        int i = 0;
        // Method1
        for (auto pos = v.begin(); pos != v.end(); ++pos)
        {
            (*pos) = boost::make_shared<int>(++i); // 工厂函数进行赋值
            std::cout << **pos << ", ";            // 第一次获取数组中地址，第二次获取值
        }
        // Method2
        for (auto &e : v)
        {
            e = boost::make_shared<int>(++i);
            std::cout << *e << ", ";
        }
        // // Method3
        // BOOST_FOREACH (auto &e, v)
        // {
        //     e = boost::make_shared<int>(++i);
        //     std::cout << *e << ", ";
        // }
        std::cout << std::endl;

        boost::shared_ptr<int> p = v[9];
        *p = 100;
        std::cout << *v[9] << std::endl;
    }
}