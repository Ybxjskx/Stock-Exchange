#include "StockExchange.cpp"
#include "shortcuts.h"
#include "Order.h"
#include <exception>

namespace yaniv
{
    void RegisteredUser::start_transaction(currency_amount freezed)
    {
        if(freezed > this -> money)
        {
            throw std::invalid_argument("do not have inafe money");
        }
        
        this -> money -= freezed;
        return Transaction T(freezed,this);
    }
    void RegisteredUser::add_money(unsigned int money, unsigned int card_id);
    {
        std::string s = std::to_string(card_id);
        if(s.length() != 16)
        {
            throw std::invalid_argument("Wrong card");
        }
        this -> money += money; 
    }
    void RegisteredUser::take_money(unsigned int money, unsigned int card_id);
    {
        std::string s = std::to_string(card_id);
        if(s.length() != 16)
        {
            throw std::invalid_argument("Wrong card");
        }
        this -> money -= money; 
    }
    void RegisteredUser::currency_amount get_money()
    {
        return this -> money;
    }
    InternalOrder make_order(enum type_of_the_order Type_of_the_order,CompanySymbol& company_symbol,stock_amount stocks_num,int money_total,UserId user_id)
    {
        switch(Type_of_the_order)
        {
            case bid_market:
                return new Order_per_stock(stocks_num,company_symbol,type_of_the_order,user_id,max_prize):
            case buy_in_price:
                return new Order_per_stock(stocks_num,company_symbol,type_of_the_order,user_id,money_total/amount);
            case sale_in_price:
                return new Order_per_stock(stocks_num,company_symbol,type_of_the_order,user_id,money_total/amount);
        }     
        return Order(amount,company_symbol,type_of_the_order,user_id);
    }
    void bid_market(CompanySymbol& company_symbol,stock_amount stocks_num, currency_amount total_money)
    {
        enum type_of_the_order = bid_market;
        Order * O = make_order(bid_market,stocks_num,total_money);
        stockexchange-> bid_market(O);
    } 
    void ask_market(CompanySymbol& company_symbol,stock_amount stocks_num)
    {
        enum type_of_the_order = bid_market;
        Order * O = make_order(bid_market,stocks_num,total_money);
        ask_market(O);
    }
    void buy_in_price(CompanySymbol& company_symbol,stock_amount stocks_num)
    {
        enum type_of_the_order = bid_market;
        Order * O = make_order(bid_market,stocks_num,total_money);
        buy_in_price(O);
    }
    void sale_in_price(CompanySymbol& company_symbol,stock_amount stocks_num)
    {
        enum type_of_the_order = bid_market;
        Order * O = make_order(bid_market,stocks_num,total_money);
        sale_in_price(O);
    }

}