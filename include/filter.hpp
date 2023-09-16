#pragma once
#include <algorithm>
#include <ip.hpp>
#include <string>
#include <vector>
#include <range/v3/algorithm/any_of.hpp>

std::string filtIPStr(std::string);

template <typename T>
bool IPSelector(const IP &ip, size_t octet, T t)
{
    if (octet < IP_LENGTH)
    {
        return ip[octet] == t;
    }
    else
    {
        return true;
    }
}

template <typename T, typename... Args>
bool IPSelector(const IP &ip, size_t octet, T t, Args... args)
{
    if (octet < IP_LENGTH)
    {
        return ip[octet] == t && IPSelector(ip, ++octet, args...);
    }
    else
    {
        return true;
    }
}

template <typename T>
bool anyIPSelector(const IP &ip, T t)
{
    return ranges::any_of(ip, [t](auto octet){return octet == t;});
}

template <typename T, typename... Args>
bool anyIPSelector(const IP &ip, T t, Args... args)
{
    auto match = ranges::any_of(ip, [t](auto octet){return octet == t;});
    return match ? true : anyIPSelector(ip, args...);
}

template <typename... Args>
std::vector<IP> filter(const std::vector<IP> &vec, Args... args)
{
    std::vector<IP> selected;
    std::copy_if(vec.cbegin(), vec.cend(), std::back_inserter(selected),
                 [args...](auto ip) { return IPSelector(ip, 0, args...); });
    return selected;
}

template <typename... Args>
std::vector<IP> filterAny(const std::vector<IP> &vec, Args... args)
{
    std::vector<IP> selected;
    std::copy_if(vec.cbegin(), vec.cend(), std::back_inserter(selected),
                 [args...](auto ip) { return anyIPSelector(ip, args...); });
    return selected;
}