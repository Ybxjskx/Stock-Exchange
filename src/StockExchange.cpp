#include "StockExchange.h"
#include "shortcuts.h"

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
void StockExchange::check_correct(Order& order)
{
    if(this->users.find(order.user_id) == std::end(this->users))
	{
		throw std::invalid_argument("The user " + user_id + "is not exists");
	}

	if(this->comapnies.find(order -> company_symbol) == std::end(this->book_orders_by_company_symbol))
	{
		throw std::invalid_argument("The company " + company_symbol + "is not exists");
	}
}
void StockExchange::bid_market(Order * order)
{   
	check_correct(order);

	RegisteredUser * registered_user = this->users[user_id];

	// check input
	OrderBook* book_order = this->book_orders_by_company_symbol[company_symbol];
    Order * real_order;
	//it will not work beacuse transaction is depende 
    try
	{
		// freeze money
		Transaction transaction = registered_user->start_transaction(order.max_amount_money);
	    //make order
		real_order = book_order->bid_market(order);
	    transaction.comit(real_order.max_amount_money);
	}
    catch(...)
	{
		transaction.rollback();
	}

//	registered_user -> stocks[];
}
void StockExchange::ask_market(const Order& external_order)
{
	check_correct(order);

	RegisteredUser* registered_user = this->users[user_id];

	Order internal_order = register_user->wrap_external_order(external_order)

	// check input
	OrderBook book_order = this->book_orders_by_company_symbol[company_symbol];
    
	book_order->ask_market(internal_order);
}

Position * StockExchange::buy_in_price(const Order& order)
{
	Order * order = ; 
    
	check_correct(order);

	RegisteredUser * registered_user = this->users[user_id];

	// check input
	OrderBook * book_order = this->book_orders_by_company_symbol[company_symbol];
	Transaction transaction;
	//it will not work beacuse transaction is depende 
    try
	{
		// freeze money
		Transaction transaction = registered_user->start_transaction(order.max_amount_money);
	    //make order
		book_order -> buy_in_price(order);
	}
    catch(...)
	{
		transaction.rollback();	 
		notify("error, the function did not work, please try again later");
	}
}
void StockExchange::sale_in_price(Order& order)
{
    
	check_correct(order);
	try
	{
		check_correct(order);
	}
	catch(const std::exception& e)
	{
		notify(e.what());
	}
	catch(...)
	{
		notify("unexcepted error");
	}
	
	RegisteredUser * registered_user = this->users[order->user_id];

	// check input

	OrderBook* book_order = this->book_orders_by_company_symbol[company_symbol];
    
	try
	{
		book_order->ask_market(order); 
	}
	catch(const std::Exception & e)
	{
		notify(e.what());
	}
	catch(...)
	{
		notify("unexcepted error");
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