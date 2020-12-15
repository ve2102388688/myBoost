#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr/intrusive_ref_counter.hpp>

struct count_data
{
    int m_count = 0;
};

// 下面两个函数是内置的，只需要填写计算变量++/--
void intrusive_ptr_add_ref(count_data *p)
{
    ++p->m_count;
}

void intrusive_ptr_release(count_data *p)
{
    if (--p->m_count == 0)
        delete p;
}

// Method2
struct count_data2 : public boost::intrusive_ref_counter<count_data2>
{
    /* data */
};

int main(int argc, char *argv[])
{
    typedef boost::intrusive_ptr<count_data> counted_ptr;

    counted_ptr p(new count_data);
    assert(p);
    assert(p->m_count == 1); // p拥有

    counted_ptr p2(p);
    assert(p->m_count == 2); // 指针拷贝构造，p和p2同时拥有

    counted_ptr weak_p(p.get(), false); // 值为false,相当于weak_ptr，只是一个观察者，不会增加引用计数
    assert(weak_p->m_count == 2);       // p和p2同时拥有,weak_p观察者

    p2.reset(); // 将p2置零
    assert(!p2);
    assert(p->m_count == 1); // p拥有,weak_p观察者

    // Method2
    {
        typedef boost::intrusive_ptr<count_data2> counted_ptr2;

        counted_ptr2 p(new count_data2);
        assert(p);
        assert(p->use_count() == 1); // p拥有,正确析构
    }
}