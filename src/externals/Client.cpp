#include "Client.hpp"
#include <iostream>

namespace yaniv
{
    currency_amount Client::how_much_money_had()
    {
        return this->broker -> how_much_money(this->id);
    }
    void Client::put_money(currency_amount money)
    {
        this-> broker -> add_money(this->id, money);
    }

    void Client::take_money(currency_amount money)
    {
      try
      {
        std::cout << "you took " << this -> broker -> take_money(this->id, money)<< "shekels"<<std::endl;
      }
      catch(...)
      {
        std::cout << "you do not have the money" << std::endl;
      }
    }

    void Client::get_message(const std::string& s)
    {
        std::cout << "a message for client " << this->id << ": " << s << std::endl;
    }

    void Client::buy_in_market(const StockExchangeSymbol& stock_exchange_symbol,CompanySymbol& company_symbol,stock_amount stocks_num, currency_amount total_money)
    {
        // make order
        ExternalOrder order(stocks_num, stock_exchange_symbol,company_symbol, this->id, 0, total_money, std::bind(&Client::get_message, this, std::placeholders::_1));
       // pass the order to stock exchange and it will do the action
        broker->process_buy_market(order);
    }

    void Client::sell_in_market(StockExchangeSymbol& stock_exchange_symbol, CompanySymbol& company_symbol,stock_amount stocks_num)
    {
        // make order
        ExternalOrder order(stocks_num,stock_exchange_symbol, company_symbol, this->id, 0, 0, std::bind(&Client::get_message, this, std::placeholders::_1));
        // pass the order to stock exchange and it will do the action
        this->broker->process_sell_market(order);
    }

    void Client::buy_in_price(StockExchangeSymbol& stock_exchange_symbol, CompanySymbol& company_symbol,stock_amount stocks_num,currency_amount money_per_stock)
    {
        // make order
        ExternalOrder order(stocks_num,stock_exchange_symbol, company_symbol, this->id, money_per_stock, money_per_stock * stocks_num, std::bind(&Client::get_message, this, std::placeholders::_1));
        // pass the order to stock exchange and it will do the action
        this->broker->process_buy_limit(order);
    }

    void Client::sell_in_price(StockExchangeSymbol& stock_exchange_symbol,CompanySymbol& company_symbol, stock_amount stocks_num, currency_amount money_per_stock)
    {
        // make order
        ExternalOrder order(stocks_num,stock_exchange_symbol,company_symbol, this->id, 0, 0, std::bind(&Client::get_message, this, std::placeholders::_1));
        // pass the order to stock exchange and it will do the action
        this->broker->process_sell_limit(order);
    }
}
