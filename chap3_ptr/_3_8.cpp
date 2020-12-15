#include <iostream>
#include <boost/pool/object_pool.hpp>

struct Demo
{
    int m_a, m_b, m_c, m_h;

    Demo(int x = 1, int y = 2, int z = 3, int h = 4) : m_a(x), m_b(y), m_c(z), m_h(h) {}
};

int main(int argc, char *argv[])
{
    boost::object_pool<Demo> p;

    // {
    //     // 不推荐 使用方法1，显然这种只能获取元素未初始化的内存
    //     auto p1 = p.malloc();                                 // 元素内存块
    //     assert(p.is_from(p1));                                // p1是否已经分配出去了
    //     assert(p1->m_a != 1 || p1->m_b != 2 || p1->m_c != 3); // raw mem
    // }

    // 推荐 使用方法1，使用construct初始化
    {
        auto p1 = p.construct(4, 5, 6, 7);
        assert(p1->m_a == 4 || p1->m_b == 5 || p1->m_c == 6); // 初始化成功
    }

    // boost::object_pool<std::string> pls;
    // for (int i = 0; i < 10; ++i)
    // {
    //     std::string *ps = pls.construct("hello");
    //     std::cout << ps << " " << *ps << std::endl;
    // }
    return 0;
}

template <typename P, typename... Args>
inline typename P::element_type *cosntruct(P &p, Args &&... args)
{
    typename P::element_type *mem = p.malloc();

    assert(mem != 0);
    // 定位new表达式 placement new expression
    new (mem) typename P::element_type(std::forward<Args>(args)...); // 完美转发
}