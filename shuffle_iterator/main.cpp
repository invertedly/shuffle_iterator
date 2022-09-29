#include <forward_list>
#include <iostream>
#include <unordered_map>

#include "shuffle_range.h"

int main()
{
    int a[] = { 0, 4, 5, 2, 8, 1 };
    std::forward_list< int > b = { 0, 4, 5, 2, 8, 1 };
    std::unordered_map< int, int > c = {
        { 0, 0 }, { 4, 0 }, { 5, 0 }, { 2, 0 }, { 8, 0 }, { 1, 0 }
    };

    auto shuffle_a = shuffle_range(a, a + 6);
    auto shuffle_b = shuffle_range(b.begin(), b.end());
    auto shuffle_c = shuffle_range(c.begin(), c.end());

    for (auto i : shuffle_a)
        std::cout << i << " ";

    std::cout << std::endl << std::endl;

    for (auto i : shuffle_b)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl << std::endl;

    for (auto i : shuffle_c)
        std::cout << i.first << " " << i.second << std::endl;
}
