#ifndef MYFILE_OPERATOR_H_
#define MYFILE_OPERATOR_H_
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/xpressive/xpressive_dynamic.hpp>
#include <vector>

/** \brief      find_file  递归查找指定文件
 *  \author     wzk
 *  \copyright  GNU Public License
 *  \version    1.0 
 *  \date       2020-12-28
 * 
 *  \param[in] dir          路径
 *  \param[in] filename     文件名
 *  \return                 成功返回对应的路径，否则返回无效值optional\<path\>
 */
boost::optional<boost::filesystem::path> 
find_file(const boost::filesystem::path& dir, const std::string& filename)
{
    typedef boost::optional<boost::filesystem::path>  result_type;      /**< 定义返回值类型 */ 

    // 目录不存在或者路径不存在，返回无效值
    if(!boost::filesystem::exists(dir) || !boost::filesystem::is_directory(dir))
        return result_type();
    
    boost::filesystem::recursive_directory_iterator end;                /**<生成逾尾迭代器 */ 
    for(boost::filesystem::recursive_directory_iterator pos(dir); pos != end; ++pos){
        if(!boost::filesystem::is_directory(*pos) && pos->path().filename() == filename)
            return result_type(pos->path());
    }

    return result_type();
}


/** \brief      find_files  递归查找指定文件(带通配符)
 *  \author     wzk
 *  \copyright  GNU Public License
 *  \version    1.0 
 *  \date       2020-12-29
 * 
 *  \param[in] dir          路径
 *  \param[in] filename     文件名
 *  \return                 成功返回对应的路径(vector)，否则返回无效值optional\<path\>
 */
std::vector<boost::filesystem::path> 
find_files(const boost::filesystem::path& dir, const std::string& filename)
{
    static boost::xpressive::sregex_compiler rc;                /**<正则表达式 */
    if(!rc[filename].regex_id()) {
        /**<.在正则表达式有特殊含义，需要转换成\.,然而\需要双重转义；同理通配符*其实是.* */
        std::string str = boost::replace_all_copy(boost::replace_all_copy(filename, ".", "\\."), "*", ".*");
        rc[filename] = rc.compile(str);                             /**< 关联一个正则表达式*/
    }

    typedef std::vector<boost::filesystem::path>  result_type;      /**< 定义返回值类型 */
    result_type v;

    boost::filesystem::recursive_directory_iterator end;            /**<生成逾尾迭代器 */ 
    for(boost::filesystem::recursive_directory_iterator pos(dir); pos != end; ++pos){
        if(!boost::filesystem::is_directory(*pos) && boost::xpressive::regex_match(pos->path().filename().string(), rc[filename]))
            v.push_back(pos->path());
    }

    return v;
}


/** \brief      copy_files  递归拷贝指定文件(带通配符)
 *  \author     wzk
 *  \copyright  GNU Public License
 *  \version    1.0 
 *  \date       2020-12-29
 * 
 *  \param[in] from_dir     待拷贝的原始文件夹，不能为空文件夹
 *  \param[in] to_dir       目标文件夹
 *  \param[in] wildcard     可带通配符的匹配字段，默认全匹配
 *  \return                 返回匹配的数目
 */
size_t 
copy_files(const boost::filesystem::path& from_dir, const boost::filesystem::path& to_dir, const std::string& wildcard="*")
{
    if(!boost::filesystem::is_directory(from_dir))
        std::cout << "fisrt arg must be dir.\n";
    
    std::cout << "Prepare for copy, please wait ...\n";

    auto  v = find_files(from_dir, wildcard);
    if(v.empty()){                                                      /**< TODO BUG 源文件不能为空文件夹 */
        std::cout << "0 file copy ...\n";
        return 0;
    }

    std::cout << "Now begin copy files ...\n";
    boost::filesystem::path tmp;

    for(const auto& p : v){
        tmp = to_dir / p.string().substr(from_dir.string().length());   /**<拼接成目标路径 */
        if(!boost::filesystem::exists(tmp.parent_path()))               /**<创建子目录 */
            boost::filesystem::create_directories(tmp.parent_path());
        boost::filesystem::copy_file(p, tmp);                           /**<拷贝文件 */
    }

    std::cout << v.size() << " file copied.\n";
    return v.size();
}

#endif