#ifndef MYLEXICALCAST_H_
#define MYLEXICALCAST_H_

#include <string>
#include <boost/lexical_cast.hpp>

template<typename T>
T std_lexical_cast(const std::string& s);

template<>
int std_lexical_cast<int>(const std::string& s)         // stoi
{
    return std::stoi(s);
}

template<>
long std_lexical_cast<long>(const std::string& s)        // stol
{
    return std::stol(s);
}

template<>
unsigned long std_lexical_cast<unsigned long>(const std::string& s)        // stoul
{
    return std::stoul(s);
}

template<>
long long std_lexical_cast<long long>(const std::string& s)    // stoll
{
    return std::stoll(s);
}

template<>
unsigned long long std_lexical_cast<unsigned long long>(const std::string& s)    // stoull
{
    return std::stoull(s);
}

template<>
float std_lexical_cast<float>(const std::string& s)     // stof
{
    return std::stof(s);
}

template<>
double std_lexical_cast<double>(const std::string& s)     // stod
{
    return std::stod(s);
}

template<>
long double std_lexical_cast<long double>(const std::string& s)     // stold
{
    return std::stold(s);
}

#endif 