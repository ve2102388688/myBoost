#include <iostream>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>        // 错误异常 system_error

// 自定义错误类别，继承抽象基类boost::system::error_category
class MyCategory : public boost::system::error_category
{
public:
    // 必须重构纯虚函数
    const char * name() const BOOST_NOEXCEPT BOOST_OVERRIDE {
        return "my_category";
    }

    std::string message( int ev ) const BOOST_OVERRIDE {
        std::string msg;
        switch (ev)
        {
        case 0:
            msg = "ok";
            break;
        default:
            msg = "some error";
            break;
        }
        return msg;
    }
};


int main(int argc, char* argv[])
{
    {
        MyCategory my_cat;
        boost::system::error_code ec(10, my_cat);
        std::cout << ec.value()  << " " << ec.message() << std::endl;

        // #define	ECHILD		10	/* No child processes */ error_base.h
        ec = boost::system::error_code(10, boost::system::system_category());
        std::cout << ec.value() << " " << ec.message() << std::endl;
    }

    {
        std::cout << boost::system::system_category().name() << std::endl;

        boost::system::error_code ec;
        ec.assign(3L, boost::system::system_category());
        std::cout << ec.value()  << " " << ec.message() << std::endl;
        auto econdition = ec.default_error_condition();         // 产生和平台的无关的错误代码
        std::cout << econdition.value()  << " " << econdition.message() << std::endl;   // 相同3L，error_code和econdition都有可能不一致
    }

    {
        try
        {
            // 手动抛出一个异常
            throw boost::system::system_error(boost::system::error_code(5, boost::system::system_category()));
        }
        catch(const boost::system::system_error& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}