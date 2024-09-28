#include <chrono>
#include <thread>

#include "StockExchange.h"
#include "Client.h"

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

void client_main(unsigned int id, const stc::vector<yaniv::CompanySymbol>& symbols)
{
    // gets 'entropy' from device that generates random numbers itself
    // to seed a mersenne twister (pseudo) random generator
    std::mt19937 generator(std::random_device{}());

    // make sure all numbers have an equal chance. 
    // range is inclusive (so we need -1 for vector index)
    std::uniform_int_distribution<unsigned int> action_distribution(0, ClientActions.amount_of_actions - 1);
    std::uniform_int_distribution<yaniv::stock_amount> stock_amount_distribution(1, 1000);
    std::uniform_int_distribution<yaniv::currency_amount> money_amount_distribution(1, 100000);
    std::uniform_int_distribution<std::size_t> symbols_distribution(0, symbols.size() - 1);

    yaniv::Client client(id);
    while (true)
    {
        unsigned int action = action_distribution(generator);
        switch(action)
        {
        case ClientActions.PUT_MONEY:
            unsigned int money = money_amount_distribution(generator);
            client.put_money(money);
            break;

        case ClientActions.TAKE_MONEY:
            std::uniform_int_distribution<std::size_t> take_money_distribution(1, client.get_money());
            unsigned int money = take_money_distribution(generator);
            client.take_money(money);
            break;

        case ClientActions.SALE_IN_MARKET:
            auto symbol = symbols[symbols_distribution(generator)];
            auto owned_amount_stock = client.get_amount_stock(symbol);
            if (owned_amount_stock < 1)
            {
                break;
            }
            std::uniform_int_distribution<unsigned int> amount_to_sell_distribution(1, owned_amount_stock - 1);
            auto amount_to_sell = amount_to_sell_distribution(generator);
            client.sale_in_market(symbol, amount_to_sell);
            break;

        case ClientActions.BUY_IN_MARKET:
            auto symbol = symbols[symbols_distribution(generator)];
            auto amount_stock = stock_amount_distribution(generator);
            client.buy_in_market(symbol, amount_stock);
            break;

        case ClientActions.SALE_IN_PRICE:
            auto symbol = symbols[symbols_distribution(generator)];
            auto owned_amount_stock = client.get_amount_stock(symbol);
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
            auto symbol = symbols[symbols_distribution(generator)];
            auto amount_stock = stock_amount_distribution(generator);
            auto money_per_stock = money_amount_ditribution(generator);
            client.buy_in_price(symbol, stock_amount, total_money);
            break;

        default:
            std::cout << "Unknown action " << action << std::endl;
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    stc::vector<yaniv::CompanySymbol> symbols;
    yaniv::StockExchange stock_exchange("s&p");

    // TODO: Create several Clients with threat for each of them.
    std::vector<std::thread> clients;
    
    for(size_t id = 0; id < AMOUNT_OF_CLIENTS; i++)
    {
        std::thread client(client_main, id, symbols);
        clients.push_back(client);
    }

    for(auto client: clients)
    {
        client.join();
    }

    return 0;
}
