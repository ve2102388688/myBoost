#include <iostream>
#include <string>
#include <tuple>
#include <boost/exception/all.hpp>

// 自定义异常类，都需要虚继承，struct默认是public
struct MyException : virtual std::exception, virtual boost::exception {
};

int main(int argc, char *argv[])
{
    {
        // 自定义异常类，都虚继承
        typedef boost::error_info<struct TagErrNo, int> err_no;             // 定义一个标识，第一个参数是一个空类
        typedef boost::error_info<struct TagErrStr, std::string> err_str;

        try
        {
            try
            {
                throw MyException() << err_no(10);  // 传入int,比如10
            }
            catch(const MyException& e)
            {
                std::cerr << *boost::get_error_info<err_no>(e) << '\n';    // 获得之前存储的10
                std::cerr << e.what() << '\n';     // std::exception
                e << err_str("other info");
                throw;
            }
        } catch(const MyException& e) {
            std::cerr <<  *boost::get_error_info<err_str>(e) << '\n';
        }
    }

    {
        // 其他错误信息类
        try
        {
            throw MyException() << boost::errinfo_api_function(__FUNCTION__)    // 函数名字
                                << boost::errinfo_errno(10)
                                << boost::errinfo_at_line(__LINE__)             // 所在行
                                << boost::throw_file(__FILE__);                 // 文件名字
        }
        catch(const std::exception& e)
        {
            std::cerr << *boost::get_error_info<boost::errinfo_api_function>(e) << std::endl;
            std::cerr << *boost::get_error_info<boost::errinfo_errno>(e) << std::endl;
            std::cerr << *boost::get_error_info<boost::errinfo_at_line>(e) << std::endl;
            std::cerr << *boost::get_error_info<boost::throw_file>(e) << std::endl;
        }

        {
            // 自定义信息类
            //DEFINE_ERROR_INFO(int, err_no);
            try
            {
                // throw boost::enable_error_info(std::runtime_error("runtime"))
                //     << boost::errinfo_at_line(__LINE__);
                boost::throw_exception(std::runtime_error("runtime"));
            }
            catch(const boost::exception& e)
            {
                //std::cerr << *boost::get_error_info<boost::errinfo_at_line>(e) << std::endl;
            }
        }
    }

    {
        try
        {
            throw boost::enable_error_info(std::runtime_error("runtime"));
            // BOOST_THROW_EXCEPTION(std::runtime_error("runtime"));
        }
        catch(const boost::exception& e)
        {
            std::cerr << boost::diagnostic_information(e) << std::endl;
            std::cerr << boost::current_exception_diagnostic_information() << std::endl;
        }
        
        typedef boost::tuple<boost::errinfo_api_function, boost::errinfo_errno> err_group;
        try
        {
            throw boost::enable_error_info(std::out_of_range("runtime")) << err_group("syslogd", 874);
        }
        catch(const boost::exception& e)
        {
            std::cerr << boost::diagnostic_information(e) << std::endl;
            std::cerr << boost::current_exception_diagnostic_information() << std::endl;
        }
    }
}