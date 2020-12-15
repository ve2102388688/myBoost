#ifndef CHAP3_PTR_3_4_3_H_
#define CHAP3_PTR_3_4_3_H_
#include <boost/smart_ptr.hpp>
#include <iostream>

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

#endif