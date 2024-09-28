#include "Client.h"
#include "RegisteredUser.h"
#include <iostream>

namespace yaniv
{
    void Client::put_money(unsigned int money)
    {
        try
        {
            this -> stock_exchange -> add_money(money,id);
        }
        catch(std::invalid_argument e)
        {
            std::clog<< "there is a problem" << std::endl;  
        }
    }

    void Client::got_message(const std::string& s) const {
        std::cout << "Got a message for client " << id << ": " << s << std::endl;
    }

    void Client::take_money(unsigned int money);
    {
        try
        {
            this -> stock_exchange -> take_money();
        }
        catch(std::exception e)
        {
            std::cout<< "there is problem with the card" << std::endl;  
        }
        catch(...)
        {
            std::cout<< "there is unexcepted problem " << std::endl;
        }
    }

    void Client::how_much_money_had()
    {
        return this -> stock_exchange.get_money();
    }

    void Client::bid_market(CompanySymbol& company_symbol,stock_amount stocks_num, currency_amount total_money)
    {
        this -> stock_exchange.bid_market(company_symbol,stocks_num, total_money);
    }
    Client(unsigned int id, StockExchange& stock_exchange): id(id), stock_exchange(stock_exchange) {}
    
    void Client::ask_market(CompanySymbol& company_symbol,stock_amount stocks_num)
    {
        Order order(stocks_num, company_symbol, id,  {} { this.got_message("example")}); 
        this -> stock_exchange.ask_market(order);
    }

    void Client::buy_in_price(CompanySymbol& company_symbol,stock_amount stocks_num,currency_amount money_per_stock)
    {
        this -> stock_exchange.buy_in_price(company_symbol,stocks_num,money_per_stock);
    }

    void Client::sale_in_price(CompanySymbol& company_symbol,stock_amount stocks_num,currency_amount money_per_stock)
    {
        this -> stock_exchange.sale_in_price(company_symbol,stocks_num,money_per_stock);
    }
}
