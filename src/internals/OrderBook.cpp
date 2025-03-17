#include <cmath>
#include "OrderBook.hpp"
#include <iostream>

namespace yaniv
{
    
// Getters

currency_amount OrderBook::get_market_bid()
{
    m.lock();  
    currency_amount market_price = this->bids.top().amount_per_stock;
    m.unlock();
    return market_price;
}

currency_amount OrderBook::get_market_ask()
{
    m.lock();  
    currency_amount market_price = this->asks.top().amount_per_stock;
    m.unlock();
    return market_price;
}

currency_amount OrderBook::get_spread()
{
    return this->get_market_ask() - this->get_market_bid();
}

// Trading functions
double OrderBook::bid_market(InternalOrder& order)
{
    currency_amount money_left = order.max_amount_money;
    stock_amount stock_left = order.amount;
    
    m.lock();  // start the function therefore must lock 

    while( !(this->asks.empty()) && (stock_left > 0) )
    {
        // Get head
        const Position& ask_position = this->asks.top();
        if(ask_position.amount_per_stock > money_left){ break; }
        
        // Calculate amount to bid
        stock_amount max_availe_to_purche = std::floor((double) money_left / ask_position.amount_per_stock);

        stock_amount amount_to_get_from_this_position = std::min(stock_left, ask_position.get_available_amount());

        stock_amount amount_purched = std::min(max_availe_to_purche, amount_to_get_from_this_position);
        currency_amount amount_of_money_used = amount_purched * ask_position.amount_per_stock;

        ask_position.notify(amount_of_money_used,amount_purched); 
    
        if (ask_position.get_available_amount() < 1)
        {
            this->asks.pop();
        }
        
        money_left -= amount_of_money_used;
        stock_left -= amount_to_get_from_this_position;
    }
    m.unlock(); // end the function therefore must unlock 

    order.notify(order.max_amount_money - money_left,order.amount - stock_left);
    return money_left;
}
int OrderBook::ask_market(InternalOrder& order)
{
    currency_amount money_got = 0;
    stock_amount stock_left = order.amount;

    m.lock();   // start the function therefore must lock 
    //std::cout<<1;
    while(!this->bids.empty() && stock_left > 0)
    {
        //std::cout<<2;
        // Get head
        const Position& bid_position = this->bids.top();
        
        // Calculate amount to bid
        //std::cout<<3;
        stock_amount amount_sold_in_this_position =
            std::min(stock_left, bid_position.get_available_amount());
        //std::cout<<4;
        currency_amount amount_got_from_this_bid = amount_sold_in_this_position * bid_position.amount_per_stock;
        //std::cout<<5;
        // notify position
        bid_position.notify(amount_got_from_this_bid,amount_sold_in_this_position);

        //std::cout<<6;
        if (bid_position.get_available_amount() < 1)
        {
            this->bids.pop();
        }

        money_got += amount_got_from_this_bid;
        stock_left -= amount_sold_in_this_position;
    }

    order.notify(money_got, order.amount - stock_left);
    std::cout<<1;
    m.unlock();   // end the function therefore must unlock
    return stock_left;
}
void OrderBook::bid_in_price(InternalOrder& order)
{

    // בתחהלה יש לנסות לקנות מה שאפשרי, אחר כך להכניס את מה שנשאר ל bids     
    
    currency_amount money_left = order.max_amount_money;
    stock_amount stock_left = order.amount;
    double price_per_stock = order.price_per_stock;

    m.lock(); // start the trading therefore must lock

    while(!this->asks.empty() && (stock_left > 0) && (this->asks.top().amount_per_stock > price_per_stock) )
    {
        // Get head
        const Position& ask_position = this->asks.top();
        if(ask_position.amount_per_stock > money_left){ break; }
        
        // Calculate amount to bid
        stock_amount max_availe_to_purche = std::floor((double) money_left / ask_position.amount_per_stock);

        stock_amount amount_to_get_from_this_position =
            std::min(stock_left, ask_position.get_available_amount());

        stock_amount amount_purched = std::min(max_availe_to_purche, amount_to_get_from_this_position);
        currency_amount amount_of_money_used = amount_purched * ask_position.amount_per_stock;

        // notify position
         //  אחרי הקנייה של יש לדווח לצד השני  שנקנה ממנו
        ask_position.notify(amount_of_money_used,amount_purched);
        
        if (ask_position.get_available_amount() < 1)
        {
            this->asks.pop();
        }
        
        money_left -= amount_of_money_used;
        stock_left -= amount_to_get_from_this_position;
    }

    order.notify(order.max_amount_money - money_left,order.amount - stock_left);

    const stock_amount amount_stock = order.amount;
    const currency_amount  amount_money_per_stock = (order.max_amount_money / order.amount);

    Position p(stock_left, amount_money_per_stock, order.notify);

    bids.push(p);

    
    m.unlock(); // end the function therefore must unlock 
}

void OrderBook::ask_in_price(InternalOrder& order)
{
    m.lock();   // start the function therefore must lock 

    // בתחהלה יש לנסות לקנות מה שאפשרי, אחר כך להכניס את מה שנשאר ל bids 
    const currency_amount  amount_money_per_stock = order.price_per_stock;

    currency_amount money_got = 0;
    stock_amount stock_left = order.amount;
    
    while(!this->bids.empty() && stock_left > 0 && (amount_money_per_stock < this->bids.top().amount) )
    {
        // Get head
        const Position& bid_position = this->bids.top();

        // Calculate amount to bid

        stock_amount amount_sold_in_this_position =
            std::min(stock_left, bid_position.get_available_amount());
        
        currency_amount amount_got_from_this_bid = amount_sold_in_this_position * bid_position.amount_per_stock;

        // notify position

	    bid_position.notify(amount_sold_in_this_position, amount_got_from_this_bid);
        
        if(bid_position.get_available_amount() < 1)
        {
            this->bids.pop();
        }

        money_got += amount_got_from_this_bid;
        stock_left -= amount_sold_in_this_position;
    }
    order.notify(money_got,order.amount - stock_left);
 
    Position p(stock_left, amount_money_per_stock, order.notify);

    asks.push(p);
    m.unlock();  // end the function therefore must unlock
}
}