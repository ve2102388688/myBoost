#include <iostream>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>

void print_vm(const boost::program_options::variables_map &vm)
{
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

// 自定义参数分析器，如-cy代表true,-cn代表false
std::pair<std::string, std::string> my_extra_parser(const std::string& s)
{
    if(s.find("-c") == 0){
        if(s.substr(2,1) == "y")
            return std::make_pair("case", std::string("true"));
        else
            return std::make_pair("case", std::string("false"));
    } else {
        return std::pair<std::string, std::string>();
    }
}

int main(int argc, char* argv[])
{
    // {
    //     /**<三个分组 */
    //     /**<分组1 */
    //     boost::program_options::options_description opts1("group 1");
    //     opts1.add_options()
    //         ("help,h", "help message"); 
    //     /**<分组2 */
    //     boost::program_options::options_description opts2("group 2(hide)");
    //     opts2.add_options()
    //         ("filename,f", boost::program_options::value<std::string>(), "to find a string");
    //     /**<分组3 */
    //     boost::program_options::options_description opts3("group 3");
    //     opts3.add_options()
    //         ("dir,D", boost::program_options::value<std::vector<std::string>>()->composing(), "search dir")
    //         ("depth,d", boost::program_options::value<int>(), "search depth");
        
    //     /**<重定义-总和，配置、帮助 */
    //     boost::program_options::options_description opts_all;
    //     opts_all.add(opts1).add(opts2).add(opts3);

    //     boost::program_options::options_description opts_cfg;
    //     opts_cfg.add(opts2).add(opts3);

    //     boost::program_options::options_description opts_showhelp("demo options");
    //     opts_showhelp.add(opts1).add(opts3);

    //     /**<多个store可以一起使用 */
    //     boost::program_options::variables_map vm;
    //     boost::program_options::store(boost::program_options::parse_command_line(argc, argv, opts_all), vm);
    //     boost::program_options::store(boost::program_options::parse_config_file<char>("/home/topeet/myBoost/chap10_system/config.ini", opts_cfg), vm);

    //     if(vm.empty() || vm.count("help")) {
    //         std::cout << opts_showhelp << std::endl;            /**<只输出帮助栏 */
    //         return 0;
    //     }
    //     print_vm(vm);
    // }

    {
        /**<支持windows格式 */
        boost::program_options::options_description opts("demo options");

        // 添加参数信息,和assign库赋值一致
        opts.add_options()
            ("help,h", "This is a help info")                                                 // --help 帮助信息
            ("case", boost::program_options::value<std::string>(), "case switch")
            ("response", boost::program_options::value<std::string>(), "@file")
            ("filename,f", boost::program_options::value<std::string>(), "to find a file");   // --filename,产生一个typed_value类型值，用于选项存储

        boost::program_options::variables_map vm;       // 选项存储的map容器，类型boost::any，存储不确定类型参数值
        /**<command_line_parser功能更强的参数解析设置类 */
        auto pr = boost::program_options::command_line_parser(argc, argv).options(opts).
                  /**<支持未定义参数 */
                  allow_unregistered().
                  /**<自定义解析函数 */
                  extra_parser(my_extra_parser).
                  /**<支持windows的格式 */
                  style(boost::program_options::command_line_style::unix_style | boost::program_options::command_line_style::allow_slash_for_short).
                  run();
        boost::program_options::store(pr, vm); // 解析存储

        if(vm.empty() || vm.count("help")) {
            std::cout << opts << std::endl;            /**<只输出帮助栏 */
            return 0;
        }
        if(vm.count("filename")){
            std::cout << "filename: "  << vm["filename"].as<std::string>() << std::endl;
        }
        if(vm.count("case")){
            std::cout << "case: "  << vm["case"].as<std::string>() << std::endl;
        }

        /**<收集未定义参数并显示 */
        std::vector<std::string> unsed_opts = boost::program_options::collect_unrecognized(pr.options, boost::program_options::include_positional);

        std::cout << "unsed_opts:" << std::endl;
        BOOST_FOREACH(const auto& e, unsed_opts){
            std::cout << e << std::endl;
        }
    }
}