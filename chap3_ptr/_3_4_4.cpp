#include <iostream>
#include <boost/smart_ptr.hpp>

class Node
{
public:
    ~Node() { std::cout << "deleted" << std::endl; }

    typedef boost::weak_ptr<Node> ptr_type;
    ptr_type next; // 链表-下一个元素
};

int main(int argc, char *argv[])
{
    auto p1 = boost::make_shared<Node>();
    auto p2 = boost::make_shared<Node>();

    assert(p1.use_count() == 1);
    assert(p2.use_count() == 1);

    // 成环
    p1->next = p2;
    p2->next = p1;
}