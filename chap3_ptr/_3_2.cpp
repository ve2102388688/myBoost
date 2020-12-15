#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>

using namespace boost;

struct posix_file
{
    posix_file(const char *file_name)
    {
        std::cout << "open file: " << file_name << std::endl;
    }
    ~posix_file()
    {
        std::cout << "close file: " << std::endl;
    }
};

class shared
{
private:
    boost::shared_ptr<int> m_p;

public:
    // 拷贝方式
    shared(boost::shared_ptr<int> p) : m_p(p){};
    ~shared(){};

    void print()
    {
        std::cout << "count: " << m_p.use_count() << " v= " << *m_p << std::endl;
    }
};

// 拷贝方式
void print_fun(boost::shared_ptr<int> p)
{
    std::cout << "count: " << p.use_count() << " v= " << *p << std::endl;
}

int main(int argc, char *argv[])
{
    {
        scoped_ptr<posix_file> fp(new posix_file("../test.cpp"));
    }

    {
        std::unique_ptr<int> up(new int);

        assert(up); // 装换成bool测试是否有效
        *up = 10;
        std::cout << *up << std::endl;

        up.reset();  // 置0
        assert(!up); // up已经空了
    }

    // make_shared()
    {
        auto p = boost::make_shared<int>(10);
    }

    // shared_ptr的基本用法
    {
        shared_ptr<int> sp(new int(10));
        assert(sp.unique()); // sp是唯一的持有者

        shared_ptr<int> sp2 = sp; // 拷贝，同时指向同一个内存int(10)
        assert(sp == sp2 && sp.use_count() == 2 && sp2.use_count() == 2);

        sp.reset();  // 停止使用sp
        assert(!sp); // 停止成功
    }

    // 引用计数问题
    {
        boost::shared_ptr<int> p(new int(100));
        shared s1(p), s2(p);

        s1.print();
        s2.print();

        *p = 20;
        print_fun(p);

        s1.print();
        s2.print();
    }
}
