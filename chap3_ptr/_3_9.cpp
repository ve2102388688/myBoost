#include <iostream>
#include <boost/pool/singleton_pool.hpp>

int main(int argc, char *argv[])
{
    typedef boost::singleton_pool<struct pool_tag, sizeof(int)> sp;

    int *p = (int *)sp::malloc();
    assert(sp::is_from(p));
    sp::release_memory();
    return 0;
}
