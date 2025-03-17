#ifndef REGISTERED_USER_HPP
#define REGISTERED_USER_HPP
#include <mutex>
#include <string>
#include <exception>
#include <map>
#include "../shortcuts.hpp"
#include "InternalOrder.hpp"
#include "Transaction.hpp"

#include <utility>

namespace yaniv
{
    class Transaction;

class RegisteredUser
{
public:
    RegisteredUser(UserId id):id(id), money(0) {}
    RegisteredUser(RegisteredUser * other): id(other -> id), money(other -> money), stocks(other-> stocks){}

    std::map<std::pair<StockExchangeSymbol,CompanySymbol>, stock_amount> stocks;// option to hold and have stocks
    UserId id;
    currency_amount money;

    RegisteredUser(const RegisteredUser&) = default;
    RegisteredUser(RegisteredUser&&) noexcept = default;

    RegisteredUser& operator=(const RegisteredUser&) = default;
    RegisteredUser& operator=(RegisteredUser&&) noexcept = default;

    void add_money(currency_amount money);
    int take_money(currency_amount money);
    // TODO: add_stock
    void add_stocks(stock_amount stock,StockExchangeSymbol stock_exchange_name,  CompanySymbol company_name);
    void take_stocks(stock_amount additional_stocks, StockExchangeSymbol stock_exchange_name, CompanySymbol company_name);
    Transaction* start_transaction(currency_amount freezedMoney,currency_amount freezedStocks,StockExchangeSymbol stockEx, CompanySymbol company_symbol);
    currency_amount get_money();
};
}


#endif