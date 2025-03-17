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

public:
    std::mutex m;
    std::string name;
    //UserId id_of_the_host; 
	std::map<unsigned int, Position> positions;
	max_heap<Position> asks;// in the future need to change to map, for finding deals, and get max and min by a.begin and a.rend()
	min_heap<Position> bids;
public:
    OrderBook() = default;
    OrderBook(const OrderBook&) = delete;
    OrderBook& operator=(const OrderBook&) = delete;
    OrderBook(std::string name):name(name){}
	// Getters
	currency_amount get_market_bid();
	currency_amount get_market_ask();
	currency_amount get_spread();

	// Trading functions

	double bid_market(InternalOrder& order);
	void bid_in_price(InternalOrder& order);
	int ask_market(InternalOrder& order);
	void ask_in_price(InternalOrder& order);
};
}

#endif