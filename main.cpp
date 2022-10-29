#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "version.h"

using ip_address = std::vector<uint16_t>;

std::vector<std::string> split(const std::string& str, const char d) {
    std::vector<std::string> r;
    auto stop = str.find_first_of(d);
    decltype(stop) start = 0;

    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

ip_address address(const std::vector<std::string>& vec) {
    if (vec.size() != 4)
        return {};

    ip_address r;
    for (const auto& v : vec) 
        r.push_back(std::stoi(v));
    
    return r;
}

void print(const std::vector<ip_address>::const_iterator& beg_it, const std::vector<ip_address>::const_iterator& end_it) {
    for (auto it = beg_it; it != end_it; ++it) {
        const auto& ip = *it;
        std::cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << std::endl;
    }
}

void rl_sort(std::vector<ip_address>& pool) {
    std::sort(pool.begin(), pool.end(), [](const ip_address& lhs, const ip_address& rhs) {
        return std::tie(lhs) > std::tie(rhs);
    });
}

std::vector<ip_address> filter(const std::vector<ip_address>&pool, 
                               const int first, 
                               const int second = -1, 
                               const int third = -1, 
                               const int fourth = -1) {
    std::vector<ip_address> r;
    std::copy_if(pool.begin(), pool.end(), std::back_inserter(r),
        [first, second, third, fourth](const ip_address& ip) {
        if (  (first != -1  && ip[0] != first)
           || (second != -1 && ip[1] != second)
           || (third != -1  && ip[2] != third)
           || (fourth != -1 && ip[3] != fourth))
            return false;

        return true;
    });

    return r;
}

std::vector<ip_address> filter_any(const std::vector<ip_address>& pool, const int value) {
    std::vector<ip_address> r;
    std::copy_if(pool.begin(), pool.end(), std::back_inserter(r), [value](const ip_address& ip) {
        return value == ip[0] || value == ip[1] || value == ip[2] || value == ip[3];
    });

    return r;
}


int main(int, char**) {
    std::cout << "otus-homework-2." << PROJECT_VERSION_PATCH << std::endl;
	
    try {
        std::vector<ip_address> ip_pool;

        for (std::string line; std::getline(std::cin, line);) {
            auto v = split(line, '\t');
            auto ip = address(split(v.at(0), '.'));
            ip_pool.push_back(ip);
        }

        // reverse lexicographically sort
        rl_sort(ip_pool);
        print(ip_pool.cbegin(), ip_pool.cend());

        // filter by first byte and output 
        auto ip = filter(ip_pool, 1);
        print(ip.begin(), ip.end());

        // filter by first and second bytes and output
        ip = filter(ip_pool, 46, 70);
        print(ip.begin(), ip.end());

        // filter by any byte and output
        ip = filter_any(ip_pool, 46);
        print(ip.begin(), ip.end());
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

	return 0;
}
