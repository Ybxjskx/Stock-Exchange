#include <queue>
#include <mutex>
#include <map>
#include "shortcuts.h"
#include "Order.h"




// TODO: Add locks to this class.
class OrderBook
{
private:
    mutex m;
	unsigned int amount_of_stocks;
	std::map<unsigned int, Position*> positions; 
	max_heap<yaniv::Position> asks;
	min_heap<yaniv::Position> bids;

public:
	// Constructor
	OrderBook(unsigned int amount_of_stocks): amount_of_stocks(amount_of_stocks) {}

	// Getters
	currency_amount get_market_bid();
	currency_amount get_market_ask();
	currency_amount get_spread();

	// Trading functions

	Order bid_market(const Order& order);
	Order ask_market(const Order& order);
};