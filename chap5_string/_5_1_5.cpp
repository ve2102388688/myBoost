#include <iostream>
#include <boost/lexical_cast.hpp>

template <typename T>
struct OutAble
{
    // lexical_cast需要支持<<
    friend std::ostream& operator<<(std::ostream& os, const T& r){
        os << typeid(T).name();
        return os;
    }
};

class Demo : public OutAble<Demo>
{
};

int main(int argc, char *argv[])
{
    std::cout << typeid(Demo).name() << std::endl;
}
