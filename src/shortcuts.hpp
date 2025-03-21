#ifndef SHORTCUTS_H
#define SHORTCUTS_H

#include <queue>
#include <string>

namespace yaniv
{

template<typename t>
using min_heap = std::priority_queue<t, std::vector<t>, std::greater<t>>;

template<typename t>
using max_heap = std::priority_queue<t>;

using currency_amount = double;
using stock_amount = unsigned int;

using StockExchangeSymbol = const std::string;
using CompanySymbol = const std::string;
using UserId = unsigned int;

}
#endif