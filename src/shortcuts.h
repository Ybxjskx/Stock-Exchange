#include <queue>
#include <string>

#ifndef SHORTCUTS_H
#define SHORTCUTS_H
namespace yaniv
{

template<typename t>
using min_heap = std::priority_queue<t, std::vector<t>, std::greater<t>>;

template<typename t>
using max_heap = std::priority_queue<t>;

using currency_amount = unsigned int;
using stock_amount = unsigned int;

using CompanySymbol = const std::string;
using UserId = unsigned int;

}
#endif