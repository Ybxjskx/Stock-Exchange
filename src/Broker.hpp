#ifndef BROKER_HPP
#define BROKER_HPP

#include "StockExchange.hpp"
#include "externals/ExternalOrder.hpp"
#include <string>
#include "externals/Client.hpp"

namespace yaniv
{
    class Client;
    class Broker
    {

    private:
    public:
        int max_size = 100000;
        std::string name;
        std::map<UserId, RegisteredUser*> users;
        std::map<std::string,StockExchange*> stock_exchanges;

    public:
        Broker(std::string Brokername) : name(Brokername) {}
        void add_stock_exchange(StockExchange *stock_exchange);
        Client* addUser();
        void check_user(UserId user_id);
        void check_order(ExternalOrder &external_order);

        int how_much_money(UserId);
        void add_money(UserId, currency_amount);
        int take_money(UserId id, currency_amount money);


        void process_buy_market(ExternalOrder& order);
        void process_sell_market(ExternalOrder& order);
        void process_buy_limit(ExternalOrder& order);
        void process_sell_limit(ExternalOrder& order);
        void add_stock_exchange(std::string &name);

        ~Broker() {
            for (auto& user : users) {
                delete user.second;
            }
            users.clear();

            for (auto& stock_exchange : stock_exchanges) {
                delete stock_exchange.second;
            }
            stock_exchanges.clear();

        }
    };
}

#endif


