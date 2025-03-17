#ifndef REGISTERED_USER_CPP
#define REGISTERED_USER_CPP
#include "RegisteredUser.hpp"
#include <stdexcept>
#include "Transaction.hpp"

namespace yaniv
{
    Transaction* RegisteredUser::start_transaction(currency_amount freezedMoney,currency_amount freezedStocks,StockExchangeSymbol stockEx, CompanySymbol company_symbol )
    {
        if(freezedStocks == 0) {
            if(freezedMoney > this->money)
            {
                throw std::invalid_argument("do not have the needed money");
            }
        }
        else
        {
            if(this->stocks.find({stockEx,company_symbol}) == this->stocks.end())
            {
                throw std::invalid_argument("do not have the needed stocks");
            }
            else if( this->stocks[{stockEx,company_symbol}] < freezedStocks)
            {
                throw std::invalid_argument("do not have the needed stocks");
            }
        }

        this->money -= freezedMoney;
        this->stocks[{stockEx,company_symbol}] -= freezedStocks;
        return new Transaction(freezedMoney,freezedStocks,this,stockEx,company_symbol);
    }
    currency_amount RegisteredUser::get_money()
    {
        return this -> money;
    }
    void RegisteredUser::add_money(currency_amount additional_money)
    {
        this->money += additional_money;
    }
    int RegisteredUser::take_money(currency_amount additional_money)
    {
        if(this->money - additional_money <  0)
        {
            throw std::out_of_range("do not have the needed money");
        }
        this->money -= additional_money;
        return additional_money;
    }
    void RegisteredUser::add_stocks(stock_amount additional_stocks,StockExchangeSymbol stock_exchange_name, CompanySymbol company_name)
    {
        std::pair<StockExchangeSymbol,CompanySymbol> name_pair = std::make_pair(stock_exchange_name,company_name);

        auto it = stocks.find(name_pair);
        int current_stocks = stocks.count(name_pair) ? 0 : stocks.at(name_pair);
        this -> stocks[name_pair] = current_stocks + additional_stocks;
    }
    void RegisteredUser::take_stocks(stock_amount additional_stocks,StockExchangeSymbol stock_exchange_name, CompanySymbol company_name)
    {
        std::pair<StockExchangeSymbol,CompanySymbol> name_pair = std::make_pair(stock_exchange_name,company_name);

        if(this->stocks.find(name_pair)  == this->stocks.end())
        {
            throw std::invalid_argument("the company does not exists");
        }
        if(this->stocks.find(name_pair)->second - additional_stocks <  0)
        {
            throw std::out_of_range("do not have the needed money");
        }
        this -> stocks[name_pair] -= additional_stocks;
    }

}
#endif