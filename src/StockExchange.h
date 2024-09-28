#include <map>
#include <string>
#include <mutex>
#include "RegisteredUser"
#include "OrderBook.h"
#include "shortcuts.h"
#ifndef STOCK_EXCHANGE_H
#define STOCK_EXCHANGE_H
namespace yaniv
{

class StockExchange
{
private: 
	// Members
	const std::string name;
	std::map<CompanySymbol, OrderBook> book_orders_by_company_symbol;
    std::map<UserId, *RegisteredUser> users;

public:
    // Constructors
	StockExchange(const std::string& name): name(name) {}

	// Initialization
	void add_company(CompanySymbol& company_symbol, unsigned int amount);
    Client* add_user(UserId& user_id,std::string& name);
	
    // Market Actions
	void bid_market(const ExternalOrder& order);
    void ask_market(const ExternalOrder& order);
    void buy_in_price(const ExternalOrder& order);
    void sale_in_price(const ExternalOrder& order);

private:
    void check_correct(ExternalOrder& order);

	// TODO: Add limit buy/sell. Add stop-lose
};

}
#endif
