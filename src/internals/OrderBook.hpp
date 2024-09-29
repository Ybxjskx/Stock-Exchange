#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <queue>
#include <mutex>
#include <map>
#include "../shortcuts.hpp"
#include "InternalOrder.hpp"
#include "Position.hpp"

namespace yaniv
{

// TODO: Add locks to this class.
class OrderBook
{
private:
    std::mutex m;
public:

	unsigned int amount_of_stocks;
	std::map<unsigned int, Position*> positions; 
	max_heap<Position> asks;
	min_heap<Position> bids;

	// Constructor
	OrderBook(unsigned int amount_of_stocks): amount_of_stocks(amount_of_stocks) {}

	// Getters
	currency_amount get_market_bid();
	currency_amount get_market_ask();
	currency_amount get_spread();

	// Trading functions

	InternalOrder bid_market(const InternalOrder& order);
	InternalOrder bid_in_price(const InternalOrder& order);
	InternalOrder ask_market(const InternalOrder& order);
	InternalOrder ask_in_price(const InternalOrder& order);
};
}

#endif