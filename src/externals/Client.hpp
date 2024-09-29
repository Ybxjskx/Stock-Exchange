#ifndef CLIENT_H
#define CLIENT_H

#include "../StockExchange.hpp"

namespace yaniv
{

class Client
{
    // Implement this class with locks.
private:
    const unsigned int id;
    const StockExchange& stock_exchange; // will not be friend

public:
    Client(unsigned int id, StockExchange& stock_exchange): id(id), stock_exchange(stock_exchange) {}

    void got_message(std::string s);
    void put_money(unsigned int money);
    void take_money(unsigned int money);
    void how_much_money_had();
    

   

    void bid_market(CompanySymbol& company_symbol,stock_amount stocks_num, currency_amount total_money);
    void ask_market(CompanySymbol& company_symbol,stock_amount stocks_num);
    void buy_in_price(CompanySymbol& company_symbol,stock_amount stocks_num,currency_amount money_per_stock);
    void sale_in_price(CompanySymbol& company_symbol,stock_amount stocks_num,currency_amount money_per_stock);
};

}

#endif