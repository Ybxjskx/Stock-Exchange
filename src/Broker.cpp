#ifndef BROKER_CPP
#define BROKER_H
#include "Broker.hpp"
#include <stdexcept>
#include "externals/Client.hpp"
#include "shortcuts.hpp"
#include "internals/RegisteredUser.hpp"
#include <random>
#include <format>
#include "internals/Transaction.hpp"
namespace yaniv
{
      Client* Broker::addUser()
    {
      UserId id;
      bool find_open_id = false;
      if(users.size() >= max_size)
      {
          throw std::range_error("Too many users in the broker");
      }
      while(!find_open_id)
      {
          std::random_device rd;  // מחולל מספרים רנדומליים אמיתי (אם קיים במערכת)
          std::mt19937 gen(rd()); // מחולל מספרים מבוסס אלגוריתם Mersenne Twister
          std::uniform_int_distribution<int> distrib(1, max_size);
          id = (UserId) distrib(gen);
          if(users.find(id) == users.end())
          {
            find_open_id = true;
          }
      }
      users[id] = new RegisteredUser(id);
      return new Client(id,this);
    }
    void Broker::check_user(UserId user_id)
    {
        if(users.find(user_id) == std::end(users))
        {
            throw std::invalid_argument("The user does not exists");
        }
    }
    void Broker::check_order(ExternalOrder &external_order)
    {
        if(users.find(external_order.user_id) == std::end(users))
        {
            throw std::invalid_argument("The user does not exists");
        }
        if(stock_exchanges.find(external_order.stock_exchange_symbol) == std::end(stock_exchanges))
        {
          throw std::invalid_argument("The company symbol does not exists");
        }
    }

    void Broker::add_stock_exchange(StockExchange *stock_exchange)
    {
        if(stock_exchange != nullptr && stock_exchanges.find(stock_exchange->name) == stock_exchanges.end())
        {
            stock_exchanges[stock_exchange->name] = stock_exchange;
        }
    }

    void Broker::add_money(UserId id,currency_amount money)
    {
        check_user(id);
        users.find(id)->second->add_money(money);
    }

    int Broker::take_money(UserId id, currency_amount money)
    {
        this->check_user(id);

        return this -> users.find(id)->second->take_money(money);
     }


    int Broker::how_much_money(UserId user_id)
    {
        if(users.find(user_id) == std::end(users))
        {
            throw std::invalid_argument("The user does not exists");
        }
        return users.find(user_id)->second->get_money();
    }


    void Broker::process_buy_market(ExternalOrder &external_order)
    {
        check_order(external_order);
        RegisteredUser * registered_user = this->users[external_order.user_id];

          std::function<void(currency_amount, stock_amount)> notify =
          [&](currency_amount money_taken, stock_amount stocks_take) {
          registered_user->add_stocks(stocks_take, external_order.stock_exchange_symbol, external_order.company_symbol);
          std::string s = std::format("You buy {} stocks of the company {} from the stock exchange {}, you gave {} money",
                                      stocks_take, external_order.company_symbol, external_order.stock_exchange_symbol, money_taken);
          external_order.notify(s);
          };

          InternalOrder internal_order(external_order, notify);
        //it will not work beacuse transaction is depende
        StockExchange * stock_exchange = this->stock_exchanges[external_order.stock_exchange_symbol];

        Transaction * transaction = registered_user->start_transaction(external_order.max_amount_money,0,
        internal_order.stock_exchange_symbol, internal_order.company_symbol);
        try
        {
            currency_amount a = stock_exchange -> bid_market(internal_order);
            // freeze money
            transaction->settleMoney(a);
        }
        catch(...)
        {
            transaction->rollback();
            throw std::runtime_error("error, the function did not work, but every thing is okay, we gave you the money back, please try again later");
        }

    }

    void Broker::process_sell_market(ExternalOrder& external_order)
    {
        check_order(external_order);
        RegisteredUser * registered_user = this->users[external_order.user_id];

        std::function<void(currency_amount, stock_amount)> notify = [&](int money_to_add, int stocks_take){
              registered_user->add_money(money_to_add);
              std::string s = std::format("You sold {} stocks of the company {} from the stock exchange {}, you got {} money", stocks_take, external_order.company_symbol,external_order.stock_exchange_symbol ,money_to_add);
              external_order.notify(s);
        };

        InternalOrder internal_order(external_order,notify);

        StockExchange * stock_exchange = this->stock_exchanges[external_order.stock_exchange_symbol];


        Transaction *transaction = registered_user->start_transaction(0,external_order.stocks_num,external_order.stock_exchange_symbol, external_order.company_symbol);
        try
        {
            // freeze money
            transaction->settleStocks( stock_exchange -> ask_market(internal_order) );
        }
        catch(std::exception & e)
        {
            transaction->rollback();
            throw std::invalid_argument("error, the function did not work, but every thing is okay, we gave you the money back, please try again later");
        }
    }

    void Broker::process_buy_limit(ExternalOrder& external_order)
    {

        check_order(external_order);
        RegisteredUser * registered_user = this->users[external_order.user_id];

        std::function<void(currency_amount, stock_amount)> notify =  [=](currency_amount money_to_add, stock_amount stocks_take)
          {
            registered_user->add_stocks(stocks_take,external_order.stock_exchange_symbol ,external_order.company_symbol);
            std::string s = std::format("You buy {} stocks of the company {} from the stock exchange {}, you gave {} money", stocks_take, external_order.company_symbol,external_order.stock_exchange_symbol,money_to_add);
            external_order.notify(s);
          };


        InternalOrder internal_order(external_order,notify);
        //it will not work beacuse transaction is depende
        StockExchange * stock_exchange = this->stock_exchanges[external_order.stock_exchange_symbol];

        // freeze money

        Transaction *transaction = registered_user->start_transaction(internal_order.max_amount_money,0,internal_order.stock_exchange_symbol, internal_order.company_symbol);
        try
        {
            stock_exchange -> bid_in_price(internal_order);
        }
        catch(...)
        {
            transaction->rollback();
            throw std::runtime_error("error, the function did not work, but every thing is okay, we gave you the money back, please try again later");
        }
    }

    void Broker::process_sell_limit(ExternalOrder& external_order)
    {
        check_order(external_order);
        RegisteredUser * registered_user = this->users[external_order.user_id];

        std::function<void(currency_amount, stock_amount)> notify =[&](currency_amount money_to_add, stock_amount stocks_take)
        {
             registered_user->add_money(money_to_add);
             std::string s = std::format("You sold {} stocks of the company {} from the stock exchange {}, you earned {} money", stocks_take, external_order.company_symbol,external_order.stock_exchange_symbol,money_to_add);
             external_order.notify(s);
        };
          InternalOrder internal_order(external_order,notify);
        //it will not work beacuse transaction is depende
        StockExchange * stock_exchange = this->stock_exchanges[external_order.stock_exchange_symbol];

        // freeze money

        Transaction *transaction = registered_user->start_transaction(0,external_order.stocks_num,external_order.stock_exchange_symbol, external_order.company_symbol);
        try
        {
            stock_exchange -> ask_in_price(internal_order);
        }
        catch(...)
        {
            transaction->rollback();
            throw std::invalid_argument("error, the function did not work, but every thing is okay, we gave you the money back, please try again later");
        }
    }
}
#endif
