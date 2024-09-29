#include "RegisteredUser.hpp"

namespace yaniv
{
    void RegisteredUser::add_money(unsigned int money, unsigned int card_id);
    {
        std::string s = std::to_string(card_id);
        if(s.length() != 16)
        {
            throw std::invalid_argument("Wrong card");
        }
        this -> money += money; 
    }
    void RegisteredUser::start_transaction(currency_amount freezed)
    {
        if(freezed > this -> money)
        {
            throw std::invalid_argument("do not have inafe money");
        }
        
        this -> money -= freezed;
        return Transaction T(freezed,this);
    }
    void RegisteredUser::add_money(unsigned int money);
    {
        /*std::string s = std::to_string(card_id);
        if(s.length() != 16)
        {
            throw std::invalid_argument("Wrong card");
        }*/
        this -> money += money; 
    }
    void RegisteredUser::take_money(unsigned int money);
    {
        /*std::string s = std::to_string(card_id);  if you want this part you have to add card_id
        if(s.length() != 16)
        {
            throw std::invalid_argument("Wrong card");
        }*/
        this -> money -= money; 
    }
    void RegisteredUser::currency_amount get_money()
    {
        return this->money;
    }
    void bid_market(CompanySymbol& company_symbol,stock_amount stocks_num, currency_amount total_money)
    {
        
    } 
    void ask_market(CompanySymbol& company_symbol,stock_amount stocks_num)
    {
        
    }
    void buy_in_price(CompanySymbol& company_symbol,stock_amount stocks_num)
    {
        
    }
    void sale_in_price(CompanySymbol& company_symbol,stock_amount stocks_num)
    {
        
    }
    void add_money(unsigned int additional_money)
    {
        money += additional_money
    }
    void take_money(unsigned int additional_money)
    {
        if(money + additional_money <  0)
        {
            throw std::out_of_range("do not have the needed money");
        }
        money -= additional_money;
    }
    void add_stocks(unsigned int additional_stocks, CompanySymbol company_name)
    {
        stocks[company_name] += additional_money;
    }
    void take_stocks(unsigned int additional_stocks, CompanySymbol company_name)
    {
        if(money + additional_stocks <  0)
        {
            throw std::out_of_range("do not have the needed money");
        }
        stocks[company_name] -= additional_stocks;
    }

}