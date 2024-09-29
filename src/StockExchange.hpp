#ifndef STOCK_EXCHANGE_H
#define STOCK_EXCHANGE_H

#include <map>
#include <string>
#include <mutex>
#include "internals/RegisteredUser.hpp"
#include "internals/OrderBook.hpp"
#include "shortcuts.hpp"
#include "externals/ExternalOrder.hpp"

namespace yaniv
{

class StockExchange
{
private: 
	// Members
	const std::string name;
	std::map<CompanySymbol, OrderBook> book_orders_by_company_symbol;
    std::map<UserId, RegisteredUser> users;

public:
    // Constructors
	StockExchange(const std::string& name): name(name) {}

	// Initialization
	void add_company(CompanySymbol& company_symbol, stock_amount amount);
    Client* add_user(UserId user_id, const std::string& name);
	
    // Market Actions
	void bid_market(const ExternalOrder& order);
    void ask_market(const ExternalOrder& order);
    void bid_in_price(const ExternalOrder& order);
    void ask_in_price(const ExternalOrder& order);

private:
    void check_correct(ExternalOrder& order);

	// TODO: Add limit buy/sell. Add stop-lose
};

}
#endif
