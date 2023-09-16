#include <algorithm>
#include <filter.hpp>
#include <iostream>
#include <ip.hpp>
#include <vector>
#include <range/v3/algorithm/sort.hpp>
#include <range/v3/algorithm/for_each.hpp>

template <typename Container>
static void printIPs(const Container &cont)
{
    ranges::for_each(cont, [](auto item){std::cout << toString(item) << std::endl;});
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<IP> pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            auto ipStr = filtIPStr(line);
            pool.emplace_back(makeIP(ipStr));
        }

        ranges::sort(pool.begin(), pool.end(), std::greater<IP>());
        // std::sort(pool.begin(), pool.end(), std::greater<IP>());

        printIPs(pool);

        auto filtered1 = filter(pool, 1);
        printIPs(filtered1);

        auto filtered4670 = filter(pool, 46, 70);
        printIPs(filtered4670);

        auto filteredAny46 = filterAny(pool, 46);
        printIPs(filteredAny46);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}