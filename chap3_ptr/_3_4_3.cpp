#include <iostream>
#include <boost/smart_ptr.hpp>

template <class T>
class EnableSharedFromThis
{
public:
    boost::shared_ptr<T> shared_from_this();
};

class SelfShared : public EnableSharedFromThis<SelfShared>
{
public:
    SelfShared(int n) : x(n) {}
    int x;
    void print()
    {
        std::cout << "self_shared: " << x << std::endl;
    }
};

int main(int argc, char *argv[])
{
    auto sp = boost::make_shared<SelfShared>(313);
    sp->print();

    auto p = sp->shared_from_this();
    p->x = 1000;
    sp->print();
}