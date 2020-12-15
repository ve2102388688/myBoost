#include <iostream>
#include <boost/smart_ptr.hpp>

int main(int argc, char *argv[])
{
    boost::shared_ptr<int> sp(new int(10));
    assert(sp.use_count() == 1); // sp拥有

    boost::weak_ptr<int> wp(sp);
    assert(wp.use_count() == 1); // sp拥有, wp(旁观者)
    assert(!wp.empty());         // 旁观者非空

    if (!wp.expired()) // 测试计算机是否是0
    {
        boost::shared_ptr<int> sp2 = wp.lock(); // 提升wp到shared_ptr---sp2
        *sp2 = 100;
        assert(sp2.use_count() == 2); // sp 和 sp2拥有
    }

    assert(wp.use_count() == 1); // sp拥有, wp(旁观者)
    sp.reset();                  // (shared_ptr)sp失效
    assert(wp.expired());        // use_count() == 0
    assert(!wp.lock());          // 空指针，本体已经消逝。旁观者跟着消逝
}