#include "StockExchange.hpp"
#include "shortcuts.hpp"
#include <string>
#include "internals/Transaction.hpp"

namespace yaniv
{

void StockExchange::add_company(CompanySymbol& company_symbol, stock_amount amount)
{
	if (this->book_orders_by_company_symbol.find(company_symbol) != std::end(this->book_orders_by_company_symbol))
	{
		throw std::invalid_argument("The company " + company_symbol + " is already exists");
	}

	OrderBook company_book_order(amount);
	this->book_orders_by_company_symbol[company_symbol] = company_book_order;// replace with push for 

	// TODO: Add all stocks to comapny
}
void StockExchange::check_correct(const ExternalOrder& order)
{
    if(this->users.find(order.user_id) == std::end(this->users))
	{
		throw std::invalid_argument("The user " + order.user_id + "is not exists");
	}

	if(this->comapnies.find(order.company_symbol) == std::end(this->book_orders_by_company_symbol))
	{
		throw std::invalid_argument("The company " + order.company_symbol + "is not exists");
	}
}
void StockExchange::bid_market(const ExternalOrder& external_order)
{   
	// check input 	
	check_correct(order);

	RegisteredUser * registered_user = this->users[external_order.user_id];
    
	InternalOrder internal_order(external_order, [&](int money_to_add, int stocks)
    {
        registered_user -> add_stocks(stocks, external_order.company_name);
		std::string s = std::format("You buy {} stocks of the company {}, you gave {} money", stocks, external_order.company_symbol,money_to_add); 
		external_order.notify(s);
    }); 

	// check input
	OrderBook* book_order = this->book_orders_by_company_symbol[company_symbol];
	// freeze money
	Transaction transaction = registered_user->start_transaction(order.max_amount_money);
    try
	{
	    //return money
		int money_to_give_back = book_order->bid_market(external_order);
	    transaction.settle(money_to_give_back);
	}
    catch(...)
	{
		transaction.rollback();
	}
}
void StockExchange::ask_market(const ExternalOrder& external_order)
{
	this->check_correct(external_order);

	RegisteredUser* registered_user = this->users[user_id];

	InternalOrder internal_order(external_order, [&](int money_to_add, int stocks_take)
    {
		registered_user -> take_money(money_to_add);
        registered_user -> add_stocks(stocks, company_name);
		std::string s = std::format("You sold {} stocks of the company {}, you got {} money", stocks_take, external_order.company_symbol,money_to_add); 
		external_order.notify(s);
    });

	// check input
	OrderBook * book_order = this->book_orders_by_company_symbol[external_order.company_symbol];
    
	book_order->ask_market(internal_order);
}

void StockExchange::bid_in_price(const ExternalOrder& external_order)
{
	check_correct(external_order);

    InternalOrder internal_order(external_order, [&](int money_to_add, int stocks_take)
    {
        registered_user -> add_stocks(stocks, company_name);
		std::string s = std::format("You buy {} stocks of the company {}, you gave {} money", stocks_take, external_order.company_symbol,money_to_add); 
		external_order.notify(s);
    });
	RegisteredUser * registered_user = this->users[external_order.user_id];

	// check input
	OrderBook * book_order = this->book_orders_by_company_symbol[external_order.company_symbol];
	Transaction transaction = registered_user->start_transaction(internal_order.max_amount_money);
	//it will not work beacuse transaction is depende 
    try
	{
		// freeze money
		book_order -> bid_in_price(internal_order);
	}
    catch(...)
	{
		transaction.rollback();	 
		throw std::exception("error, the function did not work, but every thing is okay, we gave you the money back, please try again later");
	}
}
void StockExchange::ask_in_price(ExternalOrder& external_order)
{
	this->check_correct(external_order);
	
	RegisteredUser * registered_user = this->users[external_order.user_id];

	// check input

	OrderBook* book_order = this->book_orders_by_company_symbol[external_order.company_symbol];
    
	try
	{
		book_order->ask_market(external_order); 
	}
	catch(const std::Exception & e)
	{
		throw e;
	}
	catch(...)
	{
		throw std::exception("unexcepted error");
	}
}
Client * StockExchange::add_user(UserId& user_id)
{
	if(this->users.find(user_id) != std::end(this->users))
	{
		throw std::invalid_argument("The user " + user_id + " is exists");
	}
    RegisteredUser new_user(user_id);
	users[user_id] = new_user;
	return new_user.Client;
}
}