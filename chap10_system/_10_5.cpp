#include <iostream>
#include <boost/program_options.hpp>

int main(int argc, char* argv[])
{
    {
        try
        {
            // 需要链接 -lboost_program_options
            boost::program_options::options_description opts("demo options");

            // 添加参数信息
            opts.add_options()
                ("help", "This is a help info")                                                 // --help 帮助信息
                ("filename", boost::program_options::value<std::string>(), "to find a file");   // --filename

            boost::program_options::variables_map vm;       // 选项存储的map容器
            boost::program_options::store(boost::program_options::parse_command_line(argc, argv, opts), vm);    // 解析存储

            // 解析完成，逻辑处理
            if(vm.count("help")){       // --help
                std::cout << opts << std::endl;
                return 0;
            }
            if(vm.count("filename")){   // --filename
                std::cout << "find " << vm["filename"].as<std::string>() << std::endl;
            }
            if(vm.empty()){
                std::cout << "no options" << std::endl;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
}