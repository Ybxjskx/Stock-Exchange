#include <chrono>
#include <thread>
#include <random>
#include <iostream>
#include <vector>

#include "StockExchange.hpp"
#include "Broker.hpp"

#include "shortcuts.hpp"
#include "externals/Client.hpp"
#include "internals/RegisteredUser.hpp"
/*const unsigned int AMOUNT_OF_CLIENTS = 2;
enum ClientActions
{
    PUT_MONEY,
    TAKE_MONEY,
    SALE_IN_MARKET,
    BUY_IN_MARKET,
    SALE_IN_PRICE,
    BUY_IN_PRICE,
    amount_of_actions
};

void client_main(yaniv::Client& client, const std::vector<yaniv::CompanySymbol>& symbols)
{

    // gets 'entropy' from device that generates random numbers itself
    // to seed a mersenne twister (pseudo) random generator
    std::mt19937 generator(std::random_device{}());

    // make sure all numbers have an equal chance. 
    // range is inclusive (so we need -1 for vector index)
    std::uniform_int_distribution<unsigned int> action_distribution(0, amount_of_actions - 1);
    std::uniform_int_distribution<yaniv::stock_amount> stock_amount_distribution(1, 1000);
    std::uniform_int_distribution<yaniv::currency_amount> money_amount_distribution(1, 100000);
    std::uniform_int_distribution<std::size_t> symbols_distribution(0, symbols.size() - 1);

    while (true)
    {
        unsigned int money = take_money_distribution(generator);
        auto symbol = symbols[symbols_distribution(generator)];
        auto owned_amount_stock = client.get_amount_stock(symbol); // TODO: Make this
        unsigned int action = action_distribution(generator);
        switch(action)
        {
        case ClientActions.PUT_MONEY:
            client.put_money(money);
            break;

        case ClientActions.TAKE_MONEY:
            std::uniform_int_distribution<std::size_t> take_money_distribution(1, client.how_much_money_had());
            client.take_money(money);
            break;

        case ClientActions.SALE_IN_MARKET:
            if (owned_amount_stock < 1)
            {
                break;
            }
            std::uniform_int_distribution<unsigned int> amount_to_sell_distribution(1, owned_amount_stock - 1);
            auto amount_to_sell = amount_to_sell_distribution(generator);
            client.sale_in_market(symbol, amount_to_sell);
            break;

        case ClientActions.BUY_IN_MARKET:
            auto amount_stock = stock_amount_distribution(generator);
            client.buy_in_market(symbol, amount_stock, money);
            break;

        case ClientActions.SALE_IN_PRICE:
            if (owned_amount_stock < 1)
            {
                break;
            }
            std::uniform_int_distribution<unsigned int> amount_to_sell_distribution(1, owned_amount_stock - 1);
            auto amount_to_sell = amount_to_sell_distribution(generator);
            auto money_per_stock = money_amount_ditribution(generator);
            client.sale_in_price(symbol, amount_to_sell, money_per_stock);
            break;

        case ClientActions.BUY_IN_PRICE:
            auto amount_stock = stock_amount_distribution(generator);
            auto money_per_stock = money_amount_ditribution(generator);
            client.buy_in_price(symbol, amount_stock, money_per_stock);
            break;

        default:
            std::cout << "Unknown action " << action << std::endl;
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
*/
int main()
{/*
    std::vector<yaniv::CompanySymbol> symbols;
    yaniv::StockExchange stock_exchange("s&p");

    // TODO: Create several Clients with threat for each of them.
    std::vector<std::thread> clients;
    
    for(size_t id = 0; id < AMOUNT_OF_CLIENTS; id++)
    {
        yaniv::Client client(id, stock_exchange);
        std::thread client_thread(client_main, client, symbols);
        clients.push_back(client_thread);
    }

    for(auto client: clients)
    {
        client.join();
    }
 */
    yaniv::Broker * Broker = new yaniv::Broker("Plus500");
    yaniv::StockExchange * stock_exchange = new yaniv::StockExchange("S&P");
    Broker->add_stock_exchange(stock_exchange);

    stock_exchange->add_company("google",10,20);
    yaniv::Client * client1 = Broker->addUser();

    for(auto company:stock_exchange->book_orders_by_company_symbol) {
        std::cout << (company.second)->name<<" ";
    }

    client1->put_money(10000);

    client1->buy_in_market("S&P","google",3,1000);

    yaniv::Client * client2 = Broker->addUser();
    client2->put_money(500);
    client2->buy_in_price("S&P","google",3,100);

    client1->sell_in_market("S&P","google",1);
    return 0;
}
