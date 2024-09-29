#include "Client.hpp"
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
            std::clog<< "there is a problem wuth adding money to user: " << id << std::endl;  
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
            std::cout<< "there is unexcepted problem" << std::endl;
        }
    }

    void Client::how_much_money_had()
    {
        return this -> stock_exchange.get_money(id);
    }

    void Client::bid_market(CompanySymbol& company_symbol,stock_amount stocks_num, currency_amount total_money)
    {
        ExternalOrder * order = new ExternalOrder(stocks_num, company_symbol, this-> id,0,total_money,std::bind(Client&::got_message,this));
        this -> stock_exchange.bid_market(order);
    }
    Client(unsigned int id, StockExchange& stock_exchange, currency_amount money_per_stock): id(id), stock_exchange(stock_exchange) {}
    
    void Client::ask_market(CompanySymbol& company_symbol,stock_amount stocks_num,currency_amount money_per_stock)
    {
        ExternalOrder * order = new ExternalOrder(stocks_num, company_symbol, this-> id,money_per_stock,0,std::bind(Client&::got_message,this));
        this -> stock_exchange.ask_market(order);
    }

    void Client::buy_in_price(CompanySymbol& company_symbol,stock_amount stocks_num,currency_amount money_per_stock)
    {
        ExternalOrder * order = new ExternalOrder(stocks_num, company_symbol, this-> id,money_per_stock,money_per_stock*stocks_num,std::bind(Client&::got_message,this));
        this -> stock_exchange.buy_in_price(order);
    }

    void Client::sale_in_price(CompanySymbol& company_symbol,stock_amount stocks_num,currency_amount money_per_stock)
    {
        ExternalOrder * order = new ExternalOrder(stocks_num, company_symbol, this-> id,money_per_stock,0,std::bind(Client&::got_message,this));
        this -> stock_exchange.sale_in_price(order);
    }
}
