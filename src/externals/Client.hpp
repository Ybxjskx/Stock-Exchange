#ifndef CLIENT_H
#define CLIENT_H

#include "../Broker.hpp"
#include "shortcuts.hpp"

namespace yaniv
{
    class Broker;

class Client
{
public:

    UserId id;
    Broker* broker;


    Client(UserId id, Broker * broker): id(id), broker(broker) {}

    currency_amount how_much_money_had();
    void put_money(currency_amount money);
    void take_money(currency_amount money);

    void buy_in_market( StockExchangeSymbol& stock_exchange_symbol, CompanySymbol& company_symbol,stock_amount stocks_num, currency_amount total_money);
    void sell_in_market( StockExchangeSymbol& stock_exchange_symbol, CompanySymbol& company_symbol,stock_amount stocks_num);
    void buy_in_price( StockExchangeSymbol& stock_exchange_symbol, CompanySymbol& company_symbol,stock_amount stocks_num,double money_per_stock);
    void sell_in_price( StockExchangeSymbol& stock_exchange_symbol,  CompanySymbol& company_symbol,stock_amount stocks_num,double money_per_stock);

    void get_message(const std::string &s);


};

}

#endif