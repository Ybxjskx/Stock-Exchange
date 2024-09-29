#ifndef REGISTERED_USER_H
#define REGISTERED_USER_H

#include <mutex>
#include <string>
#include "../shortcuts.hpp"
#include "InternalOrder.hpp"
#include "../StockExchange.hpp"

namespace yaniv
{

class RegisteredUser
{
public:
    std::map<CompanySymbol, stock_amount> stocks;// option to hold and have  stocks 
    unsigned int id;
    currency_amount money;
    StockExchange * stock_exchange;
    void add_money(unsigned int money);
    void take_money(unsigned int money);

    RegisteredUser(unsigned int id):id(id), money(0) {}
    void start_transaction(currency_amount freezed);

public:
    currency_amount get_money();
};

}

#endif