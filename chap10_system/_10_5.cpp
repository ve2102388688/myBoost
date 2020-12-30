#include <iostream>
#include <boost/program_options.hpp>
#include <sstream>
#include <fstream>

void print_vm(const boost::program_options::options_description &opts, const boost::program_options::variables_map &vm)
{
    if(vm.empty()){
        std::cout << opts << std::endl;
        return ;
    }
    if(vm.count("help")){       /**<处理help */
        std::cout << opts << std::endl;
    }

    /**<filename总有默认值，总是存在的 */
    std::cout << "find opt: " << vm["filename"].as<std::string>() << std::endl;

    if(vm.count("dir")){
        std::cout << "dir opt: ";
        for(const auto& str : vm["dir"].as<std::vector<std::string>>())
            std::cout << str << ", ";
        std::cout << std::endl;
    }
    if(vm.count("depth")){
        std::cout << "depth opt: "  << vm["depth"].as<int>() << std::endl;
    }
    if(vm.count("uname")){
        std::cout << "$USER: "  << vm["uname"].as<std::string>() << std::endl;
    }
    if(vm.count("home")){
        std::cout << "$HOME: "  << vm["home"].as<std::string>() << std::endl;
    }
}

std::string name_mapper(const std::string& env_name)
{
    static std::map<std::string, std::string> nm = {{"HOME", "home"}, {"USER", "uname"}};
    return nm[env_name];
}

int main(int argc, char* argv[])
{
    // {
    //     // 使用流程
    //     try
    //     {
    //         // 需要链接 -lboost_program_options
    //         boost::program_options::options_description opts("demo options");

    //         // 添加参数信息,和assign库赋值一致
    //         opts.add_options()
    //             ("help", "This is a help info")                                                 // --help 帮助信息
    //             ("filename", boost::program_options::value<std::string>(), "to find a file");   // --filename,产生一个typed_value类型值，用于选项存储

    //         boost::program_options::variables_map vm;       // 选项存储的map容器，类型boost::any，存储不确定类型参数值
    //         boost::program_options::store(boost::program_options::parse_command_line(argc, argv, opts), vm);    // 解析存储

    //         // 解析完成，逻辑处理
    //         if(vm.count("help")){       // --help
    //             std::cout << opts << std::endl;
    //             return 0;
    //         }
    //         if(vm.count("filename")){   // --filename
    //             std::cout << "find " << vm["filename"].as<std::string>() << std::endl;          /**<需要通过as<>()转换 */
    //         }
    //         if(vm.empty()){
    //             std::cout << "no options" << std::endl;
    //         }
    //     }
    //     catch(const std::exception& e)
    //     {
    //         std::cerr << e.what() << '\n';
    //     } 
    // }

    {
        // // 选项描述器
        // boost::program_options::options_description opts("demo options");
        // std::string filename;

        // opts.add_options()
        //     ("help,h", "help message\n\tfllow this rules.")
        //     /**<--filename或者-f, 存储在外部filename，需要用notify更新，并设置默认值test */
        //     ("filename,f", boost::program_options::value<std::string>(&filename)->default_value("test"), "to find a text")
        //     ("dir,D", boost::program_options::value<std::vector<std::string>>()->multitoken(), "search dir")
        //     ("depth,d", boost::program_options::value<int>()->implicit_value(5), "search deep");
        
        // boost::program_options::variables_map vm;

        // // 从文件中读取， 分析器
        // // /**<Method1流输出 */ 
        // // std::stringstream ss;
        // // ss << "filename=a.cpp\ndir=/usr/bin\ndepth=3";
        // // boost::program_options::store(boost::program_options::parse_config_file(ss, opts), vm);

        // // /**<Method2文件输入 */ 
        // // std::ifstream ifs("chap10_system/config.ini");
        // // if(!ifs.is_open()){
        // //     std::cout << "can't find configuration file: config.ini\n";
        // //     return 0;
        // // }
        // // boost::program_options::store(boost::program_options::parse_config_file(ifs, opts, true), vm);

        // /**<Method3文件输入 */ 
        // const char *str = ("chap10_system/config.ini");
        // boost::program_options::store(boost::program_options::parse_config_file<char>(str, opts, true), vm);
        
        // /**<Method3外界输入 */
        // // boost::program_options::store(boost::program_options::parse_command_line(argc, argv, opts), vm);
        // boost::program_options::notify(vm);                                     // 将结果存储在外部变量

        // print_vm(opts, vm);
    }

    {
        // 位置选项值
        boost::program_options::options_description opts("demo options");
        std::string filename;
        opts.add_options()
            ("help,h", "help message\n\tfllow this rules.")
            /**<--filename或者-f, 存储在外部filename，需要用notify更新，并设置默认值test */
            ("filename,f", boost::program_options::value<std::string>(&filename)->default_value("test"), "to find a text")
            ("dir,D", boost::program_options::value<std::vector<std::string>>()->multitoken(), "search dir")
            ("depth,d", boost::program_options::value<int>()->implicit_value(5), "search deep")
            ("home", boost::program_options::value<std::string>(), "home dir")
            ("uname", boost::program_options::value<std::string>(), "user's name");

        boost::program_options::variables_map vm;
        
        boost::program_options::positional_options_description pod;         /**<位置选项 */
        pod.add("filename", 1).add("dir", 2).add("depth", -1);
        auto pr = boost::program_options::command_line_parser(argc, argv).
                                            options(opts).                  /**<选项参数 */
                                            positional(pod).                /**<位置描述*/
                                            run();                          /**<设置完成，开始解析 */
        boost::program_options::store(pr, vm);                              /**<保存解析结果 */
        boost::program_options::store(boost::program_options::parse_environment(opts, name_mapper), vm);      /**<保存解析结果--环境变量 */
        boost::program_options::notify(vm);                                 /**<将结果存储在外部变量 */ 
        print_vm(opts, vm);
    }
}