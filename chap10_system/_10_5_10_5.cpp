#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>

void print_vm(const boost::program_options::variables_map &vm)
{
    if(vm.count("filename")){
        std::cout << "filename opt: "  << vm["filename"].as<std::string>() << std::endl;
    }
    if(vm.count("depth")){
        std::cout << "depth opt: "  << vm["depth"].as<int>() << std::endl;
    }
    if(vm.count("dir")){
        std::cout << "dir opt: ";
        for(const auto& str : vm["dir"].as<std::vector<std::string>>())
            std::cout << str << ", ";
        std::cout << std::endl;
    }
}

// 响应文件@file
std::pair<std::string, std::string> my_response_file(const std::string& s)
{
    if(s[0] == '@')
        return std::make_pair("response", s.substr(1));
    else
        return std::pair<std::string, std::string>();   
}

int main(int argc, char* argv[])
{
    {
        /**<支持windows格式 */
        boost::program_options::options_description opts("demo options");

        // 添加参数信息,和assign库赋值一致
        opts.add_options()
            ("help,h", "This is a help info")                                                 // --help 帮助信息
            ("response", boost::program_options::value<std::string>(), "@file")
            ("filename,f", boost::program_options::value<std::string>(), "to find a file")   // --filename,产生一个typed_value类型值，用于选项存储
            ("dir,D", boost::program_options::value<std::vector<std::string>>()->multitoken(), "search dir")
            ("depth,d", boost::program_options::value<int>()->implicit_value(5), "search deep");

        boost::program_options::variables_map vm;       // 选项存储的map容器，类型boost::any，存储不确定类型参数值
        /**<command_line_parser功能更强的参数解析设置类 */
        auto pr = boost::program_options::command_line_parser(argc, argv).options(opts).
                  /**<自定义解析函数 */
                  extra_parser(my_response_file).   // 相应文件@file
                  run();
        boost::program_options::store(pr, vm); // 解析存储

        if(vm.empty() || vm.count("help")) {
            std::cout << opts << std::endl;            /**<只输出帮助栏 */
            return 0;
        }
        if(vm.count("response")){
            std::ifstream ifs(vm["response"].as<std::string>());
            if(!ifs.is_open()){
                std::cout << "can't open file." << std::endl;
            }
            std::stringstream ss;
            ss << ifs.rdbuf();

            std::vector<std::string> args = boost::program_options::split_unix(ss.str(), "\n");     // 注意换行符
            auto pr = boost::program_options::command_line_parser(args).options(opts).run();
            boost::program_options::store(pr, vm); // 解析存储
            if(vm.empty() || vm.count("help")) {
                std::cout << opts << std::endl;            /**<只输出帮助栏 */
                return 0;
            }
            print_vm(vm);
        }

    }
}