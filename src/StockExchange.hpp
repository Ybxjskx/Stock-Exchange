#ifndef STOCK_EXCHANGE_H
#define STOCK_EXCHANGE_H

#include <map>
#include <string>
#include <mutex>
#include "internals/RegisteredUser.hpp"
#include "internals/OrderBook.hpp"

namespace yaniv
{

class StockExchange
{
private:
public:
	// Members
	std::map<CompanySymbol, OrderBook*> book_orders_by_company_symbol;
    std::map<UserId, RegisteredUser*> users;
    inline void check_correct(InternalOrder&  order);

public:
    // Constructors
	StockExchange(StockExchangeSymbol& name): name(name) {}
	// Initialization
	void add_company(CompanySymbol& company_symbol,double price, int amount_stocks);

	
    // Market Actions
	double bid_market(InternalOrder & order);
    int ask_market(InternalOrder & order);
    void bid_in_price(InternalOrder& order);
    void ask_in_price(InternalOrder& order);
	StockExchangeSymbol name;

private:
    void check_correct(ExternalOrder& order);

	// TODO: Add limit buy/sell. Add stop-lose
};

}
#endif
